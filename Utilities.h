#pragma once
#include "stdafx.h"
#define PI (3.141592653589793f)
#define RELATIVE_ADDR(addr, size) ((PBYTE)((UINT_PTR)(addr) + *(PINT)((UINT_PTR)(addr) + ((size) - sizeof(INT))) + (size)))

#define ReadPointer(base, offset) (*(PVOID *)(((PBYTE)base + offset)))
#define ReadDWORD(base, offset) (*(PDWORD)(((PBYTE)base + offset)))
#define ReadBYTE(base, offset) (*(((PBYTE)base + offset)))

namespace Utilities {
	VOID CreateConsole();
	PBYTE FindPattern(LPCSTR pattern, LPCSTR mask);
	typedef struct {
		float X, Y, Z;
	} FVectorGert;
	FVectorGert* GetPawnRootLocation(PVOID pawn);
}