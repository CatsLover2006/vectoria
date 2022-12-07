public class line {
  float startX, endX, startY, endY;

  line (float x1, float y1, float x2, float y2) {
    startX = x1;
    endX = x2;
    startY = y1;
    endY = y2;
  }
};

line[][] lineList = {
  {
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
  }
};

line[][] koList = {
  {
    new line(450, 0, 450, 160), // Level 3
  }
};

line[][] bgList = {
  {
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
  }
};

line[][] fakeList = {
  {
    new line(0, 220, 30, 190), // Level 3
    new line(0, 180, 30, 210), // Level 3
    new line(10, 210, 10, 190), // Level 3
    new line(330, 120, 380, 120), // Level 3
    new line(330, 120, 355, 240), // Level 3
    new line(380, 120, 355, 240), // Level 3
    new line(600, 100, 500, 100), // Level 3
    new line(500, 50, 500, 0), // Level 3
  }
};

float[][] bounds = {
  {
    0,
    0,
    800,
    240
  }
};

float[][] startPos = {
  {
    20,
    220
  }
};

float[][] endPos = {
  {
    475,
    60
  }
};
