// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SPCharacter.generated.h"


UCLASS(config=Game)
class ASPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASPCharacter();

	virtual void Tick(float DeltaSeconds) override;

protected:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterMesh, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* CharacterMesh;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USPHealthComp* HealthComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UChildActorComponent* NewWeaponComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CharacterMesh, meta = (AllowPrivateAccess = "true"))
	class USceneComponent* WeaponSocket;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* Cursor;

	UFUNCTION(BlueprintCallable)
	void OnHealthChanged(AActor* InstigatorActor, USPHealthComp* OwningComp, float NewHealth, float Delta);

	



// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
// 	class ASPWeaponBase* CurrentWeapon;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	void StartShooting();	
	void StopShooting();	


	virtual void PostInitializeComponents() override;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:

	UFUNCTION(BlueprintImplementableEvent)
	void OnWeaponChanged();

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeath();

	FORCEINLINE class UChildActorComponent* GetWeaponComp() const { return NewWeaponComp; }

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

