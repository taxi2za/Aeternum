#include "Hooking.hpp"
#include "Game.hpp"
#include "D3DRenderer.hpp"
#include <MinHook/MinHook.h>
#include "Core.hpp"

//# DO NOT C&P IF U DUNNO HOW TO USE IT
//> he4rtbleed - https://github.com/he4rtbleed/Aeternum

#ifdef AETERNUM_DEBUG
#  pragma comment(lib, "MinHook-Debug.lib")
#else
#  pragma comment(lib, "MinHook-Release.lib")
#endif

namespace Aeternum
{
	LRESULT Hooks::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		g_D3DRenderer->WndProc(hWnd, msg, wParam, lParam);
		return CallWindowProc((WNDPROC)g_Hooking->m_OldWndProc, hWnd, msg, wParam, lParam);
	}

	void AutoSkill(Entity entity)
	{
		if (entity.GetLife().y)
		{
			if (entity.GetTeam() == eTeam::TEAM_DEATHMATCH || entity.GetTeam() != g_Core->localEntity.GetTeam())
			{
				if (entity.GetHeroID() == eHero::HERO_ZARYA)
				{
					uint32_t Timestamp = entity.getTimestamp(g_Core->m_getSkillStruct, 7, 0x6D8);
					if (Timestamp && Timestamp != 0xA0000000)
					{
						if (Timestamp != g_Core->m_Timestamp_Zarya)
						{
							g_Core->m_Timestamp_Zarya = Timestamp;

							if (g_Core->localEntity.GetHeroID() == eHero::HERO_DVA)
							{
								if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Dva_Zarya)
									g_Core->SetKey(eInput::INPUT_RMOUSE);
							}
							else if (g_Core->localEntity.GetHeroID() == eHero::HERO_SIGMA)
							{
								if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Sigma_Zarya)
									g_Core->SetKey(eInput::INPUT_SKILL1);
							}
						}
					}
				}
				else if (entity.GetHeroID() == eHero::HERO_MEI)
				{
					uint32_t Timestamp = entity.getTimestamp(g_Core->m_getSkillStruct, 6, 0x16F3);
					if (Timestamp && Timestamp != 0xA0000000)
					{
						if (Timestamp != g_Core->m_Timestamp_Mei)
						{
							g_Core->m_Timestamp_Mei = Timestamp;

							if (g_Core->localEntity.GetHeroID() == eHero::HERO_DVA)
							{
								if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Dva_Mei)
									g_Core->SetKey(eInput::INPUT_RMOUSE);
							}
							else if (g_Core->localEntity.GetHeroID() == eHero::HERO_SIGMA)
							{
								if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Sigma_Mei)
									g_Core->SetKey(eInput::INPUT_SKILL1);
							}
						}
					}
				}
				else if (entity.GetHeroID() == eHero::HERO_TRACER)
				{
					if (entity.isSkillAvtivate(g_Core->m_getSkillStruct, 0, 0x34A))
					{
						if (g_Core->localEntity.GetHeroID() == eHero::HERO_DVA)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Dva_Tracer)
								g_Core->SetKey(eInput::INPUT_RMOUSE);
						}
						else if (g_Core->localEntity.GetHeroID() == eHero::HERO_SIGMA)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Sigma_Tracer)
								g_Core->SetKey(eInput::INPUT_SKILL1);
						}
					}
				}
				else if (entity.GetHeroID() == eHero::HERO_HANJO)
				{
					if (entity.isSkillAvtivate(g_Core->m_getSkillStruct, 0, 0x1DB5))
					{
						if (g_Core->localEntity.GetHeroID() == eHero::HERO_DVA)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Dva_Hanjo)
								g_Core->SetKeyHold(eInput::INPUT_RMOUSE, 1000ms);
						}
						else if (g_Core->localEntity.GetHeroID() == eHero::HERO_SIGMA)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Sigma_Hanjo)
								g_Core->SetKey(eInput::INPUT_SKILL1);
						}
					}
				}
				else if (entity.GetHeroID() == eHero::HERO_REINHARDT)
				{
					if (!entity.getTimestamp(g_Core->m_getSkillStruct, 0, 0x156))
					{
						entity.clearTimestamp(g_Core->m_getSkillStruct, 0, 0x156);
						if (g_Core->localEntity.GetHeroID() == eHero::HERO_SOMBRA)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Sombra_Reinhardt)
								g_Core->SetKey(eInput::INPUT_ULT);
						}
						else if (g_Core->localEntity.GetHeroID() == eHero::HERO_REINHARDT)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Reinhardt_Reinhardt)
								g_Core->SetKeyHold(eInput::INPUT_RMOUSE, 800ms);
						}
					}
				}
				else if (entity.GetHeroID() == eHero::HERO_LUCIO)
				{
					if (entity.isSkillAvtivate(g_Core->m_getSkillStruct, 0, 0x34A))
					{
						if (g_Core->localEntity.GetHeroID() == eHero::HERO_SOMBRA)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Sombra_Lucio)
								g_Core->SetKey(eInput::INPUT_ULT);
						}
					}
				}
				else if (entity.GetHeroID() == eHero::HERO_SIGMA)
				{
					if (entity.isSkillAvtivate(g_Core->m_getSkillStruct, 6, 0xA0F))
					{
						if (g_Core->localEntity.GetHeroID() == eHero::HERO_SOMBRA)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Sombra_Sigma)
								g_Core->SetKey(eInput::INPUT_ULT);
						}
					}
				}
				else if (entity.GetHeroID() == eHero::HERO_ANA)
				{
					if (entity.isSkillAvtivate(g_Core->m_getSkillStruct, 6, 0x31))
					{
						if (g_Core->localEntity.GetHeroID() == eHero::HERO_GENJI)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Genji_Ana)
								g_Core->SetKey(eInput::INPUT_SKILL2);
						}
					}
				}
				else if (entity.GetHeroID() == eHero::HERO_MCCREE)
				{
					if (entity.isSkillAvtivate(g_Core->m_getSkillStruct, 0, 0x28E9))
					{
						if (g_Core->localEntity.GetHeroID() == eHero::HERO_TRACER)
						{
							if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) - XMLoadFloat3(&g_Core->GetViewMatrix().GetCameraVec()))) <= g_Config->m_Tracer_McCree)
								g_Core->SetKey(eInput::INPUT_SKILL2);
						}
					}
				}
			}
		}
	}

	void ESP()
	{
		try
		{
			if (g_Config->m_DrawFOV)
				g_D3DRenderer->RenderCircle(ImVec2(g_Width / 2, g_Height / 2), g_Config->m_Fov, 0xFFFFFFFF, 1.0, 128);

			float bestFov = g_Config->m_Fov;
			for (Entity entity : g_Core->Entities)
			{
				if (entity != g_Core->localEntity)
				{
					entity.RefreshBones(g_Core->m_refreshBones);

					if (g_Config->m_AutoSkill)
						AutoSkill(entity);

					XMFLOAT2 Life = entity.GetLife();
					Color health{ (uint8_t)std::min((510 * (100 - (int)(Life.y / Life.x * 100))) / 100, 255), (uint8_t)std::min((510 * (int)(Life.y / Life.x * 100)) / 100, 255), 0, 255 };

					bool isEnemy = entity.GetTeam() == eTeam::TEAM_DEATHMATCH || entity.GetTeam() != g_Core->localEntity.GetTeam();
					if (g_Config->m_OutlineESP)
						entity.SetOutlineInfo(g_Core->m_getOutlineStruct, g_Core->m_getOutlineKey, g_Core->m_getOutlineColorStruct, g_Config->m_OutlineType + 1, isEnemy ? entity.IsVisible() ? health.ApplyAlpha(255) : health.ApplyAlpha(100) : 0xFFFFFFFF);

					if (Life.y)
					{
						if (g_Config->m_ESP && isEnemy)
						{
							XMFLOAT2 outPos{};
							if (g_Core->GetViewMatrix().WorldToScreen(entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset), &outPos))
							{
								g_D3DRenderer->RenderText(entity.GetHeroName(), ImVec2(outPos.x, outPos.y), 20, entity.IsVisible() ? health.RGBA2ARGB(255) : health.RGBA2ARGB(100), true);

								if (g_Config->m_ShowBoneAnkle)
								{
									for (int i = 0; i < entity.GetBoneCount(); i++)
									{
										XMFLOAT3 bonePos;
										XMStoreFloat3(&bonePos, XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&entity.GetBoneVector(entity.GetBoneIndex(i))));
										if (g_Core->GetViewMatrix().WorldToScreen(bonePos, &outPos))
										{
											if (g_Config->m_ESP)
												g_D3DRenderer->RenderCircleFilled(ImVec2(outPos.x, outPos.y), 2, entity.IsVisible() ? health.RGBA2ARGB(255) : health.RGBA2ARGB(100));
										}
									}
								}

								if (g_Config->m_ShowHitbox)
								{
									XMFLOAT3 bonePos;
									XMStoreFloat3(&bonePos, XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&entity.GetBoneVector(entity.GetBoneIndex(entity.GetHeadBoneIndex()))));
									entity.DrawHitbox(g_Core->GetViewMatrix(), g_Config->min, g_Config->max, g_Config->m_TriggerScale / 100.f, bonePos, entity.IsVisible() ? health.RGBA2ARGB(255) : health.RGBA2ARGB(100), true);
									XMStoreFloat3(&bonePos, XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&entity.GetBoneVector(entity.GetBoneIndex(entity.GetBodyBoneIndex()))));
									entity.DrawHitbox(g_Core->GetViewMatrix(), g_Config->min2, g_Config->max2, g_Config->m_TriggerScale / 100.f, bonePos, entity.IsVisible() ? health.RGBA2ARGB(255) : health.RGBA2ARGB(100), false);
								}
							}
						}

						if (!g_Config->m_Teambot && !isEnemy)
							continue;
						
						if (isEnemy && !entity.isTargetable(g_Core->m_getSkillStruct))
							continue;

						{
							XMFLOAT2 outPos{};
							XMFLOAT3 bodyPos;
							XMStoreFloat3(&bodyPos, XMLoadFloat3(&entity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&entity.GetBoneVector(entity.GetBoneIndex(entity.GetBodyBoneIndex()))));
							if (g_Core->GetViewMatrix().WorldToScreen(bodyPos, &outPos))
							{
								Vector2 mPos = { outPos.x - g_Width / 2, outPos.y - g_Height / 2 };
								float fovDist = mPos.Size();
								if (fovDist < 360 && entity.IsVisible() && isEnemy)
								{
									if (g_Config->m_AutoMelee)
									{
										if (g_Config->m_AutoMeleeIsPercent)
										{
											if ((Life.y / Life.x) * 100.f <= g_Config->m_AutoMeleePercent)
											{
												XMFLOAT3 locPos = g_Core->GetViewMatrix().GetCameraVec();
												if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&bodyPos) - XMLoadFloat3(&locPos))) <= 3.f)
												{
													g_Core->SetKey(INPUT_MELEE);
												}
											}
										}
										else
										{
											if (Life.y <= 30.f)
											{
												XMFLOAT3 locPos = g_Core->GetViewMatrix().GetCameraVec();
												if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&bodyPos) - XMLoadFloat3(&locPos))) <= 3.f)
												{
													g_Core->SetKey(INPUT_MELEE);
												}
											}
										}
									}
								}
								if (fovDist < bestFov && entity.IsVisible())
								{
									if (g_Config->m_AutoDash)
									{
										if (g_Core->localEntity.GetHeroID() == eHero::HERO_GENJI)
										{
											if (g_Config->m_AutoDashIsPercent)
											{
												if ((Life.y / Life.x) * 100.f <= g_Config->m_AutoDashPercent)
												{
													XMFLOAT3 locPos = g_Core->GetViewMatrix().GetCameraVec();
													if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&bodyPos) - XMLoadFloat3(&locPos))) <= 15.f)
													{
														g_Core->SetKey(INPUT_SKILL1);
													}
												}
											}
											else
											{
												if (Life.y <= 50.f)
												{
													XMFLOAT3 locPos = g_Core->GetViewMatrix().GetCameraVec();
													if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&bodyPos) - XMLoadFloat3(&locPos))) <= 15.f)
													{
														g_Core->SetKey(INPUT_SKILL1);
													}
												}
											}
										}
									}
									bestFov = fovDist;
									if (g_Config->m_LockTarget)
									{
										if (!g_Hooking->bestEntity.IsValid())
											g_Hooking->bestEntity = entity;
									}
									else
										g_Hooking->bestEntity = entity;
								}
							}
						}
					}
				}
			}

			if (g_Hooking->bestEntity != g_Hooking->prevEntity)
				g_Hooking->m_Time = 0;

			g_Hooking->prevEntity = g_Hooking->bestEntity;

			if (g_Hooking->bestEntity.IsValid())
			{
				if (g_Config->m_OutlineESP)
					g_Hooking->bestEntity.SetOutlineInfo(g_Core->m_getOutlineStruct, g_Core->m_getOutlineKey, g_Core->m_getOutlineColorStruct, g_Config->m_OutlineType + 1, 0xFFFFFF00);

				XMFLOAT2 Life = g_Hooking->bestEntity.GetLife();
				Color health{ (uint8_t)std::min((510 * (100 - (int)(Life.y / Life.x * 100))) / 100, 255), (uint8_t)std::min((510 * (int)(Life.y / Life.x * 100)) / 100, 255), 0, 255 };

				XMFLOAT2 outPos{};
				XMFLOAT3 bodyPos{};
				XMStoreFloat3(&bodyPos, XMLoadFloat3(&g_Hooking->bestEntity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&g_Hooking->bestEntity.GetBoneVector(g_Hooking->bestEntity.GetBoneIndex(g_Hooking->bestEntity.GetBodyBoneIndex()))));
				if (g_Core->GetViewMatrix().WorldToScreen(bodyPos, &outPos))
				{
					Vector2 mPos = { outPos.x - g_Width / 2, outPos.y - g_Height / 2 };
					float fovDist = mPos.Size();
					if (fovDist < g_Config->m_Fov && g_Hooking->bestEntity.IsVisible())
					{
						if (g_Config->m_ESP)
						{
							if (g_Core->GetViewMatrix().WorldToScreen(g_Hooking->bestEntity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset), &outPos))
							{
								auto lockStr = skCrypt("\n*LOCKED*");
								g_D3DRenderer->RenderText(lockStr.decrypt(), ImVec2(outPos.x, outPos.y), 20, health.RGBA2ARGB(255), true);
								lockStr.clear();
							}
						}
					}
					else
						g_Hooking->bestEntity = Entity{};
				}
			}
		}
		catch (...) {}
	}

	std::once_flag once;
	HRESULT Hooks::Present(IDXGISwapChain* dis, UINT syncInterval, UINT flags)
	{
		std::call_once(once, [dis]() {
			g_GameVariables->m_Swapchain = dis;
			g_D3DRenderer->PostInit(dis); });

		if (g_Running)
		{
			g_D3DRenderer->BeginFrame();

			ImGui::SetNextWindowPos(ImVec2(50, 50), ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Once);

			std::stringstream ExpireDate;
			ExpireDate << g_Username << skCrypt(" - ") << std::put_time(std::gmtime(&g_Expire), "%Y-%m-%d %I:%M:%S %p");
			ImGui::Begin(ExpireDate.str().c_str(), NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings);
			ImGui::SetWindowSize(ImVec2(330.5f, 600.0f));

			if (strcmp(g_Config->m_Preset, g_Core->localEntity.GetHeroName().c_str()))
			{
				if (g_Core->localEntity.IsValid())
					memcpy(g_Config->m_Preset, g_Core->localEntity.GetHeroName().c_str(), sizeof(g_Config->m_Preset));
				else
					memcpy(g_Config->m_Preset, skCrypt("default"), sizeof(g_Config->m_Preset));
				g_Config->Load();
			}
			ImGui::InputText(skCrypt("PRESET"), g_Config->m_Preset, sizeof(g_Config->m_Preset));
			if (ImGui::Button(skCrypt("SAVE")))
				g_Config->Save();
			ImGui::SameLine();
			if (ImGui::Button(skCrypt("LOAD")))
				g_Config->Load();
			ImGui::SameLine();
			if (ImGui::Button(skCrypt("INIT")))
				g_Config->Init();
			ImGui::Separator();
			ImGui::Checkbox(skCrypt("Optimize"), &g_Config->m_Optimize);
			ImGui::Checkbox(skCrypt("DrawFOV"), &g_Config->m_DrawFOV);
			ImGui::SliderFloat(skCrypt("FOV"), &g_Config->m_Fov, 10.f, 1000.f, "%.f");
			ImGui::Separator();
			ImGui::Checkbox(skCrypt("ESP"), &g_Config->m_ESP);
			if (g_Config->m_ESP)
			{
				ImGui::Checkbox(skCrypt("Show Hitbox"), &g_Config->m_ShowHitbox);
				ImGui::Checkbox(skCrypt("Show Ankle"), &g_Config->m_ShowBoneAnkle);
			}
			ImGui::Checkbox(skCrypt("Outline ESP"), &g_Config->m_OutlineESP);
			if (g_Config->m_OutlineESP)
				ImGui::Combo(skCrypt("Outline TYPE"), &g_Config->m_OutlineType, g_Config->m_OutlineStrs, IM_ARRAYSIZE(g_Config->m_OutlineStrs));
			ImGui::Separator();

			ImGui::Checkbox(skCrypt("Trigger Bot"), &g_Config->m_Triggerbot);
			if (g_Config->m_Triggerbot)
			{
				ImGui::SliderFloat(skCrypt("Trigger Scale"), &g_Config->m_TriggerScale, 10.f, 200.f, "%.f");
				ImGui::Checkbox(skCrypt("IsLeft"), &g_Config->m_IsLeft);
				ImGui::Checkbox(skCrypt("Flick"), &g_Config->m_Flick);
			}
			ImGui::Separator();

			ImGui::Hotkey("1", &g_Config->m_AimKey1, ImVec2(90, 25));
			ImGui::Hotkey("2", &g_Config->m_AimKey2, ImVec2(90, 25));
			ImGui::Checkbox(skCrypt("Aim Assistant"), &g_Config->m_Aimbot);
			ImGui::Checkbox(skCrypt("Team Bot"), &g_Config->m_Teambot);
			ImGui::Checkbox(skCrypt("Lock Target"), &g_Config->m_LockTarget);
			if (g_Config->m_LockTarget)
				ImGui::SliderInt(skCrypt("Lock Time"), &g_Config->m_LockTargetTimer, 0, 1000, "%.f");
			ImGui::Checkbox(skCrypt("Fix Accuracy"), &g_Config->m_FixedAccuracy);
			if (g_Config->m_FixedAccuracy)
				ImGui::SliderFloat(skCrypt("Accuracy"), &g_Config->m_Accuracy, 0.f, 100.f, "%.f");
			ImGui::Checkbox(skCrypt("Smooth Type"), &g_Config->m_SmoothType);
			if (g_Config->m_SmoothType)
			{
				ImGui::SliderFloat(skCrypt("SmoothFactor"), &g_Config->m_SmoothFactor, 0.f, 100.f, "%.f");
				ImGui::SliderFloat(skCrypt("Smooth"), &g_Config->m_Smooth, 0.f, 100.f, "%.f");
			}
			else
			{
				ImGui::SliderFloat(skCrypt("Smooth-X"), &g_Config->m_SmoothX, 0.f, 1000.f, "%.f");
				ImGui::SliderFloat(skCrypt("Smooth-Y"), &g_Config->m_SmoothY, 0.f, 1000.f, "%.f");
			}
			ImGui::Separator();

			ImGui::Checkbox(skCrypt("Prediction"), &g_Config->m_Prediction);
			if (g_Config->m_Prediction)
			{
				ImGui::SliderFloat(skCrypt("Speed"), &g_Config->m_Speed, 0, 1000.f, "%.1f");
				ImGui::SliderFloat(skCrypt("Gravity"), &g_Config->m_Gravity, 0, 300.f, "%.f");
				ImGui::SliderFloat(skCrypt("Charge"), &g_Config->m_Charge, 0, 100.f, "%.f");
			}
			ImGui::Separator();

			ImGui::Checkbox(skCrypt("Auto Melee"), &g_Config->m_AutoMelee);
			if (g_Config->m_AutoMelee)
			{
				ImGui::Checkbox(skCrypt("Auto Melee Percent"), &g_Config->m_AutoMeleeIsPercent);
				ImGui::SliderFloat(skCrypt("Auto Melee Percent"), &g_Config->m_AutoMeleePercent, 0.f, 100.f, "%.f");
			}
			ImGui::Checkbox(skCrypt("Auto Dash"), &g_Config->m_AutoDash);
			if (g_Config->m_AutoDash)
			{
				ImGui::Checkbox(skCrypt("Auto Dash Percent"), &g_Config->m_AutoDashIsPercent);
				ImGui::SliderFloat(skCrypt("Auto Dash Percent"), &g_Config->m_AutoDashPercent, 0.f, 100.f, "%.f");
			}

			ImGui::Checkbox(skCrypt("Auto Skill"), &g_Config->m_AutoSkill);
			if (g_Config->m_AutoSkill)
			{
				ImGui::SliderFloat(skCrypt("D.Va - Zarya"), &g_Config->m_Dva_Zarya, 0.f, 30.f, "%.f");
				ImGui::SliderFloat(skCrypt("Sigma - Zarya"), &g_Config->m_Sigma_Zarya, 0.f, 30.f, "%.f");

				ImGui::SliderFloat(skCrypt("D.Va - Mei"), &g_Config->m_Dva_Mei, 0.f, 30.f, "%.f");
				ImGui::SliderFloat(skCrypt("Sigma - Mei"), &g_Config->m_Sigma_Mei, 0.f, 30.f, "%.f");

				ImGui::SliderFloat(skCrypt("D.Va - Tracer"), &g_Config->m_Dva_Tracer, 0.f, 30.f, "%.f");
				ImGui::SliderFloat(skCrypt("Sigma - Tracer"), &g_Config->m_Sigma_Tracer, 0.f, 30.f, "%.f");

				ImGui::SliderFloat(skCrypt("D.Va - Hanjo"), &g_Config->m_Dva_Hanjo, 0.f, 30.f, "%.f");
				ImGui::SliderFloat(skCrypt("Sigma - Hanjo"), &g_Config->m_Sigma_Hanjo, 0.f, 30.f, "%.f");

				ImGui::SliderFloat(skCrypt("Sombra - Reinhardt"), &g_Config->m_Sombra_Reinhardt, 0.f, 30.f, "%.f");
				ImGui::SliderFloat(skCrypt("Reinhardt - Reinhardt"), &g_Config->m_Reinhardt_Reinhardt, 0.f, 30.f, "%.f");

				ImGui::SliderFloat(skCrypt("Sombra - Lucio"), &g_Config->m_Sombra_Lucio, 0.f, 30.f, "%.f");
				ImGui::SliderFloat(skCrypt("Sombra - Sigma"), &g_Config->m_Sombra_Sigma, 0.f, 30.f, "%.f");
				ImGui::SliderFloat(skCrypt("Genji - Ana"), &g_Config->m_Genji_Ana, 0.f, 30.f, "%.f");
				ImGui::SliderFloat(skCrypt("Tracer - McCree"), &g_Config->m_Tracer_McCree, 0.f, 30.f, "%.f");
			}
			//ImGui::Checkbox(skCrypt("Debug"), &g_Config->m_Debug);
			ImGui::End();

			g_D3DRenderer->BeginScene();

			
			/*if (g_Config->m_Debug)
			{
				std::stringstream debugStr;
				debugStr << g_Core->localEntity.GetHeroName() << "\n"
					<< std::hex
					<< skCrypt("Velocity \t: ") << g_Core->localEntity.Component_VELOCITY.ComponentBase << ", " << g_Core->localEntity.Component_VELOCITY.ComponentParent << ", " << g_Core->Components_VELOCITY.size() << "\n"
					<< skCrypt("Bone \t: ") << g_Core->localEntity.Component_BONE.ComponentBase << ", " << g_Core->localEntity.Component_BONE.ComponentParent << ", " << g_Core->Components_BONE.size() << "\n"
					<< skCrypt("Team \t: ") << g_Core->localEntity.Component_TEAM.ComponentBase << ", " << g_Core->localEntity.Component_TEAM.ComponentParent << ", " << g_Core->Components_TEAM.size() << "\n"
					<< skCrypt("Rotation \t: ") << g_Core->localEntity.Component_ROTATION.ComponentBase << ", " << g_Core->localEntity.Component_ROTATION.ComponentParent << ", " << g_Core->Components_ROTATION.size() << "\n"
					<< skCrypt("ID \t: ") << g_Core->localEntity.Component_ID.ComponentBase << ", " << g_Core->localEntity.Component_ID.ComponentParent << ", " << g_Core->Components_ID.size() << "\n"
					<< skCrypt("P - Vis \t: ") << g_Core->localEntity.Component_P_VISIBILITY.ComponentBase << ", " << g_Core->localEntity.Component_P_VISIBILITY.ComponentParent << ", " << g_Core->Components_P_VISIBILITY.size() << "\n"
					<< skCrypt("Skill \t: ") << g_Core->localEntity.Component_SKILL.ComponentBase << ", " << g_Core->localEntity.Component_SKILL.ComponentParent << ", " << g_Core->Components_SKILL.size() << "\n"
					<< skCrypt("Health \t: ") << g_Core->localEntity.Component_HEALTH.ComponentBase << ", " << g_Core->localEntity.Component_HEALTH.ComponentParent << ", " << g_Core->Components_HEALTH.size() << "\n"
					<< skCrypt("P - HeroID \t: ") << g_Core->localEntity.Component_P_HEROID.ComponentBase << ", " << g_Core->localEntity.Component_P_HEROID.ComponentParent << ", " << g_Core->Components_P_HEROID.size() << "\n"
					<< skCrypt("Outline \t: ") << g_Core->localEntity.Component_OUTLINE.ComponentBase << ", " << g_Core->localEntity.Component_OUTLINE.ComponentParent << ", " << g_Core->Components_OUTLINE.size() << "\n"
					<< skCrypt("Angle \t: ") << g_Core->Components_ANGLE.ComponentBase << ", " << g_Core->Components_ANGLE.ComponentParent << "\n"
					<< skCrypt("Team \t: ") << g_Core->localEntity.GetTeam() << "\n"
					<< skCrypt("Input \t: ") << g_Core->GetKey() << "\n"
					<< std::dec
					<< skCrypt("BoneCount \t: ") << g_Core->localEntity.GetBoneCount() << "\n"
					<< skCrypt("BoneRealCount \t: ") << g_Core->localEntity.GetBoneRealCount() << "\n"
					<< skCrypt("PlayerCount \t: ") << g_Core->Entities.size() << "\n"
					<< skCrypt("Time \t: ") << g_Hooking->m_Time << "\n"
					//<< skCrypt("Charge \t: ") << g_Core->localEntity.GetHanjoCharge() << "\n"
					<< g_Core->GetAngle().x << " | " << g_Core->GetAngle().y << " | " << g_Core->GetAngle().z;
				g_D3DRenderer->RenderText(debugStr.str(), ImVec2(100, 100), 20, 0xFFFFFFFF, false);

				g_Core->localEntity.RefreshBones(g_Core->m_refreshBones);
				for (int i = 0; i < g_Core->localEntity.GetBoneCount(); i++)
				{
					XMFLOAT3 bonePos;
					XMFLOAT2 outPos{};
					XMStoreFloat3(&bonePos, XMLoadFloat3(&g_Core->localEntity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&g_Core->localEntity.GetBoneVector(g_Core->localEntity.GetBoneIndex(i))));
					if (g_Core->GetViewMatrix().WorldToScreen(bonePos, &outPos))
					{
						g_D3DRenderer->RenderCircleFilled(ImVec2(outPos.x, outPos.y), 2, 0xFFFFFFFF);
						g_D3DRenderer->RenderText(std::to_string(i), ImVec2(outPos.x, outPos.y), 16, 0xFFFFFFFF, true);
					}
				}
				XMFLOAT3 bonePos;
				XMStoreFloat3(&bonePos, XMLoadFloat3(&g_Core->localEntity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&g_Core->localEntity.GetBoneVector(g_Core->localEntity.GetBoneIndex(g_Core->localEntity.GetHeadBoneIndex()))));
				g_Core->localEntity.DrawHitbox(g_Core->GetViewMatrix(), g_Config->min, g_Config->max, g_Config->m_TriggerScale / 100.f, bonePos, 0xFFFFFFFF, true);
				XMStoreFloat3(&bonePos, XMLoadFloat3(&g_Core->localEntity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&g_Core->localEntity.GetBoneVector(g_Core->localEntity.GetBoneIndex(g_Core->localEntity.GetBodyBoneIndex()))));
				g_Core->localEntity.DrawHitbox(g_Core->GetViewMatrix(), g_Config->min2, g_Config->max2, g_Config->m_TriggerScale / 100.f, bonePos, 0xFFFFFFFF, false);
			}*/
			

			ESP();

			g_D3DRenderer->EndScene();

			g_D3DRenderer->EndFrame();
		}

		return reinterpret_cast<decltype(&Present)>(g_Hooking->m_OriginalPresent)(dis, syncInterval, flags);
	}

	HRESULT Hooks::ResizeBuffers(IDXGISwapChain* dis, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags)
	{
		if (g_Running)
		{
			g_D3DRenderer->PreResize();
			auto hr = reinterpret_cast<decltype(&ResizeBuffers)>(g_Hooking->m_OriginalResizeBuffers)(dis, bufferCount, width, height, newFormat, swapChainFlags);
			g_D3DRenderer->PostResize();

			return hr;
		}

		return reinterpret_cast<decltype(&ResizeBuffers)>(g_Hooking->m_OriginalResizeBuffers)(dis, bufferCount, width, height, newFormat, swapChainFlags);
	}

	NTSTATUS NTAPI Hooks::NtQuerySystemInformation(SYSTEM_INFORMATION_CLASS SystemInformationClass, PVOID SystemInformation, ULONG SystemInformationLength, PULONG ReturnLength)
	{
		if (SystemInformationClass == SystemProcessInformation)
		{
			return 0;
		}

		return reinterpret_cast<decltype(&NtQuerySystemInformation)>(g_Hooking->m_OriginalQSI)(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
	}

	void Cleaner()
	{
		__try
		{
			while (g_Running)
			{
				//remove useless and cleared components
				reComponent(&g_Core->Components_VELOCITY);
				reComponent(&g_Core->Components_BONE);
				reComponent(&g_Core->Components_TEAM);
				reComponent(&g_Core->Components_ROTATION);
				reComponent(&g_Core->Components_ID);
				reComponent(&g_Core->Components_P_VISIBILITY);
				reComponent(&g_Core->Components_SKILL);
				reComponent(&g_Core->Components_HEALTH);
				reComponent(&g_Core->Components_P_HEROID);
				reComponent(&g_Core->Components_OUTLINE);

				//Get whole entity list that have health component
				for (int i = 0; i < g_Core->Components_HEALTH.size(); i++)
				{
					uint64_t ComponentParent = g_Core->Components_HEALTH.at(i).ComponentParent;
					Entity entity(ComponentParent);

					swapComponent(&g_Core->Components_VELOCITY, &entity.Component_VELOCITY, ComponentParent);
					swapComponent(&g_Core->Components_BONE, &entity.Component_BONE, ComponentParent);
					swapComponent(&g_Core->Components_TEAM, &entity.Component_TEAM, ComponentParent);
					swapComponent(&g_Core->Components_ROTATION, &entity.Component_ROTATION, ComponentParent);
					swapComponent(&g_Core->Components_ID, &entity.Component_ID, ComponentParent);
					entity.PlayerID = entity.GetPlayerID(g_Core->m_decryptID);
					for (int j = 0; j < g_Core->Components_P_HEROID.size(); j++)
					{
						entity.EntityID = entity.GetEntityID(&g_Core->Components_P_HEROID, j);
						if (entity.PlayerID && entity.EntityID && (entity.PlayerID == entity.EntityID))
						{
							entity.Component_P_HEROID = g_Core->Components_P_HEROID.at(j);
							swapComponent(&g_Core->Components_P_VISIBILITY, &entity.Component_P_VISIBILITY, entity.Component_P_HEROID.ComponentParent);
							break;
						}
					}
					if (entity.PlayerID != entity.EntityID)
						continue;
					entity.HeroID = entity.GetHeroID();
					swapComponent(&g_Core->Components_SKILL, &entity.Component_SKILL, ComponentParent);
					swapComponent(&g_Core->Components_HEALTH, &entity.Component_HEALTH, ComponentParent);
					swapComponent(&g_Core->Components_OUTLINE, &entity.Component_OUTLINE, ComponentParent);

					XMFLOAT3 locPos = g_Core->GetViewMatrix().GetCameraVec();
					XMFLOAT3 _locPos = RPM<XMFLOAT3>(entity.Component_VELOCITY.ComponentBase + 0x140);
					//g_Logger->Info("%f, %f", locPos.x, _locPos.x);

					if (XMVectorGetX(XMVector3Length(XMLoadFloat3(&locPos) - XMLoadFloat3(&_locPos))) < 1.f)
					{
						if (entity.GetLife().y && entity.GetHeroID() == g_Core->m_localHero)
							g_Core->localEntity = entity;
					}

					BOOL isUnique = true;
					for (int i = 0; i < g_Core->Entities.size(); i++)
					{
						Entity _entity = g_Core->Entities.at(i);
						if (_entity.UniqueID == ComponentParent)
						{
							isUnique = false;
							g_Core->Entities.at(i) = entity;
							break;
						}
					}

					if (isUnique)
					{
						g_Core->Entities.push_back(entity);
					}
				}

				//remove invalid entities
				for (int i = 0; i < g_Core->Entities.size(); i++)
				{
					if (!g_Core->Entities.at(i).IsValid())
					{
						g_Core->Entities.erase(g_Core->Entities.begin() + i);
					}
				}

				std::this_thread::sleep_for(1ms);
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {}
	}

	void Aimbot()
	{
		__try
		{
			while (g_Running)
			{
				if (IsKeyPressed(g_Config->m_AimKey1) || IsKeyPressed(g_Config->m_AimKey2))
				{
					bool isEnemy = g_Hooking->bestEntity.GetTeam() == eTeam::TEAM_DEATHMATCH || g_Hooking->bestEntity.GetTeam() != g_Core->localEntity.GetTeam();
					if (g_Hooking->bestEntity.IsValid() && g_Core->localEntity.IsValid() && (isEnemy ? g_Hooking->bestEntity.isTargetable(g_Core->m_getSkillStruct) : g_Config->m_Teambot))
					{
						g_Hooking->bestEntity.RefreshBones(g_Core->m_refreshBones);

						if (g_Hooking->bestEntity.IsVisible())
						{
							XMFLOAT3 locPos = g_Core->GetViewMatrix().GetCameraVec();
							XMFLOAT3 bonePos{};
							XMStoreFloat3(&bonePos, XMLoadFloat3(&g_Hooking->bestEntity.GetRootVec(g_Core->m_getRootVec, g_Core->m_getRootVecOffset)) + XMLoadFloat3(&g_Hooking->bestEntity.GetBoneVector(g_Hooking->bestEntity.GetBoneIndex(IsKeyPressed(g_Config->m_AimKey1) ? g_Hooking->bestEntity.GetHeadBoneIndex() : g_Hooking->bestEntity.GetBodyBoneIndex()))));

							if (g_Config->m_Prediction)
							{
								XMFLOAT3 inVel;
								XMStoreFloat3(&inVel, XMLoadFloat3(&g_Hooking->bestEntity.GetVelocity()));
								float flDist = XMVectorGetX(XMVector3Length(XMLoadFloat3(&bonePos) - XMLoadFloat3(&locPos)));
								float flGrav;
								if (!g_Config->m_Gravity)
									flGrav = 0;
								else
									flGrav = 9.8 * 0.5 * powf(flDist / g_Config->m_Speed, 2.f);
								float flSpeed = g_Config->m_Speed;
								if (g_Core->localEntity.GetHeroID() == eHero::HERO_HANJO)
								{
									flSpeed = 25.f + 85.f * g_Core->localEntity.GetHanjoCharge();
									flGrav = 9.8 * 0.5 * powf(flDist / flSpeed, 2.f);
								}
								else if (g_Core->localEntity.GetHeroID() == eHero::HERO_ZENYATTA)
								{
									flGrav = 0;
									flSpeed = 80.f;
								}
								else if (g_Core->localEntity.GetHeroID() == eHero::HERO_MEI)
								{
									flGrav = 0;
									flSpeed = 120.f;
								}
								else if (g_Core->localEntity.GetHeroID() == eHero::HERO_TORBJORN)
								{
									flSpeed = 70.f;
									flGrav = 9.8 * 0.5 * powf(flDist / flSpeed, 2.f);
								}
								else if (g_Core->localEntity.GetHeroID() == eHero::HERO_ROADHOG)
								{
									flGrav = 0;
									flSpeed = 80.f;
								}
								else if (g_Core->localEntity.GetHeroID() == eHero::HERO_ORISA)
								{
									flGrav = 0;
									flSpeed = 80.f;
								}
								else if (g_Core->localEntity.GetHeroID() == eHero::HERO_ANA)
								{
									flGrav = 0;
									flSpeed = 60.f;
								}
								float flTime = (flDist / flSpeed);
								XMStoreFloat3(&inVel, XMLoadFloat3(&inVel) * flTime);
								bonePos.x = bonePos.x + inVel.x;
								bonePos.y = bonePos.y + inVel.y + flGrav;
								bonePos.z = bonePos.z + inVel.z;
							}

							XMFLOAT2 outPos{};
							if (g_Core->GetViewMatrix().WorldToScreen(bonePos, &outPos))
							{
								Vector2 mPos = { outPos.x - g_Width / 2, outPos.y - g_Height / 2 };
								float fovDist = mPos.Size();

								if (fovDist < g_Config->m_Fov)
								{
									if (!g_Hooking->m_Flick)
									{
										if (g_Config->m_SmoothType)
										{
											g_Hooking->m_Time += (g_Config->m_SmoothFactor / 10000.f) * (1.f + g_Config->m_Smooth / 100.f);

											if (g_Config->m_FixedAccuracy)
											{
												if (g_Hooking->m_Time >= (g_Config->m_Accuracy / 100.f))
													g_Hooking->m_Time = (g_Config->m_Accuracy / 100.f);
											}
											else
											{
												if (g_Hooking->m_Time >= (g_Config->m_SmoothFactor / 100.f) * (1.f + g_Config->m_Smooth / 100.f))
													g_Hooking->m_Time = (g_Config->m_SmoothFactor / 100.f) * (1.f + g_Config->m_Smooth / 100.f);
											}
										}

										if (g_Config->m_Aimbot)
										{
											XMFLOAT3 oAngle = g_Core->GetAngle();
											XMFLOAT3 dstAngle, dstAngleY;
											XMStoreFloat3(&dstAngle, XMVector3Normalize(XMLoadFloat3(&bonePos) - XMLoadFloat3(&locPos)));
											if (g_Config->m_SmoothType)
											{
												XMStoreFloat3(&dstAngleY, XMVectorLerp(XMLoadFloat3(&oAngle), XMLoadFloat3(&dstAngle), g_Hooking->m_Time));
												XMStoreFloat3(&dstAngle, XMVectorLerp(XMLoadFloat3(&oAngle), XMLoadFloat3(&dstAngle), g_Hooking->m_Time));
											}
											else
											{
												XMStoreFloat3(&dstAngleY, XMVectorLerp(XMLoadFloat3(&oAngle), XMLoadFloat3(&dstAngle), g_Config->m_SmoothY / 1000.f));
												XMStoreFloat3(&dstAngle, XMVectorLerp(XMLoadFloat3(&oAngle), XMLoadFloat3(&dstAngle), g_Config->m_SmoothX / 1000.f));
											}

											g_Core->SetAngle(dstAngle, dstAngleY);
										}

										if (g_Config->m_Triggerbot)
										{
											if (g_Hooking->bestEntity.IntersectRayWithAABB(g_Core->GetViewMatrix(), g_Core->GetViewMatrix().GetCameraVec(), g_Core->GetAngle(), IsKeyPressed(g_Config->m_AimKey1) ? g_Config->min : g_Config->min2, IsKeyPressed(g_Config->m_AimKey1) ? g_Config->max : g_Config->max2, g_Config->m_TriggerScale / 100.f, bonePos, IsKeyPressed(g_Config->m_AimKey1)))
											{
												if (g_Core->localEntity.GetHeroID() == eHero::HERO_HANJO)
													g_Core->SetKeyHold(eInput::INPUT_LMOUSE_UNHOLD, 100ms);
												else
													g_Core->SetKey(g_Config->m_IsLeft ? eInput::INPUT_LMOUSE : eInput::INPUT_RMOUSE);

												g_Hooking->m_Time = 0;
												if (g_Config->m_Flick)
													g_Hooking->m_Flick = true;
											}
										}
									}
								}
								else
								{
									if (g_Hooking->m_Time && g_Config->m_Triggerbot)
									{
										if (g_Core->localEntity.GetHeroID() == eHero::HERO_HANJO)
											g_Core->SetKeyHold(eInput::INPUT_LMOUSE_UNHOLD, 100ms);
										else
											g_Core->SetKey(g_Config->m_IsLeft ? eInput::INPUT_LMOUSE : eInput::INPUT_RMOUSE);
									}
									g_Hooking->bestEntity = Entity{};
								}
							}
							else
								g_Hooking->bestEntity = Entity{};
						}
						else
						{
							if (g_Hooking->m_Time && g_Config->m_Triggerbot)
							{
								if (g_Core->localEntity.GetHeroID() == eHero::HERO_HANJO)
									g_Core->SetKeyHold(eInput::INPUT_LMOUSE_UNHOLD, 100ms);
								else
									g_Core->SetKey(g_Config->m_IsLeft ? eInput::INPUT_LMOUSE : eInput::INPUT_RMOUSE);
							}
							g_Hooking->bestEntity = Entity{};
						}
					}
					else
						g_Hooking->bestEntity = Entity{};
				}
				else
				{
					if (g_Hooking->m_Time && g_Config->m_Triggerbot)
					{
						if (g_Core->localEntity.GetHeroID() == eHero::HERO_HANJO)
							g_Core->SetKeyHold(eInput::INPUT_LMOUSE_UNHOLD, 100ms);
						else
							g_Core->SetKey(g_Config->m_IsLeft ? eInput::INPUT_LMOUSE : eInput::INPUT_RMOUSE);
					}
					g_Hooking->m_Time = 0;
					g_Hooking->m_Flick = false;
				}

				std::this_thread::sleep_for(1ms);
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {}
	}

	Hooking::Hooking()
	{
		lockTimer = new Timer(std::chrono::milliseconds(g_Config->m_LockTargetTimer));

		MH_Initialize();
		MH_CreateHook((PDWORD_PTR)((PDWORD_PTR)(((PDWORD_PTR)(g_GameVariables->m_Swapchain))[0]))[Aeternum::Hooks::PresentIndex], &Hooks::Present, &m_OriginalPresent);
		MH_CreateHook((PDWORD_PTR)((PDWORD_PTR)(((PDWORD_PTR)(g_GameVariables->m_Swapchain))[0]))[Aeternum::Hooks::ResizeBuffersIndex], &Hooks::ResizeBuffers, &m_OriginalResizeBuffers);
		auto ntdllStr = skCrypt("ntdll.dll");
		auto funcStr = skCrypt("NtQuerySystemInformation");
		MH_CreateHook(GetProcAddress(GetModuleHandle(ntdllStr), funcStr), &Hooks::NtQuerySystemInformation, &m_OriginalQSI);
		ntdllStr.clear();
		funcStr.clear();
		MH_CreateHook((LPVOID)(g_Core->m_ComponentHook), &CoreHooks::ComponentHook, &g_Core->o_ComponentHook);
		MH_CreateHook((LPVOID)(g_Core->m_ViewMatrixHook), &CoreHooks::ViewMatrixHook, &g_Core->o_ViewMatrixHook);
		MH_CreateHook((LPVOID)(g_Core->m_InputHook), &CoreHooks::InputHook, &g_Core->o_InputHook);
		MH_CreateHook((LPVOID)(g_Core->m_LocalHook), &CoreHooks::LocalHook, &g_Core->o_LocalHook);

		_beginthread((_beginthread_proc_type)Cleaner, 0, nullptr);
		_beginthread((_beginthread_proc_type)Aimbot, 0, nullptr);
		WPM<BYTE>(g_Core->m_fixOutlineError, 0x41);
	}

	Hooking::~Hooking() noexcept
	{
		MH_RemoveHook((PDWORD_PTR)((PDWORD_PTR)(((PDWORD_PTR)(g_GameVariables->m_Swapchain))[0]))[Aeternum::Hooks::PresentIndex]);
		MH_RemoveHook((PDWORD_PTR)((PDWORD_PTR)(((PDWORD_PTR)(g_GameVariables->m_Swapchain))[0]))[Aeternum::Hooks::ResizeBuffersIndex]);
		auto ntdllStr = skCrypt("ntdll.dll");
		auto funcStr = skCrypt("NtQuerySystemInformation");
		MH_RemoveHook(GetProcAddress(GetModuleHandle(ntdllStr), funcStr));
		ntdllStr.clear();
		funcStr.clear();
		MH_RemoveHook((LPVOID)(g_Core->m_ComponentHook));
		MH_RemoveHook((LPVOID)(g_Core->m_ViewMatrixHook));
		MH_RemoveHook((LPVOID)(g_Core->m_InputHook));
		MH_RemoveHook((LPVOID)(g_Core->m_LocalHook));
		MH_Uninitialize();
		WPM<BYTE>(g_Core->m_fixOutlineError, 0x40);
	}

	void Hooking::Hook()
	{
		m_OldWndProc = SetWindowLongPtrA(g_GameVariables->m_GameWindow, GWLP_WNDPROC, (LONG_PTR)Hooks::WndProc);
		MH_EnableHook(MH_ALL_HOOKS);
	}

	void Hooking::Unhook()
	{
		SetWindowLongPtrA(g_GameVariables->m_GameWindow, GWLP_WNDPROC, (LONG_PTR)m_OldWndProc);
		MH_DisableHook(MH_ALL_HOOKS);
	}
}
