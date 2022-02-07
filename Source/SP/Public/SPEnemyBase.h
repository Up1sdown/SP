// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPEnemyBase.generated.h"

UCLASS()
class SP_API ASPEnemyBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASPEnemyBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "-CharacterMesh")
	class UStaticMeshComponent* CharacterMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "-Components")
	class USPHealthComp* HealthComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "-Components")
	float Damage;

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USPHealthComp* OwningComp, float NewHealth, float Delta);

	// Called when the game starts or when spawned
/*	virtual void BeginPlay() override;*/

	virtual void PostInitializeComponents() override;

public:	
// 	// Called every frame
// 	virtual void Tick(float DeltaTime) override;
// 
// 	// Called to bind functionality to input
// 	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
