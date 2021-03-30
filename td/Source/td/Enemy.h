#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIController.h"
#include "Enemy.generated.h"

UCLASS()
class TD_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	AEnemy();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
		AAIController* AIController = nullptr;

	UPROPERTY(VisibleAnywhere)
		TArray<AActor*> WaypointActors;

	UPROPERTY(VisibleAnywhere)
		AActor* CurrentWaypoint = nullptr;
};
