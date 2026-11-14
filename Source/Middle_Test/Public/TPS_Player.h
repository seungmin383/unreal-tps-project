#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TPS_Player.generated.h"

UCLASS()
class MIDDLE_TEST_API ATPS_Player : public ACharacter
{
	GENERATED_BODY()

public:
	ATPS_Player();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* springArm = nullptr;
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* camera = nullptr;
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* sniperMesh = nullptr;
	
	UPROPERTY(EditAnywhere, Category=Effect)
	class UParticleSystem* explosionEffect;
	
	UPROPERTY(EditAnywhere, Category=UI)
	TSubclassOf<class UUserWidget> crosshairUIWidget;
	UPROPERTY()
	UUserWidget* crosshairUI = nullptr;
	
	UPROPERTY(EditAnywhere, Category=UI)
    TSubclassOf<class UUserWidget> sniperUIWidget;
    UPROPERTY()
    UUserWidget* sniperUI = nullptr;
	
	bool isAimming = false;
	float startFov = 90.f;
	float targetFov = 90.f;
	float timeAcc = 0.f;
	float timer = 0.15f;
	
public:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void TurnAtRate(float AxisValue);
	void LookUpAtRate(float AxisValue);
	
	void Jump();
	void Aimming();
	void Shooting();
};
