#include <string>
#include "buttons.hpp"
// Point-on-button check
bool onButton (button* buttonToDraw, int x, int y) {
	if (buttonToDraw->x > x) return false;
	if (buttonToDraw->y > y) return false;
	if (buttonToDraw->y + buttonToDraw->h < y) return false;
	if (buttonToDraw->x + buttonToDraw->w < x) return false;
	return true;
}