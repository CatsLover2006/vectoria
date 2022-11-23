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
    new line(0, 200, 160, 180),
    new line(160, 180, 250, 80),
    new line(0, 80, 100, 200),
    new line(250, 100, 100, 200),
    new line(250, 52, 350, 50),
    new line(0, 200, 0, 0),
    new line(350, 50, 350, 0),
    new line(350, 0, 0, 0)
  }
};

float[][] bounds = {
  {
    0,
    0,
    400,
    300
  }
};

float[][] startPos = {
  {
    50,
    124.3
  }
};
