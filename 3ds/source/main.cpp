// Line Game 3DS
// By Hail AKA Half-Qilin

#define SCREEN_WIDTH 400
#define BOTTOM_SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define SUBSTEPS 6
#define MAX_SPEED 59

#include <citro2d.h>
#include <3ds.h>

#include <fstream>
#include <iostream>
#include <cmath>

#include "lineList.hpp"
#include "collisions.hpp"
#include "letters.hpp"

const float xDiv = 1 + (sqrt(6)-1)/SUBSTEPS,
			xAdd = 2.69/sqrt(SUBSTEPS*sqrt(SUBSTEPS)-pow(SUBSTEPS, xDiv)/(xDiv*sqrt(2)));

const unsigned int currentSaveVersion = 1;
unsigned int saveVersion = 0; // Save Version Update Handling

enum gamestate {
	inGame = 1,
	menu = 0
};
enum animstate {
	unset = -1,
	enteredAnim = 1,
	ded = 0,
	exitAnim = 2,
};

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
	animTimer = 0,
	depthOffset = 0;

const double pi = acos(-1.0);

u8 consoleModel = 3;
u8 lang = CFG_LANGUAGE_EN;
u8 serial = 0;

static u32 clrWhite, clrBlack, clrCyan, clrRed, clrGrey, clrFake;

int level = 0,
	oLvl = -1,
	curLine;

unsigned long levelTimer;

animstate animID = unset; // -1 not animating
gamestate gameState = menu;

bool vcolCheck = false,
    hcolCheck = false,
	tcolCheck = false,
    hasStarted = false,
	dcolCheck = false,
	levelTimerRunning = false;

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
		C2D_DrawLine(linelistBG[curLine]->startX + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 - 3 * depthOffset),
					 linelistBG[curLine]->startY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
					 clrGrey,
					 linelistBG[curLine]->endX + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 - 3 * depthOffset),
					 linelistBG[curLine]->endY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
					 clrGrey, 2, 0.05f);
	}
	for (curLine = bgStart[level]; curLine < bgEnd[level]; curLine++) {
		C2D_DrawCircleSolid(linelistBG[curLine]->endX + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 - 3 * depthOffset),
							linelistBG[curLine]->endY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
							0.05f, 1, clrGrey);
		C2D_DrawCircleSolid(linelistBG[curLine]->startX + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 - 3 * depthOffset),
							linelistBG[curLine]->startY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
							0.05f, 1, clrGrey);
	}
	for (curLine = falseStart[level]; curLine < falseEnd[level]; curLine++) {
		C2D_DrawLine(lineListFake[curLine]->startX + floor(0.5 - cX + SCREEN_WIDTH / 2),
					 lineListFake[curLine]->startY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
					 clrFake,
					 lineListFake[curLine]->endX + floor(0.5 - cX + SCREEN_WIDTH / 2),
					 lineListFake[curLine]->endY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
					 clrFake, 2, 0.09f);
	}
	for (curLine = falseStart[level]; curLine < falseEnd[level]; curLine++) {
		C2D_DrawCircleSolid(lineListFake[curLine]->endX + floor(0.5 - cX + SCREEN_WIDTH / 2),
							lineListFake[curLine]->endY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
							0.09f, 1, clrFake);
		C2D_DrawCircleSolid(lineListFake[curLine]->startX + floor(0.5 - cX + SCREEN_WIDTH / 2),
							lineListFake[curLine]->startY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
							0.09f, 1, clrFake);
	}
	for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
		C2D_DrawLine(linelist[curLine]->startX + floor(0.5 - cX + SCREEN_WIDTH / 2),
					 linelist[curLine]->startY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
					 clrBlack,
					 linelist[curLine]->endX + floor(0.5 - cX + SCREEN_WIDTH / 2),
					 linelist[curLine]->endY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
					 clrBlack, 2, 0.1f);
	}
	for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
		C2D_DrawCircleSolid(linelist[curLine]->endX + floor(0.5 - cX + SCREEN_WIDTH / 2),
							linelist[curLine]->endY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
							0.1f, 1, clrBlack);
		C2D_DrawCircleSolid(linelist[curLine]->startX + floor(0.5 - cX + SCREEN_WIDTH / 2),
							linelist[curLine]->startY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
							0.1f, 1, clrBlack);
	}
	for (curLine = koStart[level]; curLine < koEnd[level]; curLine++) {
		C2D_DrawLine(linelistKO[curLine]->startX + floor(0.5 - cX + SCREEN_WIDTH / 2),
					 linelistKO[curLine]->startY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
					 clrRed,
					 linelistKO[curLine]->endX + floor(0.5 - cX + SCREEN_WIDTH / 2),
					 linelistKO[curLine]->endY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
					 clrRed, 2, 0.11f);
	}
	for (curLine = koStart[level]; curLine < koEnd[level]; curLine++) {
		C2D_DrawCircleSolid(linelistKO[curLine]->endX + floor(0.5 - cX + SCREEN_WIDTH / 2),
							linelistKO[curLine]->endY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
							0.11f, 1, clrRed);
		C2D_DrawCircleSolid(linelistKO[curLine]->startX + floor(0.5 - cX + SCREEN_WIDTH / 2),
							linelistKO[curLine]->startY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
							0.11f, 1, clrRed);
	}
	C2D_DrawCircleSolid(endPoint[level][0] + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 + 2 * depthOffset),
						endPoint[level][1] + floor(0.5 - cY + SCREEN_HEIGHT / 2),
						0.15f, 3, clrBlack);
	C2D_DrawCircleSolid(endPoint[level][0] + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 + 2 * depthOffset),
						endPoint[level][1] + floor(0.5 - cY + SCREEN_HEIGHT / 2),
						0.4f, 2, clrCyan);
}

void saveData (unsigned long* highScores) {
    std::fstream saveFile;
    saveFile.open("save_hail_lines.txt", std::fstream::out | std::fstream::trunc);
    saveFile << std::hex << currentSaveVersion << std::endl;
    saveFile << std::hex << levels << std::endl;
	for (int i = 0; i < levels; i++) {
		unsigned long maxScoreRandomCode = rand();
		saveFile << std::hex << (highScores[i] ^ maxScoreRandomCode) << "|" << std::hex
			<< ~maxScoreRandomCode << "|" << std::endl;
	}
    saveFile.close();
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
	int jumpableFor = 25,
		jumpFor = 0;
	
	// High Scores
	unsigned long highScores[levels];
	for (int i = 0; i < levels; i++) highScores[i] = 0;
	
	// Create Colors
    clrWhite = C2D_Color32(255, 255, 255, 0xFF);
	clrBlack = C2D_Color32(0, 0, 0, 0xFF);
	clrCyan = C2D_Color32(0, 255, 255, 0xFF);
	clrRed = C2D_Color32(255, 0, 0, 0xFF);
	clrGrey = C2D_Color32(200, 200, 200, 0xFF);
	clrFake = C2D_Color32(0, 0, 100, 0xFF);
	
	// 3D Mode
    Result res = cfguInit();
    if (R_SUCCEEDED(res)) {
		CFGU_GetSystemLanguage(&lang);
        CFGU_GetSystemModel(&consoleModel);
        cfguExit();
    }
	gfxSet3D(true);
	
	// Create Screens
    C3D_RenderTarget * top_main = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    C3D_RenderTarget * top_sub = C2D_CreateScreenTarget(GFX_TOP, GFX_RIGHT);
    C3D_RenderTarget * bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	
	// Save Files
	std::fstream log;
	log.open("save_hail_lines.txt", std::fstream::out | std::fstream::app);
	log << "0";
	log.close();
    FILE * saveFile = fopen ("save_hail_lines.txt", "r");
    fscanf(saveFile, "%x", &saveVersion);
    switch (saveVersion) {
		case 1: {
			unsigned int len = 0;
			unsigned long scoreRandomCode = 0;
			unsigned long tScore = 0;
            fscanf(saveFile, "%x", &len);
			for (unsigned int i = 0; i < len; i++) {
				highScores[i] = 0;
				fscanf(saveFile, "%lx|%lx", &tScore, &scoreRandomCode);
				highScores[i] = tScore ^ (~scoreRandomCode);
			}
			break;
		}
    }
	fclose(saveFile);
	
	// Save Again
	saveData(highScores);
	
	// Log
    log.open("log_hail_lines.txt", std::fstream::out | std::fstream::trunc);
	log << "Game Ready!" << std::endl;
	
	// Main Loop
	while (aptMainLoop())
    {
    	startFrame:
		animTimer += 1 / 60.0f;
		// Input
		hidScanInput();
        hidTouchRead(&touch);
		kDown = hidKeysDown();
		kHeld = hidKeysHeld();
		kUp = hidKeysUp();
		
		switch (gameState) {
			case inGame: {
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
					levelTimer = 0;
					jumpableFor = 0;
					jumpFor = 0;
					levelTimerRunning = false;
					oLvl = level;
					dcolCheck = false;
					hasStarted = true;
				}
				for (int lol = 0; lol < SUBSTEPS; lol++) {
					oX = playerX;
					oY = playerY;
					playerYVel += 0.3 / SUBSTEPS;
					if (kHeld & (KEY_DOWN | KEY_LEFT | KEY_RIGHT | KEY_A)) {
						if (!levelTimerRunning) log << "We Going!" << std::endl;
						levelTimerRunning = true;
					}
					if (levelTimerRunning) levelTimer++;
					if (levelTimer == 0 && levelTimerRunning) { // Overflow Check
						dcolCheck = true;
						lol = SUBSTEPS + 1;
						continue;
					}
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
							vcolCheck = vcolCheck || (closestX == playerX) || abs((closestY - playerY) / (closestX - playerX))>0.5;
							if (!vcolCheck) continue;
							if (playerX == closestX) playerY = closestY + (closestY < playerY ? 10 : -10);
							else playerY = closestY + (closestY < playerY ? 10 : -10) * abs(sin(atan((playerY - closestY)/(playerX - closestX))));
							if (closestY > playerY) jumpableFor = 25;
						}
					}
					if (tcolCheck && !vcolCheck) {
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
					if ((kHeld & KEY_A)) jumpFor = 25;
					else if (jumpFor) jumpFor--;
					if (jumpableFor && jumpFor) {
						playerYVel = xAdd * -6.5 * ((kHeld&KEY_DOWN) ? 2 : 1);
						playerY -= abs(playerXVel);
						jumpableFor = 0;
						jumpFor = 0;
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
					if (pointCircle(endPoint[level][0], endPoint[level][1], playerX, playerY, 12)) lol = SUBSTEPS + 1;
				}
				cX += constrain(playerX, SCREEN_WIDTH / 2 + bounds[level][0], bounds[level][2] - SCREEN_WIDTH / 2) * 0.3;
				cX /= 1.3;
				cY += constrain(playerY, SCREEN_HEIGHT / 2 + bounds[level][1], bounds[level][3] - SCREEN_HEIGHT / 2) * 0.3;
				cY /= 1.3;
				break;
			}
			case menu: {
				if (animID == exitAnim) {
					levelTimer+=6;
					if (levelTimer > 360) {
						gameState = inGame;
						animID = enteredAnim;
						hasStarted = false;
						goto startFrame;
					}
				}
				if (!hasStarted) {
					saveData(highScores);
					hasStarted = true;
					animTimer = 0;
					dcolCheck = true;
				}
				if ((kUp & KEY_A) && (animID != exitAnim) && !dcolCheck) {
					animID = exitAnim;
					levelTimer = 0;
				}
				if (!(kHeld & KEY_A)) dcolCheck = false;
				break;
			}
		}
		
		// Start Render
		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(top_main, clrWhite);
		C2D_TargetClear(top_sub, clrWhite);
		C2D_TargetClear(bottom, clrWhite);
		
		// Top Screen
		for (int b = 0; b < 2; b++) {
			if (b == 0) {
				C2D_SceneBegin(top_main);
				depthOffset = abs(osGet3DSliderState());
			}
			if (b == 1) {
				C2D_SceneBegin(top_sub);
				depthOffset = -depthOffset;
			}
			switch (gameState) {
				case inGame: {
					// Draw Level
					drawLevel();

					// Draw Player
					C2D_DrawCircleSolid(floor(0.5 - cX + SCREEN_WIDTH / 2) + playerX,
										floor(0.5 - cY + SCREEN_HEIGHT / 2) + playerY,
										0.3f, (animID == -1 ? 10 : min(animTimer * 100, 10)), clrBlack);
					C2D_DrawCircleSolid(floor(0.5 - cX + SCREEN_WIDTH / 2) + cos(rot) * (animID == -1 ? 5 : min(animTimer * 50, 5)) + playerX,
										floor(0.5 - cY + SCREEN_HEIGHT / 2) + sin(rot) * (animID == -1 ? 5 : min(animTimer * 50, 5)) + playerY,
										0.4f, (animID == -1 ? 3 : min(animTimer * 30, 3)), clrCyan);

					if (animID == enteredAnim) C2D_DrawRectSolid(0, 0, 0.9f, SCREEN_WIDTH, SCREEN_HEIGHT, C2D_Color32(0, 255, 255, C2D_FloatToU8(max(0, 1 - animTimer))));
					break;
				}
				case menu: {
					drawString("VECTORIA", (SCREEN_WIDTH-getWidth("VECTORIA", 1.3f, 4))/2 + floor(0.5 + 6 * depthOffset), SCREEN_HEIGHT/2 + floor(14 * sin(sin(sin(animTimer * 2.342))) + 13), 1.3f, 4, clrBlack);
					if (animID == enteredAnim) C2D_DrawRectSolid(0, 0, 0.9f, SCREEN_WIDTH, SCREEN_HEIGHT, C2D_Color32(0, 255, 255, C2D_FloatToU8(max(0, 1 - animTimer))));
					if (animID == exitAnim) C2D_DrawRectSolid(0, 0, 0.9f, SCREEN_WIDTH, SCREEN_HEIGHT, C2D_Color32(0, 255, 255, C2D_FloatToU8(levelTimer / 360.0f)));
					break;
				}
			}
		}
		
		// Bottom Screne
        C2D_SceneBegin(bottom);
		switch (gameState) {
			case inGame: break;
			case menu: break;
		}
        
        // Done Rendering!
		C3D_FrameEnd(0);
		
		/* ------------- AFTER FRAME CHECKS ------------- */
		switch (gameState) {
			case inGame: {
				// Death Check
				if (playerY > bounds[level][3] || dcolCheck) {
					playerY = constrain(playerY, bounds[level][1], bounds[level][3]);
					playerX = constrain(playerX, bounds[level][0], bounds[level][2]);
					// Start Render
					C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
					C2D_TargetClear(top_main, clrWhite);
					C2D_TargetClear(top_sub, clrWhite);
					for (int b = 0; b < 2; b++) {
						if (b == 0) {
							C2D_SceneBegin(top_main);
							depthOffset = abs(osGet3DSliderState());
						}
						if (b == 1) {
							C2D_SceneBegin(top_sub);
							depthOffset = -depthOffset;
						}
						// Draw Level
						drawLevel();
					}
					// Done Rendering!
					C3D_FrameEnd(0);
					// Log It
					log << "Oof! Died after " << levelTimer/360.0f << " seconds on level " << level << std::endl;
					animID = ded;
					int frames = 0;
					while (frames < 24) {
						frames++;
						// Start Render
						C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
						for (int b = 0; b < 2; b++) {
							if (b == 0) {
								C2D_SceneBegin(top_main);
								depthOffset = abs(osGet3DSliderState());
							}
							if (b == 1) {
								C2D_SceneBegin(top_sub);
								depthOffset = -depthOffset;
							}
							// Draw Level
							drawLevel();
							// Funni Animation
							C2D_DrawCircleSolid(playerX + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 + 5 * depthOffset),
												playerY + floor(0.5 - cY + SCREEN_HEIGHT / 2), 0.9f, (frames / 24.0f) * 69,
												C2D_Color32(255, 200 - 200 * (frames / 24.0f), 0,
															C2D_FloatToU8(0.5 - (frames / 48.0f))));
							C2D_DrawCircleSolid(playerX + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 + 5 * depthOffset),
												playerY + floor(0.5 - cY + SCREEN_HEIGHT / 2), 0.9f, (frames / 24.0f) * 69,
												C2D_Color32(255, 255, 255, C2D_FloatToU8((frames / 12.0f) - 1)));
						}
						// Done Rendering!
						C3D_FrameEnd(0);
					}
					frames = 0;
					while (frames < 10) {
						frames++;
						// Start Render
						C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
						C2D_TargetClear(top_main, clrWhite);
						C2D_TargetClear(top_sub, clrWhite);
						for (int b = 0; b < 2; b++) {
							if (b == 0) {
								C2D_SceneBegin(top_main);
								depthOffset = abs(osGet3DSliderState());
							}
							if (b == 1) {
								C2D_SceneBegin(top_sub);
								depthOffset = -depthOffset;
							}
							// Draw Level
							drawLevel();
							// Funni Animation
							C2D_DrawCircleSolid(playerX + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 + 5 * depthOffset),
												playerY + floor(0.5 - cY + SCREEN_HEIGHT / 2), 0.9f, 69,
												C2D_Color32(255, 255, 255, C2D_FloatToU8(1-(frames / 10.0f))));
						}
						// Done Rendering!
						C3D_FrameEnd(0);
					}
					hasStarted = false;
				}
				
				// Done Level Check
				if (pointCircle(endPoint[level][0], endPoint[level][1], playerX, playerY, 12)) {
					// Log it
					log << "Nice! Beat level " << level << " with a time of " << levelTimer/360.0f << " seconds!" << std::endl;
					if (highScores[level] == 0 || levelTimer < highScores[level]) {
						highScores[level] = levelTimer;
						log << "New high score!" << std::endl;
					}
					animID = enteredAnim;
					int frames = 0;
					float x = max(endPoint[level][0] - cX + SCREEN_WIDTH / 2, SCREEN_WIDTH - (endPoint[level][0] - cX + SCREEN_WIDTH / 2));
					float y = max(endPoint[level][1] - cY + SCREEN_HEIGHT / 2, SCREEN_HEIGHT - (endPoint[level][1] - cY + SCREEN_HEIGHT / 2));
					float dist = sqrt(x * x + y * y);
					while (2 + frames * 10 < dist) {
						frames++;
						// Start Render
						C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
						for (int b = 0; b < 2; b++) {
							if (b == 0) {
								C2D_SceneBegin(top_main);
								depthOffset = abs(osGet3DSliderState());
							}
							if (b == 1) {
								C2D_SceneBegin(top_sub);
								depthOffset = -depthOffset;
							}
							// Draw Level
							drawLevel();
							// Draw Player
							C2D_DrawCircleSolid(playerX + floor(0.5 - cX + SCREEN_WIDTH / 2),
												playerY + floor(0.5 - cY + SCREEN_HEIGHT / 2),
												0.3f, 10, clrBlack);
							C2D_DrawCircleSolid(playerX + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(cos(rot) * 5),
												playerY + floor(0.5 - cY + SCREEN_HEIGHT / 2) + floor(sin(rot) * 5),
												0.4f, 3, clrCyan);
							// Funni Animation
							C2D_DrawCircleSolid(endPoint[level][0] + floor(0.5 - cX + SCREEN_WIDTH / 2) + floor(0.5 + 2 * depthOffset),
												endPoint[level][1] + floor(0.5 - cY + SCREEN_HEIGHT / 2),
												0.9f, 2 + frames * 10, clrCyan);
						}
						// Done Rendering!
						C3D_FrameEnd(0);
					}
					level++;
					if (level >= levels) {
						level = 0;
						gameState = menu;
					}
					hasStarted = false;
				}
				break;
			}
			case menu: break;
		}
	}
	
	// Deinit Graphics
    C2D_Fini();
    C3D_Fini();
    gfxExit();
	
	// End Log
    log.close();
	
	// Save on exit
	saveData(highScores);
	
	// Exit ROM
    romfsExit();
	
	return 0;
}