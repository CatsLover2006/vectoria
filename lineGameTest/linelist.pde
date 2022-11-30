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
    new line(0, 250, 100, 270), // Level 2
    new line(200, 250, 300, 270), // Level 2
    new line(400, 200, 350, 220), // Level 2
    new line(400, 155, 375, 165), // Level 2
    new line(330, 145, 270, 145), // Level 2
    new line(0, -100, 0, 250), // Level 2
    new line(400, -100, 400, 250), // Level 2
    new line(0, -100, 400, -100), // Level 2
    new line(130, 145, 70, 145), // Level 2
    new line(0, 90, 70, 100), // Level 2
    new line(130, 55, 70, 65), // Level 2
    new line(330, 55, 270, 55), // Level 2
    new line(330, 55, 400, 0), // Level 2
    new line(330, -20, 270, -20), // Level 2
  }
};

line[][] koList = {
 {
   new line(100, 280, 200, 260), // Level 2
   new line(300, 280, 400, 260), // Level 2
   new line(300, 200, 300, 150), // Level 2
   new line(270, 155, 130, 155), // Level 2
   new line(270, 65, 130, 65), // Level 2
 }
};

line[][] bgList = {
  {
    new line(100, 270, 200, 250), // Level 2
    new line(300, 270, 400, 250), // Level 2
    new line(300, 145, 300, 150), // Level 2
    new line(270, 145, 130, 145), // Level 2
    new line(270, 55, 130, 55), // Level 2
    new line(320, 225, 320 - sqrt(200), 225 + sqrt(200)), // Level 2, Arrow 1
    new line(320, 225, 320 - sqrt(200), 225), // Level 2, Arrow 1
    new line(320, 225, 320, 225 + sqrt(200)), // Level 2, Arrow 1
    new line(345, 150, 345 + sqrt(200), 150 + sqrt(200)), // Level 2, Arrow 2
    new line(345, 150, 345 + sqrt(200), 150), // Level 2, Arrow 2
    new line(345, 150, 345, 150 + sqrt(200)), // Level 2, Arrow 2
    new line(100, 100, 100 + sqrt(200), 100 + sqrt(200)), // Level 2, Arrow 3
    new line(100, 100, 100 + sqrt(200), 100), // Level 2, Arrow 3
    new line(100, 100, 100, 100 + sqrt(200)), // Level 2, Arrow 3
    new line(210, 17.5, 190, 17.5), // Level 2, Arrow 4
    new line(210, 17.5, 200, 7.5), // Level 2, Arrow 4
    new line(210, 17.5, 200, 27.5), // Level 2, Arrow 4
    new line(270, -20, 150, -20), // Level 2, Extended Arrow
  }
};

float[][] bounds = {
  {
    0,
    -100,
    400,
    300
  }
};

float[][] startPos = {
  {
    50,
    249.8
  }
};

float[][] endPos = {
  {
    115,
    -20
  }
};
