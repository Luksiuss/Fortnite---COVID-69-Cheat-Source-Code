#include "includes.h"
#include "MatrixStructs.h"
#include "Major.h"
#include "DrawMenu.h"
#include "MainHooking.h"

ImVec4 backgroundColorRGB = ImVec4(23, 23, 23, 255);
ImVec4 innerColorRGB = ImVec4(0, 167, 245, 255);

ImVec4 backgroundColor = ImVec4(backgroundColorRGB.x / 255.f, backgroundColorRGB.y / 255.f, backgroundColorRGB.z / 255.f, backgroundColorRGB.w / 255.f);
ImVec4 innerColor = ImVec4(innerColorRGB.x / 255.f, innerColorRGB.y / 255.f, innerColorRGB.z / 255.f, innerColorRGB.w / 255.f);
ImVec4 textColor = ImVec4(151, 244, 247, 255);

bool first = false;
void MainTick()
{
	RadarLoop();
	if (!first) {
		X = (float)spoof_call(game_rbx_jmp, GetSystemMetrics, SM_CXSCREEN);
		Y = (float)spoof_call(game_rbx_jmp, GetSystemMetrics, SM_CYSCREEN);
		width = (float)spoof_call(game_rbx_jmp, GetSystemMetrics, SM_CXSCREEN); // width
		height = (float)spoof_call(game_rbx_jmp, GetSystemMetrics, SM_CYSCREEN); // height
		first = true;
	}

	entityx = 0;
	bool bUpdated = MainAddress();
	if (bUpdated)
	{
		if (Settings.ESP.RandomAim) { RandomiseHit(); }
		if (!LocalPawn) return;
		if (Settings.Aimbot || Settings.SilentAimbot || Settings.ESP.Players) OnlyActorsLoop();
		if (Settings.ESP.Players) PickupLoop();
		if (Settings.WeakSpot) WeakSpots();
		if (Settings.Aimbot) if (GetAimKey()) DoMemoryAimbot();
		if (Settings.MouseAim) if (GetAimKey()) DoMouseAim();
		if (Settings.ESP.AimLine) DrawAimingEnemy();
	}
	
	if (Settings.Crosshair) Crosshair(width, height);
	if (Settings.ESP.AimbotFOV) {
		float Radius = (Settings.AimbotFOV * X / GlobalFOV) / 2;
		if (Settings.isRecFov) {
			utils::DrawLine((float)(width / 2) - Radius, (float)(height / 2) - Radius, (float)(width / 2) + Radius, (float)(height / 2) - Radius, 255, 255, 255, 255, 1);
			utils::DrawLine((float)(width / 2) - Radius, (float)(height / 2) + Radius, (float)(width / 2) + Radius, (float)(height / 2) + Radius, 255, 255, 255, 255, 1);
			utils::DrawLine((float)(width / 2) + Radius, (float)(height / 2) - Radius, (float)(width / 2) + Radius, (float)(height / 2) + Radius, 255, 255, 255, 255, 1);
			utils::DrawLine((float)(width / 2) - Radius, (float)(height / 2) - Radius, (float)(width / 2) - Radius, (float)(height / 2) + Radius, 255, 255, 255, 255, 1);
		}
		else
			ImGui::GetOverlayDrawList()->AddCircle(ImVec2(width / 2, height / 2), Radius, ImGui::GetColorU32({ 1.0f, 1.0f, 1.0f, 1.0f }), 32);
	}
	if (!bUpdated) { 
		entityx = 0;
		return;
	}else {
		if (entityx) {
			if (!read<uint64_t>(entityx + Offsets::RootComponent)) { entityx = 0; return; }
			if (!read<uint64_t>(entityx + Offsets::PlayerState)) { entityx = 0; return; }
			if (!read<uint64_t>(entityx + Offsets::Mesh)) { entityx = 0; return; }
			uint8_t bIsDying = *(uint8_t*)(entityx + Offsets::bIsDying);
			if (BIT_CHECK(bIsDying, 3)) { entityx = 0; return; }
		}
		RadarLoop();
	}
	if (!radarPawns.empty())
		radarPawns.clear();

	if (!weakspotPawns.empty())
		weakspotPawns.clear();

	//if (TargetBoat)
	//	TargetBoat = nullptr;
}



BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved) {
	HANDLE m_timer;
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(module);
	
		SettingsHelper::Initialize();
		Main();
		
		DYNAMIC_FUNCTION(CreateTimerQueueTimer,
			skCrypt("KERNEL32.DLL"))(&m_timer, DYNAMIC_FUNCTION(CreateTimerQueue,
				skCrypt("KERNEL32.DLL"))(),
				reinterpret_cast<WAITORTIMERCALLBACK>(&Renderintial), nullptr, 1, NULL, NULL);
	}

	return TRUE;
}