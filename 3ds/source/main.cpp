// Line Game 3DS
// By Hail AKA Half-Qilin


#define SCREEN_WIDTH 400
#define BOTTOM_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#include <citro2d.h>

#include <fstream>
#include <iostream>
#include <cmath>

#include "lineList.hpp"
#include "collisions.hpp"

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

const double pi = acos(-1.0);

u8 wideModifier = 2;

static u32 clrWhite, clrBlack;

int level = 0,
	curLine;

bool vcolCheck = false,
    hcolCheck = false,
    hasStarted = false;

float constrain(float x, float min, float max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

int main(int argc, char* argv[]) {
    // Init Libs
    romfsInit();
    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    srand(time(NULL));
	
	// Input Vars
    touchPosition touch;
	u32 kDown, kHeld, kUp;
	
	// Create Colors
    clrWhite = C2D_Color32(255, 255, 255, 0xFF),
	clrBlack = C2D_Color32(0, 0, 0, 0xFF);
	
	// Wide mode
    Result res = cfguInit();
    if (R_SUCCEEDED(res)) {
        CFGU_GetModelNintendo2DS(&wideModifier);
        wideModifier = 2 - wideModifier;
        cfguExit();
    }
    gfxSetWide(wideModifier == 2);
	
	// Create Screens
    C3D_RenderTarget * top_main = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget * bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	
	// Log
	std::fstream log;
    log.open("log_hail_lines.txt", std::fstream::out | std::fstream::trunc);
	
	// Main Loop
	while (aptMainLoop())
    {
		// Input
		hidScanInput();
        hidTouchRead(&touch);
		kDown = hidKeysDown();
		kHeld = hidKeysHeld();
		kUp = hidKeysUp();
		
		// Gameloop
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
		oX = playerX;
		oY = playerY;
		playerYVel += 0.3;
		if (kHeld & KEY_DOWN) playerYVel += 0.9;
		if (playerYVel > 15) playerYVel = 15;
		if (playerYVel < -15) playerYVel = -15;
		playerXVel = playerXVel / 2;
		if (kHeld & KEY_LEFT) playerXVel -= 2;
		if (kHeld & KEY_RIGHT) playerXVel += 2;
		playerX += playerXVel;
		hcolCheck = false;
		if (vcolCheck) playerY -= abs(playerXVel);
		for (int i = 0; i < levelLen[level]; i++) {
			curLine = levelStart[level]+i;
			if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
				hcolCheck = true;
				break;
			}
		}
		while (hcolCheck) {
			bool tcolCheck = false;
			for (int i = 0; i < levelLen[level]; i++) {
				curLine = levelStart[level]+i;
				if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
					tcolCheck = true;
					break;
				}
			}
			if (tcolCheck) {
				playerX -= 0.1 * (playerX < closestX ? 1 : -1);
			} else break;
		}
		if (vcolCheck) playerY += abs(playerXVel);
		vcolCheck = false;
		if (hcolCheck) playerXVel = 0;
		playerY += playerYVel;
		for (int i = 0; i < levelLen[level]; i++) {
			curLine = levelStart[level]+i;
			if (abs((linelist[curLine]->startY-linelist[curLine]->endY)/(linelist[curLine]->startX-linelist[curLine]->endX))>3) continue;
			if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
				vcolCheck = (closestX == playerX) || abs((closestY - playerY) / (closestX - playerX))>0.5;
				break;
			}
		}
		if (!vcolCheck && playerYVel > 0) {
			playerY += abs(playerXVel);
			for (int i = 0; i < levelLen[level]; i++) {
				curLine = levelStart[level]+i;
				if (abs((linelist[curLine]->startY-linelist[curLine]->endY)/(linelist[curLine]->startX-linelist[curLine]->endX))>3) continue;
				if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
					vcolCheck = (closestX == playerX) || abs((closestY - playerY) / (closestX - playerX))>0.5;
					break;
				}
			}
			if (!vcolCheck) {
				playerY -= abs(playerXVel);
			}
		}
		while (vcolCheck) {
			bool tcolCheck = false;
			for (int i = 0; i < levelLen[level]; i++) {
				curLine = levelStart[level]+i;
				if (abs((linelist[curLine]->startY-linelist[curLine]->endY)/(linelist[curLine]->startX-linelist[curLine]->endX))>3) continue;
				if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
					tcolCheck = (closestX == playerX) || abs((closestY - playerY) / (closestX - playerX))>0.5;
					break;
				}
			}
			if (tcolCheck) {
				playerY -= 0.1 * (playerY < closestY ? 1 : -1);
			} else break;
		}
		if (vcolCheck) {
			if ((kDown & KEY_A) && playerYVel > 0) playerYVel = -5 * ((kHeld&KEY_DOWN) ? 2 : 1);
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
		
		// Start Render
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top_main, clrWhite);
		C2D_TargetClear(bottom, clrWhite);
		
		// Top Screen
		C2D_SceneBegin(top_main);
		
		for (int i = 0; i < levelLen[level]; i++) {
			curLine = levelStart[level]+i;
			C2D_DrawLine(linelist[curLine]->startX - cX + SCREEN_WIDTH / 2,
						 linelist[curLine]->startY - cY + SCREEN_HEIGHT / 2,
						 clrBlack,
						 linelist[curLine]->endX - cX + SCREEN_WIDTH / 2,
						 linelist[curLine]->endY - cY + SCREEN_HEIGHT / 2,
						 clrBlack, 1.5, 0.1f);
		}
		C2D_DrawCircleSolid(playerX - cX + SCREEN_WIDTH / 2,
							playerY - cY + SCREEN_HEIGHT / 2,
							0.3f, 10, clrBlack);
		C2D_DrawCircleSolid(playerX + cos(rot) * 7 - cX + SCREEN_WIDTH / 2,
							playerY + sin(rot) * 7 - cY + SCREEN_HEIGHT / 2,
							0.4f, 2.5, C2D_Color32(255, 0, 0, 0xFF));
		
		// Bottom Screne
        C2D_SceneBegin(bottom);
        
        // Done Rendering!
		C3D_FrameEnd(0);
		
		if (playerY > bounds[level][3]) { //rip
			int frames = 0;
			while (frames < 24) {
				// Start Render
				C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
				C2D_SceneBegin(top_main);
				// Funni Animation
				C2D_DrawCircleSolid(playerX - cX + SCREEN_WIDTH / 2,
									SCREEN_HEIGHT, 0.8f, (frames / 24.0f) * 20,
									C2D_Color32(255, 200 + 55 * (frames / 24.0f), 255 * (frames / 24.0f), 0xFF));
        		// Done Rendering!
				C3D_FrameEnd(0);
				frames++;
			}
			hasStarted = false;
		}
	}
	
	// Deinit Graphics
    C2D_Fini();
    C3D_Fini();
    gfxExit();
	
	// End Log
    log.close();
	
	// Exit ROM
    romfsExit();
	
	return 0;
}