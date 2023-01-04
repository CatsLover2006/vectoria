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
    new line(0, 0, 0, 200), // Level 5
    new line(0, 0, 220, 0), // Level 5
    new line(225, -1, 220, 0), // Level 5
    new line(40, 60, 0, 60), // Level 5
    new line(125, 250, 0, 200), // Level 5
    new line(70, 195, 160 - (360.0f / 13), 60), // Level 5
    new line(185, 180, 185, 240), // Level 5
    new line(170, 185, 200, 175), // Level 5
    new line(315, 130, 315, 240), // Level 5
    new line(300, 135, 330, 125), // Level 5
  }
};

line[][] lineListLift = {
  {
    new line(179, 74, 165, 0), // Level 5
    new line(182, 77, 175, 0), // Level 5
    new line(185, 80, 185, 0), // Level 5
    new line(188, 77, 195, 0), // Level 5
    new line(191, 74, 205, 0), // Level 5
  }
};

line[][] koList = {
  {
    new line(100, 0, 85, 97.5), // Level 5
    new line(55, 140, 70, 195), // Level 5
    new line(55, 140, 85, 97.5), // Level 5
 }
};

line[][] bgList = {
  {
  }
};

line[][] fakeList = {
  {
  }
};

float[][] bounds = {
  {
    0,
    0,
    400,
    240
  }
};

float[][] startPos = {
  {
    20,
    50
  }
};

float[][] endPos = {
  {
    72,
    150
  }
};
