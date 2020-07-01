#include "Game.hpp"

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

namespace Aeternum
{
	IDXGISwapChain* GetSwapChain(HWND hWnd)
	{
		HMODULE hDXGIDLL = 0;
		do
		{
			auto dxgiStr = skCrypt("dxgi.dll");
			hDXGIDLL = GetModuleHandle(dxgiStr);
			dxgiStr.clear();
			Sleep(1);
		} while (!hDXGIDLL);

		DXGI_SWAP_CHAIN_DESC swapDesc;
		ZeroMemory(&swapDesc, sizeof(swapDesc));
		swapDesc.BufferCount = 1;
		swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapDesc.OutputWindow = hWnd;
		swapDesc.SampleDesc.Count = 1;
		swapDesc.Windowed = TRUE;

		D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

		IDXGISwapChain* pSwapChain = 0;
		ID3D11Device* pDevice = NULL;
		ID3D11DeviceContext* pContext = NULL;
		if (SUCCEEDED(D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
			&featureLevel,
			1,
			D3D11_SDK_VERSION,
			&swapDesc,
			&pSwapChain,
			&pDevice,
			NULL,
			&pContext)))
		{
			pContext->Release();
			pDevice->Release();
			return pSwapChain;
		}
		else
			return NULL;
	}

	GameVariables::GameVariables()
	{
		auto wndStr = skCrypt("TankWindowClass");
		m_GameWindow = FindWindowA(wndStr, NULL);
		wndStr.clear();
		m_Swapchain = GetSwapChain(m_GameWindow);
	}

	GameFunctions::GameFunctions()
	{
	}
}