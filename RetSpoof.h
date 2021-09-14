#pragma once
#include "includes.h"

namespace Spoofer {
	namespace _SpoofCallInternal {
		extern "C" PVOID RetSpoofStub();

		template <typename Ret, typename... Args>
		inline Ret Wrapper(PVOID shell, Args... args) {
			auto fn = (Ret(*)(Args...))(shell);
			return fn(args...);
		}

		template <std::size_t Argc, typename>
		struct Remapper {
			template<typename Ret, typename First, typename Second, typename Third, typename Fourth, typename... Pack>
			static Ret Call(PVOID shell, PVOID shell_param, First first, Second second, Third third, Fourth fourth, Pack... pack) {
				return Wrapper<Ret, First, Second, Third, Fourth, PVOID, PVOID, Pack...>(shell, first, second, third, fourth, shell_param, nullptr, pack...);
			}
		};

		template <std::size_t Argc>
		struct Remapper<Argc, std::enable_if_t<Argc <= 4>> {
			template<typename Ret, typename First = PVOID, typename Second = PVOID, typename Third = PVOID, typename Fourth = PVOID>
			static Ret Call(PVOID shell, PVOID shell_param, First first = First{}, Second second = Second{}, Third third = Third{}, Fourth fourth = Fourth{}) {
				return Wrapper<Ret, First, Second, Third, Fourth, PVOID, PVOID>(shell, first, second, third, fourth, shell_param, nullptr);
			}
		};
	}

	template <typename Ret, typename... Args>
	Ret SpoofCall(Ret(*fn)(Args...), Args... args) {
		static PVOID trampoline = nullptr;
		if (!trampoline) {
			trampoline = Utilities::FindPattern(skCrypt("\xFF\x27"), skCrypt("xx"));
			if (!trampoline) {
				Warn(skCrypt("Failed to find valid trampoline"));
				ExitProcess(0);
			}
		}

		struct {
			PVOID Trampoline;
			PVOID Function;
			PVOID Reg;
		} params = {
			trampoline,
			reinterpret_cast<void*>(fn),
		};

		return _SpoofCallInternal::Remapper<sizeof...(Args), void>::template Call<Ret, Args...>(&_SpoofCallInternal::RetSpoofStub, &params, args...);
	}
}