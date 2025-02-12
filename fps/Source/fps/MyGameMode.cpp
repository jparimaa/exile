#include "MyGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy.h"
#include "MainPlayer.h"
#include "EngineUtils.h"

AMyGameMode::AMyGameMode()
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;
	LastSpawnTime = std::chrono::system_clock::now();
}

void AMyGameMode::BeginPlay()
{
	if (!EnemyClass) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("EnemyClass not set!"));
		PrimaryActorTick.bStartWithTickEnabled = false;
		PrimaryActorTick.bCanEverTick = false;
	}

	ChangeMenuWidget(nullptr);
}

void AMyGameMode::Tick(float DeltaTime)
{
	if (IsGameOver) {
		return;
	}

	const auto Now = std::chrono::system_clock::now();
	if ((Now - LastSpawnTime) > std::chrono::seconds(3))
	{
		LastSpawnTime = Now;
		TArray<AActor*> FoundActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), FoundActors);
		const AActor* ChosenActor = FoundActors[rand() % FoundActors.Num()];

		const FTransform Transform(ChosenActor->GetActorLocation());
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		GetWorld()->SpawnActor(EnemyClass.Get(), &Transform, SpawnParameters);
	}
}

void AMyGameMode::GameOver()
{
	IsGameOver = true;
	int i = 0;
	for (TActorIterator<AEnemy> iter(GetWorld()); iter; ++iter)
	{
		iter->StopMovement(i);
		++i;
	}
	for (TActorIterator<AMainPlayer> iter(GetWorld()); iter; ++iter)
	{
		iter->DisableControls();
	}

	ChangeMenuWidget(RestartWidgetClass);
}

void AMyGameMode::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidget)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}
	if (NewWidget != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidget);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}