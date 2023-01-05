
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
    new line(125, 240, 0, 200), // Level 5
    new line(70, 195, 160 - (360.0f / 13), 60), // Level 5
    new line(190, 180, 190, 240), // Level 5
    new line(170, 185, 210, 175), // Level 5
    new line(320, 130, 320, 240), // Level 5
    new line(300, 135, 340, 125), // Level 5
    new line(100, 0, 85, 97.5), // Level 5
    new line(50, 140, 70, 195), // Level 5
    new line(50, 140, 85, 97.5), // Level 5
  }
};

line[][] lineListTop = {
  {
  }
};
line[][] lineListLift = {
  {
    new line(166, 74, 180, 0), // Level 5
    new line(178, 77, 185, 0), // Level 5
    new line(190, 80, 190, 0), // Level 5
    new line(202, 77, 195, 0), // Level 5
    new line(214, 74, 200, 0), // Level 5
  }
};

line[][] koList = {
  {
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
  },
};

float[][] startPos = {
  
  {
      25,
      50
    },
};

float[][] endPos = {
  {
    25,
    -350
  }
};
