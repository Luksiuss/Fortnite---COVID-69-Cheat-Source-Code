#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define COBJMACROS
#define WIN32_LEAN_AND_MEAN
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_INDEX_BUFFER 128 * 1024
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_D3D11_IMPLEMENTATION
#define NK_IMPLEMENTATION
#define skCrypt(str) _xor_(str).c_str()
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))
#define MAKE_IMU32(r, g, b, a) ((a << 24) + (b << 16) + (g << 8) + r)

// ITEM ESP
#define ITEM_COLOR_TIER_WHITE ImVec4{ 0.8f, 0.8f, 0.8f, 0.95f }
#define ITEM_COLOR_TIER_GREEN ImVec4{ 0.0f, 0.95f, 0.0f, 0.95f }
#define ITEM_COLOR_TIER_BLUE ImVec4{ 0.2f, 0.4f, 1.0f, 0.95f }
#define ITEM_COLOR_TIER_PURPLE ImVec4{ 0.7f, 0.25f, 0.85f, 0.95f }
#define ITEM_COLOR_TIER_ORANGE ImVec4{ 0.85f, 0.65f, 0.0f, 0.95f }
#define ITEM_COLOR_TIER_GOLD ImVec4{ 0.95f, 0.85f, 0.45f, 0.95f }
#define ITEM_COLOR_TIER_UNKNOWN ImVec4{ 1.0f, 0.0f, 1.0f, 0.95f }
#define ITEM_COLOR_MEDS ImVec4{ 0.9f, 0.55f, 0.55f, 0.95f }
#define ITEM_COLOR_SHIELDPOTION ImVec4{ 0.35f, 0.55f, 0.85f, 0.95f }
#define ITEM_COLOR_CHEST ImVec4{0.95f, 0.95f, 0.0f, 0.95f}
#define ITEM_COLOR_SUPPLYDROP ImVec4{ 0.9f, 0.1f, 0.1f, 0.9f }

#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#include "xorstr.hpp"
#include <math.h>
#include "Structs.h"
#include <codecvt>
#include <Psapi.h>
#include <list>
#include "spoof_call.h"
#include "lazyimporter.h"
#include "memory.h"
#include "Offsets.h"
#include "MainOptions.h"
#include "FortUpdater.h"
#include "Helper.h"
#include "CheatHelper.h"
#include "Exploits.h"
#include "Renderer/imgui.h"
#include "Renderer/imgui_impl_dx11.h"
#include "Renderer/imgui.h"
#include "Renderer/imgui_internal.h"
#include "Renderer/color.h"
#include "Vectors.h"
#include "dynamicimports.h"

#include "MinHook.h"
#pragma comment(lib, "minhook.lib")





std::string Warn(std::string warningText) {
    Spoofer::SpoofCall(MessageBoxA, (HWND)0, (LPCSTR)(warningText.c_str()), (LPCSTR)skCrypt("Warning"), (UINT)0);
}

std::vector<uint64_t> radarPawns;
/*
int enemyAroundYou = 0;
int visibleEnemyAround = 0;*/

// isAdministrator: 0 = Regular User
// isAdministrator: 1 = Administrator
int isAdministrator = 0;

namespace Explotsw {
	typedef struct {
		float Pitch;
		float Yaw;
		float Roll;
	} FRotator2323;
	typedef struct {
		float X, Y, Z;
	} FVector2;
	typedef struct {
		FVector2 Location;
		FRotator2323 Rotation;
		float FOV;
		float OrthoWidth;
		float OrthoNearClipPlane;
		float OrthoFarClipPlane;
		float AspectRatio;
	} FMinimalViewInfo2323;

	struct {
		FMinimalViewInfo2323 Info;
		float ProjectionMatrix[4][4];
	} view = { 0 };

	FMinimalViewInfo2323& GetViewInfo() {
		return view.Info;
	}

	FVector2* GetPawnRootLocation(PVOID pawn) {
		auto root = ReadPointer(pawn, Offsets::RootComponent);
		if (!root) {
			return nullptr;
		}

		return reinterpret_cast<FVector2*>(reinterpret_cast<PBYTE>(root) + Offsets::RelativeLocation);
	}
}