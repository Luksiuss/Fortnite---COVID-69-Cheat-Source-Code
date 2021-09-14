#pragma once
#define skCrypt_(str) _xor_(str).c_str()
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))


#include "RetSpoof.h"
#include "MatrixStructs.h"

HWND hWindow = 0;
bool bHidden = false;
bool bAimingLock = false;

Vector3 CalcAim();
typedef uintptr_t(__fastcall* Cam)(uintptr_t, FMinimalViewInfo*);
Cam o_GetCameraInfo = NULL;


HRESULT(*PresentOriginal)(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) = nullptr;
HRESULT(*ResizeOriginal)(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) = nullptr;

static bool firstTime = true;
static auto Dummy_vTable = new uintptr_t[0x1001];

ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediateContext = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;


GObjects* objects = nullptr;

FString(*GetObjectNameInternal)(PVOID) = nullptr;

VOID(*CalculateProjectionMatrixGivenView)(FMinimalViewInfo* viewInfo, BYTE aspectRatioAxisConstraint, PBYTE viewport, FSceneViewProjectionData* inOutProjectionData) = nullptr;

PVOID(*GetWeaponStats)(PVOID) = nullptr;

//PVOID TargetPawn = nullptr;
PVOID boatPawns = nullptr;
PVOID TargetBoat = nullptr;
//PVOID LocalPlayerPawn = nullptr;
//PVOID LocalPlayerController = nullptr;

uint64_t base_address;
DWORD_PTR Uworld;
DWORD_PTR LocalPawn;
DWORD_PTR LocalWeapon;
DWORD_PTR PlayerCameraManager;
DWORD_PTR Localplayer;
DWORD_PTR Rootcomp;
DWORD_PTR PawnMesh;
DWORD_PTR localPlayerState;
DWORD_PTR localPlayerTeamIndex;
DWORD_PTR localPlayerSquadID;
DWORD_PTR PlayerController;
DWORD_PTR Ulevel;
DWORD_PTR AActors;
DWORD_PTR Levels;

uint64_t entityx;
Vector3 CamLoc;
Vector3 CamRot;

uint64_t OFFSET_UOBJECT = NULL;
uint64_t OFFSET_UWORLD = NULL;
uint64_t OFFSET_GETOBJECTNAMES = NULL;
uint64_t OFFSET_GETNAMEBYINDEX = NULL;
uint64_t OFFSET_FNFREE = NULL;

static int rapidfire = 0;

char buf_1[512];
char buf_2[512];

static FMatrix* myMatrix = new FMatrix();

int LevelsCount;
int actor_count;
//int Actors[2] = { 0,0 };
//int Bots[4] = { 0,0,0,0 };

VOID(*FreeInternal)(PVOID) = nullptr;

float GlobalFOV = 80.f;

uintptr_t OldAimingActor = 0;


BOOL IsValid(DWORD64 address)
{
	if (!spoof_call(game_rbx_jmp, IsBadReadPtr, (const void*)address, (UINT_PTR)8)) return TRUE;
	else return FALSE;
}

template<typename T>
T read(DWORD_PTR address, const T& def = T())
{
	if (IsValid(address))
		return *(T*)address;
	else
		return T();
}

bool GetAimKey()
{
	return Spoofer::SpoofCall(GetAsyncKeyState, Settings.aimkey);
}

VOID Free(PVOID buffer) {
	FreeInternal(buffer);
}

void FreeObjName(__int64 address)
{
	if (!IsValid(address)) return;

	auto func = reinterpret_cast<__int64(__fastcall*)(__int64 a1)>(OFFSET_FNFREE);

	spoof_call(game_rbx_jmp, func, address);
}

std::string GetObjectName(uintptr_t Object) {
	if (Object == NULL)
		return skCrypt_("");
	auto fGetObjName = reinterpret_cast<FString * (__fastcall*)(FString * name, uintptr_t entity)>(OFFSET_GETOBJECTNAMES);
	FString result;
	fGetObjName(&result, Object);
	if (result.c_str() == NULL)
		return skCrypt_("");
	auto result_str = result.ToString();
	if (result.c_str() != NULL)
		FreeObjName((__int64)result.c_str());
	return result_str;
}

Vector3 GetPawnEyeViewRot(__int64 Entity)
{
	if (!Entity || !read<uintptr_t>(Entity)) return Vector3(0, 0, 0);

	Vector3 out, out_Rot;

	auto GetActorEyesViewPoint = (*(void(__fastcall**)(__int64, Vector3*, Vector3*))(*(uint64_t*)Entity + 0x5F8));
	spoof_call(game_rbx_jmp, GetActorEyesViewPoint, Entity, &out, &out_Rot);

	return out_Rot;
}

bool IsTargetVisible(uintptr_t entity)
{
	if (!entity || !LocalPawn || !LocalWeapon || !PawnMesh || !PlayerController) return false;

	Vector3 tmp = { 0,0,0 };

	auto fLineOfSight = ((BOOL(__fastcall*)(uintptr_t, uintptr_t, Vector3*))(Offsets::fnLineOfSightTo));
	return spoof_call(game_rbx_jmp, fLineOfSight, PlayerController, entity, &tmp);
}

namespace GetObjects {
	BOOL(*LineOfSightToInternal)(PVOID PlayerController, PVOID Actor, GetStructs::FVector* ViewPoint) = nullptr;
	BOOLEAN LineOfSightTo(PVOID PlayerController, PVOID Actor, GetStructs::FVector* ViewPoint);

	BOOLEAN LineOfSightTo(PVOID PlayerController, PVOID Actor, GetStructs::FVector* ViewPoint) {
		return Spoofer::SpoofCall(LineOfSightToInternal, PlayerController, Actor, ViewPoint);
	}

	std::wstring GetObjectFirstName(UObject* object) {
		auto internalName = GetObjectNameInternal(object);
		if (!internalName.c_str()) {
			return L"";
		}

		std::wstring name(internalName.c_str());
		FreeObjName((__int64)internalName.c_str());

		return name;
	}

	std::string GetObjectName(PVOID Object) {
		if (Object == NULL)
			return skCrypt("");
		auto fGetObjName = reinterpret_cast<FString * (__fastcall*)(FString * name, uintptr_t entity)>(OFFSET_GETOBJECTNAMES);
		FString result;
		fGetObjName(&result, (uintptr_t)Object);
		if (result.c_str() == NULL)
			return skCrypt("");
		auto result_str = result.ToString();
		if (result.c_str() != NULL)
			Free(result.c_str());
		return result_str;
	}

	PVOID FindObject(std::string name) {
		for (auto array : objects->ObjectArray->Objects) {
			auto fuObject = array;
			for (auto i = 0; i < 0x10000 && fuObject->Object; ++i, ++fuObject) {
				auto object = fuObject->Object;
				if (object->ObjectFlags != 0x41)
					continue;

				if (strstr(GetObjectName(object).c_str(), name.c_str()))
					return object;
			}
		}
		return 0;
	}
}

extern std::string Warn(std::string warningText);

class FText {
private:
	char _padding_[0x28];
	PWCHAR Name;
	DWORD Length;

public:
	inline PWCHAR c_str() {
		return Name;
	}
};