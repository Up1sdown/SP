// Fill out your copyright notice in the Description page of Project Settings.


#include "SPProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASPProjectileBase::ASPProjectileBase()
{
	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollisionComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereCollisionComp;

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMoveComp");
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 5000;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("StatickMesh");
	MeshComp->SetupAttachment(RootComponent);

	Damage = 0.0f;
}


void ASPProjectileBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();	
	SphereCollisionComp->OnComponentHit.AddDynamic(this, &ASPProjectileBase::OnActorHit);
}


void ASPProjectileBase::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplyDamage(OtherActor);
	Destroy();
}

void ASPProjectileBase::ApplyDamage(AActor* OtherActor)
{	
	//UE_LOG(LogTemp, Log, TEXT(Owner->GetFName()));
	UGameplayStatics::ApplyDamage(OtherActor, Damage, GetInstigatorController(), GetInstigator(), nullptr);
}

