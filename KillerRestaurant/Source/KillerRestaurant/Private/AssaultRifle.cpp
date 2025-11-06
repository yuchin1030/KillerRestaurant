// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle.h"
#include "WeaponSystem.h"
#include "WeaponData.h"
#include "Sound/SoundBase.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/SoundAttenuation.h"
#include "Sound/SoundConcurrency.h"
#include "NiagaraSystem.h"       
#include <Kismet/KismetMathLibrary.h>
#include "BulletTrace.h"

AAssaultRifle::AAssaultRifle()
{
	PrimaryActorTick.bCanEverTick = true;

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(defaultSceneRoot);
	Muzzle->SetRelativeLocation(FVector(0, 70, 9));
	Muzzle->SetRelativeRotation(FRotator(0, 90, 0));

}

void AAssaultRifle::Fire()
{
	if (!bReloading)
	{
		if (WeaponSystem->FireCheck(WeaponSystem->Weapon_Details.Weapon_AmmoData.AmmoCount))
		{
			UGameplayStatics::PlayWorldCameraShake(GetWorld(), ShakeClass, GetActorLocation(), 0, 500);

			FVector FromCameraStart = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetComponentLocation();
			FVector FromCameraEnd = FromCameraStart + UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetForwardVector() * WeaponData->MaxRange;
			
			FHitResult FromCameraHitResult;
			FCollisionQueryParams C_params;
			C_params.AddIgnoredActor(this);

			bool bCameraHit = GetWorld()->LineTraceSingleByChannel(FromCameraHitResult, FromCameraStart, FromCameraEnd, ECC_Visibility, C_params);
			DrawDebugLine(GetWorld(), FromCameraStart, FromCameraEnd, bCameraHit ? FColor::Green : FColor::Yellow, false, 5.0f, 0, 1.0f);

			if (bCameraHit)
			{
				FHitResult FromMuzzleHitResult;
				FCollisionQueryParams M_params;
				M_params.AddIgnoredActor(this);
				M_params.AddIgnoredActor(WeaponSystem->CharacterRef);

				FVector FromMuzzleStart = weaponMesh->GetSocketLocation("Muzzle");
				FVector FromMuzzleEnd = (FromMuzzleStart - FromMuzzleHitResult.Location) * 500;

				bool bMuzzleHit = GetWorld()->LineTraceSingleByChannel(FromMuzzleHitResult, FromMuzzleStart, FromMuzzleEnd, ECC_Visibility, M_params);

				FireFX();
				FireGun(FromMuzzleHitResult, bMuzzleHit);
			}
			else
			{
				FireFX();
				FireBlankTracer();
			}
		}
		else
		{
			if (WeaponSystem->Weapon_Details.Weapon_AmmoData.MaxAmmo > 0)
			{
				if (bAutoReload)
				{
					// Reload();

				}
			}
			else
			{
				WeaponSystem->EmptyFX(EmptySound);
			}
		}
	}
}

void AAssaultRifle::FireFX()
{
	// Weapon Fire SFX
	WeaponSystem->FireFX(WeaponData->FireSound, weaponMesh->GetSocketLocation("Muzzle"), AttenuationSettings, ConcurrencySettings);

	// Muzzle Effect
	WeaponSystem->MuzzleVFX(niagara, Muzzle);

	// Fire Animations
	WeaponSystem->FireMontage(nullptr, WeaponData->BodyFireMontage);
	weaponMesh->PlayAnimation(WeaponData->WeaponFireMontage, false);
}

void AAssaultRifle::FireBlankTracer()
{
	FVector spawnLoc = weaponMesh->GetSocketLocation("Muzzle");
	FVector loc1 = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetComponentLocation();
	FVector loc2 = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetForwardVector() * 20000;

	FRotator spawnRot = UKismetMathLibrary::MakeRotFromX((loc1 + loc2) - spawnLoc);

	FActorSpawnParameters spawnParams;
	GetWorld()->SpawnActor<ABulletTrace>(BulletTraceClass, spawnLoc, spawnRot, spawnParams);
}

FVector2D AAssaultRifle::RandomPointInCircle(float radius)
{
	float angle = FMath::RandRange(0.f, 360.f);
	float distanceFromCenter = FMath::RandRange(0.f, radius);

	float PointX = distanceFromCenter * FMath::Cos(FMath::DegreesToRadians(angle));
	float PointY = distanceFromCenter * FMath::Sin(FMath::DegreesToRadians(angle));

	return FVector2D(PointX, PointY);

}

void AAssaultRifle::FireGun(const FHitResult& HitResult, bool bReturnHit)
{
	for (int32 i = 1; i <= WeaponData->BurstAmount; i++)
	{
		float radius = FMath::Tan(FMath::DegreesToRadians(WeaponData->BulletSpread)) * 500;

		float pX =  RandomPointInCircle(radius).X;
		float pY = RandomPointInCircle(radius).Y;
		



		FHitResult FireGunHitResult;
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);
		params.AddIgnoredActor(WeaponSystem->CharacterRef);


		FVector start = weaponMesh->GetSocketLocation("Muzzle");
		FVector tempLoc = HitResult.Location 
			+ UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetRightVector() * pX
			+ UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetRootComponent()->GetUpVector() * pY;

		FVector newLoc = start + (start - tempLoc) * -5;
		FVector end = start + newLoc;


		bool bFireGunHit = GetWorld()->LineTraceSingleByChannel(FireGunHitResult, start, end, ECC_Visibility, params);
		DrawDebugLine(GetWorld(), start, end, bFireGunHit ? FColor::Green : FColor::Red, false, 5.0f, 0, 1.0f);

		if (bFireGunHit)
		{
			if (FireGunHitResult.GetComponent()->IsSimulatingPhysics())
			{
				FireGunHitResult.GetComponent()->AddImpulseAtLocation(FireGunHitResult.Normal * -1000, FireGunHitResult.Location);
			}
			
			// ApplyHit
		}
	}
}
