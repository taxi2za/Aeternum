#include "Config.hpp"

namespace Aeternum
{
	Config::Config()
	{
		try
		{
			auto appdataStr = skCrypt("appdata");
			m_FilePath.append(std::getenv(appdataStr));
			appdataStr.clear();
			auto aeternumName = AETERNUM_NAME;
			m_FilePath.append(aeternumName.decrypt());
			aeternumName.clear();
			if (!fs::exists(m_FilePath))
				fs::create_directory(m_FilePath);

			auto filename = m_FilePath;
			auto iniStr = skCrypt("default.ini");
			filename.append(iniStr.decrypt());
			iniStr.clear();
			m_File.open(filename, std::ios_base::out);
			m_Config["m_Optimize"] = m_Optimize;
			m_Config["m_DrawFOV"] = m_DrawFOV;
			m_Config["m_Fov"] = m_Fov;
			m_Config["m_ESP"] = m_ESP;
			m_Config["m_ShowHitbox"] = m_ShowHitbox;
			m_Config["m_ShowBoneAnkle"] = m_ShowBoneAnkle;
			m_Config["m_OutlineESP"] = m_OutlineESP;
			m_Config["m_OutlineType"] = m_OutlineType;
			m_Config["m_Triggerbot"] = m_Triggerbot;
			m_Config["m_TriggerScale"] = m_TriggerScale;
			m_Config["m_IsLeft"] = m_IsLeft;
			m_Config["m_Flick"] = m_Flick;

			m_Config["m_AimKey1"] = m_AimKey1;
			m_Config["m_AimKey2"] = m_AimKey2;
			m_Config["m_Aimbot"] = m_Aimbot;
			m_Config["m_Teambot"] = m_Teambot;
			m_Config["m_LockTarget"] = m_LockTarget;
			m_Config["m_SmoothType"] = m_SmoothType;
			m_Config["m_SmoothFactor"] = m_SmoothFactor;
			m_Config["m_Smooth"] = m_Smooth;
			m_Config["m_SmoothX"] = m_SmoothX;
			m_Config["m_SmoothY"] = m_SmoothY;

			m_Config["m_Prediction"] = m_Prediction;
			m_Config["m_Speed"] = m_Speed;
			m_Config["m_Gravity"] = m_Gravity;
			m_Config["m_Charge"] = m_Charge;

			m_Config["m_AutoMelee"] = m_AutoMelee;
			m_Config["m_AutoMeleeIsPercent"] = m_AutoMeleeIsPercent;
			m_Config["m_AutoMeleePercent"] = m_AutoMeleePercent;

			m_Config["m_AutoDash"] = m_AutoDash;
			m_Config["m_AutoDashIsPercent"] = m_AutoDashIsPercent;
			m_Config["m_AutoDashPercent"] = m_AutoDashPercent;

			m_Config["m_AutoSkill"] = m_AutoSkill;
			m_Config["m_Dva_Zarya"] = m_Dva_Zarya;
			m_Config["m_Sigma_Zarya"] = m_Sigma_Zarya;
			m_Config["m_Dva_Mei"] = m_Dva_Mei;
			m_Config["m_Sigma_Mei"] = m_Sigma_Mei;
			m_Config["m_Dva_Tracer"] = m_Dva_Tracer;
			m_Config["m_Sigma_Tracer"] = m_Sigma_Tracer;
			m_Config["m_Dva_Hanjo"] = m_Dva_Hanjo;
			m_Config["m_Sigma_Hanjo"] = m_Sigma_Hanjo;
			m_Config["m_Sombra_Reinhardt"] = m_Sombra_Reinhardt;
			m_Config["m_Reinhardt_Reinhardt"] = m_Reinhardt_Reinhardt;
			m_Config["m_Sombra_Lucio"] = m_Sombra_Lucio;
			m_Config["m_Sombra_Sigma"] = m_Sombra_Sigma;
			m_Config["m_Genji_Ana"] = m_Genji_Ana;
			m_Config["m_Tracer_McCree"] = m_Tracer_McCree;

			m_Config["m_FixedAccuracy"] = m_FixedAccuracy;
			m_Config["m_Accuracy"] = m_Accuracy;

			m_Config["m_LockTargetTimer"] = m_LockTargetTimer;
			m_File << m_Config.dump(4);
			m_File.close();
		}
		catch (fs::filesystem_error const&)
		{
		}
	}

	void Config::Save()
	{
		try
		{
			auto filename = m_FilePath;
			auto iniStr = skCrypt(".ini");
			filename.append(std::string(m_Preset) + iniStr.decrypt());
			iniStr.clear();
			m_File.open(filename, std::ios_base::out);
			m_Config["m_Optimize"] = m_Optimize;
			m_Config["m_DrawFOV"] = m_DrawFOV;
			m_Config["m_Fov"] = m_Fov;
			m_Config["m_ESP"] = m_ESP;
			m_Config["m_ShowHitbox"] = m_ShowHitbox;
			m_Config["m_ShowBoneAnkle"] = m_ShowBoneAnkle;
			m_Config["m_OutlineESP"] = m_OutlineESP;
			m_Config["m_OutlineType"] = m_OutlineType;
			m_Config["m_Triggerbot"] = m_Triggerbot;
			m_Config["m_TriggerScale"] = m_TriggerScale;
			m_Config["m_IsLeft"] = m_IsLeft;
			m_Config["m_Flick"] = m_Flick;

			m_Config["m_AimKey1"] = m_AimKey1;
			m_Config["m_AimKey2"] = m_AimKey2;
			m_Config["m_Aimbot"] = m_Aimbot;
			m_Config["m_Teambot"] = m_Teambot;
			m_Config["m_LockTarget"] = m_LockTarget;
			m_Config["m_SmoothType"] = m_SmoothType;
			m_Config["m_SmoothFactor"] = m_SmoothFactor;
			m_Config["m_Smooth"] = m_Smooth;
			m_Config["m_SmoothX"] = m_SmoothX;
			m_Config["m_SmoothY"] = m_SmoothY;

			m_Config["m_Prediction"] = m_Prediction;
			m_Config["m_Speed"] = m_Speed;
			m_Config["m_Gravity"] = m_Gravity;
			m_Config["m_Charge"] = m_Charge;

			m_Config["m_AutoMelee"] = m_AutoMelee;
			m_Config["m_AutoMeleeIsPercent"] = m_AutoMeleeIsPercent;
			m_Config["m_AutoMeleePercent"] = m_AutoMeleePercent;

			m_Config["m_AutoDash"] = m_AutoDash;
			m_Config["m_AutoDashIsPercent"] = m_AutoDashIsPercent;
			m_Config["m_AutoDashPercent"] = m_AutoDashPercent;

			m_Config["m_AutoSkill"] = m_AutoSkill;
			m_Config["m_Dva_Zarya"] = m_Dva_Zarya;
			m_Config["m_Sigma_Zarya"] = m_Sigma_Zarya;
			m_Config["m_Dva_Mei"] = m_Dva_Mei;
			m_Config["m_Sigma_Mei"] = m_Sigma_Mei;
			m_Config["m_Dva_Tracer"] = m_Dva_Tracer;
			m_Config["m_Sigma_Tracer"] = m_Sigma_Tracer;
			m_Config["m_Dva_Hanjo"] = m_Dva_Hanjo;
			m_Config["m_Sigma_Hanjo"] = m_Sigma_Hanjo;
			m_Config["m_Sombra_Reinhardt"] = m_Sombra_Reinhardt;
			m_Config["m_Reinhardt_Reinhardt"] = m_Reinhardt_Reinhardt;
			m_Config["m_Sombra_Lucio"] = m_Sombra_Lucio;
			m_Config["m_Sombra_Sigma"] = m_Sombra_Sigma;
			m_Config["m_Genji_Ana"] = m_Genji_Ana;
			m_Config["m_Tracer_McCree"] = m_Tracer_McCree;

			m_Config["m_FixedAccuracy"] = m_FixedAccuracy;
			m_Config["m_Accuracy"] = m_Accuracy;

			m_Config["m_LockTargetTimer"] = m_LockTargetTimer;
			m_File << m_Config.dump(4);
			m_File.close();
		}
		catch (...) {}
	}

	void Config::Load()
	{
		try
		{
			auto filename = m_FilePath;
			auto iniStr = skCrypt(".ini");
			filename.append(std::string(m_Preset) + iniStr.decrypt());
			iniStr.clear();
			std::ifstream file(filename);
			if (!file.is_open())
				return;
			nlohmann::json config;
			file >> config;
			m_Optimize = config["m_Optimize"];
			m_DrawFOV = config["m_DrawFOV"];
			m_Fov = config["m_Fov"];
			m_ESP = config["m_ESP"];
			m_ShowHitbox = config["m_ShowHitbox"];
			m_ShowBoneAnkle = config["m_ShowBoneAnkle"];
			m_OutlineESP = config["m_OutlineESP"];
			m_OutlineType = config["m_OutlineType"];
			m_Triggerbot = config["m_Triggerbot"];
			m_TriggerScale = config["m_TriggerScale"];
			m_IsLeft = config["m_IsLeft"];
			m_Flick = config["m_Flick"];

			m_AimKey1 = config["m_AimKey1"];
			m_AimKey2 = config["m_AimKey2"];
			m_Aimbot = config["m_Aimbot"];
			m_Teambot = config["m_Teambot"];
			m_LockTarget = config["m_LockTarget"];
			m_SmoothType = config["m_SmoothType"];
			m_SmoothFactor = config["m_SmoothFactor"];
			m_Smooth = config["m_Smooth"];
			m_SmoothX = config["m_SmoothX"];
			m_SmoothY = config["m_SmoothY"];

			m_Prediction = config["m_Prediction"];
			m_Speed = config["m_Speed"];
			m_Gravity = config["m_Gravity"];
			m_Charge = config["m_Charge"];

			m_AutoMelee = config["m_AutoMelee"];
			m_AutoMeleeIsPercent = config["m_AutoMeleeIsPercent"];
			m_AutoMeleePercent = config["m_AutoMeleePercent"];

			m_AutoDash = config["m_AutoDash"];
			m_AutoDashIsPercent = config["m_AutoDashIsPercent"];
			m_AutoDashPercent = config["m_AutoDashPercent"];

			m_AutoSkill = config["m_AutoSkill"];
			m_Dva_Zarya = config["m_Dva_Zarya"];
			m_Sigma_Zarya = config["m_Sigma_Zarya"];
			m_Dva_Mei = config["m_Dva_Mei"];
			m_Sigma_Mei = config["m_Sigma_Mei"];
			m_Dva_Tracer = config["m_Dva_Tracer"];
			m_Sigma_Tracer = config["m_Sigma_Tracer"];
			m_Dva_Hanjo = config["m_Dva_Hanjo"];
			m_Sigma_Hanjo = config["m_Sigma_Hanjo"];
			m_Sombra_Reinhardt = config["m_Sombra_Reinhardt"];
			m_Reinhardt_Reinhardt = config["m_Reinhardt_Reinhardt"];
			m_Sombra_Lucio = config["m_Sombra_Lucio"];
			m_Sombra_Sigma = config["m_Sombra_Sigma"];
			m_Genji_Ana = config["m_Genji_Ana"];
			m_Tracer_McCree = config["m_Tracer_McCree"];

			m_FixedAccuracy = config["m_FixedAccuracy"];
			m_Accuracy = config["m_Accuracy"];

			m_LockTargetTimer = config["m_LockTargetTimer"];
		}
		catch (...) {}
	}

	void Config::Init()
	{
		try
		{
			auto filename = m_FilePath;
			auto iniStr = skCrypt("default.ini");
			filename.append(iniStr.decrypt());
			iniStr.clear();
			std::ifstream file(filename);
			if (!file.is_open())
				return;
			nlohmann::json config;
			file >> config;
			m_Optimize = config["m_Optimize"];
			m_DrawFOV = config["m_DrawFOV"];
			m_Fov = config["m_Fov"];
			m_ESP = config["m_ESP"];
			m_ShowHitbox = config["m_ShowHitbox"];
			m_ShowBoneAnkle = config["m_ShowBoneAnkle"];
			m_OutlineESP = config["m_OutlineESP"];
			m_OutlineType = config["m_OutlineType"];
			m_Triggerbot = config["m_Triggerbot"];
			m_TriggerScale = config["m_TriggerScale"];
			m_IsLeft = config["m_IsLeft"];
			m_Flick = config["m_Flick"];

			m_AimKey1 = config["m_AimKey1"];
			m_AimKey2 = config["m_AimKey2"];
			m_Aimbot = config["m_Aimbot"];
			m_Teambot = config["m_Teambot"];
			m_LockTarget = config["m_LockTarget"];
			m_SmoothType = config["m_SmoothType"];
			m_SmoothFactor = config["m_SmoothFactor"];
			m_Smooth = config["m_Smooth"];
			m_SmoothX = config["m_SmoothX"];
			m_SmoothY = config["m_SmoothY"];

			m_Prediction = config["m_Prediction"];
			m_Speed = config["m_Speed"];
			m_Gravity = config["m_Gravity"];
			m_Charge = config["m_Charge"];

			m_AutoMelee = config["m_AutoMelee"];
			m_AutoMeleeIsPercent = config["m_AutoMeleeIsPercent"];
			m_AutoMeleePercent = config["m_AutoMeleePercent"];

			m_AutoDash = config["m_AutoDash"];
			m_AutoDashIsPercent = config["m_AutoDashIsPercent"];
			m_AutoDashPercent = config["m_AutoDashPercent"];

			m_AutoSkill = config["m_AutoSkill"];
			m_Dva_Zarya = config["m_Dva_Zarya"];
			m_Sigma_Zarya = config["m_Sigma_Zarya"];
			m_Dva_Mei = config["m_Dva_Mei"];
			m_Sigma_Mei = config["m_Sigma_Mei"];
			m_Dva_Tracer = config["m_Dva_Tracer"];
			m_Sigma_Tracer = config["m_Sigma_Tracer"];
			m_Dva_Hanjo = config["m_Dva_Hanjo"];
			m_Sigma_Hanjo = config["m_Sigma_Hanjo"];
			m_Sombra_Reinhardt = config["m_Sombra_Reinhardt"];
			m_Reinhardt_Reinhardt = config["m_Reinhardt_Reinhardt"];
			m_Sombra_Lucio = config["m_Sombra_Lucio"];
			m_Sombra_Sigma = config["m_Sombra_Sigma"];
			m_Genji_Ana = config["m_Genji_Ana"];
			m_Tracer_McCree = config["m_Tracer_McCree"];

			m_FixedAccuracy = config["m_FixedAccuracy"];
			m_Accuracy = config["m_Accuracy"];

			m_LockTargetTimer = config["m_LockTargetTimer"];
		}
		catch (...) {}
	}
}
