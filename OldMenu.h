//#pragma once
//
//if (ShowMenu)
//{
//	bHidden = false;
//	// menu here
//	ImGui::StyleColorsLight();
//
//	ImGuiStyle* style = &ImGui::GetStyle();
//	style->WindowPadding = ImVec2(15, 15);
//	style->WindowRounding = 1.0f;
//	style->FramePadding = ImVec2(5, 5);
//	style->ItemSpacing = ImVec2(12, 8);
//	style->ItemInnerSpacing = ImVec2(8, 6);
//	style->IndentSpacing = 25.0f;
//	style->ScrollbarSize = 0.0f;
//	style->ScrollbarRounding = 1.0f;
//	style->GrabMinSize = 5.0f;
//	style->GrabRounding = 3.0f;
//	style->WindowTitleAlign = ImVec2(0.06, 1.1);
//	style->Alpha = 1.f;
//	// title 
//	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, backgroundColor);
//	ImGui::PushStyleColor(ImGuiCol_TitleBg, backgroundColor);
//	ImGui::PushStyleColor(ImGuiCol_TitleBgCollapsed, backgroundColor);
//	ImGui::PushStyleColor(ImGuiCol_Border, innerColor); // 
//	ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(0.00f, 0.00f, 0.00f, 0.00f)); //
//	// window
//	ImGui::PushStyleColor(ImGuiCol_Text, textColor);
//	ImGui::PushStyleColor(ImGuiCol_TextDisabled, textColor);
//	ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, textColor);
//	ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor);
//	ImGui::PushStyleColor(ImGuiCol_Border, innerColor);
//	// button
//	ImGui::PushStyleColor(ImGuiCol_Button, backgroundColor);
//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, backgroundColor);
//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, backgroundColor);
//	ImGui::PushStyleColor(ImGuiCol_PlotLines, ImVec4(0.40f, 0.39f, 0.38f, 1.00f));
//	ImGui::PushStyleColor(ImGuiCol_PlotLinesHovered, ImVec4(0.25f, 1.00f, 0.00f, 1.00f));
//	ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.40f, 0.39f, 0.38f, 1.00f));
//	ImGui::PushStyleColor(ImGuiCol_PlotHistogramHovered, ImVec4(0.25f, 1.00f, 0.00f, 1.00f));
//	ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.25f, 1.00f, 0.00f, 1.00f));
//	ImGui::PushStyleColor(ImGuiCol_ModalWindowDarkening, ImVec4(94 / 255.f, 94 / 255.f, 94 / 255.f, 1.00f));
//	// Slider
//	ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(94 / 255.f, 94 / 255.f, 94 / 255.f, 1.00f));
//	ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(94 / 255.f, 94 / 255.f, 94 / 255.f, 1.00f));
//	ImGui::PushStyleColor(ImGuiCol_FrameBg, innerColor);
//	ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, innerColor);
//	ImGui::PushStyleColor(ImGuiCol_FrameBgActive, innerColor);
//	ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.48f, 0.48f, 0.48f, 1.00f));
//
//	std::string title = E("FORTNITE (Build: ");
//	title += __DATE__;
//	title += E(" ");
//	title += __TIME__;
//	title += E(")");
//	ImGuiWindowFlags TargetFlags;
//	TargetFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
//	bool trueSend = false;
//	bool falseSend = false;
//
//	if (ImGui::Begin(title.c_str(), 0, ImVec2(0, 600), -1.f, TargetFlags)) {
//		ImVec2 ve = ImVec2(ImGui::GetItemRectMin().x + 15, ImGui::GetItemRectMin().y + 80);
//		ImVec2 v = ImVec2(ImGui::GetItemRectMax().x - 15, ImGui::GetItemRectMax().y + 560);
//		ImGui::GetOverlayDrawList()->AddRect(ve, v, IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));
//
//		static short tab = 0;
//		ImGui::BeginGroup();
//		if (tab == 0) {
//			ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
//			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
//			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
//		}
//		if (tab == 0)
//			utils::PushDisabled(true);
//		else
//			utils::PushDisabled(false);
//		bool tab_aimbot = ImGui::Button(E("AIMBOT"), ImVec2(150, 23));
//		utils::PopDisabled();
//		if (tab == 0)
//			ImGui::PopStyleColor(3);
//		ImGui::SameLine(NULL, 0);
//		if (tab == 1) {
//			ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
//			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
//			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
//		}
//		if (tab == 1)
//			utils::PushDisabled(true);
//		else
//			utils::PushDisabled(false);
//		bool tab_visuals = ImGui::Button(E("VISUALS"), ImVec2(150, 23));
//		utils::PopDisabled();
//		if (tab == 1)
//			ImGui::PopStyleColor(3);
//		ImGui::SameLine(NULL, 0);
//		if (tab == 2) {
//			ImGui::PushStyleColor(ImGuiCol_Button, innerColor);
//			ImGui::PushStyleColor(ImGuiCol_ButtonHovered, innerColor);
//			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.00f, 1.00f, 1.00f, 1.00f));
//		}
//		if (tab == 2)
//			utils::PushDisabled(true);
//		else
//			utils::PushDisabled(false);
//		bool tab_misc = ImGui::Button(E("MISC & EXPLOITS"), ImVec2(150, 23));
//		utils::PopDisabled();
//		if (tab == 2)
//			ImGui::PopStyleColor(3);
//		ImGui::EndGroup();
//		//ImVec2 v = ImVec2(ImGui::GetItemRectMax().x * 1.5, ImGui::GetItemRectMax().y * 1.5);
//		ImGui::GetOverlayDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(innerColorRGB.x, innerColorRGB.y, innerColorRGB.z, innerColorRGB.w));
//
//		if (tab_aimbot) {
//			tab = 0;
//		}
//		if (tab_visuals) {
//			tab = 1;
//		}
//		if (tab_misc) {
//			tab = 2;
//		}
//		ImGui::Spacing();
//
//		if (tab == 0) { // AIMBOT TAB
//			ImGui::BeginGroup();
//			
//			ImGui::Spacing();
//			//ImGui::Spacing();
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButtonA(E("Memory Aimbot"), &Settings.Aimbot, 1);
//			
//			ImGui::Text(E("Memory Aimbot"));
//
//			if (Settings.Aimbot) {
//				
//				ImGui::SameLine(NULL, 9);
//				utils::ToggleButton(E("[OPTION] Aimbot Lock"), &Settings.AimHelper);
//				
//				ImGui::Text(E("[OPTION] Aimbot Lock"));
//			}
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButtonA(E("Silent Aimbot"), &Settings.SilentAimbot, 2);
//			
//			ImGui::Text(E("Silent Aimbot"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Draw crosshair"), &Settings.Crosshair);
//			
//			ImGui::Text(E("Draw crosshair"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Draw FOV"), &Settings.ESP.AimbotFOV);
//			
//			ImGui::Text(E("Draw FOV"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Random aim pos"), &Settings.ESP.RandomAim);
//			
//			ImGui::Text(E("Random aim pos"));
//
//			ImGui::Dummy(ImVec2(6, 6));
//			
//			ImGui::SameLine(NULL, 9);
//			ImGui::PushItemWidth(200);
//			ImGui::SliderFloat(E("Aim FOV"), &Settings.AimbotFOV, 1.0f, 80.f);
//
//			ImGui::Dummy(ImVec2(6, 6));
//			
//			ImGui::SameLine(NULL, 9);
//			ImGui::PushItemWidth(200);
//			ImGui::SliderFloat(E("Aim Smooth"), &Settings.AimbotSlow, 0.0f, 25.f);
//
//			ImGui::Dummy(ImVec2(6, 6));
//			
//			ImGui::SameLine(NULL, 9);
//			ImGui::PushItemWidth(200);
//			ImGui::SliderText(E("Aimbot pos"), &Settings.AimPos, 1, 3, E("Head"), E("Body"), E("Penis"));
//
//			ImGui::Dummy(ImVec2(6, 6));
//			
//			ImGui::SameLine(NULL, 9);
//			ImGui::PushItemWidth(200);
//			ImGui::SliderFloat(E("Crosshair scale"), &Settings.crosshairNuclear, 1, 10);
//			Settings.crosshairScale = Settings.crosshairNuclear + 7;
//
//			ImGui::EndGroup();
//
//			////////////////////////////////////////////
//			// ON THE SIDE:
//			ImGui::SameLine(ImGui::GetWindowWidth() - 111/*111: size of the button*/ - 10);
//			ImGui::BeginGroup();
//			ImGui::Dummy(ImVec2(0.0f, 5.0f));
//			//ImGui::Spacing();
//
//			
//			ImGui::SameLine(NULL, 1);
//			ImGui::Text(E("Aimbot Key"));
//			ImGui::Hotkey(E("Aimbot Key"), &Settings.aimkey, ImVec2{ 111, 36 }, 0);
//
//			ImGui::EndGroup();
//		}
//
//		if (tab == 1) { // VISUALS TAB
//			ImGui::BeginGroup();
//			
//			ImGui::Spacing();
//			//ImGui::Spacing();
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Enable visuals (F2)"), &Settings.ESP.Players);
//			
//			ImGui::Text(E("Enable visuals (F2)"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Show Distance"), &Settings.ESP.Distance);
//			
//			ImGui::Text(E("Show Distance"));
//
//			utils::PushDisabled(true);
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Show Player Names [Disabled]"), &Settings.ESP.PlayerNames);
//			
//			ImGui::Text(E("Show Player Names [Disabled]"));
//			utils::PopDisabled();
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Show Player Weapons"), &Settings.ESP.PlayerWeapons);
//			
//			ImGui::Text(E("Show Player Weapons"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Player Skeleton"), &Settings.ESP.Skeleton);
//			
//			ImGui::Text(E("Player Skeleton"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Player Box"), &Settings.ESP.Box);
//			
//			ImGui::Text(E("Player Box"));
//
//			if (Settings.ESP.Box) {
//				
//				ImGui::SameLine(NULL, 9);
//				utils::ToggleButton(E("[OPTION] 3D Box"), &Settings.ESP.ThreeDBox);
//				
//				ImGui::Text(E("[OPTION] 3D Box"));
//			}
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Weapons ESP"), &Settings.ESP.Weapons);
//			
//			ImGui::Text(E("Weapons ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Upgrade Bench ESP"), &Settings.ESP.UpgradeBench);
//			
//			ImGui::Text(E("Upgrade Bench ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Ammo ESP"), &Settings.ESP.Ammo);
//			
//			ImGui::Text(E("Ammo ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Chests ESP"), &Settings.ESP.Chests);
//			
//			ImGui::Text(E("Chests ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Ammo Box ESP"), &Settings.ESP.AmmoBox);
//			
//			ImGui::Text(E("Ammo Box ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Llama ESP"), &Settings.ESP.Llama);
//			
//			ImGui::Text(E("Llama ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Supply Drop ESP"), &Settings.ESP.SupplyDrop);
//			
//			ImGui::Text(E("Supply Drop ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Agents/Boss ESP"), &Settings.ESP.AgentsBoss);
//			
//			ImGui::Text(E("Agents/Boss ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Shark ESP"), &Settings.ESP.Shark);
//			
//			ImGui::Text(E("Shark ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Boats ESP"), &Settings.ESP.Boats);
//			
//			ImGui::Text(E("Boats ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Helicopters ESP"), &Settings.ESP.Helicopters);
//			
//			ImGui::Text(E("Helicopters ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Cars ESP"), &Settings.ESP.Cars);
//			
//			ImGui::Text(E("Cars ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Trucks ESP"), &Settings.ESP.Trucks);
//			
//			ImGui::Text(E("Trucks ESP"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Taxi ESP"), &Settings.ESP.Taxi);
//			
//			ImGui::Text(E("Taxi ESP"));
//
//			ImGui::EndGroup();
//
//			////////////////////////////////////////////
//			// ON THE SIDE:
//			ImGui::SameLine(NULL, 0/*47*/);
//			ImGui::BeginGroup();
//			ImGui::Dummy(ImVec2(0.0f, 5.0f));
//			//ImGui::Spacing();
//
//			ImGui::Dummy(ImVec2(6, 6));
//			
//			ImGui::SameLine(NULL, 9);
//			ImGui::PushItemWidth(200);
//			ImGui::SliderInt(E("Min Items Tier"), &Settings.ESP.MinWeaponTier, 1, 5);
//
//			ImGui::Dummy(ImVec2(6, 6));
//			
//			ImGui::SameLine(NULL, 9);
//			ImGui::PushItemWidth(200);
//			ImGui::SliderInt(E("Items max distance"), &Settings.OverallDistance, 50, 500);
//
//			ImGui::Dummy(ImVec2(6, 6));
//			
//			ImGui::SameLine(NULL, 9);
//			ImGui::PushItemWidth(200);
//			ImGui::SliderFloat(E("Line thickness"), &Settings.SnaplinePower, 1.f, 10.f);
//
//			
//			ImGui::SameLine(NULL, 6);
//			utils::ToggleButton(E("Corner box"), &Settings.ESP.CornerBox);
//			
//			ImGui::Text(E("Corner box"));
//
//			
//			ImGui::SameLine(NULL, 6);
//			utils::ToggleButton(E("Draw Direction Lazer"), &Settings.ESP.Lazer);
//			
//			ImGui::Text(E("Draw Direction Lazer"));
//
//			
//			ImGui::SameLine(NULL, 6);
//			utils::ToggleButton(E("Enable visible check"), &Settings.visCheck);
//			
//			ImGui::Text(E("Enable visible check"));
//
//			
//			ImGui::SameLine(NULL, 6);
//			utils::ToggleButton(E("Aim Line"), &Settings.ESP.AimLine);
//			
//			ImGui::Text(E("Aim Line"));
//
//			
//			ImGui::SameLine(NULL, 6);
//			utils::ToggleButton(E("XP Coin"), &Settings.ESP.XPCoin);
//			
//			ImGui::Text(E("XP Coin"));
//
//			
//			ImGui::SameLine(NULL, 6);
//			utils::ToggleButton(E("Draw snaplines"), &Settings.ESP.PlayerLines);
//			
//			ImGui::Text(E("Draw snaplines"));
//
//			
//			ImGui::SameLine(NULL, 6);
//			utils::ToggleButton(E("Square FOV"), &Settings.isRecFov);
//			
//			ImGui::Text(E("Square FOV"));
//
//			ImGui::EndGroup();
//
//		}
//		if (tab == 2) { // EXPLOITS TAB
//			ImGui::BeginGroup();
//			
//			ImGui::Spacing();
//			//ImGui::Spacing();
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Enable Info Bar"), &Settings.ShowInfoBar);
//			
//			ImGui::Text(E("Enable Info Bar"));
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Show warning about enemies in the area"), &Settings.WarningEnemiesArea);
//			
//			ImGui::Text(E("Show warning about enemies in the area"));*/
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Enable Radar ESP"), &Settings.RadarESP);
//			
//			ImGui::Text(E("Enable Radar ESP"));
//
//			if (Settings.RadarESP) {
//				ImGui::Dummy(ImVec2(6, 6));
//				
//				ImGui::SameLine(NULL, 9);
//				ImGui::PushItemWidth(200);
//				ImGui::SliderFloat(E("[OPTION] Radar Range"), &Settings.RadarESPRange, 7000.f, 50000.f);
//			}
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Enable Camera FOV Changer"), &Settings.FOVChanger);
//			
//			ImGui::Text(E("Enable Camera FOV Changer"));
//
//			if (Settings.FOVChanger) {
//				ImGui::Dummy(ImVec2(6, 6));
//				
//				ImGui::SameLine(NULL, 9);
//				ImGui::PushItemWidth(200);
//				ImGui::SliderFloat(E("[OPTION] Camera FOV Distance"), &Settings.FOV, 20.f, 140.f);
//			}
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Enable AirStuck"), &Settings.AirStuck);
//			
//			ImGui::Text(E("Enable AirStuck"));
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Instant Reload"), &Settings.InstantReload);
//			
//			ImGui::Text(E("Instant Reload"));
//			*/
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Sniper Bullet TP"), &Settings.SniperHits);
//			
//			ImGui::Text(E("Sniper Bullet TP"));
//
//			if (Settings.SniperHits) {
//				
//				ImGui::SameLine(NULL, 9);
//				utils::ToggleButton(E("[OPTION] Shoot through walls (Rage)"), &Settings.SniperThroughWalls);
//				
//				ImGui::Text(E("[OPTION] Shoot through walls (Rage)"));
//
//				
//				ImGui::SameLine(NULL, 9);
//				utils::ToggleButton(E("[OPTION] Sniper No Aimbot"), &Settings.SniperNoAimbot);
//				
//				ImGui::Text(E("[OPTION] Sniper No Aimbot"));
//			}
//			else {
//				Settings.SniperThroughWalls = false;
//				Settings.SniperNoAimbot = false;
//			}*/
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Boat Super Boost"), &Settings.BoatBoost);
//			
//			ImGui::Text(E("Boat Super Boost"));
//
//			if (Settings.BoatBoost) {
//				ImGui::Dummy(ImVec2(6, 6));
//				
//				ImGui::SameLine(NULL, 9);
//				ImGui::PushItemWidth(200);
//				ImGui::SliderFloat(E("[OPTION] Boost Speed Multiplier"), &Settings.BoatBoostMultiplier, 1.f, 10.f);
//			}*/
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Helicopter Infinite Boost"), &Settings.HelicopterInfiniteBoost);
//			
//			ImGui::Text(E("Helicopter Infinite Boost"));
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Helicopter Super Speed"), &Settings.HelicopterSpeed);
//			
//			ImGui::Text(E("Helicopter Super Speed"));
//
//			if (Settings.HelicopterSpeed) {
//				ImGui::Dummy(ImVec2(6, 6));
//				
//				ImGui::SameLine(NULL, 9);
//				ImGui::PushItemWidth(200);
//				ImGui::SliderFloat(E("[OPTION] Super Speed Multiplier"), &Settings.HelicopterSpeedMultiplier, 1.f, 10.f);
//			}*/
//
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Rapid Fire"), &Settings.RapidFire);
//			
//			ImGui::Text(E("Rapid Fire"));
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("No Spread"), &Settings.NoSpreadAimbot);
//			
//			ImGui::Text(E("No Spread"));*/
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Invisible Player"), &Settings.InvisiblePlayer);
//			
//			ImGui::Text(E("Invisible Player"));
//			*/
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Freecam [BETA]"), &Settings.FreeCam);
//			
//			ImGui::Text(E("Freecam [BETA]"));
//			*/
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Boat Fly"), &Settings.BoatFly);
//			
//			ImGui::Text(E("Boat Fly"));*/
//
//			//if (rank == 1) {
//			ImGui::Dummy(ImVec2(0.0f, 0.5f));
//			ImGui::SameLine(NULL, 9);
//			ImGui::Text(E("-> Administrator Section:"));
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Annas Nonsense"), &Settings.AnnasMisc);
//			
//			ImGui::Text(E("Annas Nonsense"));
//			*/
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("Enable Objects Names Display (Caution: Might cuz FPS drop)"), &Settings.Dev);
//			
//			ImGui::Text(E("Enable Objects Names Display (Caution: Might cuz FPS drop)"));
//
//			/*
//			
//			ImGui::SameLine(NULL, 9);
//			utils::ToggleButton(E("[BETA] Player TP"), &Settings.PlrTP);
//			
//			ImGui::Text(E("[BETA] Player TP"));*/
//
//
//			//}
//			ImGui::EndGroup();
//
//			////////////////////////////////////////////
//			// ON THE SIDE:
//			ImGui::SameLine(ImGui::GetWindowWidth() - 111/*111: size of the button*/ - 10);
//			ImGui::BeginGroup();
//			ImGui::Dummy(ImVec2(0.0f, 5.0f));
//			//ImGui::Spacing();
//
//			
//			ImGui::SameLine(NULL, 1);
//			ImGui::Text(E("AirStuck Key"));
//			ImGui::Hotkey(E("AirStuck Key"), &Settings.AirStuckKey, ImVec2{ 111, 36 }, 0);
//			/*
//			
//			ImGui::SameLine(NULL, 1);
//			ImGui::Text(E("TP Key"));
//			ImGui::Hotkey(E("TP Key"), &Settings.BoatTPkey, ImVec2{ 111, 36 }, 0);
//			*/
//			ImGui::EndGroup();
//		}
//	}
//	ImGui::End();
//
//	POINT point;
//	if (GetCursorPos(&point)) {
//		utils::DrawBox(point.x, point.y, 6, 6, 0, 0, 0, 1.f, true);
//	}
//}
//else
//bHidden = true;