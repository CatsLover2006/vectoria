// Line Game 3DS
// By Hail AKA Half-Qilin


#define SCREEN_WIDTH 400
#define BOTTOM_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SUBSTEPS 6
#define MAX_SPEED 59

#include <citro2d.h>

#include <fstream>
#include <iostream>
#include <cmath>

#include "lineList.hpp"
#include "collisions.hpp"

const float xDiv = 1 + (sqrt(6)-1)/SUBSTEPS,
			xAdd = 2.69/sqrt(SUBSTEPS*sqrt(SUBSTEPS)-pow(SUBSTEPS, xDiv)/(xDiv*sqrt(2)));

float playerX = 50,
    playerY = 50,
    oX = playerX,
    oY = playerY,
    playerYVel = 0,
    playerXVel = 0,
    rot = 0,
    rotSpd = 0,
    cX = playerX,
    cY = playerY,
	animTimer = 0;

const double pi = acos(-1.0);

u8 consoleModel = 3;
u8 lang = CFG_LANGUAGE_EN;
u8 serial = 0;
u8 wideModifier = 2;

static u32 clrWhite, clrBlack, clrCyan, clrRed, clrGrey;

int level = 0,
	oLvl = -1,
	curLine,
	animID = -1; // -1 not animating

bool vcolCheck = false,
    hcolCheck = false,
	tcolCheck = false,
    hasStarted = false,
	dcolCheck = false;

float constrain(float x, float min, float max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

float max (float a, float b) {
	if (a > b) return a;
	return b;
}

float min (float a, float b) {
	if (a < b) return a;
	return b;
}

void drawLevel() {
	for (curLine = bgStart[level]; curLine < bgEnd[level]; curLine++) {
		C2D_DrawLine(linelistBG[curLine]->startX - cX + SCREEN_WIDTH / 2,
					 linelistBG[curLine]->startY - cY + SCREEN_HEIGHT / 2,
					 clrGrey,
					 linelistBG[curLine]->endX - cX + SCREEN_WIDTH / 2,
					 linelistBG[curLine]->endY - cY + SCREEN_HEIGHT / 2,
					 clrGrey, 2, 0.05f);
	}
	for (curLine = bgStart[level]; curLine < bgEnd[level]; curLine++) {
		C2D_DrawCircleSolid(linelistBG[curLine]->endX - cX + SCREEN_WIDTH / 2,
							linelistBG[curLine]->endY - cY + SCREEN_HEIGHT / 2,
							0.05f, 1, clrGrey);
		C2D_DrawCircleSolid(linelistBG[curLine]->startX - cX + SCREEN_WIDTH / 2,
							linelistBG[curLine]->startY - cY + SCREEN_HEIGHT / 2,
							0.05f, 1, clrGrey);
	}
	for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
		C2D_DrawLine(linelist[curLine]->startX - cX + SCREEN_WIDTH / 2,
					 linelist[curLine]->startY - cY + SCREEN_HEIGHT / 2,
					 clrBlack,
					 linelist[curLine]->endX - cX + SCREEN_WIDTH / 2,
					 linelist[curLine]->endY - cY + SCREEN_HEIGHT / 2,
					 clrBlack, 2, 0.1f);
	}
	for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
		C2D_DrawCircleSolid(linelist[curLine]->endX - cX + SCREEN_WIDTH / 2,
							linelist[curLine]->endY - cY + SCREEN_HEIGHT / 2,
							0.1f, 1, clrBlack);
		C2D_DrawCircleSolid(linelist[curLine]->startX - cX + SCREEN_WIDTH / 2,
							linelist[curLine]->startY - cY + SCREEN_HEIGHT / 2,
							0.1f, 1, clrBlack);
	}
	for (curLine = koStart[level]; curLine < koEnd[level]; curLine++) {
		C2D_DrawLine(linelistKO[curLine]->startX - cX + SCREEN_WIDTH / 2,
					 linelistKO[curLine]->startY - cY + SCREEN_HEIGHT / 2,
					 clrRed,
					 linelistKO[curLine]->endX - cX + SCREEN_WIDTH / 2,
					 linelistKO[curLine]->endY - cY + SCREEN_HEIGHT / 2,
					 clrRed, 2, 0.11f);
	}
	for (curLine = koStart[level]; curLine < koEnd[level]; curLine++) {
		C2D_DrawCircleSolid(linelistKO[curLine]->endX - cX + SCREEN_WIDTH / 2,
							linelistKO[curLine]->endY - cY + SCREEN_HEIGHT / 2,
							0.11f, 1, clrRed);
		C2D_DrawCircleSolid(linelistKO[curLine]->startX - cX + SCREEN_WIDTH / 2,
							linelistKO[curLine]->startY - cY + SCREEN_HEIGHT / 2,
							0.11f, 1, clrRed);
	}
	C2D_DrawCircleSolid(endPoint[level][0] - cX + SCREEN_WIDTH / 2,
						endPoint[level][1] - cY + SCREEN_HEIGHT / 2,
						0.15f, 3, clrBlack);
	C2D_DrawCircleSolid(endPoint[level][0] - cX + SCREEN_WIDTH / 2,
						endPoint[level][1] - cY + SCREEN_HEIGHT / 2,
						0.4f, 2, clrCyan);
}

void drawLog() {
	printf("\x1b[1;1HX:       %7.2f%\x1b[K", playerX);
	printf("\x1b[2;1HY:       %7.2f%\x1b[K", playerY);
	printf("\x1b[3;1HCPU:     %6.2f%%\x1b[K", C3D_GetProcessingTime()*6.0f);
	printf("\x1b[4;1HGPU:     %6.2f%%\x1b[K", C3D_GetDrawingTime()*6.0f);
	printf("\x1b[5;1HCmdBuf:  %6.2f%%\x1b[K", C3D_GetCmdBufUsage()*100.0f);
	printf("\x1b[6;1HTmr:     %7.2f%\x1b[K", animTimer);
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
	int jumpableFor = 25;
	
	// Create Colors
    clrWhite = C2D_Color32(255, 255, 255, 0xFF);
	clrBlack = C2D_Color32(0, 0, 0, 0xFF);
	clrCyan = C2D_Color32(0, 255, 255, 0xFF);
	clrRed = C2D_Color32(255, 0, 0, 0xFF);
	clrGrey = C2D_Color32(200, 200, 200, 0xFF);
	
	// Wide mode
    Result res = cfguInit();
    if (R_SUCCEEDED(res)) {
		CFGU_GetSystemLanguage(&lang);
        CFGU_GetSystemModel(&consoleModel);
		CFGI_SecureInfoGetSerialNumber(&serial);
        cfguExit();
    }
    if (consoleModel == 3) wideModifier = 1;
	if (serial == 0) wideModifier = 1;
    gfxSetWide(wideModifier == 2);
	
	// Create Screens
    C3D_RenderTarget * top_main = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    //C3D_RenderTarget * bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	consoleInit(GFX_BOTTOM, NULL);
	
	// Log
	std::fstream log;
    log.open("log_hail_lines.txt", std::fstream::out | std::fstream::trunc);
	
	// Main Loop
	while (aptMainLoop())
    {
		animTimer += 1 / 60.0f;
		// Input
		hidScanInput();
        hidTouchRead(&touch);
		kDown = hidKeysDown();
		kHeld = hidKeysHeld();
		kUp = hidKeysUp();
		
		// Gameloop
		if (!hasStarted || oLvl != level) {
			animTimer = 0;
			playerX = startPos[level][0];
			playerY = startPos[level][1];
			playerYVel = 0;
			playerXVel = 0;
			oX = playerX;
			oY = playerY;
			if (oLvl != level) {
				cX = constrain(playerX, SCREEN_WIDTH / 2 + bounds[level][0], bounds[level][2] - SCREEN_WIDTH / 2);
				cY = constrain(playerY, SCREEN_HEIGHT / 2 + bounds[level][1], bounds[level][3] - SCREEN_HEIGHT / 2);
			}
			oLvl = level;
			dcolCheck = false;
			hasStarted = true;
		}
		for (int lol = 0; lol < SUBSTEPS; lol++) {
			oX = playerX;
			oY = playerY;
			playerYVel += 0.3 / SUBSTEPS;
			if (kHeld & KEY_DOWN) playerYVel += 0.9 / SUBSTEPS;
			if (playerYVel > MAX_SPEED) playerYVel = MAX_SPEED;
			if (playerYVel < -MAX_SPEED) playerYVel = -MAX_SPEED;
			playerXVel /= xDiv;
			if (kHeld & KEY_LEFT) playerXVel -= xAdd;
			if (kHeld & KEY_RIGHT) playerXVel += xAdd;
			playerX += playerXVel / SUBSTEPS;
			hcolCheck = false;
			if (vcolCheck) playerY -= abs(playerXVel/SUBSTEPS);
			for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
				if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
					if (abs((closestY - playerY) / (closestX - playerX))>0.84) continue;
					hcolCheck = true;
					if (playerX == closestX) continue;
					else playerX = closestX + (closestX < playerX ? 10 : -10) * abs(cos(atan((playerY - closestY)/(playerX - closestX))));
				}
			}
			if (vcolCheck) playerY += abs(playerXVel/SUBSTEPS);
			tcolCheck = vcolCheck;
			vcolCheck = false;
			playerY += playerYVel / SUBSTEPS;
			for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
				if (abs((linelist[curLine]->startY-linelist[curLine]->endY)/(linelist[curLine]->startX-linelist[curLine]->endX))>3) continue;
				if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
					vcolCheck = (closestX == playerX) || abs((closestY - playerY) / (closestX - playerX))>0.5;
					if (!vcolCheck) continue;
					if (playerX == closestX) playerY = closestY + (closestY < playerY ? 10 : -10);
					else playerY = closestY + (closestY < playerY ? 10 : -10) * abs(sin(atan((playerY - closestY)/(playerX - closestX))));
					if (closestY > playerY) jumpableFor = 25;
				}
			}
			if (tcolCheck) {
				playerY += abs(playerXVel/SUBSTEPS);
				for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
					if (abs((linelist[curLine]->startY-linelist[curLine]->endY)/(linelist[curLine]->startX-linelist[curLine]->endX))>3) continue;
					if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
						tcolCheck = (closestX == playerX) || abs((closestY - playerY) / (closestX - playerX))>0.5;
						vcolCheck = vcolCheck || tcolCheck;
						if (!tcolCheck) continue;
						if (playerX == closestX) playerY = closestY + (closestY < playerY ? 10 : -10);
						else playerY = closestY + (closestY < playerY ? 10 : -10) * abs(sin(atan((playerY - closestY)/(playerX - closestX))));
						if (closestY > playerY) jumpableFor = 25;
					}
				}
				if (!vcolCheck) playerY -= abs(playerXVel/SUBSTEPS);
			}
			if (hcolCheck) playerXVel = 0;
			if (vcolCheck) {
				playerYVel = 0;
			} else if (jumpableFor) jumpableFor--;
			if (jumpableFor && (kDown & KEY_A)) {
				playerYVel = xAdd * -6.5 * ((kHeld&KEY_DOWN) ? 2 : 1);
				playerY -= abs(playerXVel);
				jumpableFor = 0;
			}
			if (jumpableFor) rotSpd = ((playerX - oX) > 0 ? 0.1 : -0.1) * sqrt((playerX - oX) * (playerX - oX) + (playerY - oY) * (playerY - oY) * (jumpableFor ? 1 : 0));
			else rotSpd /= pow(1.1, 1/13.0);
			rot += rotSpd;
			for (curLine = koStart[level]; curLine < koEnd[level]; curLine++) {
				if (lineCircle(linelistKO[curLine]->startX, linelistKO[curLine]->startY, linelistKO[curLine]->endX, linelistKO[curLine]->endY, playerX, playerY, 10)) {
					dcolCheck = true;
					lol = SUBSTEPS + 1;
					break;
				}
			}
		}
		cX += constrain(playerX, SCREEN_WIDTH / 2 + bounds[level][0], bounds[level][2] - SCREEN_WIDTH / 2) * 0.3;
		cX /= 1.3;
		cY += constrain(playerY, SCREEN_HEIGHT / 2 + bounds[level][1], bounds[level][3] - SCREEN_HEIGHT / 2) * 0.3;
		cY /= 1.3;
		
		// Start Render
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top_main, clrWhite);
		//C2D_TargetClear(bottom, clrWhite);
		
		// Top Screen
		C2D_SceneBegin(top_main);
		
		// Draw Level
		drawLevel();
		
		// Draw Player
		C2D_DrawCircleSolid(playerX - cX + SCREEN_WIDTH / 2,
							playerY - cY + SCREEN_HEIGHT / 2,
							0.3f, (animID == -1 ? 10 : min(animTimer * 100, 10)), clrBlack);
		C2D_DrawCircleSolid(playerX + cos(rot) * (animID == -1 ? 6 : min(animTimer * 60, 6)) - cX + SCREEN_WIDTH / 2,
							playerY + sin(rot) * (animID == -1 ? 6 : min(animTimer * 60, 6)) - cY + SCREEN_HEIGHT / 2,
							0.4f, (animID == -1 ? 2.5 : min(animTimer * 25, 2.5)), clrCyan);
		
		if (animID == 0) C2D_DrawRectSolid(0, 0, 0.9f, SCREEN_WIDTH, SCREEN_HEIGHT, C2D_Color32(0, 255, 255, C2D_FloatToU8(max(0, 1 - animTimer))));
		
		// Bottom Screne
        //C2D_SceneBegin(bottom);
		drawLog();
        
        // Done Rendering!
		if (!dcolCheck) C3D_FrameEnd(0);
		
		/* ------------- AFTER FRAME CHECKS ------------- */
		
		// Death Check
		if (playerY > bounds[level][3] || dcolCheck) {
			playerY = constrain(playerY, bounds[level][1], bounds[level][3]);
			playerX = constrain(playerX, bounds[level][0], bounds[level][2]);
			// Start Render
			if (!dcolCheck) C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
			C2D_TargetClear(top_main, clrWhite);
			C2D_SceneBegin(top_main);
			// Draw Level
			drawLevel();
        	// Done Rendering!
			C3D_FrameEnd(0);
			animID = 1;
			int frames = 0;
			while (frames < 24) {
				// Start Render
				C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
				C2D_SceneBegin(top_main);
				// Draw Level
				drawLevel();
				// Funni Animation
				C2D_DrawCircleSolid(playerX - cX + SCREEN_WIDTH / 2,
									playerY - cY + SCREEN_HEIGHT / 2, 0.9f, (frames / 24.0f) * 69,
									C2D_Color32(255, 200 - 200 * (frames / 24.0f), 0,
												C2D_FloatToU8(0.5 - (frames / 48.0f))));
				C2D_DrawCircleSolid(playerX - cX + SCREEN_WIDTH / 2,
									playerY - cY + SCREEN_HEIGHT / 2, 0.9f, (frames / 24.0f) * 69,
									C2D_Color32(255, 255, 255, C2D_FloatToU8((frames / 12.0f) - 1)));
        		// Done Rendering!
				C3D_FrameEnd(0);
				frames++;
				drawLog();
			}
			hasStarted = false;
		}
		
		// Done Level Check
		if (pointCircle(endPoint[level][0], endPoint[level][1], playerX, playerY, 10)) {
			animID = 0;
			int frames = 0;
			float x = max(endPoint[level][0] - cX + SCREEN_WIDTH / 2, SCREEN_WIDTH - (endPoint[level][0] - cX + SCREEN_WIDTH / 2));
			float y = max(endPoint[level][1] - cY + SCREEN_HEIGHT / 2, SCREEN_HEIGHT - (endPoint[level][1] - cY + SCREEN_HEIGHT / 2));
			float dist = sqrt(x * x + y * y);
			while (2 + frames * 10 < dist) {
				// Start Render
				C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
				C2D_SceneBegin(top_main);
				// Draw Level
				drawLevel();
				// Draw Player
				C2D_DrawCircleSolid(playerX - cX + SCREEN_WIDTH / 2,
									playerY - cY + SCREEN_HEIGHT / 2,
									0.3f, 10, clrBlack);
				C2D_DrawCircleSolid(playerX + cos(rot) * 6 - cX + SCREEN_WIDTH / 2,
									playerY + sin(rot) * 6 - cY + SCREEN_HEIGHT / 2,
									0.4f, 2.5, clrCyan);
				// Funni Animation
				C2D_DrawCircleSolid(endPoint[level][0] - cX + SCREEN_WIDTH / 2,
									endPoint[level][1] - cY + SCREEN_HEIGHT / 2,
									0.9f, 2 + frames * 10, clrCyan);
        		// Done Rendering!
				C3D_FrameEnd(0);
				frames++;
				drawLog();
			}
			level ++;
			if (level >= levels) level = 0;
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