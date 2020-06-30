#include "Bypass.hpp"

namespace Aeternum
{
	Bypass::Bypass()
	{
		auto ntdllStr = skCrypt("ntdll");
		HMODULE ntdll = GetModuleHandle(ntdllStr);
		ntdllStr.clear();
		if (ntdll != INVALID_HANDLE_VALUE)
		{
			auto NtCreateSectionStr = skCrypt("NtCreateSection");
			auto NtUnmapViewOfSectionStr = skCrypt("NtUnmapViewOfSection");
			auto NtMapViewOfSectionStr = skCrypt("NtMapViewOfSection");
			NtCreateSection = (NtCreateSection_t)GetProcAddress(ntdll, NtCreateSectionStr);
			NtUnmapViewOfSection = (NtUnmapViewOfSection_t)GetProcAddress(ntdll, NtUnmapViewOfSectionStr);
			NtMapViewOfSection = (NtMapViewOfSection_t)GetProcAddress(ntdll, NtMapViewOfSectionStr);
			NtCreateSectionStr.clear();
			NtUnmapViewOfSectionStr.clear();
			NtMapViewOfSectionStr.clear();
		}
	}

	void Bypass::RemovePeHeader(HMODULE hModule)
	{
		PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)hModule;
		PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)((PBYTE)pDosHeader + (DWORD)pDosHeader->e_lfanew);

		if (pNTHeader->Signature != IMAGE_NT_SIGNATURE)
		{
			auto errorStr = skCrypt("NT-Sig not found.");
			g_Logger->Error(errorStr);
			errorStr.clear();
			return;
		}

		if (pNTHeader->FileHeader.SizeOfOptionalHeader)
		{
			DWORD Protect;
			WORD Size = pNTHeader->FileHeader.SizeOfOptionalHeader;
			VirtualProtect((void*)hModule, Size, PAGE_EXECUTE_READWRITE, &Protect);
			SecureZeroMemory((void*)hModule, Size);
			VirtualProtect((void*)hModule, Size, Protect, &Protect);
			auto infoStr = skCrypt("Succeed in removing pe header.");
			g_Logger->Info(infoStr);
			infoStr.clear();
		}
	}

	void Bypass::RelinkModuleToPEB(HMODULE hModule)
	{
		std::vector<UNLINKED_MODULE>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));

		if (it == UnlinkedModules.end())
		{
			auto errorStr = skCrypt("Module hasn't been unlinked yet!");
			g_Logger->Error(errorStr);
			errorStr.clear();
			return;
		}

		RELINK((*it).Entry->InLoadOrderLinks, (*it).RealInLoadOrderLinks);
		RELINK((*it).Entry->InInitializationOrderLinks, (*it).RealInInitializationOrderLinks);
		RELINK((*it).Entry->InMemoryOrderLinks, (*it).RealInMemoryOrderLinks);
		UnlinkedModules.erase(it);

		auto infoStr = skCrypt("Succeed in relinking module.");
		g_Logger->Info(infoStr);
		infoStr.clear();
	}

	void Bypass::UnlinkModuleFromPEB(HMODULE hModule)
	{
		std::vector<UNLINKED_MODULE>::iterator it = std::find_if(UnlinkedModules.begin(), UnlinkedModules.end(), FindModuleHandle(hModule));
		if (it != UnlinkedModules.end())
		{
			auto errorStr = skCrypt("Module is already unlinked!");
			g_Logger->Error(errorStr);
			errorStr.clear();
			return;
		}

		PPEB pPEB = (PPEB)__readgsqword(0x60);

		PLIST_ENTRY CurrentEntry = pPEB->Ldr->InLoadOrderModuleList.Flink;
		PLDR_DATA_TABLE_ENTRY Current = NULL;

		while (CurrentEntry != &pPEB->Ldr->InLoadOrderModuleList && CurrentEntry != NULL)
		{
			Current = CONTAINING_RECORD(CurrentEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
			if (Current->DllBase == hModule)
			{
				UNLINKED_MODULE CurrentModule = { 0 };
				CurrentModule.hModule = hModule;
				CurrentModule.RealInLoadOrderLinks = Current->InLoadOrderLinks.Blink->Flink;
				CurrentModule.RealInInitializationOrderLinks = Current->InInitializationOrderLinks.Blink->Flink;
				CurrentModule.RealInMemoryOrderLinks = Current->InMemoryOrderLinks.Blink->Flink;
				CurrentModule.Entry = Current;
				UnlinkedModules.push_back(CurrentModule);

				UNLINK(Current->InLoadOrderLinks);
				UNLINK(Current->InInitializationOrderLinks);
				UNLINK(Current->InMemoryOrderLinks);

				auto infoStr = skCrypt("Succeed in unlinking module.");
				g_Logger->Info(infoStr);
				infoStr.clear();

				break;
			}

			CurrentEntry = CurrentEntry->Flink;
		}
	}

	BOOL Bypass::Remap(const char* Module)
	{
		HANDLE hSection = NULL;
		PVOID view_base = (PVOID)Aeternum::Module(Module).Base().As<uint64_t>();
		LARGE_INTEGER section_offset = {};
		LARGE_INTEGER sectionMaxSize = {};
		SIZE_T view_size = 0;

		MEMORY_BASIC_INFORMATION mbi;
		VirtualQuery((LPVOID)view_base, &mbi, sizeof(mbi));
		SIZE_T moduleSize = mbi.RegionSize;

		if (mbi.Protect == PAGE_EXECUTE_READWRITE)
		{
			auto infoStr = skCrypt("Module(%s) already remapped!");
			g_Logger->Info(infoStr, Module);
			infoStr.clear();
			return FALSE;
		}

		ThreadStuff(true);

		uint64_t buffer = (uint64_t)VirtualAlloc(NULL, moduleSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		auto infoStr = skCrypt("Remapping module(%s) : %I64x, %x");
		g_Logger->Info(infoStr, Module, view_base, moduleSize);
		infoStr.clear();

		memcpy((void*)buffer, view_base, moduleSize);

		sectionMaxSize.QuadPart = moduleSize;

		NTSTATUS status;
		status = NtCreateSection(&hSection, SECTION_ALL_ACCESS, NULL, &sectionMaxSize, PAGE_EXECUTE_READWRITE, SEC_COMMIT, NULL);
		if (NT_SUCCESS(status))
		{
			status = NtUnmapViewOfSection(GetCurrentProcess(), view_base);
			if (NT_SUCCESS(status))
			{
				status = NtMapViewOfSection(hSection, GetCurrentProcess(), &view_base, 0, moduleSize, &section_offset, &view_size, ViewUnmap, 0, PAGE_EXECUTE_READWRITE);
				if (NT_SUCCESS(status))
				{
					memcpy(view_base, (void*)buffer, moduleSize);
					VirtualFree((LPVOID)buffer, 0, MEM_RELEASE);
					ThreadStuff(false);
					auto infoStr = skCrypt("Succeed in remapping module(%s) : %I64x");
					g_Logger->Info(infoStr, Module, view_base);
					infoStr.clear();
					return TRUE;
				}
				else
				{
					auto errorStr = skCrypt("[M] An error occurred while remapping the module(%s) : %d");
					g_Logger->Error(errorStr, Module, status);
					errorStr.clear();
				}
			}
			else
			{
				auto errorStr = skCrypt("[UM] An error occurred while remapping the module(%s) : %d");
				g_Logger->Error(errorStr, Module, status);
				errorStr.clear();
			}
		}
		else
		{
			auto errorStr = skCrypt("[CS] An error occurred while remapping the module(%s) : %d");
			g_Logger->Error(errorStr, Module, status);
			errorStr.clear();
		}
		VirtualFree((LPVOID)buffer, moduleSize, MEM_RELEASE);
		ThreadStuff(false);
		return FALSE;
	}

	BOOL Bypass::DisableIntegrityChecks()
	{
		ThreadStuff(true);

		uint64_t fnIntegrityChecks = 0;

		auto infoStr = skCrypt("Disabling code integrity check routine.");
		g_Logger->Info(infoStr);
		infoStr.clear();

		int numIntegrityChecks = 0;

		//CENSORED

		ThreadStuff(false);
		return numIntegrityChecks ? TRUE : FALSE;
	}

	BOOL Bypass::DisableAngleIntegrityChecks()
	{
		ThreadStuff(true);

		uint64_t fnIntegrityChecks = 0;

		auto infoStr = skCrypt("Disabling angle integrity check routine.");
		g_Logger->Info(infoStr);
		infoStr.clear();

		int numIntegrityChecks = 0;

		//CENSORED

		ThreadStuff(false);
		return numIntegrityChecks ? TRUE : FALSE;
	}

	BOOL Bypass::BypassSS()
	{
		return SetWindowDisplayAffinity(g_GameVariables->m_GameWindow, WDA_MONITOR);
	}
}