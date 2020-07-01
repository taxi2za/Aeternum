#pragma once

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

namespace Aeternum
{
	class GameVariables
	{
	public:
		explicit GameVariables();
		~GameVariables() noexcept = default;

		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		HWND m_GameWindow;
		IDXGISwapChain* m_Swapchain;
	};

	class GameFunctions
	{
	public:
		explicit GameFunctions();
		~GameFunctions() noexcept = default;
		GameFunctions(GameFunctions const&) = delete;
		GameFunctions(GameFunctions&&) = delete;
		GameFunctions& operator=(GameFunctions const&) = delete;
		GameFunctions& operator=(GameFunctions&&) = delete;

		
	};

	inline std::unique_ptr<GameVariables> g_GameVariables;
	inline std::unique_ptr<GameFunctions> g_GameFunctions;
}