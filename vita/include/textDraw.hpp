// Draw Line
void drawLine(float x1, float y1, float x2, float y2, float weight = 1, unsigned int color = clrBlack) {
	float dx = x1 - x2;
	float dy = y1 - y2;
	for (float i = -weight; i < weight; i+=0.5) {
		vita2d_draw_line(x1 - i * abs_c(cos(atan2(dy,dx))), y1 - i * abs_c(sin(atan2(dy,dx))), x2 - i * abs_c(cos(atan2(dy,dx))), y2 - i * abs_c(sin(atan2(dy,dx))), color);
	}
	vita2d_draw_line(x1 - weight * abs_c(cos(atan2(dy,dx))), y1 - weight * abs_c(sin(atan2(dy,dx))), x2 - weight * abs_c(cos(atan2(dy,dx))), y2 - weight * abs_c(sin(atan2(dy,dx))), color);
	vita2d_draw_fill_circle(x1, y1, weight/2, color);
	vita2d_draw_fill_circle(x2, y2, weight/2, color);
}
#include "../../data/letters.hpp"
// Draw String
void drawString(std::string str, double x, double y, double scale, double weight, unsigned int color) {
	for (unsigned int i = 0; i < str.size(); i++) {
		if (str.at(i) == ' ') x += 23 * scale + weight; // Effectively an A
		else {
			for (int j = 0; j < letters[getIndex(str.at(i))]->len; j++) {
				drawLine(letters[getIndex(str.at(i))]->lines[j]->startX * scale + (x),
						letters[getIndex(str.at(i))]->lines[j]->startY * scale + (y),
						letters[getIndex(str.at(i))]->lines[j]->endX * scale + (x),
						letters[getIndex(str.at(i))]->lines[j]->endY * scale + (y),
						weight, color);
			}
			x += (letters[getIndex(str.at(i))]->size + 3) * scale + weight;
		}
	}
}
#include "../../data/buttons.hpp"
// Draw Button
void drawButton (button* buttonToDraw, unsigned int color, double weight) {
	drawLine(buttonToDraw->x, buttonToDraw->y, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, weight, color);
	drawLine(buttonToDraw->x, buttonToDraw->y, buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, weight, color);
	drawLine(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, weight, color);
	drawLine(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, weight, color);
	drawString(buttonToDraw->buttonText, buttonToDraw->x + buttonToDraw->w/2 - getWidth(buttonToDraw->buttonText, buttonToDraw->textScale, weight)/2,
						buttonToDraw->y + (buttonToDraw->h/2) + buttonToDraw->textScale * 12.5, buttonToDraw->textScale, weight, color);
}
void drawButton (const button* buttonToDraw, unsigned int color, double weight) {
	drawLine(buttonToDraw->x, buttonToDraw->y, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, weight, color);
	drawLine(buttonToDraw->x, buttonToDraw->y, buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, weight, color);
	drawLine(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, weight, color);
	drawLine(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, weight, color);
	drawString(buttonToDraw->buttonText, buttonToDraw->x + buttonToDraw->w/2 - getWidth(buttonToDraw->buttonText, buttonToDraw->textScale, weight)/2,
						buttonToDraw->y + (buttonToDraw->h/2) + buttonToDraw->textScale * 12.5, buttonToDraw->textScale, weight, color);
}