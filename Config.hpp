#pragma once
#include <json.hpp>

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

namespace Aeternum
{
	class Config
	{
	public:
		explicit Config();
		~Config() noexcept = default;

		Config(Config const&) = delete;
		Config(Config&&) = delete;
		Config& operator=(Config const&) = delete;
		Config& operator=(Config&&) = delete;

		void Save();
		void Load();
		void Init();
	private:
		fs::path m_FilePath;
		std::ofstream m_File;
		nlohmann::json m_Config;

	public:
		char m_Preset[256] = "default";
		std::atomic_bool m_Opened = true;
		bool m_Optimize = true;
		bool m_DrawFOV = false;
		float m_Fov = 150.f;

		bool m_ESP = true;
		bool m_ShowHitbox = false;
		bool m_ShowBoneAnkle = true;
		bool m_OutlineESP = true;
		const char* m_OutlineStrs[4] = { "NORMAL", "ON", "TRACE", "OFF" };
		int m_OutlineType = 1;

		bool m_Triggerbot = true;
		float m_TriggerScale = 100.f;
		bool m_IsLeft = true;
		bool m_Flick = true;

		int m_AimKey1 = VK_XBUTTON1, m_AimKey2 = VK_XBUTTON2;
		bool m_Aimbot = true;
		bool m_Teambot = false;
		bool m_LockTarget = true;
		int m_LockTargetTimer = 100;
		bool m_SmoothType = true;
		bool m_FixedAccuracy = false;
		float m_Accuracy = 100.f;
		float m_SmoothFactor = 10.f;
		float m_Smooth = 7.f;
		float m_SmoothX = 1000.f;
		float m_SmoothY = 1000.f;

		bool m_Prediction = false;
		float m_Speed = 100.f;
		float m_Gravity = 80.f;
		float m_Charge = 60.f;

		bool m_AutoMelee = false;
		bool m_AutoMeleeIsPercent = false;
		float m_AutoMeleePercent = 15.f;

		bool m_AutoDash = false;
		bool m_AutoDashIsPercent = false;
		float m_AutoDashPercent = 25.f;

		bool m_AutoSkill = false;
		float m_Dva_Zarya = 30.f;
		float m_Sigma_Zarya = 24.f;
		float m_Dva_Mei = 25.f;
		float m_Sigma_Mei = 20.f;
		float m_Dva_Tracer = 16.f;
		float m_Sigma_Tracer = 8.f;
		float m_Dva_Hanjo = 11.f;
		float m_Sigma_Hanjo = 12.f;
		float m_Sombra_Reinhardt = 15.f;
		float m_Reinhardt_Reinhardt = 18.f;
		float m_Sombra_Lucio = 15.f;
		float m_Sombra_Sigma = 15.f;
		float m_Genji_Ana = 18.f;
		float m_Tracer_McCree = 10.f;

		bool m_Debug = false;
		XMFLOAT3 min{ -0.1f, -0.05f, -0.1f }, max{ 0.1f, 0.17f, 0.1f };
		XMFLOAT3 min2{ -0.16f, -0.3f, -0.16f }, max2{ 0.16f, 0.23f, 0.16f };
	};

	inline std::unique_ptr<Config> g_Config;
}
