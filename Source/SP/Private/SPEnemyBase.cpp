// Fill out your copyright notice in the Description page of Project Settings.


#include "SPEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SPHealthComp.h"


// Sets default values
ASPEnemyBase::ASPEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
/*	PrimaryActorTick.bCanEverTick = true;*/

	// Enemy slower than Player (600)
	GetCharacterMovement()->MaxWalkSpeed = 300.f;

	CharacterMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CharacterMesh->SetupAttachment(RootComponent);

	HealthComp = CreateDefaultSubobject<USPHealthComp>(TEXT("HealthComp"));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ASPEnemyBase::OnHealthChanged(AActor* InstigatorActor, USPHealthComp* OwningComp, float NewHealth, float Delta)
{
	// Died
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		Destroy();
	}
}

void ASPEnemyBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	// Bind events
	HealthComp->OnHealthChanged.AddDynamic(this, &ASPEnemyBase::OnHealthChanged);
}

// Called every frame
// void ASPEnemyBase::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }

// Called to bind functionality to input
// void ASPEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
// {
// 	Super::SetupPlayerInputComponent(PlayerInputComponent);
// }

