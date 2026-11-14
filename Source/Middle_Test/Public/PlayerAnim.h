#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnim.generated.h"

UCLASS()
class MIDDLE_TEST_API UPlayerAnim : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PlayerAnimation")
	float Speed;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PlayerAnimation")
	float Direction;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="PlayerAnimation")
	bool isAir = false;
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
