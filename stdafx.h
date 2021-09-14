#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <psapi.h>
#include <intrin.h>
#include "Offsets.h"
#include <string>
#include <vector>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "Utilities.h"
#include <fstream>

template<typename T>
T ReadMemory(DWORD_PTR address, const T& def = T())
{
	return *(T*)address;
}
