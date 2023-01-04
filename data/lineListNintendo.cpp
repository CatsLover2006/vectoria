#include "line.hpp"

#include "lineListNintendo.hpp"

#include <cmath>
#include "basemath.hpp"

line* linelistBG[] = {
	new line(90, 20, 80 + 10/8.0f, 45), // Level 1, A Button
	new line(90, 20, 100 - 10/8.0f, 45), // Level 1, A Button
	new line(85, 35, 95, 35), // Level 1, A Button
	new line(90, 10, 65, 35), // Level 1, A Button
	new line(90, 10, 115, 35), // Level 1, A Button
	new line(90, 60, 65, 35), // Level 1, A Button
	new line(90, 60, 115, 35), // Level 1, A Button
	new line(135, 110, 145, 110), // Level 1, Right Arrow
	new line(140, 115, 145, 110), // Level 1, Right Arrow
	new line(140, 105, 145, 110), // Level 1, Right Arrow
	new line(85, 110, 75, 110), // Level 1, Left Arrow
	new line(80, 115, 75, 110), // Level 1, Left Arrow
	new line(80, 105, 75, 110), // Level 1, Left Arrow
	new line(140, 25, 140, 45), // Level 1, Jump Arrow
	new line(130, 35, 140, 25), // Level 1, Jump Arrow
	new line(150, 35, 140, 25), // Level 1, Jump Arrow
	new line(375, 35, 375, 55), // Level 1, End Arrow
	new line(365, 45, 375, 35), // Level 1, End Arrow
	new line(385, 45, 375, 35), // Level 1, End Arrow
	new line(390, 72.5, 365, 60), // Level 1, End Flag
	new line(365, 60, 345, 100), // Level 1, End Flag
	new line(390, 72.5, 380, 92.5), // Level 1, End Flag
	new line(355, 80, 380, 92.5), // Level 1, End Flag
	new line(365, 60, 380, 92.5), // Level 1, End Flag
	new line(355, 80, 390, 72.5), // Level 1, End Flag
	new line(100, 70, 100, 100), // Level 1, D-Pad
	new line(70, 100, 100, 100), // Level 1, D-Pad
	new line(120, 70, 120, 100), // Level 1, D-Pad
	new line(70, 120, 100, 120), // Level 1, D-Pad
	new line(100, 70, 120, 70), // Level 1, D-Pad
	new line(70, 100, 70, 120), // Level 1, D-Pad
	new line(100, 120, 100, 150), // Level 1, D-Pad
	new line(120, 100, 150, 100), // Level 1, D-Pad
	new line(120, 120, 120, 150), // Level 1, D-Pad
	new line(120, 120, 150, 120), // Level 1, D-Pad
	new line(100, 150, 120, 150), // Level 1, D-Pad
	new line(150, 100, 150, 120), // Level 1, D-Pad
    new line(320, 225, 320 - sqrt(200), 225 + sqrt(200)), // Level 4, Arrow 1
    new line(320, 225, 320 - sqrt(200), 225), // Level 4, Arrow 1
    new line(320, 225, 320, 225 + sqrt(200)), // Level 4, Arrow 1
    new line(345, 150, 345 + sqrt(200), 150 + sqrt(200)), // Level 4, Arrow 2
    new line(345, 150, 345 + sqrt(200), 150), // Level 4, Arrow 2
    new line(345, 150, 345, 150 + sqrt(200)), // Level 4, Arrow 2
    new line(100, 100, 100 + sqrt(200), 100 + sqrt(200)), // Level 4, Arrow 3
    new line(100, 100, 100 + sqrt(200), 100), // Level 4, Arrow 3
    new line(100, 100, 100, 100 + sqrt(200)), // Level 4, Arrow 3
    new line(210, 18, 190, 18), // Level 4, Arrow 4
    new line(210, 18, 200, 8), // Level 4, Arrow 4
    new line(210, 18, 200, 28), // Level 4, Arrow 4
    new line(300, -20, 150, -20), // Level 4, Extended Arrow
    new line(160, -30, 150, -20), // Level 4, Extended Arrow
    new line(160, -10, 150, -20), // Level 4, Extended Arrow
    new line(150, -30, 140, -20), // Level 4, Extended Arrow
    new line(150, -10, 140, -20), // Level 4, Extended Arrow
    new line(140, -30, 130, -20), // Level 4, Extended Arrow
    new line(140, -10, 130, -20), // Level 4, Extended Arrow
    new line(255, 90, 275, 90), // Level 10, Arrow 1
    new line(265, 100, 275, 90), // Level 10, Arrow 1
    new line(265, 80, 275, 90), // Level 10, Arrow 1
    new line(355, 170, 355, 169), // Level 10, !
    new line(355, 155, 355, 165), // Level 10, !
    new line(535, 155, 555, 155), // Level 10, Arrow 2
    new line(545, 165, 555, 155), // Level 10, Arrow 2
    new line(545, 145, 555, 155), // Level 10, Arrow 2
    new line(730, 100, 730 + sqrt(200), 100 + sqrt(200)), // Level 10, Arrow 3
    new line(730, 100, 730 + sqrt(200), 100), // Level 10, Arrow 3
    new line(730, 100, 730, 100 + sqrt(200)), // Level 10, Arrow 3
    new line(550, 70, 550, 67), // Level 10, ?
    new line(550, 60, 560, 40), // Level 10, ?
    new line(550, 30, 560, 40), // Level 10, ?
    new line(550, 30, 540, 40), // Level 10, ?
    new line(540, 45, 540, 40), // Level 10, ?
    new line(35, 25, 35, 45), // Level 2, Arrow 1
    new line(25, 35, 35, 25), // Level 2, Arrow 1
    new line(45, 35, 35, 25), // Level 2, Arrow 1
    new line(50, -70, 50 - sqrt(200), sqrt(200) - 70), // Level 2, Arrow 2
    new line(50, -70, 50 - sqrt(200), -70), // Level 2, Arrow 2
    new line(50, -70, 50, sqrt(200) - 70), // Level 2, Arrow 2
    new line(140, 155, 160, 155), // Level 8, Arrow 1
    new line(150, 165, 160, 155), // Level 8, Arrow 1
    new line(150, 145, 160, 155), // Level 8, Arrow 1
    new line(190, 5, 210, 5), // Level 8, Arrow 2
    new line(200, 15, 210, 5), // Level 8, Arrow 2
    new line(200, -5, 210, 5), // Level 8, Arrow 2
    new line(63, 116, 63 - sqrt(50), 126 - sqrt(50)), // Level 8, Player
    new line(63, 116, 63 + sqrt(50), 126 - sqrt(50)), // Level 8, Player
    new line(53, 126, 63 - sqrt(50), 126 - sqrt(50)), // Level 8, Player
    new line(73, 126, 63 + sqrt(50), 126 - sqrt(50)), // Level 8, Player
    new line(63, 136, 63 - sqrt(50), 126 + sqrt(50)), // Level 8, Player
    new line(63, 136, 63 + sqrt(50), 126 + sqrt(50)), // Level 8, Player
    new line(53, 126, 63 - sqrt(50), 126 + sqrt(50)), // Level 8, Player
    new line(73, 126, 63 + sqrt(50), 126 + sqrt(50)), // Level 8, Player
    new line(70, 126, 68, 126), // Level 8, Player
    new line(69, 125, 69, 127), // Level 8, Player
    new line(290, 139, 290 - sqrt(200), 139 + sqrt(200)), // Level 3, Arrow 2
    new line(290, 139, 290 - sqrt(200), 139), // Level 3, Arrow 2
    new line(290, 139, 290, 139 + sqrt(200)), // Level 3, Arrow 2
    new line(110 + sqrt(200), 139 + sqrt(200), 110, 139), // Level 3, Arrow 1
    new line(110 + sqrt(200), 139 + sqrt(200), 110, 139 + sqrt(200)), // Level 3, Arrow 1
    new line(110 + sqrt(200), 139 + sqrt(200), 110 + sqrt(200), 139), // Level 3, Arrow 1
    new line(45, 75, 65, 75), // Level 9, Out 1
    new line(65, 75, 55, 65), // Level 9, Out 1
    new line(65, 75, 55, 85), // Level 9, Out 1
    new line(5, -5, -15, -5), // Level 9, Out 2
    new line(-15, -5, -5, 5), // Level 9, Out 2
    new line(-15, -5, -5, -15), // Level 9, Out 2
    new line(45, -125, 65, -125), // Level 9, Out 3
    new line(65, -125, 55, -115), // Level 9, Out 3
    new line(65, -125, 55, -135), // Level 9, Out 3
};

int bgStart[] = {
	0,
	72,
	94,
	37,
	0,
	0,
	0,
	78,
	100,
	56
};

int bgEnd[] = {
	37,
	78,
	100,
	56,
	0,
	0,
	0,
	94,
	109,
	72
};
