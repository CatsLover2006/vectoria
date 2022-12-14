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
    new line(0, -40, 0, 170), // Level 8
    new line(400, 0, 400, 170), // Level 8
    new line(0, 170, 60, 180), // Level 8
    new line(300, 140, 0, 110), // Level 8
    new line(400, 170, 340, 180), // Level 8
    new line(400, 0, 0, -40), // Level 8
    new line(50, 70, 100, 20), // Level 8
    new line(0, 10, 10, 20), // Level 8
  }
};

line[][] koList = {
  {
    new line(400, 50, 75, 17.5), // Level 8
  }
};

line[][] bgList = {
  {
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
  }
};

line[][] fakeList = {
  {
  }
};

float[][] bounds = {
  {
    0,
    -40,
    400,
    200
  }
};

float[][] startPos = {
  {
    30,
    164.85
  }
};

float[][] endPos = {
  {
    390,
    24
  }
};
