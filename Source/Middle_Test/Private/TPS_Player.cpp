#include "TPS_Player.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

ATPS_Player::ATPS_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	JumpMaxCount = 2;
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tempSkMesh (
		TEXT("/Script/Engine.SkeletalMesh'/Game/Characters/Mannequins/Meshes/SKM_Manny_Simple.SKM_Manny_Simple'"));
	if (tempSkMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tempSkMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0.000000,0.000000,-90.000000));
		GetMesh()->SetRelativeRotation(FRotator(0.000000,-90.000000,0.000000));
	}
	
	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (springArm == nullptr)
		return;
	springArm->SetupAttachment(RootComponent);
	springArm->SetRelativeLocation(FVector(0.000000,80.000000,80.000000));
	springArm->SetRelativeRotation(FRotator(0.000000,0.000000,0.000000));
	
	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (camera == nullptr)
		return;
	camera->SetupAttachment(springArm);
	
	sniperMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SniperMesh"));
	sniperMesh->SetupAttachment(GetMesh());
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempSniperMesh (
		TEXT("/Script/Engine.StaticMesh'/Game/Asset/SniperGun/sniper11.sniper11'"));
	if (tempSniperMesh.Succeeded())
	{
		sniperMesh->SetStaticMesh(tempSniperMesh.Object);
		sniperMesh->SetRelativeLocation(FVector(0.000000,100.000000,150.000000));
		sniperMesh->SetRelativeRotation(FRotator(0.0f,0.0f,0.0f));
		sniperMesh->SetRelativeScale3D(FVector(0.1,0.1,0.1));
	}
}

void ATPS_Player::BeginPlay()
{
	Super::BeginPlay();
	
	crosshairUI = CreateWidget<UUserWidget>(GetWorld(), crosshairUIWidget);
	if (crosshairUI == nullptr)
		return;
	crosshairUI->AddToViewport();
	
	sniperUI = CreateWidget<UUserWidget>(GetWorld(), sniperUIWidget);
	if (crosshairUI == nullptr)
		return;
}

void ATPS_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (timeAcc < timer)
	{
		timeAcc += DeltaTime;
		float t = FMath::Clamp(timeAcc / timer, 0.f, 1.f);
		
		float currentFov = FMath::Lerp(startFov, targetFov, t);
		camera->SetFieldOfView(currentFov);
	}
}

void ATPS_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis(TEXT("Horizontal"), this, &ATPS_Player::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Vertical"), this, &ATPS_Player::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATPS_Player::TurnAtRate);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ATPS_Player::LookUpAtRate);
	
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ATPS_Player::Jump);
	PlayerInputComponent->BindAction(TEXT("Aimming"), IE_Pressed, this, &ATPS_Player::Aimming);
	PlayerInputComponent->BindAction(TEXT("Aimming"), IE_Released, this, &ATPS_Player::Aimming);
	PlayerInputComponent->BindAction(TEXT("Shooting"), IE_Pressed, this, &ATPS_Player::Shooting);
}

void ATPS_Player::MoveForward(float AxisValue)
{
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(direction, AxisValue);
}

void ATPS_Player::MoveRight(float AxisValue)
{
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(direction, AxisValue);
}

void ATPS_Player::TurnAtRate(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ATPS_Player::LookUpAtRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ATPS_Player::Jump()
{
	Super::Jump();
}

void ATPS_Player::Aimming()
{
	isAimming = !isAimming;
	targetFov = isAimming ? 45.f : 90.f;
	
	isAimming ? (sniperUI->AddToViewport(), crosshairUI->RemoveFromParent()) : 
		(crosshairUI->AddToViewport(), sniperUI->RemoveFromParent());
	
	startFov = camera->FieldOfView;
	timeAcc = 0.f;
}

void ATPS_Player::Shooting()
{
	FHitResult hitResult;
	FVector startLocation = camera->GetComponentLocation();
	FVector endLocation = startLocation + camera->GetForwardVector() * 50000.f;
	FCollisionQueryParams collisionParams;
	collisionParams.AddIgnoredActor(this);
	
	bool isHit = 
		GetWorld()->LineTraceSingleByChannel(hitResult, startLocation, endLocation, ECC_Visibility, collisionParams);
	if (isHit)
	{
		if (hitResult.GetComponent()->IsSimulatingPhysics())
		{
			hitResult.GetComponent()->AddImpulseAtLocation(camera->GetForwardVector() * 500000.f, hitResult.Location);
		}
		
		if (explosionEffect != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosionEffect,hitResult.Location);
		}
	}
}

