#define SCREEN_WIDTH 400
#define BOTTOM_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#include <citro2d.h>
#include <iostream>

#include "lineList.cpp"
#include "collisions.cpp"

float playerX = 50,
    playerY = 50,
    oX = playerX,
    oY = playerY,
    playerYVel = 0,
    playerXVel = 0,
    rot = 0,
    rotSpd = 0,
    cX = playerX,
    cY = playerY;

int level = 0;

bool pressed[4] = new bool[4];
bool vcolCheck = false,
    hcolCheck = false,
    hasStarted = false;

void draw() {
    if (!hasStarted) {
        playerX = startPos[level][0];
        playerY = startPos[level][1];
        playerYVel = 0;
        playerXVel = 0;
        oX = playerX;
        oY = playerY;
        cX = constrain(playerX, SCREEN_WIDTH / 2 + bounds[level][0], bounds[level][2] - SCREEN_WIDTH / 2);
        cY = constrain(playerY, SCREEN_HEIGHT / 2 + bounds[level][1], bounds[level][3] - SCREEN_HEIGHT / 2);
        hasStarted = true;
    }
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
    for (int i = 0; i < lineList[level].length; i++) {
        if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
            hcolCheck = true;
            break;
        }
    }
    while (hcolCheck) {
        bool tcolCheck = false;
        for (int i = 0; i < lineList[level].length; i++) {
            if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
                tcolCheck = true;
                break;
            }
        }
        if (tcolCheck) {
            playerX -= 0.1 * (playerXVel > 0 ? 1 : -1);
        } else break;
    }
    if (vcolCheck) playerY += abs(playerXVel);
    vcolCheck = false;
    if (hcolCheck) playerXVel = 0;
    playerY += playerYVel;
    for (int i = 0; i < lineList[level].length; i++) {
        if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
            vcolCheck = true;
            break;
        }
    }
    if (!vcolCheck && playerYVel > 0) {
        playerY += abs(playerXVel);
        for (int i = 0; i < lineList[level].length; i++) {
            if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
                vcolCheck = true;
                break;
            }
        }
        if (!vcolCheck) {
            playerY -= abs(playerXVel);
        }
    }
    while (vcolCheck) {
        bool tcolCheck = false;
        for (int i = 0; i < lineList[level].length; i++) {
            if (lineCircle(lineList[level][i].startX, lineList[level][i].startY, lineList[level][i].endX, lineList[level][i].endY, playerX, playerY, 10)) {
                tcolCheck = true;
                break;
            }
        }
        if (tcolCheck) {
            playerY -= 0.1 * (playerYVel > 0 ? 1 : -1);
        } else break;
    }
    if (vcolCheck) {
        if (pressed[1] && playerYVel > 0) playerYVel = -5 * (pressed[2] ? 2 : 1);
        else {
            vcolCheck = playerYVel > 0;
            playerYVel = 0;
        }
    }
    cX += constrain(playerX, SCREEN_WIDTH / 2 + bounds[level][0], bounds[level][2] - SCREEN_WIDTH / 2) * 0.3;
    cX /= 1.3;
    cY += constrain(playerY, SCREEN_HEIGHT / 2 + bounds[level][1], bounds[level][3] - SCREEN_HEIGHT / 2) * 0.3;
    cY /= 1.3;
    if (vcolCheck) rotSpd = ((playerX - oX) > 0 ? 0.1 : -0.1) * sqrt((playerX - oX) * (playerX - oX) + (playerY - oY) * (playerY - oY) * (vcolCheck ? 1 : 0));
    else rotSpd /= sqrt(1.1);
    rot += rotSpd;
    fill(0);
    circle(playerX - cX + SCREEN_WIDTH / 2, playerY - cY + SCREEN_HEIGHT / 2, 20);
    fill(255, 0, 0);
    circle(playerX + cos(rot) * 7 - cX + SCREEN_WIDTH / 2, playerY + sin(rot) * 7 - cY + SCREEN_HEIGHT / 2, 5);
    stroke(0);
    for (int i = 0; i < lineList[level].length; i++) {
        line(lineList[level][i].startX - cX + SCREEN_WIDTH / 2,
            lineList[level][i].startY - cY + SCREEN_HEIGHT / 2,
            lineList[level][i].endX - cX + SCREEN_WIDTH / 2,
            lineList[level][i].endY - cY + SCREEN_HEIGHT / 2);
    }
    noStroke();
    if (playerY > bounds[level][3]) { //rip
		int frames = 0;
        while (frames < 24) {
            fill(255, 200 + 55 * (frames / 24.0f), 255 * (frames / 24.0f));
            circle(playerX - cX + SCREEN_WIDTH / 2, SCREEN_HEIGHT, (frames / 24.0f) * 40);
        }
        hasStarted = false;
    }
}