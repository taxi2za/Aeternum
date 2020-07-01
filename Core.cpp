#include "Core.hpp"

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

namespace Aeternum
{
	uint64_t Entity::GetBoneStruct()
	{
		__try
		{
			return reinterpret_cast<uint64_t(__fastcall*)(uint64_t)>(g_Core->m_getBoneStruct)(this->Component_VELOCITY.ComponentBase);
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {}
	}

	bool Entity::IsVisible()
	{
		__try
		{
			if (Component_P_VISIBILITY.IsValid())
			{
				uint64_t a1 = RPM<uint64_t>(Component_P_VISIBILITY.ComponentBase + 0x88);
				uint64_t IsVisible = RPM<uint64_t>(Component_P_VISIBILITY.ComponentBase + 0x90);
				uint64_t Decrypted = spoof_call(reinterpret_cast<uint64_t(__fastcall*)(uint64_t)>(g_Core->m_decryptVisible), a1);
				spoof_call(reinterpret_cast<uint64_t(__fastcall*)(uint64_t*, uint64_t, uint64_t)>(g_Core->m_decryptVisible2), &IsVisible, Decrypted, (uint64_t)(Component_P_VISIBILITY.ComponentBase + 0x98));
				return IsVisible;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {}
		return false;
	}

	__int64 __fastcall CoreHooks::ComponentHook(uint64_t ComponentParent, uint8_t* pIndex)
	{
		__int64 DecryptedComponent = reinterpret_cast<decltype(&ComponentHook)>(g_Core->o_ComponentHook)(ComponentParent, pIndex);
		uint8_t Index = *pIndex;

		if (DecryptedComponent)
		{
			switch (Index)
			{
			case eComponentType::TYPE_VELOCITY:
				g_Core->Components_VELOCITY.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[VELOCITY] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_BONE:
				g_Core->Components_BONE.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[BONE] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_TEAM:
				g_Core->Components_TEAM.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[TEAM] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_ROTATION:
				g_Core->Components_ROTATION.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[ROTATION] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_ID:
				g_Core->Components_ID.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[ID] \t\tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_P_VISIBILITY:
				g_Core->Components_P_VISIBILITY.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[VISIBILITY] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_SKILL:
				g_Core->Components_SKILL.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[SKILL] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_HEALTH:
				g_Core->Components_HEALTH.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[HEALTH] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_ANGLE:
				if (!g_Core->Components_ANGLE.IsValid())
					g_Core->Components_ANGLE = Component(DecryptedComponent, ComponentParent, Index);
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[ANGLE] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_P_HEROID:
				g_Core->Components_P_HEROID.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[HEROID] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			case eComponentType::TYPE_OUTLINE:
				g_Core->Components_OUTLINE.push_back(Component(DecryptedComponent, ComponentParent, Index));
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[OUTLINE] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), DecryptedComponent, ComponentParent);
				break;
			default:
				if (g_Config->m_Debug)
					g_Logger->Info(skCrypt("[UNKNOWN:%d] \tDecryptedComponent: %I64x, ComponentParent: %I64x"), Index, DecryptedComponent, ComponentParent);
				break;
			}
		}

		return DecryptedComponent;
	}

	__int64 __fastcall CoreHooks::ViewMatrixHook(__int64* a1, __int64* a2, __int64* a3, __int64* a4, __int64* a5, __int64* a6)
	{
		g_Core->m_viewMatrix = (uint64_t)a1 + 0x440;
		return reinterpret_cast<decltype(&ViewMatrixHook)>(g_Core->o_ViewMatrixHook)(a1, a2, a3, a4, a5, a6);
	}

	bool __fastcall CoreHooks::InputHook(uint64_t a1, uint64_t a2)
	{
		if (g_Core->m_Input)
		{
			if (g_Core->holdTimer->Update())
			{
				g_Core->m_Input = eInput::INPUT_NULL;
				g_Core->holdTimer->SetDelay(0ms);
			}
			else
			{
				if (g_Core->m_Input == eInput::INPUT_LMOUSE_UNHOLD)
					*(uint32_t*)(a1 + 0x30) &= ~eInput::INPUT_LMOUSE;
				else
					*(uint32_t*)(a1 + 0x30) |= g_Core->m_Input;
			}
		}
		return reinterpret_cast<decltype(&InputHook)>(g_Core->o_InputHook)(a1, a2);
	}

	__int64 __fastcall CoreHooks::LocalHook(uint64_t a1)
	{
		g_Core->m_localHero = spoof_call(reinterpret_cast<decltype(&LocalHook)>(g_Core->o_LocalHook), a1);
		return g_Core->m_localHero;
	}

	Core::Core()
	{
		m_ComponentHook = dwGameBase + g_Data;
		//m_ComponentHook = Signature(xorstr_("48 8B D0 E8 ? ? ? ? 48 8B 03 48 8B CB FF 50 08 48 85 C0 75 ?")).Scan().Add(4).Rip().As<uint64_t>()),
		auto m_ViewMatrixHookStr = skCrypt("48 89 4C 24 08 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 89");
		m_ViewMatrixHook = Signature(m_ViewMatrixHookStr).Scan().As<uint64_t>();
		m_ViewMatrixHookStr.clear();
		auto m_InputHookStr = skCrypt("48 8D 8F ? ? 00 00 48 8D 97 ? ? 00 00 E8 ? ? ? ? 8B 8F ? ? 00 00");
		m_InputHook = Signature(m_InputHookStr).Scan().Add(0xF).Rip().As<uint64_t>();
		m_InputHookStr.clear();
		auto m_LocalHookStr = skCrypt("84 C0 74 07 BE 02 00 00 00 EB 0B 48 8B CF E8");
		m_LocalHook = Signature(m_LocalHookStr).Scan().Add(0xF).Rip().As<uint64_t>();
		m_LocalHookStr.clear();
		auto m_getRootVecOffsetStr = skCrypt("48 8D 54 24 ? 49 8D 8E ? ? 00 00 E8 ? ? ? ? 48 8D 54 24 ?");
		m_getRootVecOffset = *Signature(m_getRootVecOffsetStr).Scan().Add(8).As<uint32_t*>();
		m_getRootVecOffsetStr.clear();
		auto m_getRootVecStr = skCrypt("48 8D 54 24 ? 49 8D 8E ? ? 00 00 E8 ? ? ? ? 48 8D 54 24 ?");
		m_getRootVec = Signature(m_getRootVecStr).Scan().Add(0xD).Rip().As<uint64_t>();
		m_getRootVecStr.clear();
		auto m_getBoneStructStr = skCrypt("? 8B ? ? 8B ? E8 ? ? ? ? ? 85 ? 74 ? ? 8B ? ? 8B ? ? 8B ? E8 ? ? ? ? 81");
		m_getBoneStruct = Signature(m_getBoneStructStr).Scan().As<uint64_t>();
		m_getBoneStructStr.clear();
		auto m_refreshBonesStr = skCrypt("? 8B ? ? 8B ? E8 ? ? ? ? ? 85 ? 74 ? ? 8B ? ? 8B ? ? 8B ? E8 ? ? ? ? 81");
		m_refreshBones = Signature(m_refreshBonesStr).Scan().Add(7).Rip().As<uint64_t>();
		m_refreshBonesStr.clear();
		auto m_getOutlineStructStr = skCrypt("48 8B D8 48 8B 48 ? E8 ? ? ? ? 4C 8B 53 ?");
		m_getOutlineStruct = Signature(m_getOutlineStructStr).Scan().Sub(4).Rip().As<uint64_t>();
		m_getOutlineStructStr.clear();
		auto m_getOutlineKeyStr = skCrypt("48 8B D8 48 8B 48 ? E8 ? ? ? ? 4C 8B 53 ?");
		m_getOutlineKey = Signature(m_getOutlineKeyStr).Scan().Add(8).Rip().As<uint64_t>();
		m_getOutlineKeyStr.clear();
		auto m_getOutlineColorStructStr = skCrypt("? 8B CE E8 ? ? ? ? ? 8B CE 48 8B F8 E8 ? ? ? ? ? 8B CE 48 8B D8 E8 ? ? ? ?");
		m_getOutlineColorStruct = Signature(m_getOutlineColorStructStr).Scan().Add(0x1A).Rip().As<uint64_t>();
		m_getOutlineColorStructStr.clear();
		auto m_fixOutlineErrorStr = skCrypt("F6 ? ? ? 00 00 40 74 ? ? ? ? ? ? 00 00 75 ? 8B 0D");
		m_fixOutlineError = Signature(m_fixOutlineErrorStr).Scan().Add(6).As<uint64_t>();
		m_fixOutlineErrorStr.clear();
		auto m_getSkillStructStr = skCrypt("40 53 41 56 48 83 EC ? 33 DB 4C 8B F2 66 39 5A 02");
		m_getSkillStruct = Signature(m_getSkillStructStr).Scan().As<uint64_t>();
		m_getSkillStructStr.clear();
		auto m_decryptVisibleStr = skCrypt("? 8B ? ? ? 00 00 E8 ? ? ? ? 48 8B D0 ? ? ? ? ? 00 00 48 8D 4D ? E8 ? ? ? ? 48 83 7D");
		m_decryptVisible = Signature(m_decryptVisibleStr).Scan().Add(8).Rip().As<uint64_t>();
		m_decryptVisible2 = Signature(m_decryptVisibleStr).Scan().Add(0x1B).Rip().As<uint64_t>();
		m_decryptVisibleStr.clear();
		auto m_decryptIDStr = skCrypt("48 8B 8E ? ? 00 00 E8 ? ? ? ? 48 8B C8 48 8B C3 48 33 8E ? ? 00 00");
		m_decryptID = Signature(m_decryptIDStr).Scan().Add(8).Rip().As<uint64_t>();
		m_decryptIDStr.clear();

		auto m_AngleCRCStr = CENSORED;
		auto m_AngleCRC = Signature(m_AngleCRCStr).Scan().As<uint64_t>();
		m_AngleCRCStr.clear();

		WPM<uint16_t>(m_AngleCRC, 0x9090);
		WPM<uint32_t>(m_AngleCRC + 2, 0x90909090);

		holdTimer = new Timer(0ms);

		for (int i = 0; i < 20; i++)
		{
			if (RPM<uint8_t>(m_getBoneStruct - i) == 0xE8 && RPM<uint8_t>(m_getBoneStruct - i - 2) == 0x8B)
			{
				m_getBoneStruct = RPM<int32_t>(m_getBoneStruct - i + 1) + (m_getBoneStruct - i + 1) + 4;
				break;
			}
		}
	}
}