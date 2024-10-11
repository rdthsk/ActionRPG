// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ActionRPGCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AActionRPGCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Sprint Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Equip Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EquipAction;

	/** Zoom Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ZoomAction;

public:
	AActionRPGCharacter();

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	//Allows the character to begin sprinting
	void Sprint();

	//Allows the character to stop sprinting
	void StopSprinting();

	//Allows the character to equip an item they are close to
	void EquipItem();

	//Heal the character
	UFUNCTION(BlueprintCallable, Category="Health")
	void HealPlayer(float HealAmount);

	//Heal the character's armor
	UFUNCTION(BlueprintCallable, Category="Health")
	void HealArmor(float HealAmount);

	//Damage the character
	UFUNCTION(BlueprintCallable, Category="Health")
	void DamagePlayer(float DamageAmount);

	//Zooms the camera in (aim down sights)
	void ZoomIn();

	//Zooms the camera out (blind-fire)
	void ZoomOut();


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// The amount of health the character currently has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PlayerHealth;

	// The amount of armor the character currently has.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float PlayerArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Items")
	bool bIsOverlappingItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	bool bIsZoomedIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int UpgradePoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int StrengthValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int DexterityValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int IntellectValue;

	bool bHasArmor;
	
	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

