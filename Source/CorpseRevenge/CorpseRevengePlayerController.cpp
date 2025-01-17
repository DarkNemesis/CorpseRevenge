// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "CorpseRevengePlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "CorpseRevengeCharacter.h"
#include "RangedProjectile.h"
#include "Engine/World.h"

ACorpseRevengePlayerController::ACorpseRevengePlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ACorpseRevengePlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void ACorpseRevengePlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ACorpseRevengePlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ACorpseRevengePlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ACorpseRevengePlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ACorpseRevengePlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ACorpseRevengePlayerController::OnResetVR);
}

void ACorpseRevengePlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ACorpseRevengePlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ACorpseRevengeCharacter* MyPawn = Cast<ACorpseRevengeCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ACorpseRevengePlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ACorpseRevengePlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		/*float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		TArray< TEnumAsByte< EObjectTypeQuery > > ObjectTypes;
		ObjectTypes.Add(EObjectTypeQuery::ObjectTypeQuery3);
		FHitResult Hit;
		GetHitResultUnderCursorForObjects(ObjectTypes, true, Hit);

		if (Hit.bBlockingHit)
		{
			if ((Distance > ((ACorpseRevengeCharacter*)MyPawn)->mRange))
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			}
			else if (((ACorpseRevengeCharacter*)MyPawn)->mCanShoot)
			{
				//auto projectile = GetWorld()->SpawnActor<ARangedProjectile>(ARangedProjectile::StaticClass(), MyPawn->GetActorLocation(), FRotator(0,0,0));
				//projectile->SetTarget(Hit.Actor.Get());
				//ShootProjectile.Broadcast(Hit.Actor.Get());
				//((ACorpseRevengeCharacter*)MyPawn)->mCanShoot = false;
				//((ACorpseRevengeCharacter*)MyPawn)->mShootTimer = 3000;
			}
		}
		else if ((Distance > 120.0f)) // We need to issue move command only if far enough in order for walk animation to play correctly
		{
			//auto currentLocation = MyPawn->GetActorLocation();
			//FVector direction = DestLocation - currentLocation;
			//direction.Normalize();
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, direction * 150);
		}*/
	}
}

void ACorpseRevengePlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ACorpseRevengePlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
