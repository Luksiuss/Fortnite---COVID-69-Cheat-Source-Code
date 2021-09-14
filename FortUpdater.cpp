#include "FortUpdater.h"
#include "spoof_call.h"

template<class T>
struct TArray
{
	friend struct FString;

public:
	inline TArray()
	{
		Data = nullptr;
		Count = Max = 0;
	};

	inline int Num() const
	{
		return Count;
	};

	inline T& operator[](int i)
	{
		return Data[i];
	};

	inline const T& operator[](int i) const
	{
		return Data[i];
	};

	inline bool IsValidIndex(int i) const
	{
		return i < Num();
	}

private:
	T* Data;
	int Count;
	int Max;
};

class UObject {
public:
	PVOID VTableObject;
	DWORD ObjectFlags;
	DWORD InternalIndex;
	DWORD* Class;
	BYTE _padding_0[0x8];
	UObject* Outer;
};

struct FString : private TArray<wchar_t>
{
	inline FString()
	{
	};

	inline bool IsValid() const
	{
		return Data != nullptr;
	}

	inline const wchar_t* c_str() const
	{
		return Data;
	}

	std::string ToString() const
	{
		auto length = std::wcslen(Data);

		std::string str(length, '\0');

		std::use_facet<std::ctype<wchar_t>>(std::locale()).narrow(Data, Data + length, '?', &str[0]);

		return str;
	}
};

struct FName
{
	int32_t ComparisonIndex;
	int32_t Number;
};

bool FortUpdater::Init(uintptr_t UObjectArray, uintptr_t GetObjectName, uintptr_t GetNameByIndex, uintptr_t FnFree)
{
	if (!UObjectArray || !GetObjectName || !GetNameByIndex || !FnFree) return false;

	game_rbx_jmp = gadget(NULL);

	this->ObjectsCount = *(DWORD*)(UObjectArray + 0x14);
	if (this->ObjectsCount > 0x9000) this->ObjectsCount = 0x9000;

	uintptr_t deref_1 = *(uintptr_t*)UObjectArray;
	if (spoof_call(game_rbx_jmp, IsBadReadPtr, (const void*)deref_1, (UINT_PTR)8)) return false;

	uintptr_t deref_2 = *(uintptr_t*)deref_1;
	if (spoof_call(game_rbx_jmp, IsBadReadPtr, (const void*)deref_2, (UINT_PTR)8)) return false;

	this->UObjectArray = deref_2;
	this->GetObjectName = GetObjectName;
	this->GetNameByIndex = GetNameByIndex;
	this->FnFree = FnFree;

	return true;
}

/*DWORD FortUpdater::FindOffset(const char* Class, const char* varName)
{
	for (DWORD i = 0x0; i < 0x9000; i++)
	{
		auto CurrentObject = *(uintptr_t*)(this->UObjectArray + (i * 0x18));

		if (spoof_call(game_rbx_jmp, IsBadReadPtr, (const void*)CurrentObject, (UINT_PTR)8)) { MessageBoxA(0, "error1", 0, 0); return NULL; }
		if (spoof_call(game_rbx_jmp, IsBadReadPtr, (const void*)(*(uintptr_t*)(CurrentObject + 0x50)), (UINT_PTR)8)
			|| !(*(uintptr_t*)(CurrentObject + 0x50))
			|| *(DWORD*)(CurrentObject + 0x54) == 0xFFFFFFFF) {	MessageBoxA(0, "error1", 0, 0); continue;}

		char* CurObjectName = (char*)malloc(340);

		strcpy(CurObjectName, this->fGetObjectName(CurrentObject));

		if (!spoof_call(game_rbx_jmp, strcmp, (const char*)CurObjectName, Class)) //Same class
		{
			for (auto Property = *(uint64_t*)(CurrentObject + 0x50); Property >= 0x100000000; Property = *(uint64_t*)(Property + 0x20))
			{
				auto Type = *(uint64_t*)(Property + 0x8);

				if (!spoof_call(game_rbx_jmp, IsBadReadPtr, (const void*)CurrentObject, (UINT_PTR)8) && Type && Type >= 0x100000000)
				{
					auto Property_FName = *(FName*)(Property + 0x28);
					auto Offset = *(DWORD*)(Property + 0x4C);

					if (Offset != 0)
					{
						auto Property_idx = Property_FName.ComparisonIndex;

						if (Property_idx)
						{
							char* PropertyName = (char*)malloc(150);

							strcpy(PropertyName, this->fGetNameByIndex(Property_idx));

							if (!spoof_call(game_rbx_jmp, strcmp, (const char*)PropertyName, varName))
							{
								free(CurObjectName);
								free(PropertyName);
								return Offset;
							}

							free(PropertyName);
						}
					}
				}
				if (spoof_call(game_rbx_jmp, IsBadReadPtr, (const void*)(*(uint64_t*)(Property + 0x20)), (UINT_PTR)8) || *(uint64_t*)(Property + 0x20) == NULL)
				{
					free(CurObjectName);
					return NULL; //Return NULL if checked all properties of the class.
				}
			}

			free(CurObjectName);
			return NULL; //Return NULL if checked all properties of the class.
		}
		free(CurObjectName);
	}

	return NULL;
}*/

DWORD FortUpdater::FindOffset(const char* Class, const char* varName)
{
	for (DWORD i = 0x0; i < this->ObjectsCount; i++)
	{
		auto CurrentObject = *(uintptr_t*)(this->UObjectArray + (i * 0x18));

		if (!CurrentObject) {return NULL; }
		if (!(*(uintptr_t*)(CurrentObject + 0x50)) || *(DWORD*)(CurrentObject + 0x54) == 0xFFFFFFFF) continue;

		char* CurObjectName = this->fGetObjectName(CurrentObject);

		if (!strcmp(CurObjectName, Class)) //Same class
		{
			for (auto Property = *(uint64_t*)(CurrentObject + 0x50); !IsBadReadPtr((void*)Property, 8); Property = *(uint64_t*)(Property + 0x20))
			{
				auto Type = *(uint64_t*)(Property + 0x8);

				if (!IsBadReadPtr((void*)Type, 8) && Type)
				{
					auto Property_FName = *(FName*)(Property + 0x28);
					auto Offset = *(DWORD*)(Property + 0x4C);

					if (Offset != 0)
					{
						auto Property_idx = Property_FName.ComparisonIndex;

						if (Property_idx)
						{
							char* PropertyName = this->fGetNameByIndex(Property_idx);

							if (!strcmp(PropertyName, varName))
							{
								return Offset;
							}
						}
					}
				}

			}

			return NULL; //Return NULL if checked all properties of the class.
		}
	}
}

void FortUpdater::cFixName(char* Name)
{
	for (int i = 0; Name[i] != '\0'; i++)
	{
		if (Name[i] == '_')
		{
			if (Name[i + 1] == '0' ||
				Name[i + 1] == '1' ||
				Name[i + 1] == '2' ||
				Name[i + 1] == '3' ||
				Name[i + 1] == '4' ||
				Name[i + 1] == '5' ||
				Name[i + 1] == '6' ||
				Name[i + 1] == '7' ||
				Name[i + 1] == '8' ||
				Name[i + 1] == '9')
				Name[i] = '\0';
		}
	}

	return;
}

void FortUpdater::FreeObjName(uintptr_t Address)
{
	if (Address == NULL) return;

	auto func = reinterpret_cast<__int64(__fastcall*)(__int64)>(this->FnFree);

	spoof_call(game_rbx_jmp, func, (__int64)Address);
}

char* FortUpdater::fGetObjectName(uintptr_t Object)
{
	if (Object == NULL) return (char*)"";

	auto fGetObjName = reinterpret_cast<FString * (__fastcall*)(FString*, uintptr_t)>(this->GetObjectName);

	FString result;
	spoof_call(game_rbx_jmp, fGetObjName, &result, Object);

	if (result.c_str() == NULL) return (char*)"";

	auto tmp = result.ToString();

	char return_string[1024];
	spoof_call(game_rbx_jmp, memcpy, (void*)return_string, (const void*)std::string(tmp.begin(), tmp.end()).c_str(), (size_t)1024);

	this->FreeObjName((uintptr_t)result.c_str());

	cFixName(return_string);

	return return_string;
}

char* FortUpdater::fGetNameByIndex(int Index)
{
	if (Index == 0) return (char*)"";

	auto fGetNameByIdx = reinterpret_cast<FString * (__fastcall*)(int*, FString*)>(this->GetNameByIndex);

	FString result;
	spoof_call(game_rbx_jmp, fGetNameByIdx, &Index, &result);

	if (result.c_str() == NULL) return (char*)"";

	auto tmp = result.ToString();

	char return_string[1024];
	spoof_call(game_rbx_jmp, memcpy, (void*)return_string, (const void*)std::string(tmp.begin(), tmp.end()).c_str(), (size_t)1024);

	FreeObjName((uintptr_t)result.c_str());

	cFixName(return_string);

	return return_string;
}