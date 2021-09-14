#pragma once
#include "stdafx.h"
namespace Offsets {
	typedef struct {
		LPCWSTR Name;
		DWORD& Offset;
	} OFFSET;
	extern uintptr_t fnGetBounds;
	extern uintptr_t nObjectsCount;
	extern uintptr_t uObjects;
	extern uintptr_t fnLineOfSightTo;
	extern uintptr_t fnGetBoneMatrix;
	extern uintptr_t fnGetWeaponStats;
	extern PVOID* uWorld;
	extern PVOID K2_TeleportTo;
	extern PVOID ServerTickSetup;
	extern DWORD OwningGameInstance;
	extern DWORD Levels;
	extern DWORD PersistentLevel;
	extern DWORD AActors;
	extern DWORD LocalPlayers;
	extern DWORD PlayerController;
	extern DWORD ControlRotation;
	extern PVOID SetControlRotation;
	extern DWORD RemoteViewPitch;
	extern PVOID ClientSetRotation;
	extern PVOID SetIgnoreLookInput;
	extern DWORD AcknowledgedPawn;
	extern DWORD PlayerCameraManager;
	extern DWORD PlayerState;
	extern DWORD RelativeLocation;
	extern DWORD ComponentVelocity;
	extern PVOID GetPlayerName;
	extern PVOID SetActorHiddenInGame;
	extern DWORD CustomTimeDilation;
	extern DWORD RootComponent;
	extern DWORD Mesh;
	extern DWORD RelativeLocation;
	extern DWORD ComponentVelocity;
	extern DWORD ComponentToWorld;
	extern DWORD StaticMesh;
	extern DWORD CachedWorldSpaceBounds;
	extern DWORD FortMeatballVehicleConfigsClass;
	extern DWORD BoostMinPushForce;
	extern DWORD BoostTopSpeedForceMultiplier;
	extern DWORD BoostTopSpeedMultiplier;
	extern DWORD LandTopSpeedMultiplier;
	extern DWORD LandPushForceMultiplier;
	extern DWORD BoostSteeringMultiplier;
	extern DWORD LandSteeringMultiplier;
	extern DWORD LandMinSpeedSteeringAngle;
	extern DWORD LandMaxSpeedSteeringAngle;
	extern DWORD bIsDBNO;
	extern DWORD bIsDying;
	extern DWORD CurrentWeapon;
	extern DWORD BoostMinPushForce;
	extern DWORD BoostTopSpeedForceMultiplier;
	extern DWORD BoostTopSpeedMultiplier;
	extern DWORD LandTopSpeedMultiplier;
	extern DWORD LandPushForceMultiplier;
	extern DWORD BoostSteeringMultiplier;
	extern DWORD LandSteeringMultiplier;
	extern DWORD LandMinSpeedSteeringAngle;
	extern DWORD LandMaxSpeedSteeringAngle;
	extern DWORD PrimaryPickupItemEntry;
	extern DWORD ItemDefinition;
	extern DWORD DisplayName;
	extern DWORD Tier;
	extern DWORD TeamIndex;
	extern DWORD SquadID;
	extern DWORD LastFireTime;
	extern DWORD LastFireTimeVerified;
	extern DWORD WeaponData;
	extern DWORD LastFireAbilityTime;
	extern DWORD IsReloading;
	extern DWORD WeaponStatHandle;
	extern DWORD FireStartLoc;
	//Reload
	extern DWORD ReloadTime;
	extern DWORD ReloadScale;
	extern DWORD ChargeDownTime;
	//No Recoil
	extern DWORD RecoilHoriz;
	extern DWORD RecoilVert;
	extern DWORD RecoilDownsightsMultiplier;
	//No Spread
	extern DWORD Spread;
	extern DWORD SpreadDownsights;
	extern DWORD StandingStillSpreadMultiplier;
	extern DWORD AthenaJumpingFallingSpreadMultiplier;
	extern DWORD AthenaCrouchingSpreadMultiplier;
	extern DWORD AthenaSprintingSpreadMultiplier;
	extern DWORD MinSpeedForSpreadMultiplier;
	extern DWORD MaxSpeedForSpreadMultiplier;
	extern DWORD bAlreadySearched;
	extern DWORD bActive;

	BOOLEAN Initialize();
}