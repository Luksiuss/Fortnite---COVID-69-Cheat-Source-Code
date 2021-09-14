#pragma once
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#include "stdafx.h"
#include <iostream>
#include <array>
#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <vector>
#include <WinUser.h>
#include <WinDNS.h>
#include <strsafe.h>
#include <windows.h>
#include <d3dcommon.h>
#include <intsafe.h>

template <typename T>
T DynamicImport(const std::string& functionName, const std::string& dllName)
{
	HMODULE dll_handle = ::GetModuleHandleA(dllName.c_str());
	if (dll_handle == nullptr)
	{
		dll_handle = ::LoadLibraryA(dllName.c_str());
		if (dll_handle == nullptr)
		{
			return nullptr;
		}
	}
	return reinterpret_cast<T>(GetProcAddress(dll_handle, functionName.c_str()));
}

#define DYNAMIC_FUNCTION(x, y) DynamicImport<std::decay_t<decltype(x)>>(#x, y)