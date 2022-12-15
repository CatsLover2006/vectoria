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
    new line(0, 0, 0, 60), // Level 3
    new line(0, 0, 400, 0), // Level 3
    new line(40, 60, 0, 60), // Level 3
    new line(400, 0, 400, 60), // Level 3
    new line(360, 60, 400, 60), // Level 3
    new line(200 - (160 * sin(5 * PI / 12)), 60 + (160 * cos(5 * PI / 12)), 40, 60), // Level 3
    new line(200 - (160 * sin(5 * PI / 12)), 60 + (160 * cos(5 * PI / 12)),
             200 - (160 * sin(4 * PI / 12)), 60 + (160 * cos(4 * PI / 12))), // Level 3
    new line(200 - (160 * sin(3 * PI / 12)), 60 + (160 * cos(3 * PI / 12)),
             200 - (160 * sin(4 * PI / 12)), 60 + (160 * cos(4 * PI / 12))), // Level 3
    new line(200 - (160 * sin(3 * PI / 12)), 60 + (160 * cos(3 * PI / 12)),
             200 - (160 * sin(2 * PI / 12)), 60 + (160 * cos(2 * PI / 12))), // Level 3
    new line(200 - (160 * sin(2 * PI / 12)), 60 + (160 * cos(2 * PI / 12)),
             200 - (160 * sin(PI / 12)), 60 + (160 * cos(PI / 12))), // Level 3
    new line(200, 220, 200 - (160 * sin(PI / 12)), 60 + (160 * cos(PI / 12))), // Level 3
    new line(200 + (160 * sin(5 * PI / 12)), 60 + (160 * cos(5 * PI / 12)), 360, 60), // Level 3
    new line(200 + (160 * sin(5 * PI / 12)), 60 + (160 * cos(5 * PI / 12)),
             200 + (160 * sin(4 * PI / 12)), 60 + (160 * cos(4 * PI / 12))), // Level 3
    new line(200 + (160 * sin(3 * PI / 12)), 60 + (160 * cos(3 * PI / 12)),
             200 + (160 * sin(4 * PI / 12)), 60 + (160 * cos(4 * PI / 12))), // Level 3
    new line(200 + (160 * sin(3 * PI / 12)), 60 + (160 * cos(3 * PI / 12)),
             200 + (160 * sin(2 * PI / 12)), 60 + (160 * cos(2 * PI / 12))), // Level 3
    new line(200 + (160 * sin(2 * PI / 12)), 60 + (160 * cos(2 * PI / 12)),
             200 + (160 * sin(PI / 12)), 60 + (160 * cos(PI / 12))), // Level 3
    new line(200, 220, 200 + (160 * sin(PI / 12)), 60 + (160 * cos(PI / 12))), // Level 3
    new line(200 + (80 * sin(4 * PI / 12)), 60 + 80 * cos(4 * PI / 12), 305, 110), // Level 3
  }
};

line[][] koList = {
  {
    new line(200 - (80 * sin(5 * PI / 12)), 60 + 80 * cos(5 * PI / 12), 120, 60), // Level 3
    new line(200 - (80 * sin(5 * PI / 12)), 60 + 80 * cos(5 * PI / 12),
             200 - (80 * sin(4 * PI / 12)), 60 + 80 * cos(4 * PI / 12)), // Level 3
    new line(200 - (80 * sin(3 * PI / 12)), 60 + 80 * cos(3 * PI / 12),
             200 - (80 * sin(4 * PI / 12)), 60 + 80 * cos(4 * PI / 12)), // Level 3
    new line(200 - (80 * sin(3 * PI / 12)), 60 + 80 * cos(3 * PI / 12),
             200 - (80 * sin(2 * PI / 12)), 60 + 80 * cos(2 * PI / 12)), // Level 3
    new line(200 - (80 * sin(2 * PI / 12)), 60 + 80 * cos(2 * PI / 12),
             200 - (80 * sin(PI / 12)), 60 + 80 * cos(PI / 12)), // Level 3
    new line(200, 140, 200 - (80 * sin(PI / 12)), 60 + 80 * cos(PI / 12)), // Level 3
    new line(200 + (80 * sin(5 * PI / 12)), 60 + 80 * cos(5 * PI / 12), 280, 60), // Level 3
    new line(200 + (80 * sin(5 * PI / 12)), 60 + 80 * cos(5 * PI / 12),
             200 + (80 * sin(4 * PI / 12)), 60 + 80 * cos(4 * PI / 12)), // Level 3
    new line(200 + (80 * sin(3 * PI / 12)), 60 + 80 * cos(3 * PI / 12),
             200 + (80 * sin(4 * PI / 12)), 60 + 80 * cos(4 * PI / 12)), // Level 3
    new line(200 + (80 * sin(3 * PI / 12)), 60 + 80 * cos(3 * PI / 12),
             200 + (80 * sin(2 * PI / 12)), 60 + 80 * cos(2 * PI / 12)), // Level 3
    new line(200 + (80 * sin(2 * PI / 12)), 60 + 80 * cos(2 * PI / 12),
             200 + (80 * sin(PI / 12)), 60 + 80 * cos(PI / 12)), // Level 3
    new line(200, 140, 200 + (80 * sin(PI / 12)), 60 + 80 * cos(PI / 12)), // Level 3
    new line(200 - (80 * sin(5 * PI / 12)), 60 - 80 * cos(5 * PI / 12), 120, 60), // Level 3
    new line(200 - (80 * sin(5 * PI / 12)), 60 - 80 * cos(5 * PI / 12),
             200 - (80 * sin(4 * PI / 12)), 60 - 80 * cos(4 * PI / 12)), // Level 3
    new line(200 - (80 * sin(3 * PI / 12)), 60 - 80 * cos(3 * PI / 12),
             200 - (80 * sin(4 * PI / 12)), 60 - 80 * cos(4 * PI / 12)), // Level 3
    new line(200 - (80 * sin(3 * PI / 12)), 60 - 80 * cos(3 * PI / 12),
             200 - (80 * sin(2 * PI / 12)), 60 - 80 * cos(2 * PI / 12)), // Level 3
    new line(200 + (80 * sin(5 * PI / 12)), 60 - 80 * cos(5 * PI / 12), 280, 60), // Level 3
    new line(200 + (80 * sin(5 * PI / 12)), 60 - 80 * cos(5 * PI / 12),
             200 + (80 * sin(4 * PI / 12)), 60 - 80 * cos(4 * PI / 12)), // Level 3
    new line(200 + (80 * sin(3 * PI / 12)), 60 - 80 * cos(3 * PI / 12),
             200 + (80 * sin(4 * PI / 12)), 60 - 80 * cos(4 * PI / 12)), // Level 3
    new line(200 + (80 * sin(3 * PI / 12)), 60 - 80 * cos(3 * PI / 12),
             200 + (80 * sin(2 * PI / 12)), 60 - 80 * cos(2 * PI / 12)), // Level 3
  }
};

line[][] bgList = {
  {
    new line(290, 139, 290 - sqrt(200), 139 + sqrt(200)), // Level 3, Arrow 2
    new line(290, 139, 290 - sqrt(200), 139), // Level 3, Arrow 2
    new line(290, 139, 290, 139 + sqrt(200)), // Level 3, Arrow 2
    new line(110 + sqrt(200), 139 + sqrt(200), 110, 139), // Level 3, Arrow 1
    new line(110 + sqrt(200), 139 + sqrt(200), 110, 139 + sqrt(200)), // Level 3, Arrow 1
    new line(110 + sqrt(200), 139 + sqrt(200), 110 + sqrt(200), 139), // Level 3, Arrow 1
  }
};

line[][] fakeList = {
  {
    new line(200, 60, 200 + (80 * sin(PI / 12)), 60 + (80 * cos(PI / 12))), // Level 3
    new line(200, 60, 200 + (80 * sin(4 * PI / 12)), 60 + (80 * cos(4 * PI / 12))), // Level 3
    new line(200, 60, 200 + (80 * sin(7 * PI / 12)), 60 + (80 * cos(7 * PI / 12))), // Level 3
    new line(200, 60, 200 + (80 * sin(10 * PI / 12)), 60 + (80 * cos(10 * PI / 12))), // Level 3
    new line(200, 60, 200 + (80 * sin(13 * PI / 12)), 60 + (80 * cos(13 * PI / 12))), // Level 3
    new line(200, 60, 200 + (80 * sin(16 * PI / 12)), 60 + (80 * cos(16 * PI / 12))), // Level 3
    new line(200, 60, 200 + (80 * sin(19 * PI / 12)), 60 + (80 * cos(19 * PI / 12))), // Level 3
    new line(200, 60, 200 + (80 * sin(22 * PI / 12)), 60 + (80 * cos(22 * PI / 12))), // Level 3
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
    380,
    30
  }
};
