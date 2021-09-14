

#pragma once

namespace ImGui
{
	inline bool custom_UseFontShadow;
	inline unsigned int custom_FontShadowColor;

	inline static void PushFontShadow(unsigned int col)
	{
		custom_UseFontShadow = true;
		custom_FontShadowColor = col;
	}

	inline static void PopFontShadow(void)
	{
		custom_UseFontShadow = false;
	}
}; // namespace ImGui