#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define _WIN32_WINNT _WIN32_WINNT_WIN7
#include <winsdkver.h>
#include <sdkddkver.h>
#include <windows.h>
#include <windowsx.h>
#include <winternl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <Psapi.h>
#include <TlHelp32.h>

#include <cassert>
#include <cinttypes>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <algorithm>
#include <atomic>
#include <bitset>
#include <chrono>
#include <deque>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <optional>
#include <sstream>
#include <stack>
#include <string>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <vector>

#define AETERNUM_WIDE_IMPL(str) L ## str
#define AETERNUM_WIDE(str) AETERNUM_WIDE_IMPL(str)

#define AETERNUM_STRINGIZE_IMPL(x) #x
#define AETERNUM_STRINGIZE(x) AETERNUM_STRINGIZE_IMPL(x)

#define AETERNUM_NAME skCrypt("Aeternum")
#define AETERNUM_CENSOR TRUE

namespace Aeternum
{
	using namespace std::chrono_literals;
	using namespace DirectX;
	using namespace DirectX::PackedVector;
	namespace fs = std::filesystem;

	inline HMODULE g_Module{};
	inline uint64_t g_ptrUsername{};
	inline std::string g_Username{};
	inline time_t g_Expire{};
	inline uint64_t g_Data{};
	inline std::atomic_bool g_Running = true;

	inline UINT g_Width{}, g_Height{};

	template<typename T> inline T RPM(uint64_t lpBaseAddress)
	{
		__try
		{
			T A{};
			A = *(T*)(lpBaseAddress);
			return A;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return T{};
		}
	}

	template<typename T> inline void WPM(uint64_t lpBaseAddress, T Val)
	{
		__try
		{
			*(T*)(lpBaseAddress) = Val;
			return;
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
		}
	}

	static uint64_t dwGameBase = (uint64_t)GetModuleHandle(NULL);
	static uint64_t m_retSpoof{};
}

#include <License/crypto/skCrypter.h>
#include "Spoof.h"
#include "Config.hpp"
#include "Logger.hpp"
#include "Util.hpp"
#include "Memory.hpp"
#include "Game.hpp"
#include "Timer.hpp"
#include "Types.hpp"