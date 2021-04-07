#pragma once

#include "MainGUI.h"
#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "tdGameModeBase.generated.h"

UENUM(BlueprintType)
enum TowerType
{
	Tower_Gun,
	Tower_Splash
};

UCLASS()
class TD_API AtdGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AtdGameModeBase();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void AddEnemyPassed();

	void ClickTile(AActor* Tile);

	UFUNCTION(BlueprintCallable)
		void BuildTower(TowerType type);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<UUserWidget> MainGUIClass;

private:
	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

	UMainGUI* MainGUI = nullptr;

	UPROPERTY()
		UUserWidget* CurrentWidget = nullptr;

	int EnemiesPassed = 0;

	UPROPERTY(VisibleAnywhere)
		AActor* LastClickedTile;
};
