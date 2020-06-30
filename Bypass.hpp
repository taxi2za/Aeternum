#pragma once
#include "Memory.hpp"

#define UNLINK(x)					\
	(x).Flink->Blink = (x).Blink;	\
	(x).Blink->Flink = (x).Flink;

#define RELINK(x, real)			\
	(x).Flink->Blink = (real);	\
	(x).Blink->Flink = (real);	\
	(real)->Blink = (x).Blink;	\
	(real)->Flink = (x).Flink;

namespace Aeternum
{
	class Bypass
	{
	public:
		explicit Bypass();
		~Bypass() noexcept = default;

		Bypass(Bypass const&) = delete;
		Bypass(Bypass&&) = delete;
		Bypass& operator=(Bypass const&) = delete;
		Bypass& operator=(Bypass&&) = delete;

		/**
		 * \brief Remove PE header
		 * \param Module handle
		 */
		void RemovePeHeader(HMODULE hModule);

		/**
		 * \brief Relink module
		 * \param Module handle
		 */
		void RelinkModuleToPEB(HMODULE hModule);

		/**
		 * \brief Unlink module
		 * \param Module handle
		 */
		void UnlinkModuleFromPEB(HMODULE hModule);

		/**
		 * \brief Remap module
		 * \param Module name
		 */
		BOOL Remap(const char* Module);

		/**
		 * \brief Disabling code integrity checks
		 */
		BOOL DisableIntegrityChecks();

		/**
		 * \brief Disabling Angle integrity checks
		 */
		BOOL DisableAngleIntegrityChecks();

		/**
		 * \brief Bypass screenshot checks
		 */
		BOOL BypassSS();
	private:
		typedef struct _PEB_LDR_DATA {
			UINT8 _PADDING_[12];
			LIST_ENTRY InLoadOrderModuleList;
			LIST_ENTRY InMemoryOrderModuleList;
			LIST_ENTRY InInitializationOrderModuleList;
		} PEB_LDR_DATA, * PPEB_LDR_DATA;

		typedef struct _PEB {
			UINT8 _PADDING_[24];
			PEB_LDR_DATA* Ldr;
		} PEB, * PPEB;

		typedef struct _LDR_DATA_TABLE_ENTRY {
			LIST_ENTRY InLoadOrderLinks;
			LIST_ENTRY InMemoryOrderLinks;
			LIST_ENTRY InInitializationOrderLinks;
			VOID* DllBase;
		} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

		typedef struct _UNLINKED_MODULE
		{
			HMODULE hModule;
			PLIST_ENTRY RealInLoadOrderLinks;
			PLIST_ENTRY RealInMemoryOrderLinks;
			PLIST_ENTRY RealInInitializationOrderLinks;
			PLDR_DATA_TABLE_ENTRY Entry;
		} UNLINKED_MODULE;

		std::vector<UNLINKED_MODULE> UnlinkedModules;

		struct FindModuleHandle
		{
			HMODULE m_hModule;
			FindModuleHandle(HMODULE hModule) : m_hModule(hModule)
			{
			}
			bool operator() (UNLINKED_MODULE const& Module) const
			{
				return (Module.hModule == m_hModule);
			}
		};

		typedef enum _SECTION_INHERIT
		{
			ViewUnmap = 2
		} SECTION_INHERIT;

		typedef NTSTATUS(NTAPI* NtCreateSection_t)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES, PLARGE_INTEGER, ULONG, ULONG, HANDLE);
		typedef NTSTATUS(NTAPI* NtUnmapViewOfSection_t)(HANDLE, PVOID);
		typedef NTSTATUS(NTAPI* NtMapViewOfSection_t)(HANDLE, HANDLE, PVOID*, ULONG_PTR, SIZE_T, PLARGE_INTEGER, PSIZE_T, SECTION_INHERIT, ULONG, ULONG);
		NtCreateSection_t NtCreateSection;
		NtUnmapViewOfSection_t NtUnmapViewOfSection;
		NtMapViewOfSection_t NtMapViewOfSection;

		void ThreadStuff(BOOL bSuspend)
		{
			HANDLE hThreadSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

			THREADENTRY32 threadEntry;
			threadEntry.dwSize = sizeof(THREADENTRY32);

			Thread32First(hThreadSnapshot, &threadEntry);
			do
			{
				if (threadEntry.th32OwnerProcessID == GetCurrentProcessId() && threadEntry.th32ThreadID != GetCurrentThreadId())
				{
					HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, threadEntry.th32ThreadID);
					bSuspend ? SuspendThread(hThread) : ResumeThread(hThread);
					CloseHandle(hThread);
				}
			} while (Thread32Next(hThreadSnapshot, &threadEntry));

			CloseHandle(hThreadSnapshot);
		}
	};

	inline std::unique_ptr<Bypass> g_Bypass;
}
