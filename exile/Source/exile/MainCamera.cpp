#include "MainCamera.h"

AMainCamera::AMainCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void AMainCamera::BeginPlay()
{
	Super::BeginPlay();

}

void AMainCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!m_movementInput.IsZero())
	{
		m_movementInput = m_movementInput.GetSafeNormal() * 1000.0f;
		FVector newLocation = GetActorLocation();
		newLocation += GetActorRightVector() * m_movementInput.X * DeltaTime;
		newLocation += GetActorForwardVector() * m_movementInput.Y * DeltaTime;
		newLocation += GetActorUpVector() * m_movementInput.Z * DeltaTime * m_mouseSensitivity;

		//UE_LOG(LogTemp, Log, TEXT("##### %s"), *m_movementInput.ToString());

		SetActorLocation(newLocation);
		m_movementInput.Z = 0.0f;
	}
}

void AMainCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCamera::moveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCamera::moveRight);
	PlayerInputComponent->BindAction("MoveUp", IE_Released, this, &AMainCamera::moveUp);
	PlayerInputComponent->BindAction("MoveDown", IE_Released, this, &AMainCamera::moveDown);

}

void AMainCamera::moveForward(float Value)
{
	m_movementInput.Y = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AMainCamera::moveRight(float Value)
{
	m_movementInput.X = FMath::Clamp<float>(Value, -1.0f, 1.0f);
}

void AMainCamera::moveUp()
{
	m_movementInput.Z = 1.0f;
}

void AMainCamera::moveDown()
{
	m_movementInput.Z = -1.0;
}