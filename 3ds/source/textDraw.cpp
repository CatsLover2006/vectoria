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
				C2D_DrawLine(letters[getIndex(str.at(i))]->lines[j]->startX * scale + floor(0.5 + x),
							letters[getIndex(str.at(i))]->lines[j]->startY * scale + floor(0.5 + y),
							color,
							letters[getIndex(str.at(i))]->lines[j]->endX * scale + floor(0.5 + x),
							letters[getIndex(str.at(i))]->lines[j]->endY * scale + floor(0.5 + y),
							color, weight, 0.4);
			}
			for (int j = 0; j < letters[getIndex(str.at(i))]->len; j++) {
				C2D_DrawCircleSolid(letters[getIndex(str.at(i))]->lines[j]->startX * scale + floor(0.5 + x),
									letters[getIndex(str.at(i))]->lines[j]->startY * scale + floor(0.5 + y),
									0.4, weight/2, color);
				C2D_DrawCircleSolid(letters[getIndex(str.at(i))]->lines[j]->endX * scale + floor(0.5 + x),
									letters[getIndex(str.at(i))]->lines[j]->endY * scale + floor(0.5 + y),
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