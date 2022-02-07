// Fill out your copyright notice in the Description page of Project Settings.


#include "SPWeaponSpawner.h"
#include "Components/SphereComponent.h"
#include "SPCharacter.h"
#include "SPWeaponBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASPWeaponSpawner::ASPWeaponSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationSpeed = 30.0f;

	FakeRoot = CreateDefaultSubobject<USceneComponent>(TEXT("FakeRoot"));
	RootComponent = FakeRoot;


	SphereCollisionComp = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollisionComp->SetupAttachment(RootComponent);

	WeaponToSpawn = CreateDefaultSubobject<UChildActorComponent>("WeaponToSpawn");
	WeaponToSpawn->SetupAttachment(SphereCollisionComp);
}



// Called when the game starts or when spawned
void ASPWeaponSpawner::BeginPlay()
{
	Super::BeginPlay();
	WeaponToSpawn->CreateChildActor();		
}

void ASPWeaponSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASPCharacter* Character = Cast<ASPCharacter>(OtherActor);
	if (Character)
	{		
		UChildActorComponent* WeaponComp = Character->GetWeaponComp();	
		if ( IsValid(WeaponComp->GetChildActor()))
		{
			Character->GetWeaponComp()->DestroyChildActor();
		}				
		WeaponComp->SetChildActorClass(WeaponToSpawn->GetChildActorClass());		
		WeaponComp->CreateChildActor();
		Character->OnWeaponChanged();
		Destroy();
	}
}

void ASPWeaponSpawner::PostInitializeComponents()
{
	Super::AActor::PostInitializeComponents();
	SphereCollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ASPWeaponSpawner::OnOverlapBegin);
}

// Called every frame
void ASPWeaponSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
	FRotator Rotation = FRotator(0.f, RotationSpeed, 0.f);
	AddActorLocalRotation(Rotation * DeltaTime);
}

