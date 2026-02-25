#include "LiarsDiceGameMode.h"
#include "LiarsDiceGameState.h"
#include "LiarsDicePlayerState.h"

ALiarsDiceGameMode::ALiarsDiceGameMode()
{
	GameStateClass = ALiarsDiceGameState::StaticClass();
	PlayerStateClass = ALiarsDicePlayerState::StaticClass();
	TableRadius = 200.0f; // 기본 반경 설정
}

void ALiarsDiceGameMode::BeginPlay()
{
	Super::BeginPlay();
	SetCurrentGameState(ELiarsDiceGameState::WaitingForPlayers);
}

void ALiarsDiceGameMode::SetCurrentGameState(ELiarsDiceGameState NewState)
{
	if (ALiarsDiceGameState* GS = GetGameState<ALiarsDiceGameState>())
	{
		GS->GameState = NewState;
		UE_LOG(LogTemp, Warning, TEXT("Game State Changed to: %d"), (int32)NewState);

		if (NewState == ELiarsDiceGameState::MiniGame_DetermineOrder)
		{
			MiniGameTiedPlayers = JoinedPlayers; // 초기에는 모든 플레이어가 대상
			// 클라이언트에 미니게임 UI 표시 알림 로직 추가 예정
		}
	}
}

void ALiarsDiceGameMode::ProcessMiniGameResults()
{
	if (MiniGameTiedPlayers.Num() == 0) return;

	int32 MaxRoll = -1;
	TArray<APlayerController*> HighRollers;

	for (APlayerController* PC : MiniGameTiedPlayers)
	{
		if (ALiarsDicePlayerState* PS = PC->GetPlayerState<ALiarsDicePlayerState>())
		{
			if (PS->MiniGameRollValue > MaxRoll)
			{
				MaxRoll = PS->MiniGameRollValue;
				HighRollers.Empty();
				HighRollers.Add(PC);
			}
			else if (PS->MiniGameRollValue == MaxRoll)
			{
				HighRollers.Add(PC);
			}
		}
	}

	if (HighRollers.Num() == 1)
	{
		// 한 명의 승자 확정
		SetOrderAuthority(HighRollers[0]);
	}
	else if (HighRollers.Num() > 1)
	{
		// 동점자끼리 재경기
		MiniGameTiedPlayers = HighRollers;
		UE_LOG(LogTemp, Warning, TEXT("MiniGame Tie! Re-rolling for %d players"), HighRollers.Num());
		// 클라이언트에 재경기 알림 로직 추가 예정
	}
}

void ALiarsDiceGameMode::SetOrderAuthority(APlayerController* Winner)
{
	UE_LOG(LogTemp, Warning, TEXT("MiniGame Winner: %s. Awaiting direction choice."), *Winner->GetName());
	// Winner 클라이언트에 방향 선택 UI(시계/반시계) 활성화 RPC 전송 로직 필요
	
	// 임시로 승자의 인덱스로 CurrentTurnIndex 초기화
	if (ALiarsDiceGameState* GS = GetGameState<ALiarsDiceGameState>())
	{
		GS->CurrentTurnIndex = JoinedPlayers.IndexOfByKey(Winner);
	}
}

void ALiarsDiceGameMode::HandleBet(APlayerController* Player, int32 Quantity, int32 Value)
{
	ALiarsDiceGameState* GS = GetGameState<ALiarsDiceGameState>();
	if (!GS || GS->GameState != ELiarsDiceGameState::BettingRound) return;

	// 현재 턴인 플레이어인지 확인
	int32 PlayerIndex = JoinedPlayers.IndexOfByKey(Player);
	if (PlayerIndex != GS->CurrentTurnIndex) return;

	// 베팅 유효성 검사 (이전 베팅보다 갯수가 무조건 커야 함)
	if (Quantity > GS->CurrentBet.Quantity && Value != 1)
	{
		GS->CurrentBet.Quantity = Quantity;
		GS->CurrentBet.Value = Value;
		GS->CurrentBet.Better = Player->GetPlayerState<APlayerState>();

		UE_LOG(LogTemp, Warning, TEXT("Player %s placed bet: %d of %d"), *Player->GetName(), Quantity, Value);
		
		AdvanceTurn();
	}
}

void ALiarsDiceGameMode::HandleLiar(APlayerController* Player)
{
	ALiarsDiceGameState* GS = GetGameState<ALiarsDiceGameState>();
	if (!GS || GS->GameState != ELiarsDiceGameState::BettingRound) return;

	// 현재 턴인 플레이어인지 확인
	int32 PlayerIndex = JoinedPlayers.IndexOfByKey(Player);
	if (PlayerIndex != GS->CurrentTurnIndex) return;

	UE_LOG(LogTemp, Warning, TEXT("Player %s called LIAR!"), *Player->GetName());
	
	SetCurrentGameState(ELiarsDiceGameState::RevealResults);
	// 결과 확인 로직(주사위 개수 세기) 호출 예정
}

void ALiarsDiceGameMode::AdvanceTurn()
{
	ALiarsDiceGameState* GS = GetGameState<ALiarsDiceGameState>();
	if (!GS || JoinedPlayers.Num() == 0) return;

	// 방향에 따라 다음 플레이어 결정
	if (bClockwise)
	{
		GS->CurrentTurnIndex = (GS->CurrentTurnIndex + 1) % JoinedPlayers.Num();
	}
	else
	{
		GS->CurrentTurnIndex = (GS->CurrentTurnIndex - 1 + JoinedPlayers.Num()) % JoinedPlayers.Num();
	}

	UE_LOG(LogTemp, Warning, TEXT("It's now Player %d's turn"), GS->CurrentTurnIndex);
}

void ALiarsDiceGameMode::Server_SetGameDirection_Implementation(bool bIsClockwise)
{
	bClockwise = bIsClockwise;
	UE_LOG(LogTemp, Warning, TEXT("Game Direction Set: %s"), bIsClockwise ? TEXT("Clockwise") : TEXT("Counter-Clockwise"));
	
	SetCurrentGameState(ELiarsDiceGameState::MixingDice);
	// 본 게임 주사위 섞기 단계로 진입
}

void ALiarsDiceGameMode::CheckAllPlayersReady()
{
	if (JoinedPlayers.Num() >= 2)
	{
		SetCurrentGameState(ELiarsDiceGameState::MiniGame_DetermineOrder);
	}
}

void ALiarsDiceGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (NewPlayer)
	{
		JoinedPlayers.AddUnique(NewPlayer);
		RedistributePlayers();
		CheckAllPlayersReady();
	}
}

void ALiarsDiceGameMode::Logout(AController* Exiting)
{
	if (APlayerController* PC = Cast<APlayerController>(Exiting))
	{
		JoinedPlayers.Remove(PC);
		PlayerSeatMap.Remove(PC);
		RedistributePlayers();
	}

	Super::Logout(Exiting);
}

void ALiarsDiceGameMode::RedistributePlayers()
{
	int32 PlayerCount = JoinedPlayers.Num();
	if (PlayerCount < 1) return;

	TArray<FSeatInfo> Seats = CalculateSeatPositions(PlayerCount);
	PlayerSeatMap.Empty();

	for (int32 i = 0; i < PlayerCount; ++i)
	{
		if (JoinedPlayers.IsValidIndex(i) && Seats.IsValidIndex(i))
		{
			PlayerSeatMap.Add(JoinedPlayers[i], Seats[i]);
			
			// 실제 폰(Character)의 위치를 이동시키는 로직은 폰 생성 이후 추가 예정
			UE_LOG(LogTemp, Warning, TEXT("Assigned Player %d to Location: %s"), i, *Seats[i].Location.ToString());
		}
	}
}

TArray<FSeatInfo> ALiarsDiceGameMode::CalculateSeatPositions(int32 PlayerCount)
{
	TArray<FSeatInfo> Result;
	if (PlayerCount < 2) return Result;

	float AngleStep = 360.0f / PlayerCount;
	
	// 2명일 경우 서로 마주보게 (180도), 3명 이상은 다각형 형태
	for (int32 i = 0; i < PlayerCount; ++i)
	{
		float CurrentAngle = i * AngleStep;
		float AngleRad = FMath::DegreesToRadians(CurrentAngle);

		FSeatInfo NewSeat;
		// X = R * cos(theta), Y = R * sin(theta)
		NewSeat.Location = FVector(FMath::Cos(AngleRad) * TableRadius, FMath::Sin(AngleRad) * TableRadius, 0.0f);
		
		// 테이블 중앙을 바라보게 회전값 계산
		NewSeat.Rotation = (FVector::ZeroVector - NewSeat.Location).Rotation();
		
		Result.Add(NewSeat);
	}

	return Result;
}
