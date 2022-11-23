import processing.javafx.*;

int SCREEN_WIDTH = 400,
    SCREEN_HEIGHT = 240;

float playerX = 50,
      playerY = 50, 
      oX = playerX, 
      oY = playerY, 
      playerYVel = 0, 
      playerXVel = 0,
      scaleFactor = 1,
      rot = 0,
      rotSpd = 0,
      cX = playerX,
      cY = playerY;
      
int level = 0;

boolean pressed[] = new boolean[4];
boolean vcolCheck = false,
        hcolCheck = false,
        hasStarted = false;
        
boolean doingInternalAnimation = false;

void settings() {
  size(floor(400*scaleFactor), floor(240*scaleFactor), FX2D);
}

void setup() {
  noStroke();
  frameRate(60);
}

void draw() {
  if (doingInternalAnimation) return;
  if (!hasStarted) {
    playerX = startPos[level][0];
    playerY = startPos[level][1];
    playerYVel = 0;
    playerXVel = 0;
    oX = playerX;
    oY = playerY;
    cX = constrain(playerX, SCREEN_WIDTH/2 + bounds[level][0], bounds[level][2] - SCREEN_WIDTH/2);
    cY = constrain(playerY, SCREEN_HEIGHT/2 + bounds[level][1], bounds[level][3] - SCREEN_HEIGHT/2);
    hasStarted = true;
  }
  pushMatrix();
  scale(scaleFactor);
  background(255);
  oX = playerX;
  oY = playerY;
  playerYVel += 0.3;
  if (pressed[2]) playerYVel += 0.9;
  if (playerYVel > 15) playerYVel = 15;
  if (playerYVel < -15) playerYVel = -15;
  playerXVel = playerXVel / 2;
  if (pressed[0]) playerXVel -= 2;
  if (pressed[3]) playerXVel += 2;
  playerX += playerXVel;
  hcolCheck = false;
  if (vcolCheck) playerY -= abs(playerXVel);
  for(int i = 0; i < lineList[level].length; i++) {
    if (lineCircle(lineList[level][i].startX,lineList[level][i].startY,lineList[level][i].endX,lineList[level][i].endY, playerX, playerY, 10)) {
      hcolCheck=true;
      break;
    }
  }
  while (hcolCheck) {
    boolean tcolCheck = false;
    for(int i = 0; i < lineList[level].length; i++) {
      if (lineCircle(lineList[level][i].startX,lineList[level][i].startY,lineList[level][i].endX,lineList[level][i].endY, playerX, playerY, 10)) {
        tcolCheck = true;
        break;
      }
    }
    if (tcolCheck) {
      playerX -= 0.1 * (playerXVel>0?1:-1);
    } else break;
  }
  if (vcolCheck) playerY += abs(playerXVel);
  vcolCheck = false;
  if (hcolCheck) playerXVel = 0;
  playerY += playerYVel;
  for(int i = 0; i < lineList[level].length; i++) {
    if (lineCircle(lineList[level][i].startX,lineList[level][i].startY,lineList[level][i].endX,lineList[level][i].endY, playerX, playerY, 10)) {
      vcolCheck=true;
      break;
    }
  }
  if (!vcolCheck && playerYVel > 0) {
    playerY += abs(playerXVel);
    for(int i = 0; i < lineList[level].length; i++) {
      if (lineCircle(lineList[level][i].startX,lineList[level][i].startY,lineList[level][i].endX,lineList[level][i].endY, playerX, playerY, 10)) {
        vcolCheck=true;
        break;
      }
    }
    if (!vcolCheck) {
      playerY -= abs(playerXVel);
    }
  }
  while (vcolCheck) {
    boolean tcolCheck = false;
    for(int i = 0; i < lineList[level].length; i++) {
      if (lineCircle(lineList[level][i].startX,lineList[level][i].startY,lineList[level][i].endX,lineList[level][i].endY, playerX, playerY, 10)) {
        tcolCheck = true;
        break;
      }
    }
    if (tcolCheck) {
      playerY -= 0.1* (playerYVel>0?1:-1);
    } else break;
  }
  if (vcolCheck) {
    if (pressed[1] && playerYVel > 0) playerYVel = -5 * (pressed[2]?2:1);
    else {
      vcolCheck = playerYVel>0;
      playerYVel = 0;
    }
  }
  cX += constrain(playerX, SCREEN_WIDTH/2 + bounds[level][0], bounds[level][2] - SCREEN_WIDTH/2) * 0.3;
  cX /= 1.3;
  cY += constrain(playerY, SCREEN_HEIGHT/2 + bounds[level][1], bounds[level][3] - SCREEN_HEIGHT/2) * 0.3;
  cY /= 1.3;
  if (vcolCheck) rotSpd = ((playerX-oX)>0?0.1:-0.1) * sqrt((playerX-oX)*(playerX-oX)+(playerY-oY)*(playerY-oY)*(vcolCheck?1:0));
  else rotSpd /= sqrt(1.1);
  rot += rotSpd;
  fill(0);
  circle(playerX - cX + SCREEN_WIDTH/2, playerY - cY + SCREEN_HEIGHT/2, 20);
  fill(255, 0, 0);
  circle(playerX + cos(rot) * 7 - cX + SCREEN_WIDTH/2, playerY + sin(rot) * 7 - cY + SCREEN_HEIGHT/2, 5);
  stroke(0);
  for(int i = 0; i < lineList[level].length; i++) {
    line(lineList[level][i].startX - cX + SCREEN_WIDTH/2,
         lineList[level][i].startY - cY + SCREEN_HEIGHT/2,
         lineList[level][i].endX - cX + SCREEN_WIDTH/2,
         lineList[level][i].endY - cY + SCREEN_HEIGHT/2);
  }
  noStroke();
  popMatrix();
  if (playerY > bounds[level][3]) { //rip
    thread("deathAnimation"); // Isn't stable; too lazy to fix
  }
}

void deathAnimation() {
  noLoop();
  pushMatrix();
  scale(scaleFactor);
  doingInternalAnimation = true;
  float start = millis();
  while (millis()-start < 400) {
    fill(255, 200 + 55 * (millis()-start)/400,  255 * (millis()-start)/400);
    circle(playerX - cX + SCREEN_WIDTH/2, SCREEN_HEIGHT, (millis()-start)/10);
    redraw();
  }
  popMatrix();
  hasStarted = false;
  doingInternalAnimation = false;
  loop();
}

void keyPressed() {
  switch (key) {
    case 'a':
    case 'A': {
      pressed[0] = true;
      break;
    }
    case 'w':
    case 'W': {
      pressed[1] = true;
      break;
    }
    case 's':
    case 'S': {
      pressed[2] = true;
      break;
    }
    case 'd':
    case 'D': {
      pressed[3] = true;
      break;
    }
  }
}
void keyReleased() {
  switch (key) {
    case 'a':
    case 'A': {
      pressed[0] = false;
      break;
    }
    case 'w':
    case 'W': {
      pressed[1] = false;
      break;
    }
    case 's':
    case 'S': {
      pressed[2] = false;
      break;
    }
    case 'd':
    case 'D': {
      pressed[3] = false;
      break;
    }
  }
}
