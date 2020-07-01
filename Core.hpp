#pragma once
#include "D3DRenderer.hpp"

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

#define InRange(val) (val >= dwGameBase && val <= dwGameBase + 0x9000000)

namespace Aeternum
{
	struct CoreHooks
	{
		static __int64 __fastcall ComponentHook(uint64_t ComponentParent, uint8_t* pIndex);
		static __int64 __fastcall ViewMatrixHook(__int64* a1, __int64* a2, __int64* a3, __int64* a4, __int64* a5, __int64* a6);
		static bool __fastcall InputHook(uint64_t a1, uint64_t a2);
		static __int64 __fastcall LocalHook(uint64_t a1);
	};

	enum eInput
	{
		INPUT_NULL = 0x0,
		INPUT_LMOUSE_UNHOLD = 0x1000,
		INPUT_LMOUSE = 0x1,
		INPUT_RMOUSE = 0x2,
		INPUT_INTERACTION = 0x4,
		INPUT_SKILL1 = 0x8,
		INPUT_SKILL2 = 0x10,
		INPUT_ULT = 0x20,
		INPUT_JUMP = 0x40,
		INPUT_DUCK = 0x80,
		INPUT_RELOAD = 0x400,
		INPUT_MELEE = 0x800,
	};

	enum eComponentType
	{
		TYPE_ERROR = -1,
		TYPE_VELOCITY = 4,
		TYPE_TEAM = 25,
		TYPE_BONE = 31,
		TYPE_ROTATION = 39,
		TYPE_ID = 42,
		TYPE_P_VISIBILITY = 44,
		TYPE_SKILL = 46,
		TYPE_HEALTH = 50,
		TYPE_ANGLE = 58,
		TYPE_P_HEROID = 74,
		TYPE_OUTLINE = 82,
	};

	enum eHero : uint64_t
	{
		HERO_REAPER = 0x02E0000000000002,
		HERO_TRACER = 0x02E0000000000003,
		HERO_MERCY = 0x02E0000000000004,
		HERO_HANJO = 0x02E0000000000005,
		HERO_TORBJORN = 0x02E0000000000006,
		HERO_REINHARDT = 0x02E0000000000007,
		HERO_PHARAH = 0x02E0000000000008,
		HERO_WINSTON = 0x02E0000000000009,
		HERO_WIDOWMAKER = 0x02E000000000000A,
		HERO_BASTION = 0x02E0000000000015,
		HERO_SYMMETRA = 0x02E0000000000016,
		HERO_ZENYATTA = 0x02E0000000000020,
		HERO_GENJI = 0x02E0000000000029,
		HERO_ROADHOG = 0x02E0000000000040,
		HERO_MCCREE = 0x02E0000000000042,
		HERO_JUNKRAT = 0x02E0000000000065,
		HERO_ZARYA = 0x02E0000000000068,
		HERO_SOLDIER76 = 0x02E000000000006E,
		HERO_LUCIO = 0x02E0000000000079,
		HERO_DVA = 0x02E000000000007A,
		HERO_MEI = 0x02E00000000000DD,
		HERO_ANA = 0x02E000000000013B,
		HERO_SOMBRA = 0x02E000000000012E,
		HERO_ORISA = 0x02E000000000013E,
		HERO_DOOMFIST = 0x02E000000000012F,
		HERO_MOIRA = 0x02E00000000001A2,
		HERO_BRIGITTE = 0x02E0000000000195,
		HERO_WRECKINGBALL = 0x02E00000000001CA,
		HERO_ASHE = 0x02E0000000000200,
		HERO_BAPTISTE = 0x02E0000000000221,
		HERO_SIGMA = 0x02E000000000023B,
		HERO_TRAININGBOT1 = 0x02E000000000016B,
		HERO_TRAININGBOT2 = 0x02E000000000016C,
		HERO_TRAININGBOT3 = 0x02E000000000016D,
		HERO_TRAININGBOT4 = 0x02E000000000016E,
	};

	enum eTeam
	{
		TEAM_RED,
		TEAM_BLUE,
		TEAM_UNKNOWN1,
		TEAM_UNKNOWN2,
		TEAM_DEATHMATCH,
	};

	struct Component
	{
		uint64_t ComponentBase;
		uint64_t ComponentParent;
		uint8_t ComponentType;

		Component(uint64_t ComponentBase, uint64_t ComponentParent, uint8_t ComponentType) : ComponentBase(ComponentBase), ComponentParent(ComponentParent), ComponentType(ComponentType) {};
		Component() : ComponentBase(NULL), ComponentParent(NULL), ComponentType(eComponentType::TYPE_ERROR) {};
		BOOL IsValid()
		{
			if (InRange(RPM<uint64_t>(ComponentBase)))
			{
				if (RPM<uint8_t>(ComponentBase + 0x14) == ComponentType)
				{
					return TRUE;
				}
			}
			return FALSE;
		}

		BOOL IsChild(uint64_t componentParent)
		{
			if (componentParent == ComponentParent)
			{
				return TRUE;
			}
			return FALSE;
		}
	};

	static void reComponent(std::vector<Component> *Components)
	{
		for (int i = 0; i < Components->size(); i++)
		{
			Component* component = &Components->at(i);
			if (!component->IsValid())
			{
				Components->erase(Components->begin() + i);
			}
		}
	}

	static void swapComponent(std::vector<Component>* Components, Component* swapComponent, uint64_t ComponentParent)
	{
		for (int i = 0; i < Components->size(); i++)
		{
			Component* component = &Components->at(i);
			if (component->IsChild(ComponentParent))
			{
				swapComponent->ComponentBase = component->ComponentBase;
				swapComponent->ComponentParent = component->ComponentParent;
				swapComponent->ComponentType = component->ComponentType;
				return;
			}
		}
	}

	struct Entity
	{
		uint64_t UniqueID;
		uint32_t PlayerID;
		uint32_t EntityID;
		uint64_t HeroID;
		Component Component_VELOCITY;
		Component Component_BONE;
		Component Component_TEAM;
		Component Component_ROTATION;
		Component Component_ID;
		Component Component_P_VISIBILITY;
		Component Component_SKILL;
		Component Component_HEALTH;
		Component Component_P_HEROID;
		Component Component_OUTLINE;

		Entity() : UniqueID(0) {};
		Entity(uint64_t _UniqueID) : UniqueID(_UniqueID) {};

		__forceinline bool operator==(const Entity& entity) const {
			return (UniqueID == entity.UniqueID);
		}

		__forceinline bool operator!=(const Entity& entity) const {
			return (UniqueID != entity.UniqueID);
		}

		BOOL IsValid()
		{
			if (Component_HEALTH.IsValid())
			{
				return TRUE;
			}
			return FALSE;
		}

		uint32_t GetPlayerID(uint64_t m_decryptID)
		{
			__try
			{
				uint64_t xorkey = spoof_call(reinterpret_cast<uint64_t(__fastcall*)(uint64_t)>(m_decryptID), RPM<uint64_t>(Component_ID.ComponentBase + 0x108));
				return xorkey ^ RPM<uint64_t>(Component_ID.ComponentBase + 0x100);
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return NULL;
		}

		uint32_t GetEntityID(std::vector<Component>* Component_P_HEROID, int i)
		{
			__try
			{
				return RPM<uint32_t>(Component_P_HEROID->at(i).ComponentParent + 0x240);
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return NULL;
		}

		uint64_t GetHeroID()
		{
			return RPM<uint64_t>(Component_P_HEROID.ComponentBase + 0xF8);
		}

		std::string GetHeroName()
		{
			if (g_Config->m_Debug)
			{
				std::stringstream debugStr;
				debugStr << std::hex << Component_ROTATION.ComponentBase << "\n";
				return debugStr.str();
			}
			switch (HeroID)
			{
			case eHero::HERO_REAPER:
				return skCrypt("Reaper").decrypt();
			case eHero::HERO_TRACER:
				return skCrypt("Tracer").decrypt();
			case eHero::HERO_MERCY:
				return skCrypt("Mercy").decrypt();
			case eHero::HERO_HANJO:
				return skCrypt("Hanjo").decrypt();
			case eHero::HERO_TORBJORN:
				return skCrypt("Torbjorn").decrypt();
			case eHero::HERO_REINHARDT:
				return skCrypt("Reinhardt").decrypt();
			case eHero::HERO_PHARAH:
				return skCrypt("Pharah").decrypt();
			case eHero::HERO_WINSTON:
				return skCrypt("Winston").decrypt();
			case eHero::HERO_WIDOWMAKER:
				return skCrypt("Widowmaker").decrypt();
			case eHero::HERO_BASTION:
				return skCrypt("Bastion").decrypt();
			case eHero::HERO_SYMMETRA:
				return skCrypt("Symmetra").decrypt();
			case eHero::HERO_ZENYATTA:
				return skCrypt("Zenyatta").decrypt();
			case eHero::HERO_GENJI:
				return skCrypt("Genji").decrypt();
			case eHero::HERO_ROADHOG:
				return skCrypt("Roadhog").decrypt();
			case eHero::HERO_MCCREE:
				return skCrypt("McCree").decrypt();
			case eHero::HERO_JUNKRAT:
				return skCrypt("Junkrat").decrypt();
			case eHero::HERO_ZARYA:
				return skCrypt("Zarya").decrypt();
			case eHero::HERO_SOLDIER76:
				return skCrypt("Soldier 76").decrypt();
			case eHero::HERO_LUCIO:
				return skCrypt("Lucio").decrypt();
			case eHero::HERO_DVA:
				if (GetBoneRealCount() > 240)
					return skCrypt("D.Va").decrypt();
				else
					return skCrypt("Hana").decrypt();
			case eHero::HERO_MEI:
				return skCrypt("Mei").decrypt();
			case eHero::HERO_ANA:
				return skCrypt("Ana").decrypt();
			case eHero::HERO_SOMBRA:
				return skCrypt("Sombra").decrypt();
			case eHero::HERO_ORISA:
				return skCrypt("Orisa").decrypt();
			case eHero::HERO_DOOMFIST:
				return skCrypt("Doomfist").decrypt();
			case eHero::HERO_MOIRA:
				return skCrypt("Moira").decrypt();
			case eHero::HERO_BRIGITTE:
				return skCrypt("Brigitte").decrypt();
			case eHero::HERO_WRECKINGBALL:
				return skCrypt("Wrecking Ball").decrypt();
			case eHero::HERO_ASHE:
				return skCrypt("Ashe").decrypt();
			case eHero::HERO_BAPTISTE:
				return skCrypt("Baptiste").decrypt();
			case eHero::HERO_SIGMA:
				return skCrypt("Sigma").decrypt();
			case eHero::HERO_TRAININGBOT1:
				return skCrypt("Training Bot1").decrypt();
			case eHero::HERO_TRAININGBOT2:
				return skCrypt("Training Bot2").decrypt();
			case eHero::HERO_TRAININGBOT3:
				return skCrypt("Training Bot3").decrypt();
			case eHero::HERO_TRAININGBOT4:
				return skCrypt("Training Bot4").decrypt();
			default:
				return skCrypt("default").decrypt();
			}
		}

		bool IsVisible();

		eTeam GetTeam()
		{
			uint32_t Team = RPM<uint32_t>(Component_TEAM.ComponentBase + 0x80) & 0x0F800000;
			std::bitset<sizeof(int) * CHAR_BIT> bitTeam(Team);
			if (bitTeam[0x17])
				return eTeam::TEAM_RED;
			else if (bitTeam[0x18])
				return eTeam::TEAM_BLUE;
			else if (bitTeam[0x19])
				return eTeam::TEAM_UNKNOWN1;
			else if (bitTeam[0x1A])
				return eTeam::TEAM_UNKNOWN2;
			else if (bitTeam[0x1B])
				return eTeam::TEAM_DEATHMATCH;
		}

		XMFLOAT2 GetHealth()
		{
			return RPM<XMFLOAT2>(Component_HEALTH.ComponentBase + 0xFC);
		}

		XMFLOAT2 GetArmor()
		{
			XMFLOAT2 Armor{};
			for (int i = 0; i < 10; i++)
			{
				XMFLOAT2 ArmorEx = RPM<XMFLOAT2>(Component_HEALTH.ComponentBase + 0x23C + i * 0x14);
				if (ArmorEx.x && ArmorEx.y && (ArmorEx.x + ArmorEx.y > 0.f))
				{
					XMStoreFloat2(&Armor, XMLoadFloat2(&Armor) + XMLoadFloat2(&ArmorEx));
				}
			}
			return Armor;
		}

		XMFLOAT2 GetBarrier()
		{
			XMFLOAT2 Barrier{};
			for (int i = 0; i < 3; i++)
			{
				XMFLOAT2 BarrierEx = RPM<XMFLOAT2>(Component_HEALTH.ComponentBase + 0x37C + i * 0x14);
				if (BarrierEx.x && BarrierEx.y && (BarrierEx.x + BarrierEx.y > 0.f))
				{
					XMStoreFloat2(&Barrier, XMLoadFloat2(&Barrier) + XMLoadFloat2(&BarrierEx));
				}
			}
			return Barrier;
		}

		XMFLOAT2 GetLife()
		{
			XMFLOAT2 Life;
			XMStoreFloat2(&Life, XMLoadFloat2(&GetHealth()) + XMLoadFloat2(&GetArmor()) + XMLoadFloat2(&GetBarrier()));
			return Life;
		}

		XMFLOAT3 GetRootVec(uint64_t m_getRootVec, uint64_t m_getRootVecOffset)
		{
			__try
			{
				if (Component_BONE.IsValid())
				{
					__m128 rootVec;
					reinterpret_cast<__m128 * (__fastcall*)(uint64_t, __m128*)>(m_getRootVec)(Component_BONE.ComponentBase + m_getRootVecOffset, &rootVec);
					return XMFLOAT3{ rootVec.m128_f32 };
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return XMFLOAT3{};
		}

		XMFLOAT3 GetVelocity()
		{
			return RPM<XMFLOAT3>(Component_VELOCITY.ComponentBase + 0x50);
		}

		uint64_t GetRotStruct()
		{
			__try
			{
				if (Component_ROTATION.IsValid())
				{
					return reinterpret_cast<uint64_t(__fastcall*)(uint64_t)>(RPM<uint64_t>(RPM<uint64_t>(Component_ROTATION.ComponentBase) + 0x40))(Component_ROTATION.ComponentBase);
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return NULL;
		}

		XMFLOAT3 GetRotMatrix()
		{
			return RPM<XMFLOAT3>(GetRotStruct() + 0xAA8);
		}

		int GetBodyBoneIndex()
		{
			switch (HeroID)
			{
			case eHero::HERO_REAPER:
				return 4;
			case eHero::HERO_TRACER:
				return 4;
			case eHero::HERO_MERCY:
				return 4;
			case eHero::HERO_HANJO:
				return 4;
			case eHero::HERO_TORBJORN:
				return 4;
			case eHero::HERO_REINHARDT:
				return 5;
			case eHero::HERO_PHARAH:
				return 4;
			case eHero::HERO_WINSTON:
				return 4;
			case eHero::HERO_WIDOWMAKER:
				return 4;
			case eHero::HERO_BASTION:
				return 25;
			case eHero::HERO_SYMMETRA:
				return 4;
			case eHero::HERO_ZENYATTA:
				return 4;
			case eHero::HERO_GENJI:
				return 4;
			case eHero::HERO_ROADHOG:
				return 4;
			case eHero::HERO_MCCREE:
				return 4;
			case eHero::HERO_JUNKRAT:
				return 4;
			case eHero::HERO_ZARYA:
				return 4;
			case eHero::HERO_SOLDIER76:
				return 4;
			case eHero::HERO_LUCIO:
				return 4;
			case eHero::HERO_DVA:
				if (GetBoneRealCount() > 240) //GetBoneCount() == 22 //Hana == 18
					return 15;
				else
					return 4;
			case eHero::HERO_MEI:
				return 4;
			case eHero::HERO_ANA:
				return 4;
			case eHero::HERO_SOMBRA:
				return 4;
			case eHero::HERO_ORISA:
				return 4;
			case eHero::HERO_DOOMFIST:
				return 4;
			case eHero::HERO_MOIRA:
				return 4;
			case eHero::HERO_BRIGITTE:
				return 4;
			case eHero::HERO_WRECKINGBALL:
				return 1;
			case eHero::HERO_ASHE:
				return 4;
			case eHero::HERO_BAPTISTE:
				return 4;
			case eHero::HERO_SIGMA:
				return 4;
			case eHero::HERO_TRAININGBOT1:
				return 7;
			case eHero::HERO_TRAININGBOT2:
				return 7;
			case eHero::HERO_TRAININGBOT3:
				return 7;
			case eHero::HERO_TRAININGBOT4:
				return 7;
			default:
				return 0;
			}
		}

		int GetHeadBoneIndex()
		{
			switch (HeroID)
			{
			case eHero::HERO_REAPER:
				return 12;
			case eHero::HERO_TRACER:
				return 12;
			case eHero::HERO_MERCY:
				return 12;
			case eHero::HERO_HANJO:
				return 12;
			case eHero::HERO_TORBJORN:
				return 17;
			case eHero::HERO_REINHARDT:
				return 15;
			case eHero::HERO_PHARAH:
				return 14;
			case eHero::HERO_WINSTON:
				return 13; //or 12
			case eHero::HERO_WIDOWMAKER:
				return 12;
			case eHero::HERO_BASTION:
				return 12;
			case eHero::HERO_SYMMETRA:
				return 12;
			case eHero::HERO_ZENYATTA:
				return 12;
			case eHero::HERO_GENJI:
				return 12;
			case eHero::HERO_ROADHOG:
				return 14;
			case eHero::HERO_MCCREE:
				return 12;
			case eHero::HERO_JUNKRAT:
				return 13;
			case eHero::HERO_ZARYA:
				return 12;
			case eHero::HERO_SOLDIER76:
				return 12;
			case eHero::HERO_LUCIO:
				return 12;
			case eHero::HERO_DVA:
				if (GetBoneRealCount() > 240)
					return 15;
				else
					return 12; //or 11
			case eHero::HERO_MEI:
				return 13;
			case eHero::HERO_ANA:
				return 12;
			case eHero::HERO_SOMBRA:
				return 12;
			case eHero::HERO_ORISA:
				return 10;
			case eHero::HERO_DOOMFIST:
				return 13;
			case eHero::HERO_MOIRA:
				return 12;
			case eHero::HERO_BRIGITTE:
				return 16;
			case eHero::HERO_WRECKINGBALL:
				return 20;
			case eHero::HERO_ASHE:
				return 12;
			case eHero::HERO_BAPTISTE:
				return 12;
			case eHero::HERO_SIGMA:
				return 14;
			case eHero::HERO_TRAININGBOT1:
				return 6;
			case eHero::HERO_TRAININGBOT2:
				return 6;
			case eHero::HERO_TRAININGBOT3:
				return 6;
			case eHero::HERO_TRAININGBOT4:
				return 6;
			default:
				return 0;
			}
		}

		uint64_t GetBoneStruct();

		void RefreshBones(uint64_t m_refreshBones)
		{
			__try
			{
				if (!GetBoneCount())
				{
					reinterpret_cast<void(__fastcall*)(uint64_t, uint64_t)>(m_refreshBones)(Component_ROTATION.ComponentBase, NULL);
					reinterpret_cast<void(__fastcall*)(uint64_t, uint64_t)>(m_refreshBones)(Component_ROTATION.ComponentBase, GetBoneStruct());
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}

		uint16_t GetBoneIndex(int index)
		{
			return RPM<uint16_t>(RPM<uint64_t>(Component_ROTATION.ComponentBase + 0x16B0) + index * sizeof(uint16_t));
		}

		uint32_t GetBoneCount()
		{
			return RPM<uint32_t>(Component_ROTATION.ComponentBase + 0x16B8); //0x978
		}

		uint16_t GetBoneRealCount()
		{
			return RPM<uint16_t>(GetBoneStruct() + 0x30);
		}

		XMFLOAT3 GetBoneVector(int index)
		{
			__try
			{
				if (GetBoneStruct())
				{
					XMFLOAT3 result;
					uint64_t boneStruct = RPM<uint64_t>(GetBoneStruct() + 0x8) + (index * 0x30);
					XMFLOAT3 bonePos = RPM<XMFLOAT3>(boneStruct + 0x20);
					XMMATRIX rotMatrix = XMMatrixRotationY(GetRotMatrix().y);
					XMStoreFloat3(&result, XMVector3Transform(XMLoadFloat3(&bonePos), rotMatrix));
					return result;
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return XMFLOAT3{};
		}

		bool IntersectRayWithAABB(Matrix viewMatrix, XMFLOAT3 origin, XMFLOAT3 direction, XMFLOAT3 min, XMFLOAT3 max, float scale, XMFLOAT3 basePos, bool isHead)
		{
			XMStoreFloat3(&min, XMLoadFloat3(&min) * scale);
			XMStoreFloat3(&max, XMLoadFloat3(&max) * scale);

			XMFLOAT3 points[] = {
				XMFLOAT3(min.x, min.y, min.z),
				XMFLOAT3(min.x, max.y, min.z),
				XMFLOAT3(max.x, max.y, min.z),
				XMFLOAT3(max.x, min.y, min.z),
				XMFLOAT3(max.x, max.y, max.z),
				XMFLOAT3(min.x, max.y, max.z),
				XMFLOAT3(min.x, min.y, max.z),
				XMFLOAT3(max.x, min.y, max.z)
			};

			XMFLOAT2 pointsTransformed[8];
			RECT minmaxTransformed{ 518523, 518523, 0, 0 };
			for (int i = 0; i < 8; i++)
			{
				XMMATRIX rotMatrix = isHead ? XMMatrixRotationX(GetRotMatrix().z) * XMMatrixRotationY(GetRotMatrix().y) : XMMatrixRotationY(GetRotMatrix().y);
				XMStoreFloat3(&points[i], XMVector3Transform(XMLoadFloat3(&points[i]), rotMatrix));
				XMStoreFloat3(&points[i], XMLoadFloat3(&points[i]) + XMLoadFloat3(&basePos));
				viewMatrix.WorldToScreen(points[i], &pointsTransformed[i]);
				minmaxTransformed.left = fmin(minmaxTransformed.left, pointsTransformed[i].x);
				minmaxTransformed.top = fmin(minmaxTransformed.top, pointsTransformed[i].y);
				minmaxTransformed.right = fmax(minmaxTransformed.right, pointsTransformed[i].x);
				minmaxTransformed.bottom = fmax(minmaxTransformed.bottom, pointsTransformed[i].y);
			}

			RECT rcTemp{}, crossHair{ g_Width / 2 - 1, g_Height / 2 - 1, g_Width / 2 + 1, g_Height / 2 + 1 };
			return IntersectRect(&rcTemp, &minmaxTransformed, &crossHair);
		}

		void DrawHitbox(Matrix viewMatrix, XMFLOAT3 min, XMFLOAT3 max, float scale, XMFLOAT3 basePos, uint32_t color, bool isHead)
		{
			XMStoreFloat3(&min, XMLoadFloat3(&min) * scale);
			XMStoreFloat3(&max, XMLoadFloat3(&max) * scale);

			XMFLOAT3 points[] = {
				XMFLOAT3(min.x, min.y, min.z),
				XMFLOAT3(min.x, max.y, min.z),
				XMFLOAT3(max.x, max.y, min.z),
				XMFLOAT3(max.x, min.y, min.z),
				XMFLOAT3(max.x, max.y, max.z),
				XMFLOAT3(min.x, max.y, max.z),
				XMFLOAT3(min.x, min.y, max.z),
				XMFLOAT3(max.x, min.y, max.z)
			};

			for (int i = 0; i < 8; i++)
			{
				XMMATRIX rotMatrix = isHead ? XMMatrixRotationX(GetRotMatrix().z) * XMMatrixRotationY(GetRotMatrix().y) : XMMatrixRotationY(GetRotMatrix().y);
				XMStoreFloat3(&points[i], XMVector3Transform(XMLoadFloat3(&points[i]), rotMatrix));
				XMStoreFloat3(&points[i], XMLoadFloat3(&points[i]) + XMLoadFloat3(&basePos));
			}

			XMFLOAT2 startPos, endPos;
			for (int i = 0; i < 3; i++)
			{
				if (viewMatrix.WorldToScreen(points[i], &startPos))
					if (viewMatrix.WorldToScreen(points[i + 1], &endPos))
						g_D3DRenderer->RenderLine(startPos, endPos, color);
			}
			if (viewMatrix.WorldToScreen(points[0], &startPos))
				if (viewMatrix.WorldToScreen(points[3], &endPos))
					g_D3DRenderer->RenderLine(startPos, endPos, color);

			for (int i = 4; i < 7; i++)
			{
				if (viewMatrix.WorldToScreen(points[i], &startPos))
					if (viewMatrix.WorldToScreen(points[i + 1], &endPos))
						g_D3DRenderer->RenderLine(startPos, endPos, color);
			}
			if (viewMatrix.WorldToScreen(points[4], &startPos))
				if (viewMatrix.WorldToScreen(points[7], &endPos))
					g_D3DRenderer->RenderLine(startPos, endPos, color);

			if (viewMatrix.WorldToScreen(points[0], &startPos))
				if (viewMatrix.WorldToScreen(points[6], &endPos))
					g_D3DRenderer->RenderLine(startPos, endPos, color);

			if (viewMatrix.WorldToScreen(points[1], &startPos))
				if (viewMatrix.WorldToScreen(points[5], &endPos))
					g_D3DRenderer->RenderLine(startPos, endPos, color);

			if (viewMatrix.WorldToScreen(points[2], &startPos))
				if (viewMatrix.WorldToScreen(points[4], &endPos))
					g_D3DRenderer->RenderLine(startPos, endPos, color);

			if (viewMatrix.WorldToScreen(points[3], &startPos))
				if (viewMatrix.WorldToScreen(points[7], &endPos))
					g_D3DRenderer->RenderLine(startPos, endPos, color);
		}

		void SetOutlineInfo(uint64_t m_getOutlineStruct, uint64_t m_getOutlineKey, uint64_t m_getOutlineColorStruct, uint32_t OutlineType, uint32_t OutlineColor)
		{
			__try
			{
				if (Component_OUTLINE.IsValid())
				{
					uint64_t outlineStruct = reinterpret_cast<uint64_t(__fastcall*)(uint64_t)>(m_getOutlineStruct)(Component_OUTLINE.ComponentBase + 0x20);
					uint64_t XorKey = spoof_call(reinterpret_cast<uint64_t(__fastcall*)(uint64_t)>(m_getOutlineKey), RPM<uint64_t>(outlineStruct + 0x18));
					WPM<uint64_t>(outlineStruct + 0x10, XorKey ^ OutlineType);

					uint64_t outlineColorStruct = reinterpret_cast<uint64_t(__fastcall*)(uint64_t)>(m_getOutlineColorStruct)(Component_OUTLINE.ComponentBase + 0x20);
					WPM<uint32_t>(outlineColorStruct + 0x10, OutlineColor);
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}

		float GetHanjoCharge()
		{
			__try
			{
				if (Component_SKILL.IsValid() && IsValid() && GetHeroID() == eHero::HERO_HANJO)
				{
					uint64_t skillStruct = RPM<uint64_t>(Component_SKILL.ComponentBase + 0x14B0 - 0x8); //Size of component
					if (skillStruct)
					{
						uint64_t skillCount = RPM<uint32_t>(skillStruct + 0x20);
						skillStruct = RPM<uint64_t>(skillStruct + 0x18);
						for (int i = 0; i < skillCount; i++)
						{
							uint32_t skillIdx = RPM<uint32_t>(skillStruct + i * 0x90 + 0x20) - 1;
							for (int j = 0; j < skillIdx + 1; j++)
							{
								uint64_t skillStruct2 = RPM<uint64_t>(skillStruct + i * 0x90 + 0x18);
								if (skillStruct2)
								{
									uint64_t a1 = RPM<uint64_t>(skillStruct2 + j * 0x30);
									uint32_t a2 = RPM<uint32_t>(skillStruct2 + j * 0x30 + 0x20);
									uint64_t a3 = skillStruct2 + j * 0x30 + 0x10;
									uint64_t vFunc = RPM<uint64_t>(a1);

									if (a1 && a2 && a3) //if does not working exclude a2 valid check
									{
										if (i == 4 && j == 0)
										{
											switch (a2)
											{
											case -02:
												return reinterpret_cast<__m128(__fastcall*)(uint32_t, uint64_t)>(RPM<uint64_t>(vFunc))(a1, a3).m128_f32[0];
											case -01:
												return reinterpret_cast<__m128(__fastcall*)(uint32_t, uint64_t)>(RPM<uint64_t>(vFunc + 0x8))(a1, a3).m128_f32[0];
											default:
												return reinterpret_cast<__m128(__fastcall*)(uint64_t, uint32_t, uint64_t)>(RPM<uint64_t>(vFunc + 0x10))(a1, a2, a3).m128_f32[0];
											}
										}
									}
								}
							}
						}
					}
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return 0.f;
		}

		void clearTimestamp(uint64_t m_getSkillStruct, uint32_t skillIdx, uint32_t skillIdx2)
		{
			__try
			{
				if (Component_SKILL.IsValid() && IsValid())
				{
					__m128 skillStruct{};
					skillStruct.m128_u64[1] = Component_SKILL.ComponentBase + 0xD0;
					uint16_t skillId[20] = { skillIdx, skillIdx2 };
					uint64_t skill = reinterpret_cast<uint64_t(__fastcall*)(__m128*, uint16_t*)>(m_getSkillStruct)(&skillStruct, skillId);
					if (!skill)
						return;
					WPM<uint32_t>(skill + 0x78, 1);
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
		}

		uint32_t getTimestamp(uint64_t m_getSkillStruct, uint32_t skillIdx, uint32_t skillIdx2)
		{
			__try
			{
				if (Component_SKILL.IsValid() && IsValid())
				{
					__m128 skillStruct{};
					skillStruct.m128_u64[1] = Component_SKILL.ComponentBase + 0xD0;
					uint16_t skillId[20] = { skillIdx, skillIdx2 };
					uint64_t skill = reinterpret_cast<uint64_t(__fastcall*)(__m128*, uint16_t*)>(m_getSkillStruct)(&skillStruct, skillId);
					if (!skill)
						return NULL;
					return RPM<uint32_t>(skill + 0x78);
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return NULL;
		}

		//Genji 7, 0x2BB //0, 0x28E3 ;dash
		//Sombra 0, 0x7C5 //0, 0x25A8 ;teleport invisible
		//Moira 0, 0xA0F
		//Zarya 5, 0x2BB //7, 0x6D8 ;ult
		//Reaper 1, 0x2BB
		//Doomfist 0, 0x254
		//Mei 6, 0x16F3
		//Tracer 0, 0x34A
		//Hanjo 0, 0x1DB5
		//Reinhardt 0, 0x156
		//Lucio 0, 0x34A
		//Sigma 6, 0xA0F
		bool isSkillAvtivate(uint64_t m_getSkillStruct, uint16_t skillIdx, uint16_t skillIdx2)
		{
			__try
			{
				if (Component_SKILL.IsValid() && IsValid())
				{
					__m128 skillStruct{};
					skillStruct.m128_u64[1] = Component_SKILL.ComponentBase + 0xD0;
					uint16_t skillId[20] = { skillIdx, skillIdx2 };
					uint64_t skill = reinterpret_cast<uint64_t(__fastcall*)(__m128*, uint16_t*)>(m_getSkillStruct)(&skillStruct, skillId);
					if (!skill)
						return false;
					return RPM<uint8_t>(skill + 0x70) == 1;
				}
			}
			__except (EXCEPTION_EXECUTE_HANDLER) {}
			return false;
		}

		bool isTargetable(uint64_t m_getSkillStruct)
		{
			if (!(GetHeroID() == eHero::HERO_GENJI && isSkillAvtivate(m_getSkillStruct, 7, 0x2BB)) &&
				!(GetHeroID() == eHero::HERO_GENJI && isSkillAvtivate(m_getSkillStruct, 0, 0x28E3)) &&
				!(GetHeroID() == eHero::HERO_SOMBRA && isSkillAvtivate(m_getSkillStruct, 0, 0x7C5)) &&
				!(GetHeroID() == eHero::HERO_MOIRA && isSkillAvtivate(m_getSkillStruct, 0, 0xA0F)) &&
				!(GetHeroID() == eHero::HERO_ZARYA && isSkillAvtivate(m_getSkillStruct, 5, 0x2BB)) &&
				!(GetHeroID() == eHero::HERO_REAPER && isSkillAvtivate(m_getSkillStruct, 1, 0x2BB)) &&
				!(GetHeroID() == eHero::HERO_DOOMFIST && isSkillAvtivate(m_getSkillStruct, 0, 0x254)))
			{
				return true;
			}
			return false;
		}
	};

	class Core
	{
	public:
		explicit Core();
		~Core() noexcept = default;
		Core(Core const&) = delete;
		Core(Core&&) = delete;
		Core& operator=(Core const&) = delete;
		Core& operator=(Core&&) = delete;

		std::vector<Component> Components_VELOCITY;
		std::vector<Component> Components_BONE;
		std::vector<Component> Components_TEAM;
		std::vector<Component> Components_ROTATION;
		std::vector<Component> Components_ID;
		std::vector<Component> Components_P_VISIBILITY;
		std::vector<Component> Components_SKILL;
		std::vector<Component> Components_HEALTH;
		std::vector<Component> Components_P_HEROID;
		std::vector<Component> Components_OUTLINE;
		Component			   Components_ANGLE;

		std::vector<Entity> Entities;
		Entity localEntity{ 0 };

		uint32_t m_Timestamp_Zarya{};
		uint32_t m_Timestamp_Mei{};

		uint64_t m_ComponentHook{};
		void* o_ComponentHook{};

		uint64_t m_viewMatrix{};
		uint64_t m_ViewMatrixHook{};
		void* o_ViewMatrixHook{};

		Timer* holdTimer;
		uint32_t m_Input{};
		uint64_t m_InputHook{};
		void* o_InputHook{};

		uint64_t m_localHero{};
		uint64_t m_LocalHook{};
		void* o_LocalHook{};

		uint32_t m_getRootVecOffset{};
		uint64_t m_getRootVec{};
		uint64_t m_getBoneStruct{};
		uint64_t m_refreshBones{};
		uint64_t m_getOutlineStruct{};
		uint64_t m_getOutlineKey{};
		uint64_t m_getOutlineColorStruct{};
		uint64_t m_fixOutlineError{};
		uint64_t m_getSkillStruct{};
		uint64_t m_decryptVisible{};
		uint64_t m_decryptVisible2{};
		uint64_t m_decryptID{};

		Matrix GetViewMatrix()
		{
			return RPM<Matrix>(m_viewMatrix);
		}

		XMFLOAT3 GetAngle()
		{
			return RPM<XMFLOAT3>(Components_ANGLE.ComponentBase + 0x10B0);
		}

		void SetAngle(XMFLOAT3 dstAngle, XMFLOAT3 dstAngleY)
		{
			WPM<float>(Components_ANGLE.ComponentBase + 0x10B0, dstAngle.x);
			WPM<float>(Components_ANGLE.ComponentBase + 0x10B4, dstAngleY.y);
			WPM<float>(Components_ANGLE.ComponentBase + 0x10B8, dstAngle.z);
		}

		uint32_t GetKey()
		{
			return RPM<uint32_t>(Components_ANGLE.ComponentBase + 0x1054);
		}

		void SetKey(uint32_t Key)
		{
			WPM<uint32_t>(Components_ANGLE.ComponentBase + 0x1054, Key);
		}

		void SetKeyHold(uint32_t Key, std::chrono::milliseconds sleep)
		{
			if (!m_Input)
			{
				holdTimer->Update();
				holdTimer->SetDelay(sleep);
				m_Input = Key;
			}
		}

		friend struct CoreHooks;
	private:
	};

	inline std::unique_ptr<Core> g_Core;
}