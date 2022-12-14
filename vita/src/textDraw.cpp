#include "../../data/line.hpp"
#include "../../data/basemath.hpp"
#include <string>
#include <vita2d.h>
#include <cmath>
// Draw Arc
void vita2d_draw_fill_arc(float x, float y, float radius, float initial_rotation, float end_rotation, unsigned int color)
{
	static const int num_segments = 100;
	vita2d_color_vertex *vertices = (vita2d_color_vertex *)vita2d_pool_memalign(
		(num_segments + 1) * sizeof(vita2d_color_vertex),
		sizeof(vita2d_color_vertex));
	vertices[0].x = x;
	vertices[0].y = y;
	vertices[0].z = +0.5f;
	vertices[0].color = color;
	float theta = (end_rotation - initial_rotation) / (float)(num_segments-1);
	float c = cos(theta);
	float s = sin(theta);
	float t;
	float xx = radius * cos(initial_rotation);
	float yy = radius * sin(initial_rotation);
	int i; 
	for (i = 1; i <= num_segments; i++) {
		vertices[i].x = x + xx;
		vertices[i].y = y + yy;
		vertices[i].z = +0.5f;
		vertices[i].color = color;

		t = xx;
		xx = c * xx - s * yy;
		yy = s * t + c * yy;
	}
	vita2d_draw_array(SCE_GXM_PRIMITIVE_TRIANGLE_FAN, vertices, num_segments + 1);
}
// Draw Gradient Rectangle
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
	vita2d_draw_fill_arc(x1, y1, weight, lineangle - pi, lineangle, color);
	vita2d_draw_fill_arc(x2, y2, weight, lineangle, lineangle + pi, color);
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