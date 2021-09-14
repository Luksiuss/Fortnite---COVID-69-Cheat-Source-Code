#pragma once
#include "includes.h"

bool InitD3DHook()
{
	uint64_t uworld_address = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"), skCrypt_("48 8B 1D ? ? ? ? 48 85 DB 74 3B")));

	uworld_address = reinterpret_cast<uintptr_t>(RELATIVE_ADDR(uworld_address, 7));

	auto uobject_address = Utilities::FindPattern(skCrypt("\x48\x8B\x05\x7E\x38\x79\x05\x4C\x8D\x34\xCD"), skCrypt("xxx????xxxx"));
	if (!uobject_address)
	{
		Warn(skCrypt("Uobject failed"));
		return FALSE;
	}

	objects = reinterpret_cast<decltype(objects)>(RELATIVE_ADDR(uobject_address, 7));

	OFFSET_UWORLD = uworld_address;

	OFFSET_GETOBJECTNAMES = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"), skCrypt_("40 53 48 83 EC 20 48 8B D9 48 85 D2 75 45 33 C0 48 89 01 48 89 41 08 8D 50 05 E8 ? ? ? ? 8B 53 08 8D 42 05 89 43 08 3B 43 0C 7E 08 48 8B CB E8 ? ? ? ? 48 8B 0B 48 8D 15 ? ? ? ? 41 B8 ? ? ? ? E8 ? ? ? ? 48 8B C3 48 83 C4 20 5B C3 48 8B 42 18")));
	OFFSET_GETNAMEBYINDEX = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"), skCrypt_("48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC 30 8B")));
	OFFSET_FNFREE = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"), skCrypt_("48 85 C9 74 2E 53 48 83 EC 20 48 8B D9 48 8B 0D ? ? ? ? 48 85 C9 75 0C")));

	auto addr = Utilities::FindPattern(skCrypt_("\x48\x83\xEC\x58\x48\x8B\x91\x00\x00\x00\x00\x48\x85\xD2\x0F\x84\x00\x00\x00\x00\xF6\x81\x00\x00\x00\x00\x00\x74\x10\x48\x8B\x81\x00\x00\x00\x00\x48\x85\xC0\x0F\x85\x00\x00\x00\x00\x48\x8B\x8A\x00\x00\x00\x00\x48\x89\x5C\x24\x00\x48\x8D\x9A\x00\x00\x00\x00\x48\x85\xC9"), skCrypt_("xxxxxxx????xxxxx????xx?????xxxxx????xxxxx????xxx????xxxx?xxx????xxx"));
	if (!addr) 
	{
		return FALSE;
	}
	GetWeaponStats = reinterpret_cast<decltype(GetWeaponStats)>(addr);

	addr = Utilities::FindPattern(skCrypt("\x48\x85\xC9\x74\x2E\x53\x48\x83\xEC\x20\x48\x8B\xD9\x48\x8B\x0D\x00\x00\x00\x00\x48\x85\xC9\x75\x0C"), skCrypt("xxxxxxxxxxxxxxxx????xxxxx"));
	if (!addr) 
	{
		return FALSE;
	}

	FreeInternal = reinterpret_cast<decltype(FreeInternal)>(addr);

	GetObjectNameInternal = reinterpret_cast<decltype(GetObjectNameInternal)>(OFFSET_GETOBJECTNAMES);

	Offsets::ClientSetRotation = GetObjects::FindObject(skCrypt("ClientSetRotation"));
	if (!Offsets::ClientSetRotation)
		return FALSE;

	Offsets::SetIgnoreLookInput = GetObjects::FindObject(skCrypt("SetIgnoreLookInput"));
	if (!Offsets::SetIgnoreLookInput)
		return FALSE;

	uint64_t ValidateFire_address = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"),
		skCrypt_("E8 ? ? ? ? 0F B6 D8 EB 9E")));
	if (!IsValid(ValidateFire_address)) 
	{
		Warn(skCrypt("ValidateFire_address failed!")); 
		return false; 
	}
	uintptr_t ValidateFire_add = (ValidateFire_address + *(DWORD*)(ValidateFire_address + 0x1) + 0x5 - 0x100000000);



	auto GetBounds_Addr = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"),
		skCrypt_("E8 ? ? ? ? 48 8B 4D 77 B3 01")));
	if (!IsValid(GetBounds_Addr)) 
	{
		Warn(skCrypt("GetBounds_Addr failed!")); 
		return false;
	}
	Offsets::fnGetBounds = (GetBounds_Addr + *(DWORD*)(GetBounds_Addr + 0x1) + 0x5);




	auto GetBoneMatrix_add = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"),
		skCrypt_("E8 ? ? ? ? 48 8B 47 30 F3 0F 10 45 ?")));
	if (!IsValid(GetBoneMatrix_add))
	{
		Warn(skCrypt("GetBounds_Addr failed!")); 
		return false; 
	}
	Offsets::fnGetBoneMatrix = (GetBoneMatrix_add + *(DWORD*)(GetBoneMatrix_add + 0x1) + 0x5 - 0x100000000);



	Offsets::fnLineOfSightTo = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"),
		skCrypt_("40 55 53 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 E0 49")));

	Offsets::fnGetWeaponStats = (memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"),
		skCrypt_("48 83 EC 58 48 8B 91 ? ? ? ? 48 85 D2 0F 84 ? ? ? ? F6 81 ? ? ? ? ? 74 10 48 8B 81 ? ? ? ? 48 85 C0 0F 85 ? ? ? ? 48 8B 8A ? ? ? ? 48 89 5C 24 ? 48 8D 9A ? ? ? ? 48 85 C9")));
	if (!ValidateFire_add 
		|| !Offsets::fnGetBounds 
		|| !IsValid(Offsets::fnGetBoneMatrix) 
		|| !IsValid(Offsets::fnLineOfSightTo) 
		|| !IsValid(Offsets::fnGetWeaponStats))
	{
		Warn(skCrypt("failed!"));
	}
	
	oValidateLastFire = (LFAT)SetHook_1((void*)ValidateFire_add, (void*)hkValidateLastFire, 16);

	auto CalculateProjectionMatrixGivenViewOccurence = Utilities::FindPattern(skCrypt("\x45\x0F\x57\xC0\x45\x8B\x81\x00\x00\x00\x00"), skCrypt("xxxxxxx????"));
	CalculateProjectionMatrixGivenViewOccurence -= 0x280;

	MH_CreateHook(CalculateProjectionMatrixGivenViewOccurence, CalculateProjectionMatrixGivenViewHook, (PVOID*)&CalculateProjectionMatrixGivenView);
	MH_EnableHook(CalculateProjectionMatrixGivenViewOccurence);

	/*
	 addr = memory::occurence(skCrypt_("FortniteClient-Win64-Shipping.exe"),
		skCrypt_("40 55 56 57 41 54 41 55 41 56 41 57 48 81 EC ? ? ? ? 48 8D 6C 24 ? 48 89 9D ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C5 48 89 85 ? ? ? ? 8B 41 0C 45 33 F6 3B 05 ? ? ? ? 4D 8B F8 48 8B F2 4C 8B E1 41 B8 ? ? ? ? 7D 2A"));

	 MH_CreateHook(addr, UPEx, (PVOID*)&UEvent);
	 MH_EnableHook(addr);
	 */


	auto calcShot = Utilities::FindPattern(skCrypt("\x48\x89\x5C\x24\x08\x48\x89\x74\x24\x10\x48\x89\x7C\x24\x18\x4C\x89\x4C\x24\x20\x55\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x6C\x24\xD0"), skCrypt("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"));

	MH_CreateHook(calcShot, CalculateShotHook, (PVOID*)&CalculateShot);
	MH_EnableHook(calcShot);

	auto PE = Utilities::FindPattern(skCrypt("\x48\x89\x5C\x24\x00\x48\x89\x74\x24\x00\x57\x48\x83\xEC\x20\x48\x8B\xD9\x41\x8B\xF0\x48\x8B\x49\x30\x48\x8B\xFA\xE8\x00\x00\x00\x00\xBA\x00\x00\x00\x00\x48\x8B\xC8"), E("xxxx?xxxx?xxxxxxxxxxxxxxxxxxx????x????xxx"));

	MH_CreateHook(PE, GetViewPointHook, (PVOID*)&GetViewPoint);
	MH_EnableHook(PE);

	auto ProcessEvent = Utilities::FindPattern(skCrypt("\x40\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x81\xEC\x00\x00\x00\x00\x48\x8D\x6C\x24\x00\x48\x89\x9D\x00\x00\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC5\x48\x89\x85\x00\x00\x00\x00\x8B\x41\x0C\x45\x33\xF6\x3B\x05\x00\x00\x00\x00\x4D\x8B\xF8\x48\x8B\xF2\x4C\x8B\xE1\x41\xB8\x00\x00\x00\x00\x7D\x2A"), E("xxxxxxxxxxxxxxx????xxxx?xxx????xxx????xxxxxx????xxxxxxxx????xxxxxxxxxxx????xx"));

	MH_CreateHook(ProcessEvent, UPEx, (PVOID*)&UEvent);
	MH_EnableHook(ProcessEvent);
	
	return true;
}

bool InitGetKeys()
{
	HMODULE API = GetModuleHandle(skCrypt_(TEXT("win32u.dll")));
	if (API != NULL)
	{
		o_getasynckeystate = (LPFN_MBA)GetProcAddress(API, skCrypt_("NtUserGetAsyncKeyState"));
		if (o_getasynckeystate != NULL)
			return true;
		else
			return false;
	}
}

VOID Main() {

	MH_Initialize();

	extern uint64_t base_address;
	uintptr_t UObjectArray = (uintptr_t)Utilities::FindPattern(skCrypt("\x48\x8B\x05\x00\x00\x00\x00\x4C\x8D\x34\xCD"), skCrypt("xxx????xxxx"));
	UObjectArray = reinterpret_cast<uintptr_t>(RELATIVE_ADDR(UObjectArray, 7));
	uintptr_t GetNameByIndex = (uintptr_t)Utilities::FindPattern(skCrypt("\x48\x89\x5C\x24\x00\x55\x56\x57\x48\x8B\xEC\x48\x83\xEC\x30\x8B"), skCrypt("xxxx?xxxxxxxxxxx"));
	uintptr_t GetObjectName = (uintptr_t)Utilities::FindPattern(skCrypt("\x40\x53\x48\x83\xEC\x20\x48\x8B\xD9\x48\x85\xD2\x75\x45\x33\xC0\x48\x89\x01\x48\x89\x41\x08\x8D\x50\x05\xE8\x00\x00\x00\x00\x8B\x53\x08\x8D\x42\x05\x89\x43\x08\x3B\x43\x0C\x7E\x08\x48\x8B\xCB\xE8\x00\x00\x00\x00\x48\x8B\x0B\x48\x8D\x15\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\xC3\x48\x83\xC4\x20\x5B\xC3\x48\x8B\x42\x18"), skCrypt("xxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxx????xxxxxx????xx????x????xxxxxxxxxxxxx"));
	uintptr_t FnFree = (uintptr_t)Utilities::FindPattern(skCrypt("\x48\x85\xC9\x74\x2E\x53\x48\x83\xEC\x20\x48\x8B\xD9\x48\x8B\x0D\x00\x00\x00\x00\x48\x85\xC9\x75\x0C"), skCrypt("xxxxxxxxxxxxxxxx????xxxxx"));
	FortUpdater* Updater = new FortUpdater();
	//Utilities::CreateConsole();
	if (Updater->Init(UObjectArray, GetObjectName, GetNameByIndex, FnFree))
	{
		Offsets::Levels = Updater->FindOffset(skCrypt("World"), skCrypt("Levels"));
		Offsets::PersistentLevel = Updater->FindOffset(skCrypt("World"), skCrypt("PersistentLevel"));
		Offsets::LocalPlayers = Updater->FindOffset(skCrypt("GameInstance"), skCrypt("LocalPlayers"));
		Offsets::OwningGameInstance = Updater->FindOffset(skCrypt("World"), skCrypt("OwningGameInstance"));
		Offsets::ControlRotation = Updater->FindOffset(skCrypt("Controller"), skCrypt("ControlRotation"));
		Offsets::PlayerCameraManager = Updater->FindOffset(skCrypt("PlayerController"), skCrypt("PlayerCameraManager"));
		Offsets::AcknowledgedPawn = Updater->FindOffset(skCrypt("PlayerController"), skCrypt("AcknowledgedPawn"));
		Offsets::PlayerState = Updater->FindOffset(skCrypt("Pawn"), skCrypt("PlayerState"));
		Offsets::RootComponent = Updater->FindOffset(skCrypt("Actor"), skCrypt("RootComponent"));
		Offsets::Mesh = Updater->FindOffset(skCrypt("Character"), skCrypt("Mesh"));
		Offsets::RelativeLocation = Updater->FindOffset(skCrypt("SceneComponent"), skCrypt("RelativeLocation"));
		Offsets::ComponentVelocity = Updater->FindOffset(skCrypt("SceneComponent"), skCrypt("ComponentVelocity"));
		Offsets::StaticMesh = Updater->FindOffset(skCrypt("StaticMeshComponent"), skCrypt("StaticMesh"));
		Offsets::ComponentToWorld = Updater->FindOffset(skCrypt("StaticMeshComponent"), skCrypt("ComponentToWorld"));
		Offsets::CachedWorldSpaceBounds = Updater->FindOffset(skCrypt("SkinnedMeshComponent"), skCrypt("CachedWorldSpaceBounds"));
		Offsets::CustomTimeDilation = Updater->FindOffset(skCrypt("Actor"), skCrypt("CustomTimeDilation"));
		Offsets::LastFireTimeVerified = Updater->FindOffset(skCrypt("FortWeapon"), skCrypt("LastFireTimeVerified"));
		Offsets::LastFireTime = Updater->FindOffset(skCrypt("FortWeapon"), skCrypt("LastFireTime"));
		Offsets::IsReloading = Updater->FindOffset(skCrypt("FortWeapon"), skCrypt("bIsReloadingWeapon"));
		Offsets::bIsDBNO = Updater->FindOffset(skCrypt("FortPawn"), skCrypt("bIsDBNO"));
		Offsets::bIsDying = Updater->FindOffset(skCrypt("FortPawn"), skCrypt("bIsDying"));
		Offsets::TeamIndex = Updater->FindOffset(skCrypt("FortPlayerStateAthena"), skCrypt("TeamIndex"));
		Offsets::PrimaryPickupItemEntry = Updater->FindOffset(skCrypt("FortPickup"), skCrypt("PrimaryPickupItemEntry"));
		Offsets::DisplayName = Updater->FindOffset(skCrypt("FortItemDefinition"), skCrypt("DisplayName"));
		Offsets::Tier = Updater->FindOffset(skCrypt("FortItemDefinition"), skCrypt("Tier"));
		Offsets::ItemDefinition = Updater->FindOffset(skCrypt("FortItemEntry"), skCrypt("ItemDefinition"));
		Offsets::CurrentWeapon = Updater->FindOffset(skCrypt("FortPawn"), skCrypt("CurrentWeapon"));
		Offsets::WeaponData = Updater->FindOffset(skCrypt("FortWeapon"), skCrypt("WeaponData"));
		Offsets::RemoteViewPitch = Updater->FindOffset(skCrypt("Pawn"), skCrypt("RemoteViewPitch"));
		Offsets::LastFireAbilityTime = Updater->FindOffset(skCrypt("FortWeapon"), skCrypt("LastFireAbilityTime"));
		Offsets::WeaponStatHandle = Updater->FindOffset(skCrypt("FortWeaponItemDefinition"), skCrypt("WeaponStatHandle"));
		Offsets::FireStartLoc = Updater->FindOffset(skCrypt("FortProjectileAthena"), skCrypt("FireStartLoc"));
		Offsets::ReloadTime = Updater->FindOffset(skCrypt("FortBaseWeaponStats"), skCrypt("ReloadTime"));
		Offsets::ReloadScale = Updater->FindOffset(skCrypt("FortBaseWeaponStats"), skCrypt("ReloadScale"));
		Offsets::ChargeDownTime = Updater->FindOffset(skCrypt("FortBaseWeaponStats"), skCrypt("ChargeDownTime"));
		Offsets::RecoilHoriz = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("RecoilHoriz"));
		Offsets::RecoilVert = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("RecoilVert"));
		Offsets::RecoilDownsightsMultiplier = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("RecoilDownsightsMultiplier"));
		Offsets::Spread = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("Spread"));
		Offsets::SpreadDownsights = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("SpreadDownsights"));
		Offsets::StandingStillSpreadMultiplier = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("StandingStillSpreadMultiplier"));
		Offsets::AthenaJumpingFallingSpreadMultiplier = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("AthenaJumpingFallingSpreadMultiplier"));
		Offsets::AthenaCrouchingSpreadMultiplier = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("AthenaCrouchingSpreadMultiplier"));
		Offsets::AthenaSprintingSpreadMultiplier = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("RecoilDownsightsMultiplier"));
		Offsets::MinSpeedForSpreadMultiplier = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("MinSpeedForSpreadMultiplier"));
		Offsets::MaxSpeedForSpreadMultiplier = Updater->FindOffset(skCrypt("FortRangedWeaponStats"), skCrypt("MaxSpeedForSpreadMultiplier"));
		Offsets::bAlreadySearched = Updater->FindOffset(skCrypt("BuildingContainer"), skCrypt("bAlreadySearched"));
		Offsets::bActive = Updater->FindOffset(skCrypt("BuildingWeakSpot"), skCrypt("bActive"));
		Offsets::FortMeatballVehicleConfigsClass = Updater->FindOffset(skCrypt("FortMeatballVehicle"), skCrypt("FortMeatballVehicleConfigsClass"));
		Offsets::BoostMinPushForce = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("BoostMinPushForce"));
		Offsets::BoostTopSpeedForceMultiplier = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("BoostTopSpeedForceMultiplier"));
		Offsets::BoostTopSpeedMultiplier = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("BoostTopSpeedMultiplier"));
		Offsets::LandTopSpeedMultiplier = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("LandTopSpeedMultiplier"));
		Offsets::LandPushForceMultiplier = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("LandPushForceMultiplier"));
		Offsets::BoostSteeringMultiplier = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("BoostSteeringMultiplier"));
		Offsets::LandSteeringMultiplier = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("LandSteeringMultiplier"));
		Offsets::LandMinSpeedSteeringAngle = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("LandMinSpeedSteeringAngle"));
		Offsets::LandMaxSpeedSteeringAngle = Updater->FindOffset(skCrypt("FortMeatballVehicleConfigs"), skCrypt("LandMaxSpeedSteeringAngle"));
	}
	else
	{
		Warn(skCrypt("Unknown Error!"));
	}
	
	
	//std::cout << skCrypt("FortMeatballVehicleConfigsClass: 0x") << std::hex << std::uppercase << Offsets::FortMeatballVehicleConfigsClass << std::endl;
	//std::cout << skCrypt("BoostMinPushForce: 0x") << std::hex << std::uppercase << Offsets::BoostMinPushForce << std::endl;
	//std::cout << skCrypt("BoostTopSpeedForceMultiplier: 0x") << std::hex << std::uppercase << Offsets::BoostTopSpeedForceMultiplier << std::endl;
	//std::cout << skCrypt("BoostTopSpeedMultiplier: 0x") << std::hex << std::uppercase << Offsets::BoostTopSpeedMultiplier << std::endl;
	//std::cout << skCrypt("LandTopSpeedMultiplier: 0x") << std::hex << std::uppercase << Offsets::LandTopSpeedMultiplier << std::endl;
	//std::cout << skCrypt("LandPushForceMultiplier: 0x") << std::hex << std::uppercase << Offsets::LandPushForceMultiplier << std::endl;
	//std::cout << skCrypt("BoostSteeringMultiplier: 0x") << std::hex << std::uppercase << Offsets::BoostSteeringMultiplier << std::endl;
	//std::cout << skCrypt("LandSteeringMultiplier: 0x") << std::hex << std::uppercase << Offsets::LandSteeringMultiplier << std::endl;
	//std::cout << skCrypt("LandMinSpeedSteeringAngle: 0x") << std::hex << std::uppercase << Offsets::LandMinSpeedSteeringAngle << std::endl;
	//std::cout << skCrypt("LandMaxSpeedSteeringAngle: 0x") << std::hex << std::uppercase << Offsets::LandMaxSpeedSteeringAngle << std::endl;
	//std::cout << skCrypt("World::Levels: 0x") << std::hex << std::uppercase << Offsets::World::Levels << std::endl;
	//std::cout << skCrypt("World::PersistentLevel: 0x") << std::hex << std::uppercase << Offsets::World::PersistentLevel << std::endl;
	//std::cout << skCrypt("GameInstance::LocalPlayers: 0x") << std::hex << std::uppercase << Offsets::GameInstance::LocalPlayers << std::endl;
	//std::cout << skCrypt("World::OwningGameInstance: 0x") << std::hex << std::uppercase << Offsets::World::OwningGameInstance << std::endl;
	//std::cout << skCrypt("ControlRotation: 0x") << std::hex << std::uppercase << Offsets::ControlRotation << std::endl;
	//std::cout << skCrypt("PlayerController::PlayerCameraManager: 0x") << std::hex << std::uppercase << Offsets::PlayerController::PlayerCameraManager << std::endl;
	//std::cout << skCrypt("PlayerController::AcknowledgedPawn: 0x") << std::hex << std::uppercase << Offsets::PlayerController::AcknowledgedPawn << std::endl;
	//std::cout << skCrypt("PlayerState: 0x") << std::hex << std::uppercase << Offsets::PlayerState << std::endl;
	//std::cout << skCrypt("Actor::RootComponent: 0x") << std::hex << std::uppercase << Offsets::RootComponent << std::endl;
	//std::cout << skCrypt("Mesh: 0x") << std::hex << std::uppercase << Offsets::Mesh << std::endl;
	//std::cout << skCrypt("RelativeLocation: 0x") << std::hex << std::uppercase << Offsets::RelativeLocation << std::endl;
	//std::cout << skCrypt("ComponentVelocity: 0x") << std::hex << std::uppercase << Offsets::ComponentVelocity << std::endl;
	//std::cout << skCrypt("StaticMeshComponent::StaticMesh: 0x") << std::hex << std::uppercase << Offsets::StaticMeshComponent::StaticMesh << std::endl;
	//std::cout << skCrypt("SkinnedMeshComponent::CachedWorldSpaceBounds: 0x") << std::hex << std::uppercase << Offsets::SkinnedMeshComponent::CachedWorldSpaceBounds << std::endl;
	//std::cout << skCrypt("Actor::CustomTimeDilation: 0x") << std::hex << std::uppercase << Offsets::CustomTimeDilation << std::endl;
	//std::cout << skCrypt("Offsets::LastFireTimeVerified: 0x") << std::hex << std::uppercase << Offsets::LastFireTimeVerified << std::endl;
	//std::cout << skCrypt("Offsets::LastFireTime: 0x") << std::hex << std::uppercase << Offsets::LastFireTime << std::endl;
	//std::cout << skCrypt("Offsets::IsReloading: 0x") << std::hex << std::uppercase << Offsets::IsReloading << std::endl;
	//std::cout << skCrypt("bIsDBNO: 0x") << std::hex << std::uppercase << Offsets::bIsDBNO << std::endl;
	//std::cout << skCrypt("bIsDying: 0x") << std::hex << std::uppercase << Offsets::bIsDying << std::endl;
	//std::cout << skCrypt("FortPlayerStateAthena::TeamIndex: 0x") << std::hex << std::uppercase << Offsets::FortPlayerStateAthena::TeamIndex << std::endl;
	//std::cout << skCrypt("FortPickup::PrimaryPickupItemEntry: 0x") << std::hex << std::uppercase << Offsets::FortPickup::PrimaryPickupItemEntry << std::endl;
	//std::cout << skCrypt("DisplayName: 0x") << std::hex << std::uppercase << Offsets::DisplayName << std::endl;
	//std::cout << skCrypt("Tier: 0x") << std::hex << std::uppercase << Offsets::Tier << std::endl;
	//std::cout << skCrypt("FortItemEntry::ItemDefinition: 0x") << std::hex << std::uppercase << Offsets::FortItemEntry::ItemDefinition << std::endl;
	//std::cout << skCrypt("CurrentWeapon: 0x") << std::hex << std::uppercase << Offsets::CurrentWeapon << std::endl;
	//std::cout << skCrypt("WeaponData: 0x") << std::hex << std::uppercase << Offsets::WeaponData << std::endl;
	//std::cout << skCrypt("LastFireAbilityTime: 0x") << std::hex << std::uppercase << Offsets::LastFireAbilityTime << std::endl;
	//std::cout << skCrypt("FortWeaponItemDefinition::WeaponStatHandle: 0x") << std::hex << std::uppercase << Offsets::FortWeaponItemDefinition::WeaponStatHandle << std::endl;
	//std::cout << skCrypt("FortProjectileAthena::FireStartLoc: 0x") << std::hex << std::uppercase << Offsets::FortProjectileAthena::FireStartLoc << std::endl;
	//std::cout << skCrypt("FortBaseWeaponStats::ReloadTime: 0x") << std::hex << std::uppercase << Offsets::FortBaseWeaponStats::ReloadTime << std::endl;
	//std::cout << skCrypt("FortBaseWeaponStats::ReloadScale: 0x") << std::hex << std::uppercase << Offsets::FortBaseWeaponStats::ReloadScale << std::endl;
	//std::cout << skCrypt("FortBaseWeaponStats::ChargeDownTime: 0x") << std::hex << std::uppercase << Offsets::FortBaseWeaponStats::ChargeDownTime << std::endl;
	//std::cout << skCrypt("RecoilHoriz: 0x") << std::hex << std::uppercase << Offsets::RecoilHoriz << std::endl;
	//std::cout << skCrypt("RecoilVert: 0x") << std::hex << std::uppercase << Offsets::RecoilVert << std::endl;
	//std::cout << skCrypt("RecoilDownsightsMultiplier: 0x") << std::hex << std::uppercase << Offsets::RecoilDownsightsMultiplier << std::endl;
	//std::cout << skCrypt("Spread: 0x") << std::hex << std::uppercase << Offsets::Spread << std::endl;
	//std::cout << skCrypt("SpreadDownsights: 0x") << std::hex << std::uppercase << Offsets::SpreadDownsights << std::endl;
	//std::cout << skCrypt("StandingStillSpreadMultiplier: 0x") << std::hex << std::uppercase << Offsets::StandingStillSpreadMultiplier << std::endl;
	//std::cout << skCrypt("AthenaJumpingFallingSpreadMultiplier: 0x") << std::hex << std::uppercase << Offsets::AthenaJumpingFallingSpreadMultiplier << std::endl;
	//std::cout << skCrypt("AthenaCrouchingSpreadMultiplier: 0x") << std::hex << std::uppercase << Offsets::AthenaCrouchingSpreadMultiplier << std::endl;
	//std::cout << skCrypt("AthenaSprintingSpreadMultiplier: 0x") << std::hex << std::uppercase << Offsets::AthenaSprintingSpreadMultiplier << std::endl;
	//std::cout << skCrypt("MinSpeedForSpreadMultiplier: 0x") << std::hex << std::uppercase << Offsets::MinSpeedForSpreadMultiplier << std::endl;
	//std::cout << skCrypt("MaxSpeedForSpreadMultiplier: 0x") << std::hex << std::uppercase << Offsets::MaxSpeedForSpreadMultiplier << std::endl;
	//std::cout << skCrypt("BuildingContainer::bAlreadySearched: 0x") << std::hex << std::uppercase << Offsets::BuildingContainer::bAlreadySearched << std::endl;
	//std::cout << skCrypt("Offsets::RemoteViewPitch: 0x") << std::hex << std::uppercase << Offsets::RemoteViewPitch << std::endl;
	
	game_rbx_jmp = gadget(NULL);
	if (!InitGetKeys()) 
	{ 
		Warn(skCrypt("InitGetKeys failed"));
		return;
	}

	if (!InitD3DHook()) 
	{ 
		Warn(skCrypt("d3dhook failed"));
		return;
	}
	
}