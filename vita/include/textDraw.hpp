#include "../../data/letters.hpp"
// Draw String
void drawString(std::string str, double x, double y, double scale, double weight, unsigned int color) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') x += 23 * scale + weight; // Effectively an A
		else {
			for (int j = 0; j < letters[getIndex(str.at(i))]->len; j++) {
				vita2d_draw_line(letters[getIndex(str.at(i))]->lines[j]->startX * scale + (x),
							letters[getIndex(str.at(i))]->lines[j]->startY * scale + (y),
							letters[getIndex(str.at(i))]->lines[j]->endX * scale + (x),
							letters[getIndex(str.at(i))]->lines[j]->endY * scale + (y),
							color);
			}
			/*for (int j = 0; j < letters[getIndex(str.at(i))]->len; j++) {
				C2D_DrawCircleSolid(letters[getIndex(str.at(i))]->lines[j]->startX * scale + floor(0.5 + x),
									letters[getIndex(str.at(i))]->lines[j]->startY * scale + floor(0.5 + y),
									0.5f, weight/2, color);
				C2D_DrawCircleSolid(letters[getIndex(str.at(i))]->lines[j]->endX * scale + floor(0.5 + x),
									letters[getIndex(str.at(i))]->lines[j]->endY * scale + floor(0.5 + y),
									0.5f, weight/2, color);
			}*/
			x += (letters[getIndex(str.at(i))]->size + 3) * scale + weight;
		}
	}
}
#include "../../data/buttons.hpp"
// Draw Button
void drawButton (button* buttonToDraw, unsigned int color, double weight) {
	vita2d_draw_line(buttonToDraw->x, buttonToDraw->y, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, color);
	vita2d_draw_line(buttonToDraw->x, buttonToDraw->y, buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, color);
	vita2d_draw_line(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color);
	vita2d_draw_line(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color);
	/*C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, 0.4f, weight/2, color);*/
	drawString(buttonToDraw->buttonText, buttonToDraw->x + buttonToDraw->w/2 - getWidth(buttonToDraw->buttonText, buttonToDraw->textScale, weight)/2,
						buttonToDraw->y + (buttonToDraw->h/2) + buttonToDraw->textScale * 12.5, buttonToDraw->textScale, weight, color);
}
void drawButton (const button* buttonToDraw, unsigned int color, double weight) {
	vita2d_draw_line(buttonToDraw->x, buttonToDraw->y, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, color);
	vita2d_draw_line(buttonToDraw->x, buttonToDraw->y, buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, color);
	vita2d_draw_line(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color);
	vita2d_draw_line(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color);
	/*C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, 0.4f, weight/2, color);*/
	drawString(buttonToDraw->buttonText, buttonToDraw->x + buttonToDraw->w/2 - getWidth(buttonToDraw->buttonText, buttonToDraw->textScale, weight)/2,
						buttonToDraw->y + (buttonToDraw->h/2) + buttonToDraw->textScale * 12.5, buttonToDraw->textScale, weight, color);
}