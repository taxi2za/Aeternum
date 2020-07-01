#include "Common.hpp"
#include "Hooking.hpp"
#include "Bypass.hpp"
#include "D3DRenderer.hpp"
#include "Core.hpp"
#include <License/License.hpp>
#include <VMProtectSDK.h>

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

void MainThread()
{
	VMProtectBeginUltra("MainThread");
	using namespace Aeternum;

	g_Logger = std::make_unique<Logger>();
	auto injectStr = skCrypt("Aeternum injected.");
	g_Logger->Info(injectStr);
	injectStr.clear();

	g_Username = std::string(reinterpret_cast<const char*>((uint64_t)g_ptrUsername + 8), *reinterpret_cast<size_t*>((uint64_t)g_ptrUsername));
	auto licenseStr = skCrypt("Checking license via account - %s");
	g_Logger->Info(licenseStr, g_Username);
	licenseStr.clear();
	g_Expire = License::License::GetExpireOW(g_Username);
	g_Data = License::License::GetDataOW(g_Username);

	if (g_Expire && g_Data)
	{
		g_Config = std::make_unique<Config>();
		auto configStr = skCrypt("g_Config Initialized.");
		g_Logger->Info(configStr);
		configStr.clear();

		g_GameVariables = std::make_unique<GameVariables>();
		auto varStr = skCrypt("g_GameVariables Initialized.");
		g_Logger->Info(varStr);
		varStr.clear();
		g_GameFunctions = std::make_unique<GameFunctions>();
		auto funcStr = skCrypt("g_GameFunctions Initialized.");
		g_Logger->Info(funcStr);
		funcStr.clear();

		g_Bypass = std::make_unique<Bypass>();
		g_Bypass->RemovePeHeader(g_Module);
		auto moduleStr = skCrypt(CENSORED);
		g_Bypass->Remap(moduleStr);
		moduleStr.clear();
		g_Bypass->DisableIntegrityChecks();
		g_Bypass->DisableAngleIntegrityChecks();
		g_Bypass->BypassSS();

		g_D3DRenderer = std::make_unique<D3DRenderer>();
		auto rendererStr = skCrypt("g_D3DRenderer Initialized.");
		g_Logger->Info(rendererStr);
		rendererStr.clear();

		g_Core = std::make_unique<Core>();
		auto coreStr = skCrypt("g_Core Initialized.");
		g_Logger->Info(coreStr);
		coreStr.clear();

		g_Hooking = std::make_unique<Hooking>();
		auto hookStr = skCrypt("g_Hooking Initialized.");
		g_Logger->Info(hookStr);
		hookStr.clear();
		g_Hooking->Hook();

		auto loadStr = skCrypt("Aeternum loaded.");
		g_Logger->Info(loadStr);
		loadStr.clear();

		while (g_Running)
		{
			if (IsKeyPressed(VK_DELETE))
				g_Running = false;

			std::this_thread::sleep_for(3ms);
			std::this_thread::yield();
		}

		std::this_thread::sleep_for(500ms);

		g_Hooking->Unhook();

		g_D3DRenderer.reset();

		std::this_thread::sleep_for(500ms);

		g_Hooking.reset();

		g_Core.reset();

		g_Bypass.reset();

		g_GameFunctions.reset();
		g_GameVariables.reset();

		g_Config.reset();
	}
	else
	{
		auto failStr = skCrypt("License validation failed - %d");
		g_Logger->Error(failStr, License::License::GetLastCode());
		failStr.clear();
	}

	auto unloadStr = skCrypt("Aeternum unloaded.");
	g_Logger->Info(unloadStr);
	unloadStr.clear();
	g_Logger.reset();

	FreeLibraryAndExitThread(g_Module, 0);
	VMProtectEnd();
}

/**
 * \brief The entry point of the library
 * \param hInstance The base address of the DLL
 * \param reason The reason for this function being called
 */
BOOL DllMain(HINSTANCE hInstance, DWORD reason, LPVOID reserved)
{
	using namespace Aeternum;

	if (reason == DLL_PROCESS_ATTACH)
	{
		get_retaddr();
		g_Module = hInstance;
		g_ptrUsername = (uint64_t)reserved;

		_beginthread((_beginthread_proc_type)MainThread, 0, NULL);
	}

	return true;
}