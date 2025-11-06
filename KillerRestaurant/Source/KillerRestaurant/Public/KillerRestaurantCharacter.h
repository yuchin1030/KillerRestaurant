// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ItemBase.h"
#include "KillerRestaurantCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AKillerRestaurantCharacter : public ACharacter
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ia_Interact;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ia_LeftClick;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ia_Shoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ia_Aim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ia_Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ia_Back;

public:
	AKillerRestaurantCharacter();

	UPROPERTY()
	class ANPCBase* currentOverlappedNPC;

	UPROPERTY()
	class AActor* currentOverlappedInteractItem;

	UPROPERTY()
	class UPlayerQuestListWidget* playerQuestListUI;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<UUserWidget> playerQuestListUI_bp;

	UPROPERTY()
	class UInventoryWidget* inventoryUI;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TSubclassOf<UUserWidget> inventoryUI_bp;

	UPROPERTY(EditAnywhere)
	class ACookManager* coM;

	UPROPERTY(EditAnywhere)
	class ACustomerManager* cuM;

	UPROPERTY(EditAnywhere)
	class AMyRestaurGameModeBase* gm;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float playerGold = 0;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	FName playercurrentQuestID = "0_3";

	UPROPERTY(EditAnywhere, Category = "MySettings")
	float playerHP = 100;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UWidgetInteractionComponent* WidgetInteraction;

	class ANPCManager* npcM;

	float currentDialogueIndex = 0;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	TArray<FItemData> inventory;

	bool bKeyF_Charging;
	float keyF_ChargingValue = 0;

	/* --------------------- Weapon ------------------------*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	bool bAiming;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySettings")
	bool bShooting;

	bool bCanShoot = true;
	bool bIsSprint;
	bool bIsDodging;
	bool bIsCrouch;
	bool bIsPrimaryEquip;

	bool CanFire();

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USceneComponent* sceneCompPrimary;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UChildActorComponent* PrimaryChild;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class USceneComponent* sceneCompHandgun;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UChildActorComponent* HandgunChild;

	UPROPERTY(VisibleAnywhere)
	class USkeletalMeshComponent* Weapon;

	UPROPERTY(EditAnywhere, Category = "MySettings")
	class UAnimMontage* ShootMontage;

	/* ------------------------------------------------*/

	// 3층 퀘스트 막힌 길에서 특정 아이템이 인벤토리에 존재하는지 여부
	UFUNCTION()
	bool HasItem(FName requiredItemName);

	UFUNCTION()
	void SetNPCDialogueEntry(float DialogueIndex);

	UFUNCTION()
	void SetInputBlocked(bool bBlocked);

	UFUNCTION()
	void ButtonClickedTrigger(float DialogueIndex);

	UFUNCTION()
	void Interact();

	UFUNCTION()
	void Floor3_ChargeValueBeforeRotate();

	UFUNCTION()
	void Floor3_CompleteChargeValue();

	UFUNCTION()
	void Click();

	UFUNCTION()
	void Floor2_Click();

	UFUNCTION()
	void Shoot(const FInputActionValue& Value);

	UFUNCTION()
	void ShootTriggered();

	UFUNCTION()
	void ShootCompleted();

	UFUNCTION()
	void Back();

	UFUNCTION()
	void PickUpItem();

	UFUNCTION()
	void Aim();

	UFUNCTION()
	void ToggleInventory();

	void AddItemToInventory(const FItemData& itemData);

	UFUNCTION()
	void TakeDamage(float damageAmount);


protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

