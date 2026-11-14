

#include "PlayerAnim.h"

#include "TPS_Player.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	// Owner Pawn
	auto pawn = TryGetPawnOwner();
	
	// Casting
	ATPS_Player* me = Cast<ATPS_Player>(pawn);
	if (me == nullptr)
	{
		return;
	}
	
	// Set Speed, Direction, isAir 
	Speed = me->GetVelocity().Dot(me->GetActorForwardVector());
	Direction = me->GetVelocity().Dot(me->GetActorRightVector());
	isAir = me->GetCharacterMovement()->IsFalling();
}
