#pragma once
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_internal.h"

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

namespace Aeternum
{
	class D3DRenderer
	{
	public:
		explicit D3DRenderer() = default;
		~D3DRenderer() noexcept;
		D3DRenderer(D3DRenderer const&) = delete;
		D3DRenderer(D3DRenderer&&) = delete;
		D3DRenderer& operator=(D3DRenderer const&) = delete;
		D3DRenderer& operator=(D3DRenderer&&) = delete;

		/**
		 * \brief Init
		 */
		void PostInit(IDXGISwapChain* swapChain);

		/**
		 * \brief Prepares the frame.
		 */
		void ClearRenderTarget();

		/**
		 * \brief Prepares the frame.
		 */
		void CreateRenderTarget();

		/**
		 * \brief Prepares the frame.
		 */
		void BeginFrame();

		/**
		 * \brief Finishes the frame and renders.
		 */
		void EndFrame();

		/**
		 * \brief Invalidates rendering resources
		 */
		void PreResize();

		/**
		 * \brief Finishes the frame and renders.
		 */
		void PostResize();

		/**
		 * \brief Processes input messages.
		 */
		void WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		void BeginScene();
		void EndScene();

		float RenderText(const std::string& text, const ImVec2& position, float size, uint32_t color, bool center = false);
		void RenderLine(const ImVec2& from, const ImVec2& to, uint32_t color, float thickness = 1.0f);
		void RenderLine(const XMFLOAT2& from, const XMFLOAT2& to, uint32_t color, float thickness = 1.0f);
		void RenderCircle(const ImVec2& position, float radius, uint32_t color, float thickness = 1.0f, uint32_t segments = 16);
		void RenderCircleFilled(const ImVec2& position, float radius, uint32_t color, uint32_t segments = 16);
		void RenderRect(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All, float thickness = 1.0f);
		void RenderRectFilled(const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
		void RenderImage(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color);
		void RenderImageRounded(ID3D11ShaderResourceView* pTexture, const ImVec2& from, const ImVec2& to, uint32_t color, float rounding = 0.0f, uint32_t roundingCornersFlags = ImDrawCornerFlags_All);
	private:
		IDXGISwapChain* m_Swapchain{};
		ID3D11Device* m_Device{};
		ID3D11DeviceContext* m_Context{};
		ID3D11RenderTargetView* m_RTV{};

		ImFont* m_pFont{};
	};

	inline std::unique_ptr<D3DRenderer> g_D3DRenderer;
}
