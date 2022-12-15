class button {
	public:
		std::string buttonText;
		float x, y, w, h, textScale;
		button(std::string text, float xIn, float yIn, float wIn, float hIn, float textScaleIn) {
			buttonText = text;
			x = xIn;
			y = yIn;
			w = wIn;
			h = hIn;
			textScale = textScaleIn;
		}
};

// Draw Button
void drawButton (button* buttonToDraw, u32 color, float weight) {
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, color, weight, 0.4f);
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y, color, buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, color, weight, 0.4f);
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color, weight, 0.4f);
	C2D_DrawLine(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color, weight, 0.4f);
	C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, 0.4f, weight/2, color);
	drawString(buttonToDraw->buttonText, buttonToDraw->x + buttonToDraw->w/2 - getWidth(buttonToDraw->buttonText, buttonToDraw->textScale, weight)/2,
						buttonToDraw->y + (buttonToDraw->h/2) + buttonToDraw->textScale * 12.5, buttonToDraw->textScale, weight, color);
}
void drawButton (const button* buttonToDraw, u32 color, float weight) {
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, color, weight, 0.4f);
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y, color, buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, color, weight, 0.4f);
	C2D_DrawLine(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color, weight, 0.4f);
	C2D_DrawLine(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, color, buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, color, weight, 0.4f);
	C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x, buttonToDraw->y + buttonToDraw->h, 0.4f, weight/2, color);
	C2D_DrawCircleSolid(buttonToDraw->x + buttonToDraw->w, buttonToDraw->y + buttonToDraw->h, 0.4f, weight/2, color);
	drawString(buttonToDraw->buttonText, buttonToDraw->x + buttonToDraw->w/2 - getWidth(buttonToDraw->buttonText, buttonToDraw->textScale, weight)/2,
						buttonToDraw->y + (buttonToDraw->h/2) + buttonToDraw->textScale * 12.5, buttonToDraw->textScale, weight, color);
}

// Point-on-button check
bool onButton (const button* buttonToDraw, int x, int y) {
	if (buttonToDraw->x > x) return false;
	if (buttonToDraw->y > y) return false;
	if (buttonToDraw->y + buttonToDraw->h < y) return false;
	if (buttonToDraw->x + buttonToDraw->w < x) return false;
	return true;
}
bool onButton (button* buttonToDraw, int x, int y) {
	if (buttonToDraw->x > x) return false;
	if (buttonToDraw->y > y) return false;
	if (buttonToDraw->y + buttonToDraw->h < y) return false;
	if (buttonToDraw->x + buttonToDraw->w < x) return false;
	return true;
}