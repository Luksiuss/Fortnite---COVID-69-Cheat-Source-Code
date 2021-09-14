/*
COVID69 IS A SCAM, TOKEN LOGGER
message to ytmcpaster and kenny (PRO PASTER): plz stop scamming kids thx
message to moodless: did you enjoy your 6h ddos? XD (by Pepe.#1337)

fucked by !Yatinu#1234 and Pepe.#1337
*/

#pragma once
#include "includes.h"
#include "Major.h"
#include "MinHook.h"
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
		//ImGui::GetOverlayDrawList()->AddText(ImVec2(x, y), ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)), utf_8_2.c_str(), &);
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


		auto& style = ImGui::GetStyle();
		style.WindowPadding = { 10.f, 10.f };
		style.PopupRounding = 0.f;
		style.FramePadding = { 8.f, 4.f };
		style.ItemSpacing = { 10.f, 8.f };
		style.ItemInnerSpacing = { 6.f, 6.f };
		style.TouchExtraPadding = { 0.f, 0.f };
		style.IndentSpacing = 21.f;
		style.ScrollbarSize = 15.f;
		style.GrabMinSize = 8.f;
		style.WindowBorderSize = 1.5f;
		style.ChildBorderSize = 1.5f;
		style.PopupBorderSize = 1.5f;
		style.FrameBorderSize = 0.f;
		style.WindowRounding = 3.f;
		style.ChildRounding = 3.f;
		style.FrameRounding = 1.0f;
		style.ScrollbarRounding = 1.f;
		style.GrabRounding = 1.f;
		style.ButtonTextAlign = { 0.5f, 0.5f };
		style.DisplaySafeAreaPadding = { 3.f, 3.f };

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.f);
		colors[ImGuiCol_TextDisabled] = ImVec4(1.00f, 0.90f, 0.19f, 1.f);
		colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.06f, 0.06f, 1.f);
		colors[ImGuiCol_ChildBg] = ImVec4(0.08f, 0.08f, 0.08f, 1.f);
		colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);
		colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
		colors[ImGuiCol_BorderShadow] = ImVec4(1.f, 1.f, 1.f, 1.f);
		colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.f);
		colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.21f, 0.21f, 0.78f);
		colors[ImGuiCol_FrameBgActive] = ImVec4(0.28f, 0.27f, 0.27f, 1.f);
		colors[ImGuiCol_TitleBg] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
		colors[ImGuiCol_TitleBgActive] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
		colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
		colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.f);
		colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.8f);
		colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
		colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
		colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.f);
		colors[ImGuiCol_CheckMark] = ImVec4(1.00f, 1.00f, 1.00f, 1.f);
		colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.30f, 0.30f, 1.f);
		colors[ImGuiCol_SliderGrabActive] = ImVec4(0.34f, 0.34f, 0.34f, 1.f);
		colors[ImGuiCol_Button] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
		colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.f);
		colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.f);
		colors[ImGuiCol_Header] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
		colors[ImGuiCol_HeaderHovered] = ImVec4(0.19f, 0.19f, 0.19f, 1.f);
		colors[ImGuiCol_HeaderActive] = ImVec4(0.25f, 0.25f, 0.25f, 1.f);
		colors[ImGuiCol_Separator] = ImVec4(0.38f, 0.38f, 0.38f, 0.5f);
		colors[ImGuiCol_SeparatorHovered] = ImVec4(0.46f, 0.46f, 0.46f, 0.5f);
		colors[ImGuiCol_SeparatorActive] = ImVec4(0.46f, 0.46f, 0.46f, 0.64f);
		colors[ImGuiCol_ResizeGrip] = ImVec4(0.26f, 0.26f, 0.26f, 1.f);
		colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.31f, 0.31f, 0.31f, 1.f);
		colors[ImGuiCol_ResizeGripActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.f);
		colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.f);
		colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.f);
		colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.f);
		colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.f);
		colors[ImGuiCol_TextSelectedBg] = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.9f);
		ImGui::GetOverlayDrawList()->AddRectFilled(ImGui::GetIO().MousePos, ImVec2(ImGui::GetIO().MousePos.x + 5.f, ImGui::GetIO().MousePos.y + 5.f), ImColor(255, 0, 0, 255));
/*
COVID69 IS A SCAM, TOKEN LOGGER
message to ytmcpaster and kenny (PRO PASTER): plz stop scamming kids thx
message to moodless: did you enjoy your 6h ddos? XD (by Pepe.#1337)

fucked by !Yatinu#1234 and Pepe.#1337
*/
		if (ImGui::Begin(_xor_("COVID-69 | Fortnite " __DATE__ " " __TIME__ " (INSERT) (menu is only usable in game)").c_str(), 0, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
		{
			ImGui::SetWindowPos(ImVec2(10.f, 100.f), ImGuiCond_Once);
			ImGui::SetWindowSize(ImVec2(516.f, 610.f), ImGuiCond_Once);

			if (ImGui::CollapsingHeader(_xor_("ESP").c_str()))
			{
				ImGui::Columns(2, (_xor_("##esp_cols").c_str()));

				static float col_width = 0.f;
				if (col_width == 0.f)
					col_width = ImGui::GetColumnWidth(1);

				ImGui::SetColumnWidth(1, col_width - 10.f);

				ImGui::Checkbox(_xor_("Players Boxes").c_str(), &Settings.ESP.CornerBox);
				//ImGui::Checkbox(_xor_("lobby nig").c_str(), &Settings.ESP.ThreeDBox);
				ImGui::Checkbox(_xor_("Players Skeleton").c_str(), &Settings.ESP.Skeleton);
				ImGui::Checkbox(_xor_("Players Names").c_str(), &Settings.ESP.PlayerNames);
				ImGui::Checkbox(_xor_("Players Distance").c_str(), &Settings.ESP.Distance);
				ImGui::Checkbox(_xor_("Items").c_str(), &Settings.ESP.Weapons);
				ImGui::Checkbox(_xor_("Ammo / Bullets").c_str(), &Settings.ESP.Ammo);
				ImGui::Checkbox(_xor_("Chests").c_str(), &Settings.ESP.Chests);
				ImGui::Checkbox(_xor_("Ammo Box").c_str(), &Settings.ESP.AmmoBox);
				ImGui::SliderInt(_xor_("Max Distance##esp").c_str(), &Settings.OverallDistance, 25, 1000, ("%.0f"));

				ImGui::NextColumn();
				ImGui::Checkbox(_xor_("Helicopters").c_str(), &Settings.ESP.Helicopters);
				ImGui::Checkbox(_xor_("Car ESP").c_str(), &Settings.ESP.Cars);
				ImGui::Checkbox(_xor_("Boats").c_str(), &Settings.ESP.Boats);
				ImGui::Checkbox(_xor_("Snap Lines").c_str(), &Settings.ESP.PlayerLines);
				ImGui::Checkbox(_xor_("Supply Drops").c_str(), &Settings.ESP.SupplyDrop);
				ImGui::Checkbox(_xor_("Llamas").c_str(), &Settings.ESP.Llama);
				ImGui::Checkbox(_xor_("Weakspot").c_str(), &Settings.WeakSpot);
				ImGui::Checkbox(_xor_("Radar").c_str(), &Settings.RadarESP);
				ImGui::SliderFloat(_xor_("Radar Range").c_str(), &Settings.RadarESPRange, 0, 100, _xor_("%.0f").c_str());
				// ImGui::ColorPicker3(("Player Bones"), (float*)&Colours::SkeletonESPColour, ImGuiColorEditFlags_NoOptions);
				// ImGui::ColorPicker3(_xor_("Player Bones").c_str(), (float*)&Settings.ESP.PlayerVisibleColor, ImGuiColorEditFlags_NoOptions);
			}

			ImGui::Columns(1, _xor_("##restore_cols_1").c_str());

			if (ImGui::CollapsingHeader(_xor_("Aimbot & Misc").c_str()))
			{
				ImGui::Columns(2, (_xor_("##aimbot_cols").c_str()));

				ImGui::Checkbox(_xor_("Softaim##aimbot").c_str(), &Settings.Aimbot);
				ImGui::Checkbox(_xor_("Aimbot##aimbot").c_str(), &Settings.AimHelper);
				//ImGui::Checkbox(_xor_("No Spread##aimbot").c_str(), &Settings.NoSpreadAimbot);
				//ImGui::Checkbox(_xor_("Silent Aim##aimbot").c_str(), &Settings.SilentAimbot);
				//ImGui::Checkbox(_xor_("Sticky Aim##aimbot").c_str(), &Settings.StickySilent);
				ImGui::Checkbox(_xor_("FOV Circle##aimbot").c_str(), &Settings.ESP.AimbotFOV);
				//ImGui::Checkbox(_xor_("Weakspot Aimbot##aimbot").c_str(), &Settings.WeakSpot);
				//ImGui::Checkbox(_xor_("Line to Target##aimbot").c_str(), &Settings.ESP.AimLine);
				ImGui::SliderFloat(_xor_("FOV##aimbot").c_str(), &Settings.AimbotFOV, 1, 60, ("%.0f"));
				ImGui::SliderFloat(_xor_("Smoothness##aimbot").c_str(), &Settings.AimbotSlow, 0.f, 20.f, ("%.2f"));
				//Hotkey(_xor_("Aimbot Keybind##AimKey").c_str(), &Settings.aimkey);

				//ImGui::Spacing(); ImGui::Spacing();

				ImGui::NextColumn();

				//ImGui::Checkbox(_xor_("Boat Boost").c_str(), &Settings.BoatBoost);
				ImGui::Checkbox(_xor_("Rapid Fire").c_str(), &Settings.RapidFire);

				ImGui::Checkbox(_xor_("Crosshair").c_str(), &Settings.Crosshair);

				ImGui::Checkbox(_xor_("In Game FOV Changer").c_str(), &Settings.FOVChanger);
				if (Settings.FOVChanger)
					ImGui::SliderFloat(_xor_("FOV Changer").c_str(), &Settings.FOV, 80, 160, ("%.0f"));

				ImGui::Checkbox(_xor_("Visibility Check").c_str(), &Settings.visCheck);
			}

			ImGui::End();
		}
	}
	else
	{
		bHidden = true;
	}
}






extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
__declspec(dllexport) LRESULT CALLBACK WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (msg == WM_KEYUP && (wParam == VK_INSERT)) {
		ShowMenu = !ShowMenu;
		ImGui::GetIO().MouseDrawCursor = ShowMenu;
	}

	ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);

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

				ImGui::GetIO().Fonts->AddFontFromFileTTF(skCrypt("C:\\Windows\\Fonts\\seguihis.ttf"), 16.5f);
				m_pFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(skCrypt("C:\\Windows\\Fonts\\seguihis.tff"), 16.5f);
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