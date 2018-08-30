// Fill out your copyright notice in the Description page of Project Settings.

#include "RangedProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ARangedProjectile::ARangedProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

ARangedProjectile::ARangedProjectile(const FVector & i_SpawnLocation, AActor* i_Target) : m_SpawnLocation(i_SpawnLocation), m_Target(i_Target)
{
	SetActorLocation(i_SpawnLocation, false, nullptr, ETeleportType::TeleportPhysics);
}

// Called when the game starts or when spawned
void ARangedProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARangedProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AActor * ARangedProjectile::GetTarget()
{
	return m_Target;
}

void ARangedProjectile::SetTarget(AActor* i_Target)
{
	m_Target = i_Target;
}

