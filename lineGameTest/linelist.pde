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
    new line(15, 230, 35, 230), // Level 9
    new line(15, 230, -15, 240), // Level 9
    new line(35, 230, 65, 240), // Level 9
    new line(30, 100, 50, 40), // Level 9, Out 1
    new line(20, 20, 0, -40), // Level 9, Out 2
    new line(30, -100, 50, -160), // Level 9, Out 3
    new line(0, 200, 0, -205), // Level 9, Wall
    new line(50, 200, 50, -205), // Level 9, Wall
    new line(30, 100, 50, 40), // Level 9, Out 1
    new line(20, 20, 0, -40), // Level 9, Out 2
    new line(30, -100, 50, -160), // Level 9, Out 3
    new line(40, -300, 10, -300), // Level 9
    new line(70, -330, 50, -350), // Level 9
    new line(-20, -330, 0, -350), // Level 9
  }
};

line[][] lineListTop = {
  {
    new line(30, 100, 50, 40), // Level 9, Out 1
    new line(20, 20, 0, -40), // Level 9, Out 2
    new line(30, -100, 50, -160), // Level 9, Out 3
  }
};
line[][] lineListLift = {
  {
    new line(10, 190, 10, -300), // Level 9
    new line(20, 180, 20, -300), // Level 9
    new line(30, 180, 30, -300), // Level 9
    new line(40, 190, 40, -300), // Level 9
    new line(50, 200, 25, 175), // Level 9
    new line(0, 200, 25, 175), // Level 9
  }
};

line[][] koList = {
  {
    new line(10, -300, 25, -285), // Level 9
    new line(40, -300, 25, -285), // Level 9
 }
};

line[][] bgList = {
  {
    new line(45, 75, 65, 75), // Level 9, Out 1
    new line(65, 75, 55, 65), // Level 9, Out 1
    new line(65, 75, 55, 85), // Level 9, Out 1
    new line(5, -5, -15, -5), // Level 9, Out 2
    new line(-15, -5, -5, 5), // Level 9, Out 2
    new line(-15, -5, -5, -15), // Level 9, Out 2
    new line(45, -125, 65, -125), // Level 9, Out 3
    new line(65, -125, 55, -115), // Level 9, Out 3
    new line(65, -125, 55, -135), // Level 9, Out 3
  }
};

line[][] fakeList = {
  {
  }
};

float[][] bounds = {
  
  {
    0,
    -400,
    50,
    240
  },
};

float[][] startPos = {
  
  {
      25,
      220
    },
};

float[][] endPos = {
  {
    25,
    -350
  }
};
