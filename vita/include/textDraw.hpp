void vita2d_draw_rectangle_gradient(float x, float y, float w, float h, unsigned int colorTR, unsigned int colorTL, unsigned int colorBR, unsigned int colorBL)
{
	vita2d_color_vertex *vertices = (vita2d_color_vertex *)vita2d_pool_memalign(
		4 * sizeof(vita2d_color_vertex), // 4 vertices
		sizeof(vita2d_color_vertex));

	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].z = +0.5f;
	vertices[0].color = colorTR;

	vertices[1].x = x + w;
	vertices[1].y = y;
	vertices[1].z = +0.5f;
	vertices[1].color = colorTL;

	vertices[2].x = x;
	vertices[2].y = y + h;
	vertices[2].z = +0.5f;
	vertices[2].color = colorBR;

	vertices[3].x = x + w;
	vertices[3].y = y + h;
	vertices[3].z = +0.5f;
	vertices[3].color = colorBL;

	vita2d_draw_array(SCE_GXM_PRIMITIVE_TRIANGLE_STRIP, vertices, 4);
}
// Draw Line
void drawLine(float x1, float y1, float x2, float y2, float weight = 1, unsigned int color = 0xFF000000) {
	float dx = x1 - x2;
	float dy = y1 - y2;
	weight /= 2;
	float lineangle = atan2(dy,dx) + pi/2;
	while (lineangle < 0) lineangle += pi;
	/*for (float i = -weight; i < weight; i+=1/5.0f) {
		vita2d_draw_line(x1 - i * cos(lineangle), y1 - i * sin(lineangle), x2 - i * cos(lineangle), y2 - i * sin(lineangle), color);
	}
	vita2d_draw_line(x1 - weight * cos(lineangle), y1 - weight * sin(lineangle), x2 - weight * cos(lineangle), y2 - weight * sin(lineangle), color);*/
	vita2d_color_vertex *vertices = (vita2d_color_vertex *)vita2d_pool_memalign(
		4 * sizeof(vita2d_color_vertex), // 4 vertices
		sizeof(vita2d_color_vertex));
	vertices[0].x = x1 - weight * cos(lineangle);
	vertices[0].y = y1 - weight * sin(lineangle);
	vertices[0].z = +0.5f;
	vertices[0].color = color;

	vertices[1].x = x1 + weight * cos(lineangle);
	vertices[1].y = y1 + weight * sin(lineangle);
	vertices[1].z = +0.5f;
	vertices[1].color = color;

	vertices[2].x = x2 - weight * cos(lineangle);
	vertices[2].y = y2 - weight * sin(lineangle);
	vertices[2].z = +0.5f;
	vertices[2].color = color;

	vertices[3].x = x2 + weight * cos(lineangle);
	vertices[3].y = y2 + weight * sin(lineangle);
	vertices[3].z = +0.5f;
	vertices[3].color = color;

	vita2d_draw_array(SCE_GXM_PRIMITIVE_TRIANGLE_STRIP, vertices, 4);
	vita2d_draw_fill_circle(x1, y1, weight, color);
	vita2d_draw_fill_circle(x2, y2, weight, color);
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