int level = 0,
  jumpableFor = 0,
  SUBSTEPS = 6;
float playerY = 50,
  playerX = 50,
  oX = playerX,
  oY = playerY,
  playerYVel = 0,
  playerXVel = 0,
  scaleFactor = 2.4f,
  rot = 0,
  rotSpd = 0,
  cX = playerX,
  cY = playerY,
  xDiv = 1 + (sqrt(6)-1)/SUBSTEPS,
  xAdd = 2.69/sqrt(SUBSTEPS*sqrt(SUBSTEPS)-pow(SUBSTEPS, xDiv)/(xDiv*sqrt(SUBSTEPS/3))),
  doLogic = 0;

float abs_c (float x) {
  if (x < 0) return -x;
  return x;
}

boolean pressed[] = new boolean[4];
boolean vcolCheck = false,
  hcolCheck = false,
  hasStarted = false,
  tcolCheck = false,
  invertGrav = false;

void settings() {
  size(960, 544, P2D);
  pixelDensity(displayDensity());
  scaleFactor = max(height/240.0f, width/400.0f);
  smooth(4); 
}//*/

void setup() {
  noStroke();
  frameRate(60);
  println(lineList[level].length);
  println(koList[level].length);
  println(lineListLift[level].length);
  println(lineListTop[level].length);
  println(bgList[level].length);
  println(fakeList[level].length);
}//*/

void draw() {
  if (!hasStarted) {
    playerX = startPos[level][0];
    playerY = startPos[level][1];
    playerYVel = 0;
    playerXVel = 0;
    oX = playerX;
    oY = playerY;
    cX = constrain(playerX, (width/scaleFactor)/2 + bounds[level][0], bounds[level][2] - (width/scaleFactor)/2);
    cY = constrain(playerY, (height/scaleFactor)/2 + bounds[level][1], bounds[level][3] - (height/scaleFactor)/2);
    hasStarted = true;
    return;
  }
  pushMatrix();
  scale(scaleFactor);
  background(255);
  doLogic += 1 / frameRate;
  while (doLogic > 1 / (SUBSTEPS * 60.0f)) {
    oX = playerX;
    oY = playerY;
    invertGrav = false;
    for (int i = 0; i < lineListLift[level].length; i++) {
      invertGrav = lineCircle(lineListLift[level][i].startX, lineListLift[level][i].startY, lineListLift[level][i].endX, lineListLift[level][i].endY, playerX, playerY, 10);
      if (invertGrav) break;
    }
    if (!vcolCheck || jumpableFor == 0 || invertGrav) {
      playerYVel += (invertGrav?-0.3:0.3) / SUBSTEPS;
      if (pressed[2]) playerYVel += 0.9 / SUBSTEPS;
    }
    if (playerYVel > 59) playerYVel = 59;
    if (playerYVel < -(59/8)) playerYVel = -(59/8);
    playerXVel = playerXVel / xDiv;
    if (pressed[0]) playerXVel -= xAdd;
    if (pressed[3]) playerXVel += xAdd;
    playerX += playerXVel / SUBSTEPS;
    hcolCheck = false;
    if (vcolCheck) playerY -= abs_c(playerXVel / SUBSTEPS);
    for (int i = 0; i < lineList[level].length; i++) {
      if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
        hcolCheck=true;
        if (playerX == closestX) continue;
        else playerX = closestX + (closestX < playerX ? 10 : -10) * abs_c(cos(atan((playerY - closestY)/(playerX - closestX))));
      }
    }
    if (vcolCheck) playerY += abs_c(playerXVel / SUBSTEPS);
    tcolCheck = vcolCheck;
    vcolCheck = false;
    playerY += playerYVel / SUBSTEPS;
    for (int i = 0; i < lineList[level].length; i++) {
      if (abs_c((lineList[level][i].startY-lineList[level][i].endY)/(lineList[level][i].startX-lineList[level][i].endX))>2) continue;
      if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
        vcolCheck = vcolCheck || (closestX == playerX) || abs_c((closestY - playerY) / (closestX - playerX))>0.5;
        if (!vcolCheck) continue;
        if (playerX == closestX) playerY = closestY + (closestY < playerY ? 10 : -10);
        else playerY = closestY + (closestY < playerY ? 10 : -10) * abs_c(sin(atan((playerY - closestY)/(playerX - closestX))));
        if (closestY > playerY) jumpableFor = 25;
      }
    }
    if (tcolCheck && !vcolCheck) {
      playerY += abs_c(playerXVel / SUBSTEPS) * 2;
      for (int i = 0; i < lineList[level].length; i++) {
        if (abs_c((lineList[level][i].startY-lineList[level][i].endY)/(lineList[level][i].startX-lineList[level][i].endX))>2) continue;
        if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
          vcolCheck = (closestX == playerX) || abs_c((closestY - playerY) / (closestX - playerX))>0.5;
          if (!vcolCheck) continue;
          if (playerX == closestX) playerY = closestY + (closestY < playerY ? 10 : -10);
          else playerY = closestY + (closestY < playerY ? 10 : -10) * abs_c(sin(atan((playerY - closestY)/(playerX - closestX))));
          if (closestY > playerY) jumpableFor = 25;
        }
      }
      if (!vcolCheck) {
        playerY -= abs_c(playerXVel / SUBSTEPS) * 2;
      }
    }
    if (jumpableFor > 0) rotSpd = ((playerX - oX) > 0 ? 0.1 : -0.1) * sqrt((playerX - oX) * (playerX - oX) + (playerY - oY) * (playerY - oY) * (jumpableFor > 0 ? 1 : 0));
    else rotSpd /= pow(1.1, 1/13.0);
    if (vcolCheck) {
      playerYVel = 0;
    } else if (jumpableFor > 0) jumpableFor--;
    if (jumpableFor > 0 && pressed[1]) {
      playerYVel = xAdd * sqrt(42.3) * (pressed[2]?-2:-1);
      playerY -= abs_c(playerXVel);
      jumpableFor = 0;
    }
    cX += constrain(playerX, (width/scaleFactor)/2 + bounds[level][0], bounds[level][2] - (width/scaleFactor)/2) * 0.06;
    cX /= 1.06;
    if ((width/scaleFactor)/2 + bounds[level][0] > bounds[level][2] - (width/scaleFactor)/2) cX = bounds[level][0] + bounds[level][2] / 2;
    cY += constrain(playerY, (height/scaleFactor)/2 + bounds[level][1], bounds[level][3] - (height/scaleFactor)/2) * 0.06;
    cY /= 1.06;
    rot += rotSpd;
    if (playerY > bounds[level][3]) { //rip
      hasStarted = false;
      doLogic = 0;
    }
    for (int i = 0; i < koList[level].length; i++)
      if (lineCircle(koList[level][i].startX, koList[level][i].startY, koList[level][i].endX, koList[level][i].endY, playerX, playerY, 10)) {
        hasStarted = false;
        doLogic = 0;
      }
    doLogic -= 1 / (SUBSTEPS * 60.0f);
  }
  strokeWeight(2);
  stroke(200);
  for (int i = 0; i < bgList[level].length; i++) {
    line((((width/scaleFactor)/2)-cX) + bgList[level][i].startX,
      (((height/scaleFactor)/2)-cY) + bgList[level][i].startY,
      (((width/scaleFactor)/2)-cX) + bgList[level][i].endX,
      (((height/scaleFactor)/2)-cY) + bgList[level][i].endY);
  }
  stroke(0, 0, 100);
  for (int i = 0; i < fakeList[level].length; i++) {
    line((((width/scaleFactor)/2)-cX) + fakeList[level][i].startX,
      (((height/scaleFactor)/2)-cY) + fakeList[level][i].startY,
      (((width/scaleFactor)/2)-cX) + fakeList[level][i].endX,
      (((height/scaleFactor)/2)-cY) + fakeList[level][i].endY);
  }
  stroke(0);
  for (int i = 0; i < lineList[level].length; i++) {
    line((((width/scaleFactor)/2)-cX) + lineList[level][i].startX,
      (((height/scaleFactor)/2)-cY) + lineList[level][i].startY,
      (((width/scaleFactor)/2)-cX) + lineList[level][i].endX,
      (((height/scaleFactor)/2)-cY) + lineList[level][i].endY);
  }
  stroke(0, 255, 0);
  for (int i = 0; i < lineListLift[level].length; i++) {
    line((((width/scaleFactor)/2)-cX) + lineListLift[level][i].startX,
      (((height/scaleFactor)/2)-cY) + lineListLift[level][i].startY,
      (((width/scaleFactor)/2)-cX) + lineListLift[level][i].endX,
      (((height/scaleFactor)/2)-cY) + lineListLift[level][i].endY);
  }
  stroke(255, 0, 0);
  for (int i = 0; i < koList[level].length; i++) {
    line((((width/scaleFactor)/2)-cX) + koList[level][i].startX,
      (((height/scaleFactor)/2)-cY) + koList[level][i].startY,
      (((width/scaleFactor)/2)-cX) + koList[level][i].endX,
      (((height/scaleFactor)/2)-cY) + koList[level][i].endY);
  }
  stroke(0);
  for (int i = 0; i < lineListTop[level].length; i++) {
    line((((width/scaleFactor)/2)-cX) + lineListTop[level][i].startX,
      (((height/scaleFactor)/2)-cY) + lineListTop[level][i].startY,
      (((width/scaleFactor)/2)-cX) + lineListTop[level][i].endX,
      (((height/scaleFactor)/2)-cY) + lineListTop[level][i].endY);
  }
  noStroke();
  fill(0);
  circle((((width/scaleFactor)/2)-cX) + endPos[level][0], (((height/scaleFactor)/2)-cY) + endPos[level][1], 6);
  circle((((width/scaleFactor)/2)-cX) + playerX, (((height/scaleFactor)/2)-cY) + playerY, 20);
  fill(0, 255, 255);
  circle((((width/scaleFactor)/2)-cX) + cos(rot) * 5 + playerX, (((height/scaleFactor)/2)-cY) + sin(rot) * 5 + playerY, 6);
  circle((((width/scaleFactor)/2)-cX) + endPos[level][0], (((height/scaleFactor)/2)-cY) + endPos[level][1], 4);
  popMatrix();
}

void keyPressed() {
  switch (key) {
  case 'a':
  case 'A':
    {
      pressed[0] = true;
      break;
    }
  case 'w':
  case 'W':
    {
      pressed[1] = true;
      break;
    }
  case 's':
  case 'S':
    {
      pressed[2] = true;
      break;
    }
  case 'd':
  case 'D':
    {
      pressed[3] = true;
      break;
    }
  case 'l':
  case 'L':
    {
      println(playerX + "," + playerY);
      break;
    }
  }
}
void keyReleased() {
  switch (key) {
  case 'a':
  case 'A':
    {
      pressed[0] = false;
      break;
    }
  case 'w':
  case 'W':
    {
      pressed[1] = false;
      break;
    }
  case 's':
  case 'S':
    {
      pressed[2] = false;
      break;
    }
  case 'd':
  case 'D':
    {
      pressed[3] = false;
      break;
    }
  }
}
