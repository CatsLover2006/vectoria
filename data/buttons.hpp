class button {
	public:
		std::string buttonText;
		double x, y, w, h, textScale;
		button(std::string text, double xIn, double yIn, double wIn, double hIn, double textScaleIn) {
			buttonText = text;
			x = xIn;
			y = yIn;
			w = wIn;
			h = hIn;
			textScale = textScaleIn;
		}
};
bool onButton (button* buttonToDraw, int x, int y);