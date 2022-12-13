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
    new line(0, -300, 0, 170), // Level 2
    new line(0, 170, 80, 180), // Level 2
    new line(50, 130, 100, 120), // Level 2
    new line(100, -300, 100, 120), // Level 2
    new line(30, 80, 70, 80), // Level 2
    new line(70, 40, 100, 30), // Level 2
    new line(60, 0, 0, -60), // Level 2
    new line(100, -100, 80, -80), // Level 2
    new line(0, -160, 30, -130), // Level 2
  }
};

line[][] koList = {
  {
    new line(0, 100, 20, 80), // Level 2
    new line(0, 60, 20, 80), // Level 2
  }
};

line[][] bgList = {
  {
    new line(35, 25, 35, 45), // Level 2, Arrow 1
    new line(25, 35, 35, 25), // Level 2, Arrow 1
    new line(45, 35, 35, 25), // Level 2, Arrow 1
    new line(50, -70, 50 - sqrt(200), sqrt(200) - 70), // Level 2, Arrow 2
    new line(50, -70, 50 - sqrt(200), -70), // Level 2, Arrow 2
    new line(50, -70, 50, sqrt(200) - 70), // Level 2, Arrow 2
  }
};

line[][] fakeList = {
  {
  }
};

float[][] bounds = {
  {
    0,
    -200,
    100,
    200
  }
};

float[][] startPos = {
  {
    50,
    166.2
  }
};

float[][] endPos = {
  {
    50,
    -180
  }
};
