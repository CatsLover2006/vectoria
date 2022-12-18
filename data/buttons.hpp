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