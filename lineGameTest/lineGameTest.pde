float playerX = 50,
  playerY = 50,
  oX = playerX,
  oY = playerY,
  playerYVel = 0,
  playerXVel = 0,
  scaleFactor = 2.4f,
  rot = 0,
  rotSpd = 0,
  cX = playerX,
  cY = playerY;

int level = 0;

boolean pressed[] = new boolean[4];
boolean vcolCheck = false,
  hcolCheck = false,
  hasStarted = false,
  tcolCheck = false;

void settings() {
  size(960, 544);
  scaleFactor = max(height/240.0f, width/400.0f);
  smooth(2);
  println(lineList[level].length);
  println(koList[level].length);
  println(bgList[level].length);
  println(fakeList[level].length);
}//*/

void setup() {
  noStroke();
  frameRate(60);
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
  }
  pushMatrix();
  scale(scaleFactor);
  background(255);
  oX = playerX;
  oY = playerY;
  playerYVel += 0.3;
  if (pressed[2]) playerYVel += 0.9;
  if (playerYVel > 59) playerYVel = 59;
  if (playerYVel < -59) playerYVel = -59;
  playerXVel = playerXVel / sqrt(5.2);
  if (pressed[0]) playerXVel -= 2.5;
  if (pressed[3]) playerXVel += 2.5;
  playerX += playerXVel;
  hcolCheck = false;
  if (vcolCheck) playerY -= abs(playerXVel);
  for (int i = 0; i < lineList[level].length; i++) {
    if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
      if (abs((closestY - playerY) / (closestX - playerX))>0.84) continue;
      hcolCheck=true;
      if (playerX == closestX) continue;
      else playerX = closestX + (closestX < playerX ? 10 : -10) * abs(cos(atan((playerY - closestY)/(playerX - closestX))));
    }
  }
  if (vcolCheck) playerY += abs(playerXVel);
  tcolCheck = vcolCheck;
  vcolCheck = false;
  if (hcolCheck) playerXVel = 0;
  playerY += playerYVel;
  for (int i = 0; i < lineList[level].length; i++) {
    if (abs((lineList[level][i].startY-lineList[level][i].endY)/(lineList[level][i].startX-lineList[level][i].endX))>3) continue;
    if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
      vcolCheck = vcolCheck || (closestX == playerX) || abs((closestY - playerY) / (closestX - playerX))>0.5;
      if (!vcolCheck) continue;
      if (playerX == closestX) playerY = closestY + (closestY < playerY ? 10 : -10);
      else playerY = closestY + (closestY < playerY ? 10 : -10) * abs(sin(atan((playerY - closestY)/(playerX - closestX))));
    }
  }
  if (tcolCheck && !vcolCheck) {
    playerY += abs(playerXVel);
    for (int i = 0; i < lineList[level].length; i++) {
      if (abs((lineList[level][i].startY-lineList[level][i].endY)/(lineList[level][i].startX-lineList[level][i].endX))>3) continue;
      if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
        vcolCheck = (closestX == playerX) || abs((closestY - playerY) / (closestX - playerX))>0.5;
        if (!vcolCheck) continue;
        if (playerX == closestX) playerY = closestY + (closestY < playerY ? 10 : -10);
        else playerY = closestY + (closestY < playerY ? 10 : -10) * abs(sin(atan((playerY - closestY)/(playerX - closestX))));
      }
    }
    if (!vcolCheck) {
      playerY -= abs(playerXVel);
    }
  }
  if (vcolCheck) {
    if (pressed[1] && playerYVel > 0) {
      playerYVel = -5.7 * (pressed[2]?2:1);
      playerY -= abs(playerXVel);
    } else {
      vcolCheck = playerYVel>0;
      playerYVel = 0;
    }
  }
  cX += constrain(playerX, (width/scaleFactor)/2 + bounds[level][0], bounds[level][2] - (width/scaleFactor)/2) * 0.3;
  cX /= 1.3;
  cY += constrain(playerY, (height/scaleFactor)/2 + bounds[level][1], bounds[level][3] - (height/scaleFactor)/2) * 0.3;
  cY /= 1.3;
  if (vcolCheck) rotSpd = ((playerX-oX)>0?0.1:-0.1) * sqrt((playerX-oX)*(playerX-oX)+(playerY-oY)*(playerY-oY)*(vcolCheck?1:0));
  else rotSpd /= sqrt(1.1);
  rot += rotSpd;
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
  stroke(255, 0, 0);
  for (int i = 0; i < koList[level].length; i++) {
    line((((width/scaleFactor)/2)-cX) + koList[level][i].startX,
      (((height/scaleFactor)/2)-cY) + koList[level][i].startY,
      (((width/scaleFactor)/2)-cX) + koList[level][i].endX,
      (((height/scaleFactor)/2)-cY) + koList[level][i].endY);
  }
  noStroke();
  fill(0);
  circle((((width/scaleFactor)/2)-cX) + endPos[level][0], (((height/scaleFactor)/2)-cY) + endPos[level][1], 6);
  circle((((width/scaleFactor)/2)-cX) + playerX, (((height/scaleFactor)/2)-cY) + playerY, 20);
  fill(0, 255, 255);
  circle((((width/scaleFactor)/2)-cX) + cos(rot) * 5 + playerX, (((height/scaleFactor)/2)-cY) + sin(rot) * 5 + playerY, 6);
  circle((((width/scaleFactor)/2)-cX) + endPos[level][0], (((height/scaleFactor)/2)-cY) + endPos[level][1], 4);
  popMatrix();
  if (playerY > bounds[level][3]) { //rip
    hasStarted = false;
  }
  for (int i = 0; i < koList[level].length; i++)
    if (lineCircle(koList[level][i].startX, koList[level][i].startY, koList[level][i].endX, koList[level][i].endY, playerX, playerY, 10)) hasStarted = false;
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
