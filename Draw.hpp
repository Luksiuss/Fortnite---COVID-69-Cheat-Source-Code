#pragma once

class nkDraw
{
public:
	nk_context* CopyContext;
	struct nk_font_atlas* atlas;
	void SetBuffer(nk_command_buffer* buffer);
	void SetOverlaySize(float X, float Y);
	float* GetOverlaySize();
	void DrawCicle(int Radius, int x, int y, int rx, int gx, int bx, int ax);
	void DrawFOV(int Radius);
	void nkDrawText(const char* String, int X, int Y, int Size, nk_color c);
	void DrawLine(int x1, int y1, int x2, int y2, int thickness, nk_color color);
	void DrawFilledRect(int x, int y, int w, int h, float rounding, nk_color color);

private:
	nk_command_buffer* b;
	float ScreenSize[2];
};

void nkDraw::SetBuffer(nk_command_buffer* buffer)
{
	this->b = buffer;
}

void nkDraw::SetOverlaySize(float X, float Y)
{
	ScreenSize[0] = X;
	ScreenSize[1] = Y;
}

float* nkDraw::GetOverlaySize()
{
	return ScreenSize;
}

void nkDraw::DrawFOV(int Radius)
{
	if (!b) return;
	nk_color c = { 0xB2,0x22,0x22,0xFF };
	auto r = nk_rect(this->ScreenSize[0] / 2 - Radius, this->ScreenSize[1] / 2 - Radius, Radius*2, Radius * 2);
	nk_stroke_circle(b, r, 1, c);
}

void nkDraw::DrawCicle(int Radius, int x, int y, int rx, int gx, int bx, int ax)
{
	if (!b) return;
	auto r = nk_rect(x - Radius, y - Radius, Radius * 2, Radius * 2);
	nk_color c = { rx,gx,bx,ax };
	nk_stroke_circle(b, r, 1, c);
}

void nkDraw::nkDrawText(const char* String, int X, int Y, int Size, nk_color c)
{
	if (!b || !CopyContext || !CopyContext->style.font) return;

	nk_color bg = { 1,1,1,0xFF };
	auto r = nk_rect(X - 1 - (CopyContext->style.font->width(CopyContext->style.font->userdata, CopyContext->style.font->height, String, Size) / 2), Y - 1 - (CopyContext->style.font->height/2), 500, 100);
	nk_draw_text(b, r, String, Size, CopyContext->style.font, bg, c);
}

void nkDraw::DrawLine(int x1, int y1, int x2, int y2, int thickness, nk_color color)
{
	if (!b) return;
	
	nk_stroke_line(b, x1, y1, x2, y2, thickness, color);
}

void nkDraw::DrawFilledRect(int x, int y, int w, int h, float rounding, nk_color color)
{
	if (!b) return;

	nk_fill_rect(b, nk_rect(x, y, w, h), rounding, color);
}