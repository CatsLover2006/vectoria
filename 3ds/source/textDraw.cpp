#include "../../data/line.hpp"

#include <citro2d.h>
#include <string>
#include "../../data/letters.hpp"
// Draw String
void drawString(std::string str, double x, double y, double scale, double weight, u32 color) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') x += 23 * scale + weight; // Effectively an A
		else {
			for (int j = 0; j < letters[getIndex(str.at(i))]->len; j++) {
				C2D_DrawLine(letters[getIndex(str.at(i))]->lines[j]->startX * scale + (x),
							letters[getIndex(str.at(i))]->lines[j]->startY * scale + (y),
							color,
							letters[getIndex(str.at(i))]->lines[j]->endX * scale + (x),
							letters[getIndex(str.at(i))]->lines[j]->endY * scale + (y),
							color, weight, 0.4);
			}
			for (int j = 0; j < letters[getIndex(str.at(i))]->len; j++) {
				C2D_DrawCircleSolid(letters[getIndex(str.at(i))]->lines[j]->startX * scale + (x),
									letters[getIndex(str.at(i))]->lines[j]->startY * scale + (y),
									0.4, weight/2, color);
				C2D_DrawCircleSolid(letters[getIndex(str.at(i))]->lines[j]->endX * scale + (x),
									letters[getIndex(str.at(i))]->lines[j]->endY * scale + (y),
									0.4, weight/2, color);
			}
			x += (letters[getIndex(str.at(i))]->size + 3) * scale + weight;
		}
	}
}
#include "../../data/buttons.hpp"
// Draw Button
void drawButton (button* buttonToDraw, u32 color, double weight) {
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, color, weight, 0.5);
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y, color, buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, color, weight, 0.5);
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color, weight, 0.5);
	C2D_DrawLine(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color, weight, 0.5);
	C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y, 0.5, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, 0.5, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, 0.5, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, 0.5, weight/2, color);
	drawString(buttonToDraw->buttonText, buttonToDraw->x + buttonToDraw->w/2 - getWidth(buttonToDraw->buttonText, buttonToDraw->textScale, weight)/2,
						buttonToDraw->y + (buttonToDraw->h/2) + buttonToDraw->textScale * 12.5, buttonToDraw->textScale, weight, color);
}
C3D_RenderTarget* C2D_CreateScreenTargetAA(gfxScreen_t screen, gfx3dSide_t side)
{
	int height;
	switch (screen)
	{
		default:
		case GFX_BOTTOM:
			height = GSP_SCREEN_HEIGHT_BOTTOM;
			break;
		case GFX_TOP:
			height = !gfxIsWide() ? GSP_SCREEN_HEIGHT_TOP : GSP_SCREEN_HEIGHT_TOP_2X;
			break;
	}
	C3D_RenderTarget* target = C3D_RenderTargetCreate(GSP_SCREEN_WIDTH * 2, height * 2, GPU_RB_RGBA8, GPU_RB_DEPTH16);
	if (target)
		C3D_RenderTargetSetOutput(target, screen, side,
			GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) |
			GX_TRANSFER_IN_FORMAT(GPU_RB_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) |
			GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_XY));
	return target;
}
C3D_RenderTarget* C2D_CreateScreenTargetHAA(gfxScreen_t screen, gfx3dSide_t side)
{
	int height;
	switch (screen)
	{
		default:
		case GFX_BOTTOM:
			height = GSP_SCREEN_HEIGHT_BOTTOM;
			break;
		case GFX_TOP:
			height = !gfxIsWide() ? GSP_SCREEN_HEIGHT_TOP : GSP_SCREEN_HEIGHT_TOP_2X;
			break;
	}
	C3D_RenderTarget* target = C3D_RenderTargetCreate(GSP_SCREEN_WIDTH * 2, height, GPU_RB_RGBA8, GPU_RB_DEPTH16);
	if (target)
		C3D_RenderTargetSetOutput(target, screen, side,
			GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) |
			GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) |
			GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_X));
	return target;
}