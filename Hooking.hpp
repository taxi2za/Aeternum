#pragma once
#include "Core.hpp"

namespace Aeternum
{
	struct Hooks
	{
		static LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		static constexpr auto PresentIndex = 8;
		static HRESULT Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags);

		static constexpr auto ResizeBuffersIndex = 13;
		static HRESULT ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags);

		static NTSTATUS NTAPI NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength);
	};

	class Hooking
	{
	public:
		explicit Hooking();
		~Hooking() noexcept;
		Hooking(Hooking const&) = delete;
		Hooking(Hooking&&) = delete;
		Hooking& operator=(Hooking const&) = delete;
		Hooking& operator=(Hooking&&) = delete;

		void Hook();
		void Unhook();

		Timer* lockTimer;
		float m_Time = 0.f;
		bool m_Flick = false;
		Entity prevEntity;
		Entity bestEntity;

		friend struct Hooks;
	private:
		void* m_OriginalWndProc{};
		void* m_OriginalPresent{};
		void* m_OriginalResizeBuffers{};
		void* m_OriginalQSI{};
		uint64_t m_OldWndProc{};
	};

	inline std::unique_ptr<Hooking> g_Hooking;
}
