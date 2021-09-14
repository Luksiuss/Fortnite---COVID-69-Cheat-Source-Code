#pragma once
#include "includes.h"
#include "Major.h"
#define E(str) skCrypt_(str)


void MainTick();

ImFont* m_pFont;
extern ImVec4 backgroundColor;
extern ImVec4 innerColor;
extern ImVec4 innerColorRGB;
extern ImVec4 textColor;

// Colors of Annas GUI

//ImVec4 ImGui::backgroundColorRGB = ImVec4(237, 237, 237, 255);
//ImVec4 ImGui::innerColorRGB = ImVec4(9, 189, 114, 255);

//ImVec4 ImGui::backgroundColor = ImVec4(ImGui::backgroundColorRGB.x / 255.f, ImGui::backgroundColorRGB.y / 255.f, ImGui::backgroundColorRGB.z / 255.f, ImGui::backgroundColorRGB.w / 255.f); // current: Grey
//ImVec4 ImGui::innerColor = ImVec4(ImGui::innerColorRGB.x / 255.f, ImGui::innerColorRGB.y / 255.f, ImGui::innerColorRGB.z / 255.f, ImGui::innerColorRGB.w / 255.f); // current: Dark Red

namespace utils {

	void DrawFilledBox(const Vector2& vecStart, const Vector2& vecEnd, uint32_t color, float rounding, uint32_t roundingCornersFlags)
	{
		float a = (color >> 24) & 0xFF;
		float r = (color >> 16) & 0xFF;
		float g = (color >> 8) & 0xFF;
		float b = (color) & 0xFF;

		ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(vecStart.x, vecStart.y), ImVec2(vecStart.x + vecEnd.x, vecStart.y + vecEnd.y), ImGui::GetColorU32({ r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f }), rounding, roundingCornersFlags);
	}

	std::string string_To_UTF8(const std::string& str)
	{
		int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

		wchar_t* pwBuf = new wchar_t[nwLen + 1];
		ZeroMemory(pwBuf, nwLen * 2 + 2);

		::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

		int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);

		char* pBuf = new char[nLen + 1];
		ZeroMemory(pBuf, nLen + 1);

		::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);

		std::string retStr(pBuf);

		delete[]pwBuf;
		delete[]pBuf;

		pwBuf = NULL;
		pBuf = NULL;

		return retStr;
	}

	void DrawCircle(int x, int y, int radius, int R, int G, int B, int A, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddCircle(ImVec2(x, y), radius, ImGui::ColorConvertFloat4ToU32(ImVec4(R / 255.0, G / 255.0, B / 255.0, A / 255.0)), thickness);
	}

	void DrawLineF(int x1, int y1, int x2, int y2, int thickness, float r, float g, float b, float a)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, a)), thickness);
	}

	void DrawBox(int x1, int y1, int x2, int y2, float r, float g, float b, float a, bool isFilled)
	{
		if (isFilled)
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(x1, y1), ImVec2(x1 + x2, y1 + y2), ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, a)));
		else
			ImGui::GetOverlayDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x1 + x2, y1 + y2), ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, a)));
	}

	void DrawNewText(int x, int y, int R, int G, int B, int A, const char* str)
	{
		ImFont a;
		std::string utf_8_1 = std::string(str);
		std::string utf_8_2 = string_To_UTF8(utf_8_1);
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str());
		ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(R / 255.0, G / 255.0, B / 255.0, A / 255.0)), utf_8_2.c_str());
	}

	void DrawLine(int x1, int y1, int x2, int y2, int R, int G, int B, int A, int thickness)
	{
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::ColorConvertFloat4ToU32(ImVec4(R / 255.0, G / 255.0, B / 255.0, A / 255.0)), thickness);
	}

	void ToggleButton(const char* str_id, bool* v)
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetOverlayDrawList();

		float height = ImGui::GetFrameHeight() - 10;
		float width = height * 1.45f;
		float radius = height * 0.50f;

		ImGui::InvisibleButton(str_id, ImVec2(width, height));
		if (ImGui::IsItemClicked())
			*v = !*v;

		float t = *v ? 1.0f : 0.0f;

		ImGuiContext& g = *GImGui;
		float ANIM_SPEED = 0.05f;
		if (g.ActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
		{
			float t_anim = ImSaturate(g.ActiveIdTimer / ANIM_SPEED);
			t = *v ? (t_anim) : (1.0f - t_anim);
		}

		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), innerColor, t));
		else
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), innerColor, t));

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f + 1.0f, IM_COL32(0, 0, 0, 255));
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
	}

	void ToggleButtonA(const char* str_id, bool* v, int A)
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetOverlayDrawList();

		float height = ImGui::GetFrameHeight() - 10;
		float width = height * 1.45f;
		float radius = height * 0.50f;

		ImGui::InvisibleButton(str_id, ImVec2(width, height));
		if (ImGui::IsItemClicked()) {
			if (A == 1) {
				Settings.SilentAimbot = false;
				Settings.MouseAim = false;
			}
			else if (A == 2) {
				Settings.Aimbot = false;
				Settings.MouseAim = false;
			}
			else if (A == 3) {
				Settings.Aimbot = false;
				Settings.SilentAimbot = false;
			}
			*v = !*v;
		}

		float t = *v ? 1.0f : 0.0f;

		ImGuiContext& g = *GImGui;
		float ANIM_SPEED = 0.05f;
		if (g.ActiveId == g.CurrentWindow->GetID(str_id))// && g.LastActiveIdTimer < ANIM_SPEED)
		{
			float t_anim = ImSaturate(g.ActiveIdTimer / ANIM_SPEED);
			t = *v ? (t_anim) : (1.0f - t_anim);
		}

		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), innerColor, t));
		else
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 1.0f), innerColor, t));

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f + 1.0f, IM_COL32(0, 0, 0, 255));
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
	}

	void PushDisabled(bool disabled = true) {
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, disabled);
	}
	void PopDisabled(int num = 1) {
		while (num--) {
			ImGui::PopItemFlag();
		}
	}
}

bool page1VISUALS = true;
void DrawMenu()
{
	if (o_getasynckeystate((DWORD)VK_INSERT) == -32767) ShowMenu = !ShowMenu;
	//if (o_getasynckeystate((DWORD)VK_F1) == -32767) ShowMenu = !ShowMenu;

	if (o_getasynckeystate((DWORD)VK_PRIOR) == -32767) {
		if (Settings.ESP.MinWeaponTier != 5)
			Settings.ESP.MinWeaponTier += 1;
	}

	if (o_getasynckeystate((DWORD)VK_NEXT) == -32767) {
		if (Settings.ESP.MinWeaponTier != 1)
			Settings.ESP.MinWeaponTier -= 1;
	}

	if (ShowMenu)
	{
		bHidden = false;
		// menu here
		ImGui::StyleColorsLight();

		ImGuiStyle* style = &ImGui::GetStyle();
		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 1.0f;
		style->FramePadding = ImVec2(5, 5);
		style->ItemSpacing = ImVec2(12, 8);
		style->ItemInnerSpacing = ImVec2(8, 6);
		style->IndentSpacing = 25.0f;
		style->ScrollbarSize = 0.0f;
		style->ScrollbarRounding = 1.0f;
		style->GrabMinSize = 5.0f;
		style->GrabRounding = 3.0f;
		style->WindowTitleAlign = ImVec2(0.5, 1.1);
		style->Alpha = 1.f;
		// title 
		ImGui::PushStyleColor(ImGuiCol_TitleBgActive, backgroundColor);
		ImGui::PushStyleColor(ImGuiCol_TitleBg, backgroundColor);
		ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, backgroundColor);
		ImGui::PushStyleColor(ImGuiCol_Border, innerColor); // 
		ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.00f, 0.00f, 0.00f, 0.00f)); //
		// window
		ImGui::PushStyleColor(ImGuiCol_Text, textColor);
		ImGui::PushStyleColor(ImGuiCol_TextDisabled, textColor);
		ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, textColor);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
		ImGui::PushStyleColor(ImGuiCol_Border, innerColor);
		// button
		ImGui::PushStyleColor(ImGuiCol_Button, backgroundColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, backgroundColor);
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, backgroundColor);
		ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.40f, 0.39f, 0.38f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_PlotLinesHovered, ImVec4(0.25f, 1.00f, 0.00f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.40f, 0.39f, 0.38f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_PlotHistogramHovered, ImVec4(0.25f, 1.00f, 0.00f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.25f, 1.00f, 0.00f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_ModalWindowDarkening, ImVec4(94 / 255.f, 94 / 255.f, 94 / 255.f, 1.00f));
		// Slider
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(94 / 255.f, 94 / 255.f, 94 / 255.f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(94 / 255.f, 94 / 255.f, 94 / 255.f, 1.00f));
		ImGui::PushStyleColor(ImGuiCol_FrameBg, innerColor);
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, innerColor);
		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, innerColor);
		ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.57f, 0.255f, 0.20f, 1.00f));

		std::string title = E("Target Fortnite riks on top version kekw");
		ImGuiWindowFlags TargetFlags;
		TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;

		static short tab = 0;
		if (ImGui::Begin(title.c_str(), 0, ImVec2(700, 331), -1.f, TargetFlags)) {
			ImVec2 ve = ImVec2(ImGui::GetItemRectMin().x + 180, ImGui::GetItemRectMin().y + 40);
			ImVec2 v = ImVec2(ImGui::GetItemRectMax().x - 15, ImGui::GetItemRectMax().y + 290);
			ImGui::GetOverlayDrawList()->AddRect(ve, v, IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));

			bool tab_aimbot, tab_visuals, tab_exploits, tab_misc, tab_admin;

			// TABS
			ImGui::BeginGroup();
			{
				ImGui::BeginGroup();
				if (tab == 0) {
					ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
				}
				if (tab == 0)
					utils::PushDisabled(true);
				else
					utils::PushDisabled(false);
				tab_aimbot = ImGui::Button(E("AIMBOT"), ImVec2(150, 23));
				utils::PopDisabled();
				if (tab == 0)
					ImGui::PopStyleColor(3);
				ImGui::EndGroup();
				ImGui::GetOverlayDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));

				ImGui::BeginGroup();
				if (tab == 1) {
					ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
				}
				if (tab == 1)
					utils::PushDisabled(true);
				else
					utils::PushDisabled(false);
				tab_visuals = ImGui::Button(E("VISUALS"), ImVec2(150, 23));
				utils::PopDisabled();
				if (tab == 1)
					ImGui::PopStyleColor(3);
				ImGui::EndGroup();
				ImGui::GetOverlayDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));

				ImGui::BeginGroup();
				if (tab == 2) {
					ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
				}
				if (tab == 2)
					utils::PushDisabled(true);
				else
					utils::PushDisabled(false);
				tab_exploits = ImGui::Button(E("EXPLOITS"), ImVec2(150, 23));
				utils::PopDisabled();
				if (tab == 2)
					ImGui::PopStyleColor(3);
				ImGui::EndGroup();
				ImGui::GetOverlayDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));

				ImGui::BeginGroup();
				if (tab == 3) {
					ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
				}
				if (tab == 3)
					utils::PushDisabled(true);
				else
					utils::PushDisabled(false);
				tab_misc = ImGui::Button(E("MISC"), ImVec2(150, 23));
				utils::PopDisabled();
				if (tab == 3)
					ImGui::PopStyleColor(3);
				ImGui::EndGroup();
				ImGui::GetOverlayDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));

				if (isAdministrator) {
					ImGui::BeginGroup();
					if (tab == 4) {
						ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
						ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
						ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
					}
					if (tab == 4)
						utils::PushDisabled(true);
					else
						utils::PushDisabled(false);
					tab_admin = ImGui::Button(E("ADMINISTRATOR"), ImVec2(150, 23));
					utils::PopDisabled();
					if (tab == 4)
						ImGui::PopStyleColor(3);
					ImGui::EndGroup();
					ImGui::GetOverlayDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));
				}
				if (tab_aimbot)
					tab = 0;
				if (tab_visuals)
					tab = 1;
				if (tab_exploits)
					tab = 2;
				if (tab_misc)
					tab = 3;
				if (tab_admin)
					tab = 4;
			}
			ImGui::EndGroup();

			ImGui::SameLine(NULL, 20/*47*/);
			// AIMBOT TAB
			if (tab == 0)
			{
				// AIMBOT TAB: LEFT
				{
					ImGui::BeginGroup();
					ImGui::Dummy(ImVec2(0.0f, 3.0f));

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					//auto memAim = ImGui::Checkbox("Mouse Aimbot", &Settings.MouseAim);
					auto memAim = ImGui::Checkbox("Memory Aimbot", &Settings.Aimbot);

					if (Settings.Aimbot) {
						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox("[OPTION] Aimbot Lock", &Settings.AimHelper);
					}

					//ImGui::Dummy(ImVec2(0.0f, 0.0f));
					//ImGui::SameLine(NULL, 9);
					//auto silentAim = ImGui::Checkbox(E("Silent Aimbot"), &Settings.SilentAimbot);

					//ImGui::Dummy(ImVec2(0.0f, 0.0f));
					//ImGui::SameLine(NULL, 9);
					//auto mouseAim = ImGui::Checkbox(E("Mouse Aimbot"), &Settings.MouseAim);

					if (memAim) {
						Settings.SilentAimbot = false;
						Settings.MouseAim = false;
					}
					/*if (silentAim) {
						Settings.Aimbot = false;
						Settings.MouseAim = false;
					}
					if (mouseAim) {
						Settings.Aimbot = false;
						Settings.SilentAimbot = false;
					}*/
					//Settings.MouseAim = false;

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					auto clickedH = ImGui::Checkbox("Head Aim", &Settings.AimPosSt.head);
					if (clickedH && Settings.AimPosSt.head) {
						Settings.AimPosSt.body = false;
						Settings.AimPosSt.dick = false;
					}
					else if (clickedH && !Settings.AimPosSt.body && !Settings.AimPosSt.dick) {
						Settings.AimPosSt.head = true;
					}
					ImGui::SameLine(NULL, 9);
					auto clickedB = ImGui::Checkbox("Body Aim", &Settings.AimPosSt.body);
					if (clickedB && Settings.AimPosSt.body) {
						Settings.AimPosSt.head = false;
						Settings.AimPosSt.dick = false;
					}
					else if (clickedB && !Settings.AimPosSt.head && !Settings.AimPosSt.dick) {
						Settings.AimPosSt.body = true;
					}
					ImGui::SameLine(NULL, 9);
					auto clickedD = ImGui::Checkbox("Dick Aim", &Settings.AimPosSt.dick);
					if (clickedD && Settings.AimPosSt.dick) {
						Settings.AimPosSt.head = false;
						Settings.AimPosSt.body = false;
					}
					else if (clickedD && !Settings.AimPosSt.head && !Settings.AimPosSt.body) {
						Settings.AimPosSt.dick = true;
					}
					if (Settings.AimPosSt.head)
						Settings.AimPos = 1;
					else if (Settings.AimPosSt.body)
						Settings.AimPos = 2;
					else if (Settings.AimPosSt.dick)
						Settings.AimPos = 3;

					ImGui::Dummy(ImVec2(6, 1));
					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::PushItemWidth(100);
					ImGui::SliderFloat(E("Aim FOV"), &Settings.AimbotFOV, 0.0f, 50.5f);

					ImGui::Dummy(ImVec2(6, 1));
					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::PushItemWidth(100);
					ImGui::SliderFloat(E("Aim Smooth"), &Settings.AimbotSlow, 0.0f, 25.f);

					ImGui::Dummy(ImVec2(6, 6));
					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::PushItemWidth(100);
					ImGui::SliderFloat(E("Crosshair scale"), &Settings.crosshairNuclear, 1, 10);
					Settings.crosshairScale = Settings.crosshairNuclear + 7;

					ImGui::EndGroup();
				}

				// AIMBOT TAB: RIGHT
				ImGui::SameLine(ImGui::GetWindowWidth() - 222/*111: size of the button*/ + 30);
				{
					ImGui::BeginGroup();
					ImGui::Dummy(ImVec2(0.0f, 5.0f));

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 52);
					ImGui::Text(E("Aimbot Key"));
					ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 13 + 14);
				//	ImGui::Hotkey(E("Aimbot Key"), &Settings.aimkey, ImVec2{ 151, 36 }, 0);
					ImGui::PopStyleColor(3);

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox("Draw FOV", &Settings.ESP.AimbotFOV);

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox("Random aim pos", &Settings.ESP.RandomAim);

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox(E("Draw crosshair"), &Settings.Crosshair);

					//ImGui::Dummy(ImVec2(0.0f, 0.0f));
					//ImGui::SameLine(NULL, 9);
					//ImGui::Checkbox("Weakspot aim", &Settings.WeakSpot);

					ImGui::EndGroup();
				}
			}
			// VISUALS TAB
			if (tab == 1)
			{
				// PAGE 1
				if (page1VISUALS) {
					// VISUALS TAB: LEFT
					{
						ImGui::BeginGroup();
						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Enable visuals"), &Settings.ESP.Players);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Show Distance"), &Settings.ESP.Distance);

						utils::PushDisabled(true);
						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Show Player Names"), &Settings.ESP.PlayerNames);
						utils::PushDisabled(false);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Show Player Weapons"), &Settings.ESP.PlayerWeapons);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Player Skeleton"), &Settings.ESP.Skeleton);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Player Box"), &Settings.ESP.Box);

						if (Settings.ESP.Box) {
							ImGui::Dummy(ImVec2(0.0f, 0.0f));
							ImGui::SameLine(NULL, 9);
							ImGui::Checkbox(E("[OPTION] 3D Box"), &Settings.ESP.ThreeDBox);
						}

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Weapons ESP"), &Settings.ESP.Weapons);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Upgrade Bench ESP"), &Settings.ESP.UpgradeBench);

						if (!Settings.ESP.Box) {
							ImGui::Dummy(ImVec2(0.0f, 0.0f));
							ImGui::SameLine(NULL, 9);
							ImGui::Checkbox(E("Ammo ESP"), &Settings.ESP.Ammo);
						}
						ImGui::EndGroup();
					}
					// VISUALS TAB: MIDDLE
					ImGui::SameLine(ImGui::GetWindowWidth() - 222/*111: size of the button*/ + 30 - 136);
					{
						ImGui::BeginGroup();
						ImGui::Dummy(ImVec2(0.0f, 5.0f));

						if (Settings.ESP.Box) {
							ImGui::Dummy(ImVec2(0.0f, 0.0f));
							ImGui::SameLine(NULL, 9);
							ImGui::Checkbox(E("Ammo ESP"), &Settings.ESP.Ammo);
						}

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Chests ESP"), &Settings.ESP.Chests);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Ammo Box ESP"), &Settings.ESP.AmmoBox);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Llama ESP"), &Settings.ESP.Llama);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Supply Drop ESP"), &Settings.ESP.SupplyDrop);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Agents/Boss ESP"), &Settings.ESP.AgentsBoss);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Shark ESP"), &Settings.ESP.Shark);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Boats ESP"), &Settings.ESP.Boats);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Helicopters ESP"), &Settings.ESP.Helicopters);

						if (!Settings.ESP.Box) {
							ImGui::Dummy(ImVec2(0.0f, 0.0f));
							ImGui::SameLine(NULL, 9);
							ImGui::Checkbox(E("Cars ESP"), &Settings.ESP.Cars);
						}

						ImGui::EndGroup();
					}
					// VISUALS TAB: RIGHT
					ImGui::SameLine(ImGui::GetWindowWidth() - 222/*111: size of the button*/ + 30 - 136 + 161);
					{
						ImGui::BeginGroup();
						ImGui::Dummy(ImVec2(0.0f, 5.0f));

						if (Settings.ESP.Box) {
							ImGui::Dummy(ImVec2(0.0f, 0.0f));
							ImGui::SameLine(NULL, 9);
							ImGui::Checkbox(E("Cars ESP"), &Settings.ESP.Cars);
						}

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Trucks ESP"), &Settings.ESP.Trucks);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Taxi ESP"), &Settings.ESP.Taxi);

						ImGui::Dummy(ImVec2(6, 6));
						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9 - 3);
						ImGui::PushItemWidth(31);
						ImGui::SliderInt(E("Min Items Tier"), &Settings.ESP.MinWeaponTier, 1, 5);

						ImGui::Dummy(ImVec2(6, 6));
						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9 - 3);
						ImGui::PushItemWidth(31);
						ImGui::SliderInt(E("Items max distance"), &Settings.OverallDistance, 50, 500);

						ImGui::Dummy(ImVec2(6, 6));
						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9 - 3);
						ImGui::PushItemWidth(31);
						ImGui::SliderFloat(E("Line thickness"), &Settings.SnaplinePower, 1.f, 10.f);

						if (!Settings.ESP.Box) {
							ImGui::Dummy(ImVec2(0.0f, 0.0f));
							ImGui::SameLine(NULL, 9);
							ImGui::Dummy(ImVec2(1.0f, 20.0f));
						}
						ImGui::Dummy(ImVec2(6, 6));
						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9 - 3 + 5);
						ImGui::BeginGroup();
						auto page1 = ImGui::Button(E("GOTO: PAGE 2"), ImVec2(150 - 28, 23));
						if (page1) {
							page1VISUALS = false;
						}
						ImGui::EndGroup();
						ImGui::GetOverlayDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));

						ImGui::EndGroup();
					}
				}
				else {
					// VISUALS TAB: LEFT
					{
						ImGui::BeginGroup();
						ImGui::Dummy(ImVec2(0.0f, 3.0f));

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Corner box"), &Settings.ESP.CornerBox);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Draw Direction Lazer"), &Settings.ESP.Lazer);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Enable visible check"), &Settings.visCheck);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Aim Line"), &Settings.ESP.AimLine);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("XP Coin"), &Settings.ESP.XPCoin);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Draw snaplines"), &Settings.ESP.PlayerLines);

						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 9);
						ImGui::Checkbox(E("Square FOV"), &Settings.isRecFov);

						ImGui::EndGroup();
					}

					ImGui::Dummy(ImVec2(6, 6 + 16));
					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9 - 3 + 5 + 518);
					ImGui::BeginGroup();
					auto page1 = ImGui::Button(E("GOTO: PAGE 1"), ImVec2(150 - 28, 23));
					if (page1)
						page1VISUALS = true;

					ImGui::EndGroup();
					ImGui::GetOverlayDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));
				}
			}
			// EXPLOITS TAB
			if (tab == 2) {
				// EXPLOITS TAB: LEFT
				{
					ImGui::BeginGroup();
					ImGui::Dummy(ImVec2(0.0f, 3.0f));

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox(E("Enable Camera FOV Changer"), &Settings.FOVChanger);

					if (Settings.FOVChanger) {
						ImGui::Dummy(ImVec2(6, 6));
						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 8);
						ImGui::PushItemWidth(200 - 96);
						ImGui::SliderFloat(E("[OPTION] Camera FOV Distance"), &Settings.FOV, 20.f, 140.f);
					}

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox(E("Enable AirStuck"), &Settings.AirStuck);

					//ImGui::Dummy(ImVec2(0.0f, 0.0f));
					//ImGui::SameLine(NULL, 9);
					//ImGui::Checkbox(E("Enable No Spread"), &Settings.NoSpreadAimbot);

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox(E("Enable Rapid Fire"), &Settings.RapidFire);

					ImGui::EndGroup();
				}
				// EXPLOITS TAB: RIGHT
				ImGui::SameLine(ImGui::GetWindowWidth() - 222/*111: size of the button*/ + 30);
				{
					ImGui::BeginGroup();
					ImGui::Dummy(ImVec2(0.0f, 5.0f));

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 52);
					ImGui::Text(E("AirStuck Key"));
					ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
					ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 13 + 14);
					//ImGui::Hotkey(E("AirStuck Key"), &Settings.AirStuckKey, ImVec2{ 151, 36 }, 0);
					ImGui::PopStyleColor(3);

					ImGui::EndGroup();
				}
			}
			// MISC TAB
			if (tab == 3) {
				// MISC TAB: LEFT
				{
					ImGui::BeginGroup();
					ImGui::Dummy(ImVec2(0.0f, 3.0f));

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox(E("Enable Info Bar"), &Settings.ShowInfoBar);

					//ImGui::Dummy(ImVec2(0.0f, 0.0f));
					//ImGui::SameLine(NULL, 9);
					//ImGui::Checkbox(E("Enable warning about enemies in the area"), &Settings.WarningEnemiesArea);

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox(E("Enable Radar ESP"), &Settings.RadarESP);
					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Text(E("TIP: You can move/resize radar when the menu is on."));

					if (Settings.RadarESP) {
						ImGui::Dummy(ImVec2(6, 6));
						ImGui::Dummy(ImVec2(0.0f, 0.0f));
						ImGui::SameLine(NULL, 8);
						ImGui::PushItemWidth(200 - 96);
						ImGui::SliderFloat(E("[OPTION] Radar Range"), &Settings.RadarESPRange, 7000.f, 50000.f);
					}

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox(E("Draw Weakspots"), &Settings.WeakSpot);

					ImGui::EndGroup();
				}
			}
			// ADMINISTRATOR TAB
			if (tab == 4) {
				// ADMINISTRATOR TAB: LEFT
				{
					ImGui::BeginGroup();
					ImGui::Dummy(ImVec2(0.0f, 3.0f));

					ImGui::Dummy(ImVec2(0.0f, 0.0f));
					ImGui::SameLine(NULL, 9);
					ImGui::Checkbox(E("Enable Objects Names Display (Caution: Might cuz FPS drop)"), &Settings.Dev);

					ImGui::EndGroup();
				}
			}
		}
		ImGui::End();

		POINT point;
		if (GetCursorPos(&point)) {
			ImGui::GetOverlayDrawList()->AddRectFilled(ImVec2(point.x, point.y), ImVec2(point.x + 6, point.y + 6), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1.f)));
			//utils::DrawBox(point.x, point.y, 6, 6, 0, 0, 0, 1.f, true);
		}
	} else
		bHidden = true;
}






extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
__declspec(dllexport) LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYUP && (wParam == VK_F4)) {
		ShowMenu = !ShowMenu;
		ImGui::GetIO().MouseDrawCursor = ShowMenu;
	}

	if (ShowMenu) {
		ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		return TRUE;
	}

	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}




bool once = true;
_declspec(dllexport) HRESULT PresentHook(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags)
{
	static float width = 0;
	static float height = 0;
	static HWND hWnd = 0;

	if (firstTime) {

		if (!device) {
			swapChain->GetDevice(__uuidof(device), reinterpret_cast<PVOID*>(&device));
			device->GetImmediateContext(&immediateContext);

			DXGI_SWAP_CHAIN_DESC desc;
			swapChain->GetDesc(&desc);

			ID3D11Texture2D* renderTarget = nullptr;
			if (SUCCEEDED(swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget)))
			{
				device->CreateRenderTargetView(renderTarget, NULL, &renderTargetView);
				renderTarget->Release();
				device->Release();

				ID3D11Texture2D* backBuffer = 0;
				swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (PVOID*)&backBuffer);
				D3D11_TEXTURE2D_DESC backBufferDesc = { 0 };
				backBuffer->GetDesc(&backBufferDesc);

				hWnd = FindWindow((L"UnrealWindow"), (L"Fortnite  "));
				if (!width) {
					oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProcHook)));
				}

				width = (float)backBufferDesc.Width;
				height = (float)backBufferDesc.Height;
				backBuffer->Release();

				ImGui::GetIO().Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\Evocancode Regular.ttf"), 12.0f);
				m_pFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(("C:\\Windows\\Fonts\\Evocancode Regular.tff"), 12.0f);
				ImGui_ImplDX11_Init(desc.OutputWindow, device, immediateContext);
				ImGui_ImplDX11_CreateDeviceObjects();
			}
		
		}
		firstTime = false;
	}

	if (renderTargetView)
	{
		immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
		ImGui_ImplDX11_NewFrame();
	

			MainTick();

			DrawMenu();

			
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
	
	return PresentOriginal(swapChain, syncInterval, flags);
}

void GetViewProjectionMatrix(FSceneViewProjectionData* projectionData, float out[4][4]) {
	auto loc = &projectionData->ViewOrigin;

	float translation[4][4] = {
		{ 1.0f, 0.0f, 0.0f, 0.0f, },
		{ 0.0f, 1.0f, 0.0f, 0.0f, },
		{ 0.0f, 0.0f, 1.0f, 0.0f, },
		{ -loc->X, -loc->Y, -loc->Z, 0.0f, },
	};

	float temp[4][4];
	MultiplyMatrices(translation, projectionData->ViewRotationMatrix.M, temp);
	MultiplyMatrices(temp, projectionData->ProjectionMatrix.M, out);
}

void CalculateProjectionMatrixGivenViewHook(FMinimalViewInfo* viewInfo, BYTE aspectRatioAxisConstraint, PBYTE viewport, FSceneViewProjectionData* inOutProjectionData)
{
	CalculateProjectionMatrixGivenView(viewInfo, aspectRatioAxisConstraint, viewport, inOutProjectionData);

	view.Info = *viewInfo;
	GetViewProjectionMatrix(inOutProjectionData, view.ProjectionMatrix);
}

typedef uintptr_t(__fastcall* LFAT)(uintptr_t* a1, unsigned int a2, char a3);
LFAT oValidateLastFire = NULL;
__int64 hkValidateLastFire(uintptr_t* a1, unsigned int a2, char a3)
{
	__int64 ret = spoof_call(game_rbx_jmp, oValidateLastFire, a1, a2, a3);

	if (a1 && LocalWeapon) return 1;
	else return ret;
}


__declspec(dllexport) HRESULT ResizeHook(IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags) {
	ImGui_ImplDX11_Shutdown();
	renderTargetView->Release();
	immediateContext->Release();
	device->Release();
	device = nullptr;

	return ResizeOriginal(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}


bool Renderintial()
{
	IDXGISwapChain* swapChain = nullptr;
	ID3D11Device* device = nullptr;
	ID3D11DeviceContext* context = nullptr;
	auto                 featureLevel = D3D_FEATURE_LEVEL_11_0;

	DXGI_SWAP_CHAIN_DESC sd = { 0 };
	sd.BufferCount = 1;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.OutputWindow = GetForegroundWindow();
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;

	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, 0, &featureLevel, 1, D3D11_SDK_VERSION, &sd, &swapChain, &device, nullptr, &context))) {
		MessageBox(0, L"Failed to create D3D11 device and swap chain", L"Failure", MB_ICONERROR);
		return FALSE;
	}

	auto table = *reinterpret_cast<PVOID**>(swapChain);
	auto present = table[8];
	auto resize = table[13];

	context->Release();
	device->Release();
	swapChain->Release();

	MH_CreateHook(present, PresentHook, reinterpret_cast<PVOID*>(&PresentOriginal));
	MH_EnableHook(present);

	MH_CreateHook(resize, ResizeHook, reinterpret_cast<PVOID*>(&ResizeOriginal));
	MH_EnableHook(resize);

	return TRUE;
}