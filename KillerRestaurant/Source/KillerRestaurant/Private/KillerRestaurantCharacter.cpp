// Copyright Epic Games, Inc. All Rights Reserved.

#include "KillerRestaurantCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "NPCBase.h"
#include "PlayerQuestListWidget.h"
#include "RawSausage.h"
#include "Dough.h"
#include "CookManager.h"
#include "CustomerManager.h"
#include <Kismet/GameplayStatics.h>
#include "GrilledSausage.h"
#include "PicklesBox.h"
#include "OnionsBox.h"
#include "KetchupBox.h"
#include "MustardBox.h"
#include "ServingBell.h"
#include "MyRestaurGameModeBase.h"
#include "Components/WidgetInteractionComponent.h"
#include "Components/WidgetComponent.h"
#include "NPCManager.h"
#include "EngineUtils.h"
#include "NPCDialogueAsset.h"
#include <ItemBase.h>
#include "InventoryWidget.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AKillerRestaurantCharacter

AKillerRestaurantCharacter::AKillerRestaurantCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void AKillerRestaurantCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (playerQuestListUI_bp != nullptr)
	{
		playerQuestListUI = CreateWidget<UPlayerQuestListWidget>(GetWorld(), playerQuestListUI_bp);

		if (playerQuestListUI != nullptr)
		{
			playerQuestListUI->AddToViewport();

			playerQuestListUI->UpdateQuestUI("0", "1");

			// 퀘스트 UI 갱신 테스트
			/*FTimerHandle hdl;
			GetWorldTimerManager().SetTimer(hdl, [&]() {
				playerQuestListUI->UpdateQuestUI("0", "3");
			}, 5, false);*/
		}
	}

	if (inventoryUI_bp)
	{
		inventoryUI = CreateWidget<UInventoryWidget>(GetWorld(), inventoryUI_bp);
		if (inventoryUI)
		{
			// 위젯은 화면에 표시되지 않도록 설정 (초기 상태)
			inventoryUI->AddToViewport();
			inventoryUI->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No inventoryUI"));
		}
	}

	coM = Cast<ACookManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACookManager::StaticClass()));
	cuM = Cast<ACustomerManager>(UGameplayStatics::GetActorOfClass(GetWorld(), ACustomerManager::StaticClass()));

	gm = Cast<AMyRestaurGameModeBase>(GetWorld()->GetAuthGameMode());

	for (TActorIterator<ANPCManager> It(GetWorld()); It; ++It)
	{
		npcM = *It;
	}

}

void AKillerRestaurantCharacter::Tick(float DeltaTime)
{
	

}

//////////////////////////////////////////////////////////////////////////
// Input

void AKillerRestaurantCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKillerRestaurantCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKillerRestaurantCharacter::Look);

		EnhancedInputComponent->BindAction(ia_Interact, ETriggerEvent::Started, this, &AKillerRestaurantCharacter::Interact);

		EnhancedInputComponent->BindAction(ia_LeftClick, ETriggerEvent::Started, this, &AKillerRestaurantCharacter::Click);
		EnhancedInputComponent->BindAction(ia_Shoot, ETriggerEvent::Started, this, &AKillerRestaurantCharacter::Shoot);

		EnhancedInputComponent->BindAction(ia_RightClick, ETriggerEvent::Started, this, &AKillerRestaurantCharacter::PickUpItem);

		EnhancedInputComponent->BindAction(ia_Inventory, ETriggerEvent::Started, this, &AKillerRestaurantCharacter::ToggleInventory);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AKillerRestaurantCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AKillerRestaurantCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AKillerRestaurantCharacter::SetInputBlocked(bool bBlocked)
{
	APlayerController* pc = Cast<APlayerController>(GetController());
	if (pc)
	{
		// 플레이어 시선 및 이동 막기(true) 또는 활성화(false)
		pc->SetIgnoreMoveInput(bBlocked);
		pc->SetIgnoreLookInput(bBlocked);

		// 이거 해줘야 UI 버튼 클릭됨
		pc->bShowMouseCursor = bBlocked;

		// 대화 초기화
		currentDialogueIndex = 0;
	}
}

void AKillerRestaurantCharacter::ButtonClickedTrigger(float DialogueIndex)
{
	if (currentOverlappedNPC && DialogueIndex == 0.2f)	// 0.2로 하면 안 됨
	{
		currentOverlappedNPC->StartInteract();
	}
		
}

void AKillerRestaurantCharacter::Interact()
{
	// 오버랩한 NPC가 존재하고, F키를 눌렀으면
	if (currentOverlappedNPC)
	{
		if (npcM)
		{
			// NPC와 상호작용 시(UI 대화할 경우) 플레이어 시선 및 움직임 block
			SetInputBlocked(true);

			// 처음에 0으로 시작, 이후엔 갱신된 currentDialogueIndex
			SetNPCDialogueEntry(currentDialogueIndex);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No npcManager"));
		}
		
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("currentOverlappedNPC is null"));
	}
}

void AKillerRestaurantCharacter::SetNPCDialogueEntry(float DialogueIndex)
{
	currentDialogueIndex = DialogueIndex;	

	// 오버랩된 NPC이름, 현재 플레이어의 퀘스트 진행도와 일치하는 대사출력
	FNPCDialogueEntry Entry = npcM->GetDialogueEntry(currentOverlappedNPC->SpeakerName, playercurrentQuestID, currentDialogueIndex);

	//UE_LOG(LogTemp, Warning, TEXT("currentOverlappedNPC: %s : %s"), *currentOverlappedNPC->SpeakerName.ToString(), *DialogueText);

	// 대화창 UI 띄우기
	npcM->ShowDialogueUI(Entry);
}

void AKillerRestaurantCharacter::Click()
{
	if (cuM)
	{
		// 영업시간 끝났으면 더 이상 불가
		if (!cuM->bCanPlaying)
			return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No gm"));
	}

	if (!coM)
	{
		UE_LOG(LogTemp, Warning, TEXT("No manager"));
		return;
	}

	FHitResult hitResult;
	APlayerController* PC = GetWorld()->GetFirstPlayerController();	

	if (PC && PC->GetHitResultUnderCursor(ECC_Visibility, false, hitResult))
	{
		FString name = hitResult.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *name);

		AActor* hitActor = hitResult.GetActor();

		UPrimitiveComponent* hitComp = hitResult.GetComponent();

		if (hitActor)
		{
			if (ADough* breadBox = Cast<ADough>(hitActor))
			{
				coM->SpawnBread();
			}
			else if (ARawSausage* sausageBox = Cast<ARawSausage>(hitActor))
			{
				coM->SpawnSausage();
			}
			else if (AGrilledSausage* grilledSausage = Cast<AGrilledSausage>(hitActor))
			{
				// 어떤 화구에 위치한 소세지를 사용했는지 알아야 사용 후 어느 위치에 소세지가 비어있는지 알 수 있기 때문에 스폰했을 때 스폰 위치 인덱스를 전달 
				coM->InsertGrilledSausageToBread(grilledSausage, grilledSausage->curSausageLocIndex);
			}
			else if (APicklesBox* picklesBox = Cast<APicklesBox>(hitActor))
			{
				coM->PlacePickles();
			}
			else if (AOnionsBox* onionsBox = Cast<AOnionsBox>(hitActor))
			{
				coM->PlaceOnions();
			}
			else if (AKetchupBox* ketchupBox = Cast<AKetchupBox>(hitActor))
			{
				coM->PlaceKetchup();
			}
			else if (AMustardBox* mustardBox = Cast<AMustardBox>(hitActor))
			{
				coM->PlaceMustard();
			}
			else if (AServingBell* servingBell = Cast<AServingBell>(hitActor))
			{
				if (hitComp)
				{
					int32 bellNum;
					//UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *hitComp->GetName());

					// hit 된 컴포넌트가 첫번째 벨이라면
					if (hitComp == servingBell->sm_FirstBell)
						bellNum = 0;
					else if (hitComp == servingBell->sm_SecondBell)
						bellNum = 1;
					else
						bellNum = 2;

					coM->FinishMaking(bellNum);
				}

			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("nothing cast"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("hitActor is null"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("pc is null"));
	}
}

void AKillerRestaurantCharacter::Shoot()
{
	FVector start = FollowCamera->GetComponentLocation(); // 총구 위치
	FVector end = start + GetActorForwardVector() * 1000.f; // 사거리

	FHitResult HitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(this); // 자기 자신 무시

	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, start, end,ECC_Visibility, params);
}

void AKillerRestaurantCharacter::PickUpItem()
{
	UE_LOG(LogTemp, Warning, TEXT("RightClcik"));

	FVector Start = FollowCamera->GetComponentLocation(); // 카메라 위치
	FVector End = Start + (FollowCamera->GetForwardVector() * 1000.0f); // 500 유닛 전방

	FHitResult hitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // 자기 자신은 무시

	bool bHit = GetWorld()->LineTraceSingleByChannel(hitResult, Start, End, ECC_Visibility, Params);
	
	if (bHit)
	{
		AItemBase* hitItem = Cast<AItemBase>(hitResult.GetActor());
		if (hitItem)
		{
			UE_LOG(LogTemp, Warning, TEXT("Get Item! : %s"), *hitItem->GetName());

			AddItemToInventory(hitItem->itemData); // 인벤토리에 추가
			hitItem->Destroy(); // 월드에서 제거
		}
		DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 2.0f);
	}
}

void AKillerRestaurantCharacter::ToggleInventory()
{
	if (inventoryUI)
	{
		// i키를 누르면 인벤토리 창 보이거나 숨기기
		if (inventoryUI->IsVisible())
		{
			inventoryUI->SetVisibility(ESlateVisibility::Hidden);
		}
		else
		{
			inventoryUI->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void AKillerRestaurantCharacter::AddItemToInventory(const FItemData& NewItem)
{
	// 기존 아이템 있으면 수량만 추가
	for (FItemData& item : inventory)
	{
		if (item.ItemName == NewItem.ItemName)
		{
			item.ItemAmount += NewItem.ItemAmount;
			UE_LOG(LogTemp, Warning, TEXT("Increase exist Item amount - %s : %d"), *item.ItemName.ToString(), item.ItemAmount);
			return;
		}
	}

	// 없으면 새로 추가
	inventory.Add(NewItem);
	UE_LOG(LogTemp, Warning, TEXT("Add New Item - %s : %d"), *NewItem.ItemName.ToString(), NewItem.ItemAmount);

	// 인벤토리 내부 값들 출력
	for (const FItemData& Item : inventory)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory - %s : %d\n"), *Item.ItemName.ToString(), Item.ItemAmount);
	}

	inventoryUI->UpdateInventory(inventory);
}
