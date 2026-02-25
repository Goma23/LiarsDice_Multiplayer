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
	}
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
