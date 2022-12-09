class line {
	public:
		float startX, endX, startY, endY;
	  
		line (float x1, float y1, float x2, float y2) {
			startX = x1;
			endX = x2;
			startY = y1;
			endY = y2;
		}
};

const line* linelist[] = {
	new line(160, 180, 240, 110), // Level 1
	new line(0, 200, 160, 180), // Level 1
	new line(0, 150, 100, 200), // Level 1
	new line(260, 120, 100, 200), // Level 1
	new line(300, 52, 400, 50), // Level 1
	new line(0, 200, 0, 0), // Level 1
	new line(400, 50, 400, 0), // Level 1
	new line(400, 0, 0, 0), // Level 1
	new line(280, 95, 240, 110), // Level 1
	new line(270, 110, 280, 95), // Level 1
	new line(270, 110, 260, 120), // Level 1
	new line(0, 250, 100, 270), // Level 2
    new line(200, 250, 300, 270), // Level 2
    new line(400, 200, 350, 220), // Level 2
    new line(400, 155, 375, 165), // Level 2
    new line(330, 145, 270, 145), // Level 2
    new line(0, -100, 0, 250), // Level 2
    new line(400, -100, 400, 260), // Level 2
    new line(0, -100, 400, -100), // Level 2
    new line(130, 145, 70, 145), // Level 2
    new line(0, 90, 70, 100), // Level 2
    new line(130, 55, 70, 65), // Level 2
    new line(330, 55, 270, 55), // Level 2
    new line(330, 55, 400, 0), // Level 2
    new line(330, -20, 270, -20), // Level 2
    new line(0, 0, 0, 220), // Level 3
    new line(0, 0, 800, 0), // Level 3
    new line(800, 0, 800, 180), // Level 3
    new line(0, 220, 20, 240), // Level 3
    new line(10, 230, 40, 230), // Level 3
    new line(30, 230, 20, 240), // Level 3
    new line(40, 180, 30, 190), // Level 3
    new line(30, 210, 30, 190), // Level 3
    new line(40, 180, 80, 170), // Level 3
    new line(40, 230, 80, 170), // Level 3
    new line(30, 210, 80, 170), // Level 3
    new line(30, 210, 40, 230), // Level 3
    new line(150, 120, 200, 120), // Level 3
    new line(150, 120, 175, 240), // Level 3
    new line(200, 120, 175, 240), // Level 3
    new line(355 - (25/120.0f)*50, 190, 355 + (25/120.0f)*50, 190), // Level 3
    new line(420, 235, 480, 235), // Level 3
    new line(610, 220, 700, 200), // Level 3
    new line(740, 160, 800, 180), // Level 3
    new line(660, 80, 700, 120), // Level 3
    new line(660, 80, 650, 80), // Level 3
    new line(600, 50, 500, 50), // Level 3
};

const line* linelistKO[] = {
	new line(320, 180, 350, 150), // Level 1, X
	new line(350, 180, 320, 150), // Level 1, X
	new line(335, 200, 335, 220), // Level 1, Death Arrow 1
	new line(325, 210, 335, 220), // Level 1, Death Arrow 1
	new line(345, 210, 335, 220), // Level 1, Death Arrow 1
	new line(225 + sqrt(200), 220 - sqrt(200), 225, 220), // Level 1, Death Arrow 2
	new line(225, 220, 225, 220 - sqrt(200)), // Level 1, Death Arrow 2
	new line(225 + sqrt(200), 220, 225, 220), // Level 1, Death Arrow 2
	new line(275, 220, 275 + sqrt(200), 220 - sqrt(200)), // Level 1, Death Arrow 3
	new line(275 + sqrt(200), 220, 275, 220), // Level 1, Death Arrow 3
	new line(275, 220 - sqrt(200), 275, 220), // Level 1, Death Arrow 3
	new line(100, 280, 200, 260), // Level 2
    new line(300, 280, 400, 260), // Level 2
    new line(300, 200, 300, 150), // Level 2
    new line(300, 155, 130, 155), // Level 2
    new line(270, 65, 130, 65), // Level 2
    new line(450, 0, 450, 160), // Level 3
};

const line* linelistBG[] = {
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
    new line(320, 225, 320 - sqrt(200), 225 + sqrt(200)), // Level 2, Arrow 1
    new line(320, 225, 320 - sqrt(200), 225), // Level 2, Arrow 1
    new line(320, 225, 320, 225 + sqrt(200)), // Level 2, Arrow 1
    new line(345, 150, 345 + sqrt(200), 150 + sqrt(200)), // Level 2, Arrow 2
    new line(345, 150, 345 + sqrt(200), 150), // Level 2, Arrow 2
    new line(345, 150, 345, 150 + sqrt(200)), // Level 2, Arrow 2
    new line(100, 100, 100 + sqrt(200), 100 + sqrt(200)), // Level 2, Arrow 3
    new line(100, 100, 100 + sqrt(200), 100), // Level 2, Arrow 3
    new line(100, 100, 100, 100 + sqrt(200)), // Level 2, Arrow 3
    new line(210, 18, 190, 18), // Level 2, Arrow 4
    new line(210, 18, 200, 8), // Level 2, Arrow 4
    new line(210, 18, 200, 28), // Level 2, Arrow 4
    new line(300, -20, 150, -20), // Level 2, Extended Arrow
    new line(160, -30, 150, -20), // Level 2, Extended Arrow
    new line(160, -10, 150, -20), // Level 2, Extended Arrow
    new line(150, -30, 140, -20), // Level 2, Extended Arrow
    new line(150, -10, 140, -20), // Level 2, Extended Arrow
    new line(140, -30, 130, -20), // Level 2, Extended Arrow
    new line(140, -10, 130, -20), // Level 2, Extended Arrow
    new line(255, 90, 275, 90), // Level 3, Arrow 1
    new line(265, 100, 275, 90), // Level 3, Arrow 1
    new line(265, 80, 275, 90), // Level 3, Arrow 1
    new line(355, 170, 355, 169), // Level 3, !
    new line(355, 155, 355, 165), // Level 3, !
    new line(535, 155, 555, 155), // Level 3, Arrow 2
    new line(545, 165, 555, 155), // Level 3, Arrow 2
    new line(545, 145, 555, 155), // Level 3, Arrow 2
    new line(730, 100, 730 + sqrt(200), 100 + sqrt(200)), // Level 3, Arrow 3
    new line(730, 100, 730 + sqrt(200), 100), // Level 3, Arrow 3
    new line(730, 100, 730, 100 + sqrt(200)), // Level 3, Arrow 3
    new line(550, 70, 550, 67), // Level 3, ?
    new line(550, 60, 560, 40), // Level 3, ?
    new line(550, 30, 560, 40), // Level 3, ?
    new line(550, 30, 540, 40), // Level 3, ?
    new line(540, 45, 540, 40), // Level 3, ?
};

const line* lineListFake[] = {
    new line(0, 220, 30, 190), // Level 3
    new line(0, 180, 30, 210), // Level 3
    new line(10, 210, 10, 190), // Level 3
    new line(330, 120, 380, 120), // Level 3
    new line(330, 120, 355, 240), // Level 3
    new line(380, 120, 355, 240), // Level 3
    new line(600, 100, 500, 100), // Level 3
    new line(500, 50, 500, 0), // Level 3
};

const int levelStart[] = {
	0,
	11,
	25
};

const int levelEnd[] = {
	11,
	25,
	47
};

const int koStart[] = {
	0,
	11,
	16
};

const int koEnd[] = {
	11,
	16,
	17
};

const int bgStart[] = {
	0,
	37,
	56
};

const int bgEnd[] = {
	37,
	56,
	72
};

const int falseStart[] = {
	0,
	0,
	0
};

const int falseEnd[] = {
	0,
	0,
	8
};


const float bounds[][4] = {
	{
		0,
		0,
		400,
		240
	},
	{
		0,
		-100,
		400,
		300
	},
	{
    	0,
    	0,
    	800,
    	240
  	}
};

const float startPos[][2] = {
	{
		50,
		163.8
	},
	{
		50,
		249.8
	},
	{
    	20,
    	220
  	}
};

const float endPoint[][2] = {
	{
		375,
		25
	},
	{
		115,
		-20
	},
	{
    	475,
    	60
  	}
};

const int levels = 3;
