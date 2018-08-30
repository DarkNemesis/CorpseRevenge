// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangedProjectile.generated.h"

class UProjectileMovementComponent;

UCLASS()
class CORPSEREVENGE_API ARangedProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARangedProjectile();

	ARangedProjectile(const FVector & i_SpawnLocation, AActor* i_Target);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	AActor* GetTarget();

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* i_Target);

private:
	//UProjectileMovementComponent * m_ProjectileMovementComponent = nullptr;

	FVector m_SpawnLocation;
	AActor* m_Target = nullptr;

	
	
};
