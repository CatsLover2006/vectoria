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
	new line(0, 250, 100, 270), // Level 4
    new line(200, 250, 300, 270), // Level 4
    new line(400, 200, 350, 220), // Level 4
    new line(400, 155, 375, 165), // Level 4
    new line(330, 145, 270, 145), // Level 4
    new line(0, -100, 0, 250), // Level 4
    new line(400, -100, 400, 260), // Level 4
    new line(0, -100, 400, -100), // Level 4
    new line(130, 145, 70, 145), // Level 4
    new line(0, 90, 70, 100), // Level 4
    new line(130, 55, 70, 65), // Level 4
    new line(330, 55, 270, 55), // Level 4
    new line(330, 55, 400, 0), // Level 4
    new line(330, -20, 270, -20), // Level 4
    new line(0, 0, 0, 220), // Level 10
    new line(0, 0, 800, 0), // Level 10
    new line(800, 0, 800, 180), // Level 10
    new line(0, 220, 20, 240), // Level 10
    new line(10, 230, 40, 230), // Level 10
    new line(30, 230, 20, 240), // Level 10
    new line(40, 180, 30, 190), // Level 10
    new line(30, 210, 30, 190), // Level 10
    new line(40, 180, 80, 170), // Level 10
    new line(40, 230, 80, 170), // Level 10
    new line(30, 210, 80, 170), // Level 10
    new line(30, 210, 40, 230), // Level 10
    new line(150, 120, 200, 120), // Level 10
    new line(150, 120, 175, 240), // Level 10
    new line(200, 120, 175, 240), // Level 10
    new line(355 - (25/120.0f)*50, 190, 355 + (25/120.0f)*50, 190), // Level 10
    new line(420, 235, 480, 235), // Level 10
    new line(610, 220, 700, 200), // Level 10
    new line(740, 160, 800, 180), // Level 10
    new line(660, 80, 700, 120), // Level 10
    new line(660, 80, 650, 80), // Level 10
    new line(600, 50, 500, 50), // Level 10
    new line(0, -300, 0, 170), // Level 2
    new line(0, 170, 80, 180), // Level 2
    new line(50, 130, 100, 120), // Level 2
    new line(100, -300, 100, 120), // Level 2
    new line(30, 80, 70, 80), // Level 2
    new line(70, 40, 100, 30), // Level 2
    new line(60, 0, 0, -60), // Level 2
    new line(100, -100, 80, -80), // Level 2
    new line(0, -160, 30, -130), // Level 2
    new line(0, -40, 0, 170), // Level 8
    new line(400, 0, 400, 170), // Level 8
    new line(0, 170, 60, 180), // Level 8
    new line(300, 140, 0, 110), // Level 8
    new line(400, 170, 340, 180), // Level 8
    new line(400, 0, 0, -40), // Level 8
    new line(50, 70, 100, 20), // Level 8
    new line(0, 10, 10, 20), // Level 8
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
	new line(100, 280, 200, 260), // Level 4
    new line(300, 280, 400, 260), // Level 4
    new line(300, 200, 300, 150), // Level 4
    new line(300, 155, 130, 155), // Level 4
    new line(270, 65, 130, 65), // Level 4
    new line(450, 0, 450, 160), // Level 10
    new line(0, 100, 20, 80), // Level 2
    new line(0, 60, 20, 80), // Level 2
    new line(400, 50, 75, 17.5), // Level 8
};

const line* lineListFake[] = {
    new line(0, 220, 30, 190), // Level 10
    new line(0, 180, 30, 210), // Level 10
    new line(10, 210, 10, 190), // Level 10
    new line(330, 120, 380, 120), // Level 10
    new line(330, 120, 355, 240), // Level 10
    new line(380, 120, 355, 240), // Level 10
    new line(600, 100, 500, 100), // Level 10
    new line(500, 50, 500, 0), // Level 10
};

const int levelStart[] = {
	0,
	47,
	0,
	11,
	0,
	0,
	0,
	56,
	0,
	25
};

const int levelEnd[] = {
	11,
	56,
	0,
	25,
	0,
	0,
	0,
	64,
	0,
	47
};

const int koStart[] = {
	0,
	17,
	0,
	11,
	0,
	0,
	0,
	19,
	0,
	16
};

const int koEnd[] = {
	11,
	19,
	0,
	16,
	0,
	0,
	0,
	20,
	0,
	17
};

const int falseStart[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0
};

const int falseEnd[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
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
    	-200,
    	100,
    	200
  	},
	{
		0,
		-100,
		400,
		300
	},
	{
		0,
		-100,
		400,
		300
	},
	{
		0,
		-100,
		400,
		300
	},
	{
		0,
		-100,
		400,
		300
	},
	{
		0,
		-100,
		400,
		300
	},
	{
	    0,
	    -40,
	    400,
	    200
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
		166.2
	},
	{
		50,
		249.8
	},
	{
		50,
		249.8
	},
	{
		50,
		249.8
	},
	{
		50,
		249.8
	},
	{
		50,
		249.8
	},
	{
	    30,
	    164.85
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
		50,
    	-180
	},
	{
		50,
		249.8
	},
	{
		115,
		-20
	},
	{
		50,
		249.8
	},
	{
		50,
		249.8
	},
	{
		50,
		249.8
	},
	{
    	390,
    	24
  	},
	{
		50,
		249.8
	},
	{
    	475,
    	60
  	}
};

const int levels = 10;
