#pragma once

namespace Aeternum
{
	extern "C" void* _spoofer_stub();
	extern "C" void* _get_rsi();

	static void get_retaddr()
	{
		const auto ntdll = reinterpret_cast<const unsigned char*>(GetModuleHandle(NULL));
		const auto dos = reinterpret_cast<const IMAGE_DOS_HEADER*>(ntdll);
		const auto nt = reinterpret_cast<const IMAGE_NT_HEADERS*>(ntdll + dos->e_lfanew);
		const auto sections = IMAGE_FIRST_SECTION(nt);
		const auto num_sections = nt->FileHeader.NumberOfSections;

		constexpr char section_name[5]{ '.', 't', 'e', 'x', 't' };
		const auto     section = std::find_if(sections, sections + num_sections, [&](const auto& s) {
			return std::equal(s.Name, s.Name + 5, section_name);
			});

		constexpr unsigned char instr_bytes[2]{ 0xFF, 0x23 };
		const auto              va = ntdll + section->VirtualAddress;
		m_retSpoof = (uint64_t)std::search(va, va + section->Misc.VirtualSize, instr_bytes, instr_bytes + 2);
	}

	template <typename Ret, typename... Args>
	static inline auto shellcode_stub_helper(
		const void* shell,
		Args... args
	) -> Ret
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct argument_remapper
	{
		// At least 5 params
		template<
			typename Ret,
			typename First,
			typename Second,
			typename Third,
			typename Fourth,
			typename... Pack
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first,
				Second second,
				Third third,
				Fourth fourth,
				Pack... pack
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*,
				Pack...
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr,
				pack...
				);
		}
	};

	template <std::size_t Argc>
	struct argument_remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<
			typename Ret,
			typename First = void*,
			typename Second = void*,
			typename Third = void*,
			typename Fourth = void*
		>
			static auto do_call(
				const void* shell,
				void* shell_param,
				First first = First{},
				Second second = Second{},
				Third third = Third{},
				Fourth fourth = Fourth{}
			) -> Ret
		{
			return shellcode_stub_helper<
				Ret,
				First,
				Second,
				Third,
				Fourth,
				void*,
				void*
			>(
				shell,
				first,
				second,
				third,
				fourth,
				shell_param,
				nullptr
				);
		}
	};

	template <typename Ret, typename... Args>
	static inline auto spoof_call(
		Ret(*fn)(Args...),
		Args... args
	) -> Ret
	{
		struct shell_params
		{
			const void* trampoline;
			void* function;
			void* rbx;
		};

		if (!m_retSpoof)
			get_retaddr();

		WPM<BYTE>(m_retSpoof - 0x5, 0xE8);

		shell_params p{ (void*)m_retSpoof, reinterpret_cast<void*>(fn) };
		using mapper = argument_remapper<sizeof...(Args), void>;
		return mapper::template do_call<Ret, Args...>((const void*)&_spoofer_stub, &p, args...);
	}

	static HANDLE WINAPI SpoofedCreateThread(_In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes, _In_ SIZE_T dwStackSize, _In_ LPTHREAD_START_ROUTINE lpStartAddress, _In_opt_ __drv_aliasesMem LPVOID lpParameter, _In_ DWORD dwCreationFlags, _Out_opt_ LPDWORD lpThreadId)
	{
		return spoof_call(&CreateThread, lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
	}
}