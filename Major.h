#pragma once
#include "includes.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include "RetSpoof.h"
using namespace std;

extern ImVec4 backgroundColor;
extern ImVec4 innerColor;
std::vector<PVOID> weakspotPawns;
float* (*CalculateShot)(PVOID, PVOID, PVOID) = nullptr;

namespace utils 
{
	void DrawFilledBox(const Vector2& vecStart, const Vector2& vecEnd, uint32_t color, float rounding, uint32_t roundingCornersFlags);
	void DrawLine(int x1, int y1, int x2, int y2, int R, int G, int B, int A, int thickness);
}

Vector3 GetBoneLocByIdx(uintptr_t mesh, int id)
{
	if (!mesh) return { 0,0,0 };

	auto fGetBoneMatrix = ((FMatrix * (__fastcall*)(uintptr_t, FMatrix*, int))(Offsets::fnGetBoneMatrix));
	spoof_call(game_rbx_jmp, fGetBoneMatrix, mesh, myMatrix, id);

	return Vector3(myMatrix->M[3][0], myMatrix->M[3][1], myMatrix->M[3][2]);
}

/*
Vector3 ProjectWorldToScreen(Vector3 WorldLocation, Vector3 camrot)
{
	Vector3 Screenlocation = Vector3(0, 0, 0);
	Vector3 Rotation = camrot;

	D3DMATRIX tempMatrix = Matrix(Rotation);

	Vector3 vAxisX, vAxisY, vAxisZ;

	vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
	vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
	vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

	Vector3 vDelta = WorldLocation - CamLoc;
	Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

	float FovAngle = GlobalFOV;
	float ScreenCenterX = X / 2.0f;
	float ScreenCenterY = Y / 2.0f;

	if (vTransformed.z < 1.f || tanf(FovAngle * (float)M_PI / 360.f) == 0.f) return Vector3(0, 0, 0);

	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	
	return Screenlocation;
}
*/
bool ProjectWorldToScreen(float viewProjection[4][4], float width, float height, float inOutPosition[3]) {
	float res[4] = 
	{
		viewProjection[0][0] * inOutPosition[0] + viewProjection[1][0] * inOutPosition[1] + viewProjection[2][0] * inOutPosition[2] + viewProjection[3][0],
		viewProjection[0][1] * inOutPosition[0] + viewProjection[1][1] * inOutPosition[1] + viewProjection[2][1] * inOutPosition[2] + viewProjection[3][1],
		viewProjection[0][2] * inOutPosition[0] + viewProjection[1][2] * inOutPosition[1] + viewProjection[2][2] * inOutPosition[2] + viewProjection[3][2],
		viewProjection[0][3] * inOutPosition[0] + viewProjection[1][3] * inOutPosition[1] + viewProjection[2][3] * inOutPosition[2] + viewProjection[3][3],
	};

	auto r = res[3];
	if (r > 0) 
	{
		auto rhw = 1.0f / r;

		inOutPosition[0] = (((res[0] * rhw) / 2.0f) + 0.5f) * width;
		inOutPosition[1] = (0.5f - ((res[1] * rhw) / 2.0f)) * height;
		inOutPosition[2] = r;

		return TRUE;
	}

	return FALSE;
}

bool WorldToScreen(float width, float height, float inOutPosition[3])
{
	return ProjectWorldToScreen(view.ProjectionMatrix, width, height, inOutPosition);
}

//uintptr_t hkGetCameraInfo(uintptr_t a1, FMinimalViewInfo* a2)
//{
//	static float last_fire_ability_time = 0.f;
//
//	uintptr_t ret = spoof_call(game_rbx_jmp, o_GetCameraInfo, a1, a2);
//
//	CamLoc = a2->Location;
//	CamRot = a2->Rotation;
//
//	if (Settings.FOVChanger)
//	{
//		a2->FOV = (float)Settings.FOV;
//	}
//
//	GlobalFOV = a2->FOV;
//
//	if (Settings.SilentAimbot)
//	{
//		if (!IsValid(LocalPawn) || !IsValid(entityx)) return ret;
//
//		LocalWeapon = read<uintptr_t>(LocalPawn + Offsets::CurrentWeapon);
//
//		if (LocalWeapon)
//		{
//			if (*(float*)(LocalWeapon + Offsets::LastFireAbilityTime) != last_fire_ability_time)
//			{
//				Vector3 SilentAimAngle = CalcAim();
//
//				if (SilentAimAngle.x != 0 || SilentAimAngle.y != 0)
//					a2->Rotation = SilentAimAngle;
//
//				last_fire_ability_time = *(float*)(LocalWeapon + Offsets::LastFireAbilityTime);
//				if (Settings.RapidFire)
//				{
//					*(float*)(LocalWeapon + Offsets::LastFireAbilityTime) = 0.1;
//				}
//			}
//		}
//	}
//
//	return ret;
//}
//
//bool InstallCameraHook(uintptr_t PlayerCameraManager)
//{
//	uintptr_t vTable_address = *(uintptr_t*)(PlayerCameraManager);
//	if ((uintptr_t)hkGetCameraInfo == read<uintptr_t>(vTable_address + (0xCC * 0x8))) return true;
//	if (!vTable_address) return false;
//	int num_virtual_methods = 0;
//	int z = 0;
//	while (read<uintptr_t>(vTable_address + (z * 0x8))) {
//		num_virtual_methods += 1;
//		z++;
//	}
//	for (int i = 0; i < num_virtual_methods; i++)
//	{
//		Dummy_vTable[i] = read<uintptr_t>(vTable_address + (i * 0x8));
//	}
//	o_GetCameraInfo = (Cam)(read<uintptr_t>(vTable_address + (0xCC * 8)));
//	Dummy_vTable[0xCC] = (uintptr_t)hkGetCameraInfo;
//	*(uintptr_t**)(PlayerCameraManager) = Dummy_vTable;
//	return true;
//}

void* SetHook_1(void* pSource, void* pDestination, int dwLen)
{
	DWORD MinLen = 14;

	if (dwLen < MinLen) return NULL;

	BYTE stub[] = {
	0xFF, 0x25, 0x00, 0x00, 0x00, 0x00, // jmp qword ptr [$+6]
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 // ptr
	};

	static const void* pTrampoline = nullptr;
	if (!pTrampoline) {
		const auto ntdll = reinterpret_cast<const unsigned char*>(spoof_call(game_rbx_jmp, GetModuleHandleW, (LPCWSTR)NULL));
		const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(ntdll);
		const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(ntdll + dos->e_lfanew);
		const auto sections = IMAGE_FIRST_SECTION(nt);
		const auto num_sections = nt->FileHeader.NumberOfSections;

		constexpr char section_name[5]{ '.', 't', 'e', 'x', 't' };
		const auto     section = std::find_if(sections, sections + num_sections, [&](const auto& s) {
			return std::equal(s.Name, s.Name + 5, section_name);
			});

		constexpr unsigned char instr_bytes[2]{ 0xFF, 0x25 };
		const auto              va = ntdll + section->VirtualAddress;
		pTrampoline = std::search(va, va + section->Misc.VirtualSize, instr_bytes, instr_bytes + 2);
	}

	DWORD64 retto = (DWORD64)pSource + dwLen;

	// trampoline
	memcpy(stub + 6, &retto, 8);
	memcpy((void*)((DWORD_PTR)pTrampoline), pSource, dwLen);
	memcpy((void*)((DWORD_PTR)pTrampoline + dwLen), stub, sizeof(stub));

	// orig
	memcpy(stub + 6, &pDestination, 8);
	memcpy(pSource, stub, sizeof(stub));

	for (int i = MinLen; i < dwLen; i++)
	{
		*(BYTE*)((DWORD_PTR)pSource + i) = 0x90;
	}

	return (void*)((DWORD_PTR)pTrampoline);
}

FBox GetFBox(uintptr_t Actor)
{
	if (!Actor) return {};

	Vector3 Origin, BoxExtend;

	auto fGetActorBounds = reinterpret_cast<void(__fastcall*)(__int64, char, Vector3*, Vector3*)>(Offsets::fnGetBounds);

	spoof_call(game_rbx_jmp, fGetActorBounds, (__int64)Actor, (char)true, &Origin, &BoxExtend);

	FBox NewBox;
	NewBox.IsValid = 1;
	NewBox.Min = Origin - BoxExtend;
	NewBox.Max = Origin + BoxExtend;

	return NewBox;
}

Vector3 CalcAim()
{
	Vector3 RetVector = { 0,0,0 };

	if (!entityx) return { 0,0,0 };

	uint64_t currentactormesh = read<uint64_t>(entityx + Offsets::Mesh);
	if (!currentactormesh) return { 0,0,0 };

	if (!Settings.ESP.RandomAim)
	{
		if (Settings.AimPos == 1)
			AimBoneInt = 66;
		else if (Settings.AimPos == 2)
			AimBoneInt = 5;
		else if (Settings.AimPos == 3)
			AimBoneInt = 2;
		else // which is impossible.
			AimBoneInt = 66;
	}

	Vector3 rootHead = GetBoneLocByIdx(currentactormesh, AimBoneInt);
	if (rootHead.x == 0 && rootHead.y == 0) return Vector3(0, 0, 0);

	Vector3 VectorPos = rootHead - CamLoc;

	float distance = VectorPos.Length();
	RetVector.x = -(((float)acos(VectorPos.z / distance) * (float)(180.0f / M_PI)) - 90.f);
	RetVector.y = (float)atan2(VectorPos.y, VectorPos.x) * (float)(180.0f / M_PI);

	return RetVector;
}

double GetCrossDistance(double x1, double y1, double x2, double y2)
{
	return spoof_call(game_rbx_jmp, sqrtf, spoof_call(game_rbx_jmp, powf, (float)(x1 - x2), (float)2) + spoof_call(game_rbx_jmp, powf, (float)(y1 - y2), (float)2));
}

bool GetClosestPlayerToCrossHair(Vector3 Pos, float& max, DWORD_PTR entity)
{
	if (entity)
	{
		float Dist = GetCrossDistance(Pos.x, Pos.y, (X / 2), (Y / 2));

		if (Dist < max)
		{
			//GlobalFOV : X = NewFOV : NewSize
			//NewSize = NewFOV * X / GlobalFOV

			float Radius = (Settings.AimbotFOV * X / GlobalFOV) / 2;

			if (Pos.x <= ((X / 2) + Radius) &&
				Pos.x >= ((X / 2) - Radius) &&
				Pos.y <= ((Y / 2) + Radius) &&
				Pos.y >= ((Y / 2) - Radius))
			{
				max = Dist;
				entityx = entity;
				return true;
			}

			return false;
		}
	}

	return false;
}

void CheckClosestFOVEntity(DWORD_PTR entity, Vector3 Localcam, float& max)
{
	if (!entity || !LocalPawn || !LocalWeapon) return;

	uint64_t currentactormesh = read<uint64_t>(entity + Offsets::Mesh);
	if (!currentactormesh) return;

	Vector3 rootHead = GetBoneLocByIdx(currentactormesh, 66);
	if (WorldToScreen(width, height, &rootHead.x)) {
		if (rootHead.x <= 0 || rootHead.y <= 0) return;
		if (rootHead.x >= X || rootHead.y >= Y) return;

		if (Settings.visCheck && !IsTargetVisible(entity)) return;

		if (GetClosestPlayerToCrossHair(rootHead, max, entity))
			entityx = entity;
	}
}

FVector* GetPawnRootLocation(PVOID pawn) 
{
	auto root = ReadPointer(pawn, Offsets::RootComponent);
	if (!root) {
		return nullptr;
	}

	return reinterpret_cast<FVector*>(reinterpret_cast<PBYTE>(root) + Offsets::RelativeLocation);
}

void CheckClosestDistEntity(PVOID entity, float& max, int number)
{
	if (!entity) return;

	FVector rootHeada = *GetPawnRootLocation(entity);
	Vector3 rootHead = Vector3{ rootHeada.X, rootHeada.Y, rootHeada.Z };

	if (rootHead.x == 0 && rootHead.y == 0) return;

	//if (Settings.visCheck && !IsTargetVisible((uintptr_t)entity)) return;

	Vector3 Delta = rootHead - CamLoc;

	float Dist = spoof_call(game_rbx_jmp, sqrtf, spoof_call(game_rbx_jmp, powf, (Delta.x), (float)2) + spoof_call(game_rbx_jmp, powf, (Delta.y), (float)2) + spoof_call(game_rbx_jmp, powf, (Delta.z), (float)2));

	//if (AimDistance != 300)
	//{
	//	if ((Dist * 0.01f) > (float)AimDistance) return;
	//}

	if ((Dist * 0.01f) < max)
	{
		max = (Dist * 0.01f);
		if (number == 1)
			TargetBoat = entity;
		return;
	}
	return;
}

void Draw3DBoundingBox(uintptr_t mesh, uint64_t CurrentActor, ImU32 color)
{
	if (!CurrentActor) return;

	Vector3 min, max, vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8;

	FBox box = GetFBox(CurrentActor);

	if (!box.IsValid) return;

	min = box.Min;
	max = box.Max;

	vec3 = min;
	vec3.x = max.x;
	vec4 = min;
	vec4.y = max.y;
	vec5 = min;
	vec5.z = max.z;
	vec6 = max;
	vec6.x = min.x;
	vec7 = max;
	vec7.y = min.y;
	vec8 = max;
	vec8.z = min.z;
	if (WorldToScreen(width, height, &min.x)) {
		vec1 = min;
	}
	if (WorldToScreen(width, height, &max.x)) {
		vec2 = max;
	}
	if (WorldToScreen(width, height, &vec3.x)) {
		vec3 = vec3;
	}
	if (WorldToScreen(width, height, &vec4.x)) {
		vec4 = vec4;
	}
	if (WorldToScreen(width, height, &vec5.x)) {
		vec5 = vec5;
	}
	if (WorldToScreen(width, height, &vec6.x)) {
		vec6 = vec6;
	}
	if (WorldToScreen(width, height, &vec7.x)) {
		vec7 = vec7;
	}
	if (WorldToScreen(width, height, &vec8.x)) {
		vec8 = vec8;
	}

	if (vec1.x == 0 && vec1.y == 0) return;
	if (vec2.x == 0 && vec2.y == 0) return;
	if (vec3.x == 0 && vec3.y == 0) return;
	if (vec4.x == 0 && vec4.y == 0) return;
	if (vec5.x == 0 && vec5.y == 0) return;
	if (vec6.x == 0 && vec6.y == 0) return;
	if (vec7.x == 0 && vec7.y == 0) return;
	if (vec8.x == 0 && vec8.y == 0) return;

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec1.x, vec1.y), ImVec2(vec5.x, vec5.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec2.x, vec2.y), ImVec2(vec8.x, vec8.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec3.x, vec3.y), ImVec2(vec7.x, vec7.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec4.x, vec4.y), ImVec2(vec6.x, vec6.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec1.x, vec1.y), ImVec2(vec3.x, vec3.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec1.x, vec1.y), ImVec2(vec4.x, vec4.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec8.x, vec8.y), ImVec2(vec3.x, vec3.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec8.x, vec8.y), ImVec2(vec4.x, vec4.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec2.x, vec2.y), ImVec2(vec6.x, vec6.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec2.x, vec2.y), ImVec2(vec7.x, vec7.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec5.x, vec5.y), ImVec2(vec6.x, vec6.y), color, Settings.SnaplinePower);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(vec5.x, vec5.y), ImVec2(vec7.x, vec7.y), color, Settings.SnaplinePower);
}

void Draw2DBoundingBox(Vector3 StartBoxLoc, float flWidth, float Height, ImU32 color)
{
	StartBoxLoc.x = StartBoxLoc.x - (flWidth / 2);

	ImGui::GetOverlayDrawList()->AddLine(ImVec2(StartBoxLoc.x, StartBoxLoc.y), ImVec2(StartBoxLoc.x + flWidth, StartBoxLoc.y), color, Settings.SnaplinePower); //bottom
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(StartBoxLoc.x, StartBoxLoc.y), ImVec2(StartBoxLoc.x, StartBoxLoc.y + Height), color, Settings.SnaplinePower); //left
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(StartBoxLoc.x + flWidth, StartBoxLoc.y), ImVec2(StartBoxLoc.x + flWidth, StartBoxLoc.y + Height), color, Settings.SnaplinePower); //right
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(StartBoxLoc.x, StartBoxLoc.y + Height), ImVec2(StartBoxLoc.x + flWidth, StartBoxLoc.y + Height), color, Settings.SnaplinePower); //up
}


VOID skel_line(float width, float height, Vector3 a, Vector3 b, ImU32 color, float& minX, float& maxX, float& minY, float& maxY)
{
	float ac[3] = { a.x, a.y, a.z };
	float bc[3] = { b.x, b.y, b.z };
	if (WorldToScreen(width, height, ac) && WorldToScreen(width, height, bc)) 
	{
		if (Settings.ESP.Skeleton)
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(ac[0], ac[1]), ImVec2(bc[0], bc[1]), color, 2.0f);

		minX = min(ac[0], minX);
		minX = min(bc[0], minX);

		maxX = max(ac[0], maxX);
		maxX = max(bc[0], maxX);

		minY = min(ac[1], minY);
		minY = min(bc[1], minY);

		maxY = max(ac[1], maxY);
		maxY = max(bc[1], maxY);
	}
}

void DrawSkeleton(DWORD_PTR mesh, bool isVisible, float& minX, float& maxX, float& minY, float& maxY)
{
	if (!mesh) return;

	Vector3 head = GetBoneLocByIdx(mesh, 66);
	Vector3 neck = GetBoneLocByIdx(mesh, 65);
	Vector3 chest = GetBoneLocByIdx(mesh, 36);
	Vector3 pelvis = GetBoneLocByIdx(mesh, 2);
	Vector3 leftShoulder = GetBoneLocByIdx(mesh, 9);
	Vector3 rightShoulder = GetBoneLocByIdx(mesh, 62);
	Vector3 leftElbow = GetBoneLocByIdx(mesh, 10);
	Vector3 rightElbow = GetBoneLocByIdx(mesh, 38);
	Vector3 leftHand = GetBoneLocByIdx(mesh, 11);
	Vector3 rightHand = GetBoneLocByIdx(mesh, 39);
	Vector3 leftLeg = GetBoneLocByIdx(mesh, 67);
	Vector3 rightLeg = GetBoneLocByIdx(mesh, 74);
	Vector3 leftThigh = GetBoneLocByIdx(mesh, 73);
	Vector3 rightThigh = GetBoneLocByIdx(mesh, 80);
	Vector3 leftFoot = GetBoneLocByIdx(mesh, 68);
	Vector3 rightFoot = GetBoneLocByIdx(mesh, 75);
	Vector3 leftFeet = GetBoneLocByIdx(mesh, 71);
	Vector3 rightFeet = GetBoneLocByIdx(mesh, 78);
	Vector3 leftFeetFinger = GetBoneLocByIdx(mesh, 72);
	Vector3 rightFeetFinger = GetBoneLocByIdx(mesh, 79);

	ImU32 color = ImGui::GetColorU32({ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });
	if (isVisible)
		color = ImGui::GetColorU32({ 255 / 255.f, 000 / 255.f, 000 / 255.f, 1.0f });

	skel_line(width, height, head, neck, color, minX, maxX, minY, maxY);
	skel_line(width, height, neck, pelvis, color, minX, maxX, minY, maxY);
	skel_line(width, height, chest, leftShoulder, color, minX, maxX, minY, maxY);
	skel_line(width, height, chest, rightShoulder, color, minX, maxX, minY, maxY);
	skel_line(width, height, leftShoulder, leftElbow, color, minX, maxX, minY, maxY);
	skel_line(width, height, rightShoulder, rightElbow, color, minX, maxX, minY, maxY);
	skel_line(width, height, leftElbow, leftHand, color, minX, maxX, minY, maxY);
	skel_line(width, height, rightElbow, rightHand, color, minX, maxX, minY, maxY);
	skel_line(width, height, pelvis, leftLeg, color, minX, maxX, minY, maxY);
	skel_line(width, height, pelvis, rightLeg, color, minX, maxX, minY, maxY);
	skel_line(width, height, leftLeg, leftThigh, color, minX, maxX, minY, maxY);
	skel_line(width, height, rightLeg, rightThigh, color, minX, maxX, minY, maxY);
	skel_line(width, height, leftThigh, leftFoot, color, minX, maxX, minY, maxY);
	skel_line(width, height, rightThigh, rightFoot, color, minX, maxX, minY, maxY);
	skel_line(width, height, leftFoot, leftFeet, color, minX, maxX, minY, maxY);
	skel_line(width, height, rightFoot, rightFeet, color, minX, maxX, minY, maxY);
	skel_line(width, height, leftFeet, leftFeetFinger, color, minX, maxX, minY, maxY);
	skel_line(width, height, rightFeet, rightFeetFinger, color, minX, maxX, minY, maxY);
}

void inline DrawLaser(uintptr_t target, uintptr_t currentactormesh, ImU32 color)
{
	if (target)
	{
		Vector3 target_rot = GetPawnEyeViewRot(target);
		Vector3 target_loc = GetBoneLocByIdx(currentactormesh, 66);

		if (target_rot.x == 0 && target_rot.y == 0) return;
		if (target_loc.x == 0 && target_loc.y == 0) return;

		double radiantsYAW = ((target_rot.y * M_PI) / 180);

		float RemotePitch = *(float*)(target + Offsets::RemoteViewPitch);
		double radiantsPITCH = (((float)RemotePitch * M_PI) / 180);
		double hyp = 250;
		double X = (hyp * cos(radiantsYAW));
		double Y = (hyp * sin(radiantsYAW));
		double Z = (hyp * sin(radiantsPITCH));
		float PlX = target_loc.x + X;
		float PlZ = target_loc.y + Y;
		float PlY = target_loc.z + Z;

		Vector3 Laser, Laser_out, HeadLoc_out;
		Laser.x = PlX;
		Laser.z = PlY;
		Laser.y = PlZ;

		if (WorldToScreen(width, height, &Laser.x) && WorldToScreen(width, height, &target_loc.x)) {
			Laser_out = Laser;
			HeadLoc_out = target_loc;

			if (Laser_out.x == 0 && Laser_out.y == 0) return;
			if (HeadLoc_out.x == 0 && HeadLoc_out.y == 0) return;

			ImGui::GetOverlayDrawList()->AddLine(ImVec2(HeadLoc_out.x, HeadLoc_out.y), ImVec2(Laser_out.x, Laser_out.y), color, Settings.SnaplinePower);
		}
	}
}

Vector3 Normalize(Vector3 vec)
{
	float a1 = vec.x;
	float a2 = vec.y;
	float a3 = vec.z;
	double length = vec.Length();

	if (length == 0.0) return { 0,0,0 };

	return Vector3(a1 / length, a2 / length, a3 / length);
}

Vector3 inline LimitRotation(Vector3 startRotation, Vector3 endRotation)
{
	Vector3 ret;
	auto scale = Settings.AimbotSlow;
	auto currentRotation = startRotation;

	ret.x = (endRotation.x - startRotation.x) / scale + startRotation.x;
	ret.y = (endRotation.y - startRotation.y) / scale + startRotation.y;

	return ret;
}


void DoMemoryAimbot()
{
	if (bAimingLock)
		bAimingLock = false;

	if (!read<uint64_t>(entityx + Offsets::RootComponent))
	{
		entityx = 0;
		return;
	}
	if (!read<uint64_t>(entityx + Offsets::PlayerState))
	{
		entityx = 0;
		return;
	}
	if (!read<uint64_t>(entityx + Offsets::Mesh))
	{
		entityx = 0;
		return;
	}
	uint8_t bIsDying = *(uint8_t*)(entityx + Offsets::bIsDying);
	if (BIT_CHECK(bIsDying, 3))
	{
		entityx = 0;
		return;
	}

	if (!PlayerController || !read<uintptr_t>(PlayerController))
	{
		entityx = 0;
		return;
	}

	//auto weaponName = GetObjects::GetObjectFirstName((UObject*)LocalWeapon);
	//auto isPickAxe = wcsstr(weaponName.c_str(), skCrypt(L"Pickaxe_"));
	//if (isPickAxe)
	//	return;

	Vector3 NewAngle = CalcAim();

	if (NewAngle.x == 0 && NewAngle.y == 0) return;

	if (Settings.AimbotSlow > 0)
		NewAngle = LimitRotation(CamRot, NewAngle);

	NewAngle.z = 0;

	if (Settings.AimHelper)
	{
		//auto SetIgnoreLookInput = (*(void(__fastcall**)(uint64_t, char bNewLookInput))(*(uint64_t*)PlayerController + 0x728));
		//spoof_call(game_rbx_jmp, SetIgnoreLookInput, PlayerController, (char)1);
		struct 
		{
			bool bNewLookInput;
		} params;
		params.bNewLookInput = 1;
		UEvent((PVOID)PlayerController, Offsets::SetIgnoreLookInput, &params, 0);
		bAimingLock = true;
	}

	//auto ClientSetRotation = (*(void(__fastcall**)(uint64_t, Vector3, char))(*(uint64_t*)PlayerController + 0x628));
	//spoof_call(game_rbx_jmp, ClientSetRotation, PlayerController, NewAngle, (char)0);
	struct
	{
		FRotator NewRotation;
		bool bResetCamera;
	} params;

	params.NewRotation = FRotator{NewAngle.x, NewAngle.y, NewAngle.z};

	UEvent((PVOID)PlayerController, Offsets::ClientSetRotation, &params, 0);
}

float AimSpeed = 2.5f;
float AimSmooth = 1.5f;
void DoMouseAim()
{
	if (!read<uint64_t>(entityx + Offsets::RootComponent))
	{
		entityx = 0;
		return;
	}
	if (!read<uint64_t>(entityx + Offsets::PlayerState))
	{
		entityx = 0;
		return;
	}
	if (!read<uint64_t>(entityx + Offsets::Mesh))
	{
		entityx = 0;
		return;
	}
	uint8_t bIsDying = *(uint8_t*)(entityx + Offsets::bIsDying);
	if (BIT_CHECK(bIsDying, 3))
	{
		entityx = 0;
		return;
	}

	if (!PlayerController || !read<uintptr_t>(PlayerController))
	{
		entityx = 0;
		return;
	}

	Vector3 NewAngle = CalcAim();

	if (NewAngle.x == 0 && NewAngle.y == 0) return;

	if (Settings.AimbotSlow > 0)
		NewAngle = LimitRotation(CamRot, NewAngle);

	NewAngle.z = 0;

	if (WorldToScreen(width, height, &NewAngle.x))
	{
		auto Width = width;
		auto Height = height;
		auto x = NewAngle.x;
		auto y = NewAngle.y;
		// EXTERNAL AIMBOT
		float ScreenCenterX = (Width / 2);
		float ScreenCenterY = (Height / 2);
		float TargetX = 0;
		float TargetY = 0;

		if (x != 0)
		{
			if (x > ScreenCenterX)
			{
				TargetX = -(ScreenCenterX - x);
				TargetX /= AimSpeed;
				if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
			}

			if (x < ScreenCenterX)
			{
				TargetX = x - ScreenCenterX;
				TargetX /= AimSpeed;
				if (TargetX + ScreenCenterX < 0) TargetX = 0;
			}
		}

		if (y != 0)
		{
			if (y > ScreenCenterY)
			{
				TargetY = -(ScreenCenterY - y);
				TargetY /= AimSpeed;
				if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
			}

			if (y < ScreenCenterY)
			{
				TargetY = y - ScreenCenterY;
				TargetY /= AimSpeed;
				if (TargetY + ScreenCenterY < 0) TargetY = 0;
			}
		}

		INPUT  input;
		input.type = INPUT_MOUSE;
		input.mi.mouseData = 0;
		input.mi.time = 0;
		input.mi.dx = floor(TargetX / Settings.AimbotSlow);
		input.mi.dy = floor(TargetY / Settings.AimbotSlow);
		input.mi.dwFlags = MOUSEEVENTF_MOVE;
		input.mi.dwExtraInfo = 0;
		SendInput(1, &input, sizeof(input));
	}
}

void DrawAimingEnemy()
{
	if (!entityx) return;

	uint64_t currentactormesh = read<uint64_t>(entityx + Offsets::Mesh);
	if (!currentactormesh) return;

	Vector3 target_loc = GetBoneLocByIdx(currentactormesh, 66);
	if (target_loc.x == 0 && target_loc.y == 0) return;

	if (WorldToScreen(width, height, &target_loc.x)) 
	{

		if (target_loc.x == 0 && target_loc.y == 0) return;

		ImGui::GetOverlayDrawList()->AddLine(ImVec2(target_loc.x, target_loc.y), ImVec2(width / 2, height / 2), ImGui::GetColorU32({ 200 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f }), Settings.SnaplinePower);
	}

}

void RadarRange(float* x, float* y, float range)
{
	if (fabs((*x)) > range || fabs((*y)) > range)
	{
		if ((*y) > (*x))
		{
			if ((*y) > -(*x))
			{
				(*x) = range * (*x) / (*y);
				(*y) = range;
			}
			else
			{
				(*y) = -range * (*y) / (*x);
				(*x) = -range;
			}
		}
		else
		{
			if ((*y) > -(*x))
			{
				(*y) = range * (*y) / (*x);
				(*x) = range;
			}
			else
			{
				(*x) = -range * (*x) / (*y);
				(*y) = -range;
			}
		}
	}
}

void CalcRadarPoint(FVector vOrigin, int& screenx, int& screeny)
{
	FRotator vAngle = FRotator{ CamRot.x, CamRot.y, CamRot.z };
	auto fYaw = vAngle.Yaw * PI / 180.0f;
	float dx = vOrigin.X - CamLoc.x;
	float dy = vOrigin.Y - CamLoc.y;

	float fsin_yaw = sinf(fYaw);
	float fminus_cos_yaw = -cosf(fYaw);

	float x = dy * fminus_cos_yaw + dx * fsin_yaw;
	x = -x;
	float y = dx * fminus_cos_yaw - dy * fsin_yaw;

	float range = (float)Settings.RadarESPRange;

	RadarRange(&x, &y, range);

	ImVec2 DrawPos = ImGui::GetCursorScreenPos();
	ImVec2 DrawSize = ImGui::GetContentRegionAvail();

	int rad_x = (int)DrawPos.x;
	int rad_y = (int)DrawPos.y;

	float r_siz_x = DrawSize.x;
	float r_siz_y = DrawSize.y;

	int x_max = (int)r_siz_x + rad_x - 5;
	int y_max = (int)r_siz_y + rad_y - 5;

	screenx = rad_x + ((int)r_siz_x / 2 + int(x / range * r_siz_x));
	screeny = rad_y + ((int)r_siz_y / 2 + int(y / range * r_siz_y));

	if (screenx > x_max)
		screenx = x_max;

	if (screenx < rad_x)
		screenx = rad_x;

	if (screeny > y_max)
		screeny = y_max;

	if (screeny < rad_y)
		screeny = rad_y;
}

void renderRadar() {
	for (auto pawn : radarPawns)
	{
		auto player = pawn;

		int screenx = 0;
		int screeny = 0;

		float Color_R = 255 / 255.f;
		float Color_G = 128 / 255.f;
		float Color_B = 0 / 255.f;

		FVector pos = *GetPawnRootLocation((PVOID)pawn);

		CalcRadarPoint(pos, screenx, screeny);

		ImDrawList* Draw = ImGui::GetOverlayDrawList();

		FVector viewPoint = { 0 };
		if (IsTargetVisible(pawn))
		{
			Color_R = 255 / 255.f;
			Color_G = 000 / 255.f;
			Color_B = 000 / 255.f;
		}
		Draw->AddRectFilled(ImVec2((float)screenx, (float)screeny),
			ImVec2((float)screenx + 5, (float)screeny + 5),
			ImColor(Color_R, Color_G, Color_B));
	}

}
bool firstS = false;
void RadarLoop()
{
	if (Settings.RadarESP)
	{
		// menu here
		ImGui::StyleColorsRadar();
		auto& style = ImGui::GetStyle();
		style.WindowTitleAlign = { 0.5f, 0.5f };
		style.WindowPadding = ImVec2(15, 15);
		style.WindowRounding = 1.0f;
		style.FramePadding = ImVec2(5, 5);
		style.ItemSpacing = ImVec2(12, 8);
		style.ItemInnerSpacing = ImVec2(8, 6);
		style.IndentSpacing = 25.0f;
		style.ScrollbarSize = 0.0f;
		style.ScrollbarRounding = 1.0f;
		style.GrabMinSize = 5.0f;
		style.GrabRounding = 3.0f;
		style.Alpha = 1.f;

		ImGuiWindowFlags TargetFlags;
		if (ShowMenu)
			TargetFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
		else
			TargetFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

		//ImGui::SetNextWindowPosCenter(ImGuiCond_Once);
		if (!firstS)
		{
			ImGui::SetNextWindowPos(ImVec2{ width - 220, 600 }, ImGuiCond_Once);
			firstS = true;
		}
		if (ImGui::Begin(skCrypt("xoxo"), 0, ImVec2(200, 200), -1.f, TargetFlags))
		{
			int Size;
			ImDrawList* Draw = ImGui::GetOverlayDrawList();
			ImVec2 DrawPos = ImGui::GetCursorScreenPos();
			ImVec2 DrawSize = ImGui::GetContentRegionAvail();

			Draw->AddLine(
				ImVec2(DrawPos.x + DrawSize.x / 2.f, DrawPos.y),
				ImVec2(DrawPos.x + DrawSize.x / 2.f, DrawPos.y + DrawSize.y),
				ImColor(1.f, 1.f, 1.f));

			Draw->AddLine(
				ImVec2(DrawPos.x, DrawPos.y + DrawSize.y / 2.f),
				ImVec2(DrawPos.x + DrawSize.x, DrawPos.y + DrawSize.y / 2.f),
				ImColor(1.f, 1.f, 1.f));

			ImVec2 midRadar = ImVec2(DrawPos.x + (DrawSize.x / 2), DrawPos.y + (DrawSize.y / 2));

			ImGui::GetWindowDrawList()->AddLine(ImVec2(midRadar.x - DrawSize.x / 2.f, midRadar.y), ImVec2(midRadar.x + DrawSize.x / 2.f, midRadar.y), MAKE_IMU32(0, 0, 0, 50));
			ImGui::GetWindowDrawList()->AddLine(ImVec2(midRadar.x, midRadar.y - DrawSize.y / 2.f), ImVec2(midRadar.x, midRadar.y + DrawSize.y / 2.f), MAKE_IMU32(0, 0, 0, 50));

			if (PlayerController || PlayerCameraManager && LocalPawn && CamRot.y)
			{
				renderRadar();
			}
		}
		ImGui::End();
	}
}

ImVec4 GetItemColor(BYTE tier)
{
	switch (tier)
	{
	case 1:
		return ITEM_COLOR_TIER_WHITE;
	case 2:
		return ITEM_COLOR_TIER_GREEN;
	case 3:
		return ITEM_COLOR_TIER_BLUE;
	case 4:
		return ITEM_COLOR_TIER_PURPLE;
	case 5:
		return ITEM_COLOR_TIER_ORANGE;
	case 6:
	case 7:
		return ITEM_COLOR_TIER_GOLD;
	case 8:
	case 9:
		return ImVec4{ 200 / 255.f, 0 / 255.f, 0 / 255.f, 0.95f };
	case 10:
		return ITEM_COLOR_TIER_UNKNOWN;
	default:
		return ITEM_COLOR_TIER_WHITE;
	}
}

//namespace Internal {
//	bool GetPlayerName(PVOID PlayerState, wchar_t* sPlayerName)
//	{
//		if (!PlayerState) return false;
//
//		static uintptr_t pGetPlayerName = 0;
//		if (!pGetPlayerName)
//		{
//			uintptr_t VTable = *(uintptr_t*)PlayerState;
//			if (!VTable)  return false;
//
//			pGetPlayerName = *(uintptr_t*)(VTable + 0x680);
//			if (!pGetPlayerName) return false;
//		}
//
//		auto GetPlayerName = reinterpret_cast<void(__fastcall*)(uintptr_t, FString*)>(pGetPlayerName);
//
//		FString Buffer;
//		Spoofer::SpoofCall(GetPlayerName, (uintptr_t)PlayerState, &Buffer);
//		if (!Buffer.c_str()) return false;
//
//		Spoofer::SpoofCall(wcscpy, sPlayerName, Buffer.c_str());
//
//		//Free((PVOID)Buffer.c_str());
//
//		return true;
//	}
//}

VOID skel_line(float width, float height, float a[3], float b[3], ImU32 color, float& minX, float& maxX, float& minY, float& maxY)
{
	float ac[3] = { a[0], a[1], a[2] };
	float bc[3] = { b[0], b[1], b[2] };
	if (WorldToScreen(width, height, ac) && WorldToScreen(width, height, bc))
	{
		if (Settings.ESP.Skeleton)
			ImGui::GetOverlayDrawList()->AddLine(ImVec2(ac[0], ac[1]), ImVec2(bc[0], bc[1]), color, 2.0f);

		minX = min(ac[0], minX);
		minX = min(bc[0], minX);

		maxX = max(ac[0], maxX);
		maxX = max(bc[0], maxX);

		minY = min(ac[1], minY);
		minY = min(bc[1], minY);

		maxY = max(ac[1], maxY);
		maxY = max(bc[1], maxY);
	}
}

FMinimalViewInfo& GetViewInfo() 
{
	return view.Info;
}

namespace utils 
{
	void DrawBox(int x1, int y1, int x2, int y2, float r, float g, float b, float a, bool isFilled);
	void DrawNewText(int x, int y, int R, int G, int B, int A, const char* str);
}

VOID drawItem(PVOID pawn, LPCSTR text, ImU32 color, bool noDistance) 
{
	auto root = GetPawnRootLocation(pawn);

	if (root) {
		auto pos = *root;
		float dx = CamLoc.x - pos.X;
		float dy = CamLoc.y - pos.Y;
		float dz = CamLoc.z - pos.Z;
		if (WorldToScreen(width, height, &pos.X)) 
		{
			float dist = spoof_call(game_rbx_jmp, sqrtf, dx * dx + dy * dy + dz * dz) / 100.0f;
			if (!noDistance) 
			{
				if (dist > Settings.OverallDistance)
					return;
			}

			CHAR modified[0xFF] = { 0 };
			snprintf(modified, sizeof(modified), skCrypt("%s %dm"), text, static_cast<INT>(dist));

			auto size = ImGui::GetFont()->CalcTextSizeA(ImGui::GetOverlayDrawList()->_Data->FontSize, FLT_MAX, 0, modified);
			ImGui::PushFontShadow(0xFF000000);
			ImGui::GetOverlayDrawList()->AddText(ImVec2(pos.X - size.x / 2.0f, pos.Y - size.y / 2.0f), color, modified);
			ImGui::PopFontShadow();
		}
	}
}


void WeakSpots() 
{
	if (weakspotPawns.empty())
		return;

	float closestDistance = FLT_MAX;

	auto weaponName = GetObjects::GetObjectFirstName((UObject*)LocalWeapon);
	auto isPickAxe = wcsstr(weaponName.c_str(), skCrypt(L"Pickaxe_"));

	for (auto pawn : weakspotPawns)
	{
		auto root = GetPawnRootLocation(pawn);

		if (root) {
			auto pos = *root;
			float dx = CamLoc.x - pos.X;
			float dy = CamLoc.y - pos.Y;
			float dz = CamLoc.z - pos.Z;

			if (WorldToScreen(width, height, &pos.X))
			{
				float dist = spoof_call(game_rbx_jmp, sqrtf, dx * dx + dy * dy + dz * dz) / 100.0f;
				if (dist < Settings.AimbotFOV && dist < closestDistance)
				{
					closestDistance = dist;
				}
				// draw weakspot
				std::string FullWeakSpot = skCrypt("WP");
				auto size = ImGui::GetFont()->CalcTextSizeA(ImGui::GetOverlayDrawList()->_Data->FontSize, FLT_MAX, 0, FullWeakSpot.c_str());
				ImGui::PushFontShadow(0xFF000000);
				ImGui::GetOverlayDrawList()->AddText(ImVec2(pos.X - size.x / 2.0f, pos.Y - size.y / 2.0f), ImGui::GetColorU32({ 255.f / 255.f, 0.f / 255.f, 0.f / 255.f, 1 }), FullWeakSpot.c_str());
				ImGui::PopFontShadow();
			}
		}
	}
}


int colorOrder = 1;
/*
int enemyID = 0;
int visEnemy = 0;*/


void PickupLoop()
{
	if (!Levels) return;

	//float boatDistanceMax = FLT_MAX;
	bool ingame = false;

	std::vector<PVOID> weakspotPawnsTemp;

	for (int i = 0; i < LevelsCount; i++) 
	{
		uint64_t Level = read<uint64_t>(Levels + (i * 8));
		if (Level == 0) continue;

		for (auto ai = 0UL; ai < read<DWORD>(Level + Offsets::AActors + sizeof(PVOID)); ++ai)
		{
			auto actors = ReadPointer(Level, Offsets::AActors);
			if (!actors) break;

			auto pawn = reinterpret_cast<UObject*>(ReadPointer(actors, ai * sizeof(PVOID)));
			if (!pawn || pawn == (PVOID)LocalPawn) continue;

			if (ingame == false)
				ingame = true;




			auto name = GetObjects::GetObjectFirstName(pawn);

			if (wcsstr(name.c_str(), skCrypt(L"FortPickupAthena")))
			{

				auto item = ReadPointer(pawn, Offsets::PrimaryPickupItemEntry + Offsets::ItemDefinition);
				if (!item) continue;

				auto itemName = reinterpret_cast<FText*>(ReadPointer(item, Offsets::DisplayName));
				if (!itemName || !itemName->c_str()) continue;

				auto isAmmo = wcsstr(itemName->c_str(), skCrypt(L"Ammo: "));
				auto itemTier = ReadBYTE(item, Offsets::Tier);
				if ((!Settings.ESP.Ammo && isAmmo) || ((!Settings.ESP.Weapons || itemTier < Settings.ESP.MinWeaponTier) && !isAmmo)) continue;

				CHAR text[0xFF] = { 0 };
				wcstombs(text, itemName->c_str() + (isAmmo ? 6 : 0), sizeof(text));

				drawItem(pawn, text, isAmmo ? ImGui::GetColorU32({ 0.75f, 0.75f, 0.75f, 1.0f }) : ImGui::GetColorU32(GetItemColor(itemTier)), false);
			}
			else if (Settings.ESP.Chests && wcsstr(name.c_str(), skCrypt(L"Tiered_Chest")) && !((ReadBYTE(pawn, Offsets::bAlreadySearched) >> 7) & 1))
			{
				drawItem(pawn, skCrypt("Chest"), ImGui::GetColorU32({ 1.0f, 0.84f, 0.0f, 1.0f }), false);
			}
			else if (Settings.ESP.Shark && wcsstr(name.c_str(), skCrypt(L"SpicySake_Parent_C"))) 
			{
				drawItem(pawn, skCrypt("Shark"), ImGui::GetColorU32({ 46 / 255.f, 78 / 255.f, 120 / 255.f, 1.0f }), false);
			}
			else if (Settings.ESP.Llama && wcsstr(name.c_str(), skCrypt(L"AthenaSupplyDrop_Llama"))) 
			{
				drawItem(pawn, skCrypt("Lama"), ImGui::GetColorU32({ 1.0f, 0.0f, 0.0f, 1.0f }), true);
			}
			else if (Settings.ESP.XPCoin && wcsstr(name.c_str(), skCrypt(L"QuestVisual_XPCoin_C")))
			{
				drawItem(pawn, skCrypt("Coin"), ImGui::GetColorU32({ 93 / 255.f, 253 / 255.f, 210 / 255.f, 1.0f }), true);
			}
			else if (Settings.ESP.SupplyDrop && wcsstr(name.c_str(), skCrypt(L"AthenaSupplyDrop_Donut"))) 
			{
				drawItem(pawn, skCrypt("Supply Drop"), ImGui::GetColorU32({ 255 / 255.f, 182 / 255.f, 193 / 255.f, 1.0f }), false);
			}
			else if (Settings.ESP.Boats && wcsstr(name.c_str(), skCrypt(L"MeatballVehicle_L"))) 
			{
				drawItem(pawn, skCrypt("Boat"), ImGui::GetColorU32({ 1.0f, 1.0f, 1.0f, 1.0f }), false);
				//if (Settings.ESP.Boats) {
					//drawItem(pawn, skCrypt("Boat"), ImGui::GetColorU32({ 1.0f, 1.0f, 1.0f, 1.0f }), false);
				//}
				//CheckClosestDistEntity(pawn, boatDistanceMax, 1); // 1: boat
			}
			else if (Settings.ESP.Helicopters && wcsstr(name.c_str(), skCrypt(L"HoagieVehicle_C"))) 
			{
				drawItem(pawn, skCrypt("Helicopter"), ImGui::GetColorU32({ 1.0f, 215 / 255.f, 0.f, 1.0f }), false);
			}
			else if (Settings.ESP.Cars && wcsstr(name.c_str(), skCrypt(L"Valet_BasicTruck_")))
			{
				drawItem(pawn, skCrypt("Basic Truck"), ImGui::GetColorU32({ 1.0f, 215 / 255.f, 0.f, 1.0f }), false);
			}
			else if (Settings.ESP.Cars && wcsstr(name.c_str(), skCrypt(L"Valet_BasicCar_"))) 
			{
				drawItem(pawn, skCrypt("Basic Car"), ImGui::GetColorU32({ 1.0f, 215 / 255.f, 0.f, 1.0f }), false);
			}
			else if (Settings.ESP.Cars && wcsstr(name.c_str(), skCrypt(L"Valet_SportsCar_"))) 
			{
				drawItem(pawn, skCrypt("Sports Car"), ImGui::GetColorU32({ 1.0f, 215 / 255.f, 0.f, 1.0f }), false);
			}
			else if (Settings.ESP.Cars && wcsstr(name.c_str(), skCrypt(L"Valet_BigRig_"))) 
			{
				drawItem(pawn, skCrypt("BigRig Truck"), ImGui::GetColorU32({ 1.0f, 215 / 255.f, 0.f, 1.0f }), false);
			}
			else if (Settings.ESP.Cars && wcsstr(name.c_str(), skCrypt(L"Valet_TaxiCab_"))) 
			{
				drawItem(pawn, skCrypt("Taxi"), ImGui::GetColorU32({ 1.0f, 0.84f, 0.0f, 1.0f }), false);
			}
			else if (Settings.ESP.AmmoBox && wcsstr(name.c_str(), skCrypt(L"Tiered_Ammo_Athena")) && !((ReadBYTE(pawn, Offsets::bAlreadySearched) >> 7) & 1))
			{
				drawItem(pawn, skCrypt("Ammo Box"), ImGui::GetColorU32({ 0.75f, 0.75f, 0.75f, 1.0f }), false);
			}
			else if (Settings.ESP.UpgradeBench && wcsstr(name.c_str(), skCrypt(L"B_Athena_Wumba")))
			{
				drawItem(pawn, skCrypt("Upgrade Bench"), ImGui::GetColorU32({ 63 / 255.f, 61 / 255.f, 22 / 255.f, 1.0f }), false);
			}
			else if (Settings.WeakSpot && wcsstr(name.c_str(), skCrypt(L"WeakSpot")))
			{
				auto root = GetPawnRootLocation(pawn);
				if (root) 
				{
					auto pos = *root;
					float dx = CamLoc.x - pos.X;
					float dy = CamLoc.y - pos.Y;
					float dz = CamLoc.z - pos.Z;
					if (WorldToScreen(width, height, &pos.X))
					{
						if (ReadDWORD(pawn, Offsets::bActive) != 0) 
						{
							weakspotPawnsTemp.clear();
							weakspotPawnsTemp.push_back(pawn);
						}
					}
				}
			}
			else if (Settings.Dev) 
			{
				CHAR text[0xFF] = { 0 };
				wcstombs(text, name.c_str(), sizeof(text));

				drawItem(pawn, text, ImGui::GetColorU32({ 1.0f, 0.84f, 0.0f, 1.0f }), false);
			}
		}
	}
	if (!weakspotPawnsTemp.empty()) 
	{
		weakspotPawns = weakspotPawnsTemp;
	}
}

void OnlyActorsLoop()
{
	if (!IsValid(LocalPawn) || !IsValid(LocalWeapon)) return;

	float FOVmax = 9999.f;
	float DistanceMax = 9999999999.f;

	int MyTeamID = 0;
	int TeamID = 1;

	
	if (Settings.ShowInfoBar) {
		ImGui::PushFontShadow(0xFF000000);
		CHAR distz[50];
		sprintf_s(distz, skCrypt("%d"), Settings.ESP.MinWeaponTier);
		std::string xx = skCrypt("[pgup/pgdown]: Loot: Tier: ");
		xx += distz;
		ImVec4 tierColor = GetItemColor(Settings.ESP.MinWeaponTier);
		utils::DrawNewText(95, 300, tierColor.x * 255, tierColor.y * 255, tierColor.z * 255, 255, xx.c_str());

		//CHAR dist[50];
		//sprintf_s(dist, skCrypt("%d"), Settings.OverallDistance);
		//std::string zz = skCrypt("Loot max distance: ");
		//zz += dist;
		//utils::DrawNewText(95, 310, 176, 181, 181, 255, zz.c_str());
		
		//CHAR dist[50];
		//sprintf_s(dist, skCrypt("%d"), Settings.OverallDistance);
		//std::string zz = skCrypt("Loot max distance: ");
		//zz += dist;
		//utils::DrawNewText(95, 310, 176, 181, 181, 255, zz.c_str());

		ImGui::PopFontShadow();
	}
	

	auto weaponName = GetObjects::GetObjectFirstName((UObject*)LocalWeapon);
	auto isPickAxe = wcsstr(weaponName.c_str(), skCrypt(L"Pickaxe_"));
	auto isBuildingTool = wcsstr(weaponName.c_str(), skCrypt(L"BuildingTool_"));
	auto isInBoat = wcsstr(weaponName.c_str(), skCrypt(L"B_Meatball_Launcher"));

	for (int i = 0; i < actor_count; i++)
	{
		uint64_t CurrentActor = read<uint64_t>(AActors + i * 0x8);
		if (!CurrentActor) continue;



		int curactorid = *(int*)(CurrentActor + 0x18);
		if (curactorid == 0) continue;

		float minX = FLT_MAX;
		float maxX = -FLT_MAX;
		float minY = FLT_MAX;
		float maxY = -FLT_MAX;

		//Enemy
		if (CurrentActor != LocalPawn && CurrentActor != Localplayer && CurrentActor != PlayerController)
		{
			auto name = GetObjects::GetObjectFirstName(reinterpret_cast<UObject*>(CurrentActor));

			if (wcsstr(name.c_str(), skCrypt(L"PlayerPawn_Athena_C"))
				|| wcsstr(name.c_str(), skCrypt(L"PlayerPawn_Athena_Phoebe_C"))
				|| (Settings.ESP.AgentsBoss && (wcsstr(name.c_str(), skCrypt(L"MangPlayerPawn_Default_C"))
				|| wcsstr(name.c_str(), skCrypt(L"MangPlayerPawn_Boss_"))
				|| wcsstr(name.c_str(), skCrypt(L"MangPlayerPawn_Default_Box"))
				|| wcsstr(name.c_str(), skCrypt(L"GibsonPlayerPawn_"))
				|| wcsstr(name.c_str(), skCrypt(L"PlayerPawn_")) ))) {

				uintptr_t MyPlayerState = read<uint64_t>(LocalPawn + Offsets::PlayerState);
				if (MyPlayerState) MyTeamID = *(int*)(MyPlayerState + Offsets::TeamIndex);

				uint8_t bIsDying = *(uint8_t*)(CurrentActor + Offsets::bIsDying);
				if (BIT_CHECK(bIsDying, 3)) continue;

				PVOID PlayerState = read<PVOID>(CurrentActor + Offsets::PlayerState);
				if (PlayerState) TeamID = *(int*)((uint64_t)PlayerState + Offsets::TeamIndex);

				if (TeamID != MyTeamID)
					radarPawns.push_back(CurrentActor);
				else
					continue;

				auto enemyTeamID = TeamID;
				if (Settings.ESP.Players)
				{
					//enemyID += 1;

					uint64_t currentactormesh = read<uint64_t>(CurrentActor + Offsets::Mesh);
					if (!currentactormesh) continue;

					Vector3 Headpos = GetBoneLocByIdx(currentactormesh, 66);

					if (Headpos.x == 0 && Headpos.y == 0) continue;

					Vector3 bone0 = GetBoneLocByIdx(currentactormesh, 0);

					Vector3 Headbox = Vector3(Headpos.x, Headpos.y, Headpos.z + 15);

					/*if (Settings.visCheck && IsTargetVisible(CurrentActor)) {
						visEnemy += 1;
					}*/

					if (WorldToScreen(width, height, &Headpos.x) && WorldToScreen(width, height, &bone0.x) && WorldToScreen(width, height, &Headbox.x)) {
						Vector3 HeadposW2s = Headpos;
						Vector3 bottom = bone0;

						if (HeadposW2s.x == 0 && HeadposW2s.y == 0) continue;
						if (bottom.x == 0 && bottom.y == 0) continue;
						if (Headbox.x == 0 && Headbox.y == 0) continue;

						if (Settings.visCheck)
						{
							if (Settings.ESP.Skeleton)
								DrawSkeleton(currentactormesh, IsTargetVisible(CurrentActor), minX, maxX, minY, maxY);
						}
						else if (Settings.ESP.Skeleton)
							DrawSkeleton(currentactormesh, true, minX, maxX, minY, maxY);

						auto color = ImGui::GetColorU32({ 200 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f });
						if (Settings.visCheck && IsTargetVisible(CurrentActor)) {
							//visibleEnemyAround += 1;
							color = ImGui::GetColorU32({ 0 / 255.f, 200 / 255.f, 0 / 255.f, 1.0f });
						}

						auto isDBNO = read<bool>(CurrentActor, Offsets::bIsDBNO);
						auto isDying = read<bool>(CurrentActor, Offsets::bIsDying);

						if (minX < width && maxX > 0 && minY < height && maxY > 0) {
							auto topLeft = ImVec2(minX - 3.0f, minY - 3.0f);
							auto bottomRight = ImVec2(maxX + 3.0f, maxY + 3.0f);


							auto centerTop = ImVec2((topLeft.x + bottomRight.x) / 2.0f + +10 + 1.65, topLeft.y);


							if (Settings.ESP.Distance || Settings.ESP.PlayerNames) {
								Vector3 posOfDoodoo = GetBoneLocByIdx(currentactormesh, 66);
								Vector3 VectorPos = posOfDoodoo - CamLoc;

								float dist = VectorPos.Length() / 100.f;
								CHAR modified[0xFF] = { 0 };

								if (Settings.ESP.Distance && Settings.ESP.PlayerNames)
									snprintf(modified, sizeof(modified), skCrypt("%dm"), static_cast<INT>(dist));
								else if (!Settings.ESP.Distance && Settings.ESP.PlayerNames)
									snprintf(modified, sizeof(modified), skCrypt("%dm"), static_cast<INT>(dist));
								else if (Settings.ESP.Distance && !Settings.ESP.PlayerNames)
									snprintf(modified, sizeof(modified), skCrypt("%dm"), static_cast<INT>(dist));

								auto size = ImGui::GetFont()->CalcTextSizeA(ImGui::GetOverlayDrawList()->_Data->FontSize, FLT_MAX, 0, modified);
								auto textLocation = ImVec2(((topLeft.x + bottomRight.x) / 2.0f) - size.x / 2.0f, centerTop.y - 20);

								ImGui::PushFontShadow(0xFF000000);
								utils::DrawNewText(textLocation.x, textLocation.y, 255, 255, 255, 255, modified);
								ImGui::PopFontShadow();
							}

							auto isBot = wcsstr(name.c_str(), skCrypt(L"PlayerPawn_Athena_Phoebe_C"));
							auto isMang = wcsstr(name.c_str(), skCrypt(L"MangPlayerPawn_Default_C"));
							auto isBoss = wcsstr(name.c_str(), skCrypt(L"MangPlayerPawn_Boss"));
							auto isMangBox = wcsstr(name.c_str(), skCrypt(L"MangPlayerPawn_Default_Box"));
							auto isMarauders = wcsstr(name.c_str(), skCrypt(L"GibsonPlayerPawn_"));
							auto isNewHenchmen = wcsstr(name.c_str(), skCrypt(L"GasketPlayerPawn_"));
							auto boxColor = ImGui::GetColorU32({ 255 / 255.f, 255 / 255.f, 255 / 255.f, 1.0f });

							if (Settings.ESP.Box)
							{
								ImGui::GetOverlayDrawList()->AddRect(topLeft, bottomRight, ImGui::GetColorU32({ 255.0f, 255.0f, 255.0f, 1.0f }));
							}

							if (isBot || isMarauders || isMangBox || isBoss || isMang || isNewHenchmen)
							{
								// 255, 170, 0
								boxColor = ImGui::GetColorU32({ 255 / 255.f, 170 / 255.f, 0 / 255.f, 1.0f });
							}
							else
							{
								if (IsTargetVisible(CurrentActor))
								{
									boxColor = ImGui::GetColorU32({ 255 / 255.f, 0 / 255.f, 0 / 255.f, 1.0f }); // visible - green
								}
							}



							if (Settings.ESP.ThreeDBox)
							{
								Draw3DBoundingBox(currentactormesh, CurrentActor, boxColor);
							}
							else
							{
								ImGui::GetOverlayDrawList()->AddRectFilled(topLeft, bottomRight, ImGui::GetColorU32({ 0.0f, 0.0f, 0.0f, 0.20f }));
							}


							if (Settings.ESP.CornerBox)
							{
								auto theAdditionY = (bottomRight.y - topLeft.y) / 3;
								auto theAdditionX = (bottomRight.x - topLeft.x) / 3;

								auto topRight = ImVec2(bottomRight.x, topLeft.y);

								auto bottomLeft = ImVec2(topLeft.x, bottomRight.y);

								ImGui::GetOverlayDrawList()->AddLine(topLeft, ImVec2(topLeft.x, topLeft.y + theAdditionY), boxColor, 2); // Top Left Y
								ImGui::GetOverlayDrawList()->AddLine(topLeft, ImVec2(topLeft.x + theAdditionX, topLeft.y), boxColor, 2); // Top Left X

								ImGui::GetOverlayDrawList()->AddLine(topRight, ImVec2(topRight.x, topRight.y + theAdditionY), boxColor, 2); // Top Right Y
								ImGui::GetOverlayDrawList()->AddLine(topRight, ImVec2(topRight.x - theAdditionX, topRight.y), boxColor, 2); // Top Right X

								ImGui::GetOverlayDrawList()->AddLine(bottomLeft, ImVec2(bottomLeft.x, bottomLeft.y - theAdditionY), boxColor, 2); // Bottom Left Y
								ImGui::GetOverlayDrawList()->AddLine(bottomLeft, ImVec2(bottomLeft.x + theAdditionX, bottomLeft.y), boxColor, 2); // Bottom Left X

								ImGui::GetOverlayDrawList()->AddLine(bottomRight, ImVec2(bottomRight.x, bottomRight.y - theAdditionY), boxColor, 2); // Bottom Right Y
								ImGui::GetOverlayDrawList()->AddLine(bottomRight, ImVec2(bottomRight.x - theAdditionX, bottomRight.y), boxColor, 2); // Bottom Right X
							}

							if (Settings.ESP.PlayerWeapons) 
							{
								auto curWeapon = ReadPointer(CurrentActor, Offsets::CurrentWeapon);
								if (curWeapon != nullptr)
								{
									auto itemDef = ReadPointer(curWeapon, Offsets::WeaponData);
									if (itemDef != nullptr) 
									{
										auto weaponName = reinterpret_cast<FText*>(ReadPointer(itemDef, Offsets::DisplayName));
										if (!weaponName || !weaponName->c_str()) continue;

										auto gunTier = ReadBYTE(itemDef, Offsets::Tier);

										CHAR text[0xFF] = { 0 };
										wcstombs(text, weaponName->c_str(), sizeof(text));

										CHAR modified[0xFF] = { 0 };
										CHAR rtext[0xFF] = { 0 };
										//snprintf(modified, sizeof(modified), skCrypt("%s"), text);
										//wcstombs(rtext, skCrypt_(L"Weapon Reloading.."), sizeof(rtext));

										//const wchar_t* rrr = skCrypt_(L"Weapon Reloading..");

										//auto isReloading = reinterpret_cast<bool*>(ReadPointer(curWeapon, Offsets::IsReloading));
										//
										//if (isReloading) {
										//	auto size = ImGui::GetFont()->CalcTextSizeA(ImGui::GetOverlayDrawList()->_Data->FontSize, FLT_MAX, 0, rtext);
										//
										//	ImGui::PushFontShadow(0xFF000000); 
										//	ImGui::GetOverlayDrawList()->AddText(ImVec2(((topLeft.x + bottomRight.x) / 2.0f) - size.x / 2.0f, bottomRight.y + 6), ImGui::GetColorU32(GetItemColor(9)), rtext);
										//	ImGui::PopFontShadow();
										//	}
										//else {
											auto size = ImGui::GetFont()->CalcTextSizeA(ImGui::GetOverlayDrawList()->_Data->FontSize, FLT_MAX, 0, modified);

										ImGui::PushFontShadow(0xFF000000);
											ImGui::GetOverlayDrawList()->AddText(ImVec2(((topLeft.x + bottomRight.x) / 2.0f) - size.x / 2.0f, bottomRight.y + 6), ImGui::GetColorU32(GetItemColor(gunTier)), modified);
											ImGui::PopFontShadow();
										//}
									}
								}
							}

							//if (Settings.ESP.PlayerNames) {
							//	if (isBot) {
							//		std::string copyyB = skCrypt("Bot");
							//		utils::DrawNewText(namePosX, namePosY, 255, 255, 255, 255, copyyB.c_str());
							//	}
							//	else if (isMang || isMangBox) {
							//		utils::DrawNewText(namePosX, namePosY, 17, 201, 53, 255, skCrypt("Agent"));
							//	}
							//	else if (isBoss) {
							//		utils::DrawNewText(namePosX, namePosY, 255, 215, 0, 255, skCrypt("[ BOSS ]"));
							//	}
							//	else if (isMarauders) {
							//		utils::DrawNewText(namePosX, namePosY, 255, 215, 0, 255, skCrypt("Marauders"));
							//	}
							//	else {
							//		wchar_t* playerName;
							//		//Internal::GetPlayerName(PlayerState, playerName);
							//		ProcessEvent(PlayerState, Offsets::PlayerState::GetPlayerName, &playerName, 0);
							//
							//		if (playerName) {
							//			CHAR copy[0xFF] = { 0 };
							//			wcstombs(copy, playerName, sizeof(copy));
							//			std::string copyy = copy;
							//			if (copyy.length() <= 1) {
							//				utils::DrawNewText(namePosX, namePosY, 255, 255, 255, 255, skCrypt("(Anonymous)"));
							//			}
							//			else {
							//				copyy = copyy.substr(0, 15);
							//				utils::DrawNewText(namePosX, namePosY, 255, 255, 255, 255, copyy.c_str());
							//			}
							//		}
							//	}
							//}
						}

						if (Settings.ESP.Lazer) DrawLaser(CurrentActor, currentactormesh, color);
						if (Settings.ESP.PlayerLines) ImGui::GetOverlayDrawList()->AddLine(ImVec2(X / 2, Y), ImVec2(bottom.x, bottom.y), color, Settings.SnaplinePower);
					}
				}
				if (!isBuildingTool) 
				{
					if ((Settings.Aimbot || Settings.SilentAimbot) && (TeamID != MyTeamID))
					{
						if (Settings.visCheck) 
						{
							if (IsTargetVisible(CurrentActor)) 
							{
								CheckClosestFOVEntity(CurrentActor, CamRot, FOVmax);
							}
						}
						else 
						{
							CheckClosestFOVEntity(CurrentActor, CamRot, FOVmax);
						}
					}
				}
			}
		}
	}


	if (!OldAimingActor && IsValid(entityx))
		if (GetAimKey())
			OldAimingActor = entityx;

	if (IsValid(OldAimingActor))
	{
		if (!read<uint64_t>(OldAimingActor + Offsets::RootComponent))
		{
			OldAimingActor = 0;
			return;
		}
		if (!read<uint64_t>(OldAimingActor + Offsets::PlayerState))
		{
			OldAimingActor = 0;
			return;
		}
		if (!read<uint64_t>(OldAimingActor + Offsets::Mesh))
		{
			OldAimingActor = 0;
			return;
		}
		uint8_t bIsDying = *(uint8_t*)(OldAimingActor + Offsets::bIsDying);
		if (BIT_CHECK(bIsDying, 3))
		{
			OldAimingActor = 0;
			return;
		}

		if (GetAimKey()) {
			entityx = OldAimingActor;
		}
		else
			OldAimingActor = NULL;
	}

	if (Settings.Dev) {
		CHAR text[0xFF] = { 0 };
		wcstombs(text, weaponName.c_str(), sizeof(text));

		CHAR modified[0xFF] = { 0 };
		snprintf(modified, sizeof(modified), skCrypt("[DEV] Curr Wep: %s"), text);

		ImGui::PushFontShadow(0xFF000000);
		ImGui::GetOverlayDrawList()->AddText(ImVec2(10, 10), ImGui::GetColorU32({ 1.0f, 0.84f, 0.0f, 1.0f }), modified);
		ImGui::PopFontShadow();
	}

	//if (Settings.WarningEnemiesArea && enemyID > 0) {
	//	std::string s = std::to_string(enemyID);
	//	std::string z = std::to_string(visEnemy);
	//	std::string a = s + skCrypt(" ENEMIES AROUND YOU!");
	//	std::string b = (skCrypt("(") + z + skCrypt(" VISIBLE)"));
	//	ImGui::PushFontShadow(0xFF000000);
	//	auto sizeA = ImGui::CalcTextSize(a.c_str());
	//	auto sizeB = ImGui::CalcTextSize(b.c_str());
	//	utils::DrawNewText((float)(width / 2) - (sizeA.x / 2), 100, 255, 0, 0, 255, a.c_str());
	//	utils::DrawNewText((float)(width / 2) - (sizeB.x / 2), 120, 128, 224, 0, 255, b.c_str());
	//	ImGui::PopFontShadow();
	//}

	/*if (enemyID != 0)
		enemyID = 0;

	if (visEnemy != 0)
		visEnemy = 0;*/
}

bool MainAddress() {

	if (!IsValid(OFFSET_UWORLD)) return false;

	Uworld = read<DWORD_PTR>(OFFSET_UWORLD);
	if (!Uworld) return false;
	if (!IsValid(Uworld))
	{ 
		Warn(skCrypt("Uworld failed!")); 
		return false; 
	}


	DWORD_PTR Gameinstance = read<DWORD_PTR>(Uworld + Offsets::OwningGameInstance);
	if (!Gameinstance) return false;
	if (!IsValid(Gameinstance)) 
	{ 
		Warn(skCrypt("Gameinstance failed!"));
		return false;
	}
	

	DWORD_PTR LocalPlayers = read<DWORD_PTR>(Gameinstance + Offsets::LocalPlayers);
	if (!LocalPlayers) return false;
	if (!IsValid(LocalPlayers)) 
	{ 
		Warn(skCrypt("LocalPlayers failed!"));
		return false; 
	}


	Localplayer = read<DWORD_PTR>(LocalPlayers);
	if (!Localplayer) return false;
	if (!IsValid(Localplayer)) { 
		Warn(skCrypt("Localplayer failed!"));
		return false;
	}




	PlayerController = read<DWORD_PTR>(Localplayer + Offsets::PlayerController);
	if (!PlayerController) return false;
	if (!IsValid(PlayerController))
	{ 
		Warn(skCrypt("PlayerController failed!"));
		return false; 
	}


	LocalPawn = read<uint64_t>(PlayerController + Offsets::AcknowledgedPawn);
	if (!LocalPawn) return false;
	if (!IsValid(LocalPawn)) {
		Warn(skCrypt("LocalPawn failed!")); return false; }


	LocalWeapon = read<uint64_t>(LocalPawn + Offsets::CurrentWeapon);
	if (!LocalWeapon) return false;
	if (!IsValid(LocalWeapon))
	{
		Warn(skCrypt("LocalWeapon failed!")); 
		return false;
	}


	PlayerCameraManager = read<uint64_t>(PlayerController + Offsets::PlayerCameraManager);
	if (!PlayerCameraManager) return false;
	if (!IsValid(PlayerCameraManager)) 
	{ 
		Warn(skCrypt("PlayerCameraManager failed!")); 
		return false;
	}


	Rootcomp = read<uint64_t>(LocalPawn + Offsets::RootComponent);
	if (!Rootcomp) return false;
	if (!IsValid(Rootcomp))
	{
		Warn(skCrypt("Rootcomp failed!")); 
		return false;
	}


	PawnMesh = read<uint64_t>(LocalPawn + Offsets::Mesh);
	if (!PawnMesh) return false;
	if (!IsValid(PawnMesh))
	{
		Warn(skCrypt("PawnMesh failed!")); 
		return false;
	}


	localPlayerState = read<uint64_t>(LocalPawn + 0x0240);
	if (!localPlayerState) return false;

	localPlayerTeamIndex = read<uint64_t>(localPlayerState + Offsets::TeamIndex);
	if (!PawnMesh) return false;

	localPlayerSquadID = read<uint64_t>(localPlayerState + Offsets::SquadID);
	if (!PawnMesh) return false;


	Levels = read<DWORD_PTR>(Uworld + Offsets::Levels);
	if (!Levels) return false;
	if (!IsValid(Levels)) {
 Warn(skCrypt("Levels failed!")); return false; }

	
	LevelsCount = read<DWORD_PTR>(Uworld + Offsets::Levels + 0x8);
	if (!LevelsCount) return false;
	//if (!IsValid(LevelsCount)) { Warn("LevelsCount failed!"); return false; }
	

	Ulevel = read<DWORD_PTR>(Uworld + Offsets::PersistentLevel);
	if (!Ulevel) return false;
	if (!IsValid(Ulevel)) {
 Warn(skCrypt("Ulevel failed!")); return false; }


	AActors = read<DWORD_PTR>(Ulevel + Offsets::AActors);
	actor_count = *(int*)(Ulevel + 0xA0);
	if (actor_count == 0) return false;

	if (!IsValid(AActors)) {
 Warn(skCrypt("AActors failed!")); return false; }
	//if (!IsValid(actor_count)) { Warn("actor_count failed!"); return false; }



	
	if (PlayerController && read<uintptr_t>(PlayerController))
	{
		if (bAimingLock) {
			struct {
				bool bNewLookInput;
			} params;
			params.bNewLookInput = 0;
			UEvent((PVOID)PlayerController, Offsets::SetIgnoreLookInput, &params, 0);
			bAimingLock = false;
		}	
	}
	uint8_t bIsDying = *(uint8_t*)(LocalPawn + Offsets::bIsDying);
	if (BIT_CHECK(bIsDying, 3))
	{
		LocalPawn = NULL;
		return false;
	}	
	return true;
}

void Crosshair(float X, float Y)
{
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2 - 11, height / 2), ImVec2(width / 2 - 2, height / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), 1.5f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2 + 11, height / 2), ImVec2(width / 2 + 3, height / 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), 1.5f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2, height / 2 - 11), ImVec2(width / 2, height / 2 - 2), ImGui::GetColorU32({ 255, 255, 255, 255 }), 1.5f);
	ImGui::GetOverlayDrawList()->AddLine(ImVec2(width / 2, height / 2 + 11), ImVec2(width / 2, height / 2 + 3), ImGui::GetColorU32({ 255, 255, 255, 255 }), 1.5f);
}

void RandomiseHit() {
	AimBoneInt == 0;
	AimBoneInt = 0;
	srand((unsigned)time(0));

	int ran = 1 + (rand() % 15);

	switch (ran) {
	case 1:
		//Aimbone head
		AimBoneInt == 66;
		AimBoneInt = 66;
		break;
	case 2:
		//aimbone body
		AimBoneInt == 7;
		AimBoneInt = 7;
		break;
	case 3:
		//aimbone legs
		AimBoneInt == 5;
		AimBoneInt = 5;
		break;
	case 4:
		//aimbone right hand
		AimBoneInt == 2;
		AimBoneInt = 2;
		break;
	}
}


PVOID FortUpdater::FindObject(const char* name)
{
	for (DWORD i = 0x0; i < this->ObjectsCount; i++)
	{
		auto CurrentObject = *(uintptr_t*)(this->UObjectArray + (i * 0x18));

		if (!CurrentObject) { return NULL; }
		//if (!(*(uintptr_t*)(CurrentObject + 0x50)) || *(DWORD*)(CurrentObject + 0x54) == 0xFFFFFFFF) continue;

		char* CurObjectName = this->fGetObjectName(CurrentObject);

		std::wcout << CurObjectName << std::endl;
	}

	//for (DWORD i = 0x0; i < this->ObjectsCount; i++)
	//{
	//	auto CurrentObject = *(uintptr_t*)(this->UObjectArray + (i * 0x18));
	//	if (!CurrentObject) { Warn(skCrypt("curobjnull")); return NULL; }
	//	auto Object = (UObject*)(CurrentObject);

	//	if (Object->ObjectFlags != 0x41) {
	//		continue;
	//	}
	//	//std::wcout << this->fGetObjectName(CurrentObject) << std::endl;
	//	//std::wcout << GetObjects::GetObjectFirstName(Object) << std::endl;
	//	MyFile << GetObjects::GetObjectFirstName(Object);
	//	MyFile << "\n";
	//}
	return 0;
}

float* CalculateShotHook(PVOID arg0, PVOID arg1, PVOID arg2) {
	auto ret = CalculateShot(arg0, arg1, arg2);
	if (ret && Settings.SilentAimbot && entityx && LocalPawn)
	{
		Vector3 SilentAimAngle = CalcAim();
		FVector head = FVector{ SilentAimAngle.x, SilentAimAngle.y, SilentAimAngle.z };

		auto rootPtr = GetPawnRootLocation((PVOID)LocalPawn);
		if (!rootPtr) return ret;
		auto root = *rootPtr;

		auto dx = head.X - root.X;
		auto dy = head.Y - root.Y;
		auto dz = head.Z - root.Z;
		if (dx * dx + dy * dy + dz * dz < 125000.0f) {
			ret[4] = head.X;
			ret[5] = head.Y;
			ret[6] = head.Z;
		}
		else {
			head.Z -= 16.0f;
			root.Z += 45.0f;

			auto y = atan2f(head.Y - root.Y, head.X - root.X);

			root.X += cosf(y + 1.5708f) * 32.0f;
			root.Y += sinf(y + 1.5708f) * 32.0f;

			auto length = spoof_call(game_rbx_jmp, sqrtf, powf(head.X - root.X, 2) + powf(head.Y - root.Y, 2));
			auto x = -atan2f(head.Z - root.Z, length);
			y = atan2f(head.Y - root.Y, head.X - root.X);

			x /= 2.0f;
			y /= 2.0f;

			ret[0] = -(sinf(x) * sinf(y));
			ret[1] = sinf(x) * cosf(y);
			ret[2] = cosf(x) * sinf(y);
			ret[3] = cosf(x) * cosf(y);
		}
	}

	return ret;
}