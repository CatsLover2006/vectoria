// Vectoria PS Vita
// By Hail AKA Half-Qilin

float scaleFactor = 2.4;

#include "../../data/basemath.hpp"
#include <cmath>

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 544
#define SUBSTEPS 6
#define MAX_SPEED 59

#include <psp2/kernel/processmgr.h>
#include <psp2/ctrl.h>
#include <psp2/touch.h>
#include <psp2/audioout.h>

#include <vita2d.h>

#include <fstream>
#include <iostream>

#include "../../data/line.hpp"

#include "../../data/lineList.hpp"
#include "../../data/lineListSony.hpp"
#include "../../data/collisions.hpp"
#include "../../data/letters.hpp"
#include "../../data/buttons.hpp"
#include "textDraw.hpp"

const float xDiv = 1 + (sqrt(SUBSTEPS)-1)/SUBSTEPS,
			xAdd = 2.69/sqrt(SUBSTEPS*sqrt(SUBSTEPS)-pow(SUBSTEPS, xDiv)/(xDiv*sqrt(SUBSTEPS/3)));

const unsigned int currentSaveVersion = 2;
unsigned int saveVersion = 0; // Save Version Update Handling

enum gamestate {
	mainLevel = 1,
	menu = 0,
};
enum animstate {
	unset = -1,
	enteredAnim = 1,
	ded = 0,
	exitAnim = 2,
	gameStart = 3,
};
enum levelExitType {
	nextLevel = 0,
	toMenu = 1,
};
enum menuID {
	mainMenu = 0,
	levelSelect = 1,
	colorPick = 2,
};

float playerX = 69,
    playerY = 420,
    oX = playerX,
    oY = playerY,
    playerYVel = 0,
    playerXVel = 0,
    rot = 0,
    rotSpd = 0,
    cX = playerX,
    cY = playerY,
	animTimer = 0,
	timerBlockOffset = 0;

static unsigned int clrWhite, clrBlack, clrPlayer, clrRed, clrGrey, clrFake, clrGreen;

int level = 2,
	curLine,
	frames = 0;

unsigned long levelTimer;

animstate animID = gameStart; // -1 not animating
gamestate gameState = menu;
levelExitType goTo = toMenu;
menuID currentMenu = mainMenu;

bool vcolCheck = false,
    hcolCheck = false,
	tcolCheck = false,
    hasStarted = false,
	levelTimerRunning = false,
	updateSave = true;

button* menuButtons[] = {
	new button("All levels", ((SCREEN_WIDTH/scaleFactor)*3/4 - 75)*scaleFactor, 24*scaleFactor, 164*scaleFactor, 28*scaleFactor, 0.55f*scaleFactor),
	new button("Level Select", ((SCREEN_WIDTH/scaleFactor)*3/4 - 75)*scaleFactor, 56*scaleFactor, 164*scaleFactor, 28*scaleFactor, 0.55f*scaleFactor),
	new button("Color Select", ((SCREEN_WIDTH/scaleFactor)*3/4 - 75)*scaleFactor, 88*scaleFactor, 164*scaleFactor, 28*scaleFactor, 0.55f*scaleFactor),
};
int menuButtonCount = 3;

void drawLevel() {
	for (curLine = bgStart[level]; curLine < bgEnd[level]; curLine++) {
		drawLine((linelistBG[curLine]->startX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (linelistBG[curLine]->startY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 (linelistBG[curLine]->endX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (linelistBG[curLine]->endY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 2 * scaleFactor, clrGrey);
	}
	for (curLine = falseStart[level]; curLine < falseEnd[level]; curLine++) {
		drawLine((lineListFake[curLine]->startX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (lineListFake[curLine]->startY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 (lineListFake[curLine]->endX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (lineListFake[curLine]->endY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 2 * scaleFactor, clrFake);
	}
	for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
		drawLine((linelist[curLine]->startX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (linelist[curLine]->startY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 (linelist[curLine]->endX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (linelist[curLine]->endY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 2 * scaleFactor, clrBlack);
	}
	for (curLine = liftStart[level]; curLine < liftEnd[level]; curLine++) {
		drawLine((lineListLift[curLine]->startX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (lineListLift[curLine]->startY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 (lineListLift[curLine]->endX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (lineListLift[curLine]->endY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 2 * scaleFactor, clrGreen);
	}
	for (curLine = koStart[level]; curLine < koEnd[level]; curLine++) {
		drawLine((linelistKO[curLine]->startX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (linelistKO[curLine]->startY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 (linelistKO[curLine]->endX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
					 (linelistKO[curLine]->endY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
					 2 * scaleFactor, clrRed);
	}
	vita2d_draw_fill_circle((endPoint[level][0] - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
						(endPoint[level][1] - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
						3 * scaleFactor, clrBlack);
	vita2d_draw_fill_circle((endPoint[level][0] - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
						(endPoint[level][1] - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
						2 * scaleFactor, clrPlayer);
}

int floatTo8Int(float i) {
	if (i > 1) return 255;
	if (i < 0) return 0;
	return floor(i * 255);
}

void saveData (unsigned long* highScores) {
    std::fstream saveFile;
    saveFile.open("ux0:data/save_hail_lines.txt", std::fstream::out | std::fstream::trunc);
    saveFile << std::hex << currentSaveVersion << std::endl;
    saveFile << std::hex << levels << std::endl;
	for (int i = 0; i < levels; i++) {
		unsigned long maxScoreRandomCode = rand();
		saveFile << std::hex << (highScores[i] ^ maxScoreRandomCode) << "|" << std::hex
			<< ~maxScoreRandomCode << "|" << std::endl;
	}
	saveFile << std::hex << clrPlayer << "|" << std::endl;
    saveFile.close();
}

int main(int argc, char* argv[]) {
    // Init Libs
	vita2d_init_advanced_with_msaa((16*1024*1024), SCE_GXM_MULTISAMPLE_4X);
    srand(time(NULL));
	
	// Input Vars
    SceTouchData touch;
    SceTouchData lastTouch;
    SceTouchData startTouch;
	unsigned int kDown, kHeld, kUp;
	SceCtrlData curButtons;
	int jumpableFor = 25,
		jumpFor = 0;
	float screenXMul, screenYMul;
	SceTouchPanelInfo pannel;
	sceTouchGetPanelInfo(0, &pannel);
	screenXMul = pannel.maxDispX / (SCREEN_WIDTH * 1.0f);
	screenYMul = pannel.maxDispY / (SCREEN_HEIGHT * 1.0f);
	
	// High Scores
	unsigned long highScores[levels];
	for (int i = 0; i < levels; i++) highScores[i] = 0;
	
	// Create Colors
    clrWhite = RGBA8(255, 255, 255, 0xFF);
	clrBlack = RGBA8(0, 0, 0, 0xFF);
	clrPlayer = RGBA8(0, 255, 255, 0xFF);
	clrRed = RGBA8(255, 0, 0, 0xFF);
	clrGrey = RGBA8(200, 200, 200, 0xFF);
	clrFake = RGBA8(0, 0, 100, 0xFF);
	clrGreen = RGBA8(0, 255, 0, 0xFF);

    // Level Buttons
    button* levelButtons[levels];
	
	// Save Files
	std::fstream log;
	log.open("ux0:data/save_hail_lines.txt", std::fstream::out | std::fstream::app);
	log << "0";
	log.close();
    log.open("ux0:data/log_hail_lines.txt", std::fstream::out | std::fstream::trunc);
    log << "Save File Read..." << std::endl;
    FILE * saveFile = fopen ("ux0:data/save_hail_lines.txt", "r");
    fscanf(saveFile, "%x", &saveVersion);
    switch (saveVersion) {
		case 1: {
			unsigned int len = 0;
			unsigned long scoreRandomCode = 0;
			unsigned long tScore = 0;
            fscanf(saveFile, "%x", &len);
			for (unsigned int i = 0; i < min(len, levels); i++) {
				highScores[i] = 0;
				fscanf(saveFile, "%lx|%lx|\n", &tScore, &scoreRandomCode);
				highScores[i] = tScore ^ (~scoreRandomCode);
    			log << "Level " << i << " high score " << highScores[i] << std::endl;
			}
			break;
		}
		case 2: {
			unsigned int len = 0;
			unsigned long scoreRandomCode = 0;
			unsigned long tScore = 0;
            fscanf(saveFile, "%x", &len);
			for (unsigned int i = 0; i < min(len, levels); i++) {
				highScores[i] = 0;
				fscanf(saveFile, "%lx|%lx|\n", &tScore, &scoreRandomCode);
				highScores[i] = tScore ^ (~scoreRandomCode);
    			log << "Level " << i << " high score " << highScores[i] << std::endl;
			}
			fscanf(saveFile, "%lx|\n", &clrPlayer);
			break;
		}
    }
	fclose(saveFile);
	
	// Save Again
	saveData(highScores);
	log << "Game Ready!" << std::endl;
	
	// Pretouch
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, SCE_TOUCH_SAMPLING_STATE_START);
    sceTouchEnableTouchForce(SCE_TOUCH_PORT_FRONT);
	vita2d_set_vblank_wait(1);
    vita2d_set_clear_color(clrWhite);
	sceTouchPeek(0, &startTouch, 1);
	
	// Main Loop
	while (true)
    {
    	startFrame:
		animTimer += 1 / 60.0f;
		
		// Input
		lastTouch = touch;
		sceCtrlPeekBufferPositiveExt(0, &curButtons, 1);
		kDown = (curButtons.buttons ^ kHeld) & curButtons.buttons;
		kUp = (curButtons.buttons ^ kHeld) ^ kDown;
		kHeld = curButtons.buttons;
        sceTouchPeek(0, &touch, 1);
		if (touch.reportNum > lastTouch.reportNum) startTouch = touch;
		
		// Game Logic
		switch (gameState) {
			case mainLevel: {
				// Gameloop
				if (!hasStarted) {
					animTimer = 0;
					playerX = startPos[level][0];
					playerY = startPos[level][1];
					playerYVel = 0;
					playerXVel = 0;
					oX = playerX;
					oY = playerY;
					if (animID == enteredAnim) {
						cX = constrain(playerX, (SCREEN_WIDTH/scaleFactor) / 2 + bounds[level][0], bounds[level][2] - (SCREEN_WIDTH/scaleFactor) / 2);
						cY = constrain(playerY, (SCREEN_HEIGHT/scaleFactor) / 2 + bounds[level][1], bounds[level][3] - (SCREEN_HEIGHT/scaleFactor) / 2);
					}
					levelTimer = 0;
					jumpableFor = 0;
					jumpFor = 0;
					levelTimerRunning = false;
					hasStarted = true;
					timerBlockOffset = getWidth(to_str(0), 0.55f*scaleFactor, 2.0f*scaleFactor) - 3 * scaleFactor;
				}
				for (int lol = 0; lol < SUBSTEPS; lol++) {
					oX = playerX;
					oY = playerY;
					if (kHeld & (SCE_CTRL_DOWN | SCE_CTRL_LEFT | SCE_CTRL_RIGHT | SCE_CTRL_CROSS)) {
						levelTimerRunning = true;
					}
					if (levelTimerRunning) levelTimer++;
					if (levelTimer == 0 && levelTimerRunning) goto exitLoopLevel; // Overflow Check
					timerBlockOffset *= 400;
					timerBlockOffset += getWidth(to_str((levelTimer / 60.0f) / SUBSTEPS), 0.55f*scaleFactor, 2.0f*scaleFactor) - 3 * scaleFactor;
					timerBlockOffset /= 401;
					invertGrav = false;
					for (curLine = liftStart[level]; curLine < liftEnd[level]; curLine++) {
      					invertGrav = lineCircle(lineListLift[curLine]->startX, lineListLift[curLine]->startY, lineListLift[curLine]->endX, lineListLift[curLine]->endY, playerX, playerY, 10);
      					if (invertGrav) break;
    				}
					if (!vcolCheck || !jumpableFor || invertGrav) {
						playerYVel += (invertGrav?-0.3:0.3) / SUBSTEPS;
						if (kHeld & SCE_CTRL_DOWN) playerYVel += 0.9 / SUBSTEPS;
					}
					if (playerYVel > MAX_SPEED) playerYVel = MAX_SPEED;
					if (playerYVel < -MAX_SPEED) playerYVel = -MAX_SPEED;
					playerXVel /= xDiv;
					if (kHeld & SCE_CTRL_LEFT) playerXVel -= xAdd;
					if (kHeld & SCE_CTRL_RIGHT) playerXVel += xAdd;
					playerX += playerXVel / SUBSTEPS;
					hcolCheck = false;
					if (vcolCheck) playerY -= abs_c(playerXVel/SUBSTEPS);
					for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
						if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
							hcolCheck = true;
							playerX = closestX + (closestX < playerX ? 10 : -10) * abs_c(cos(atan2(playerY - closestY,playerX - closestX)));
						}
					}
					if (vcolCheck) playerY += abs_c(playerXVel/SUBSTEPS);
					tcolCheck = vcolCheck;
					vcolCheck = false;
					playerY += playerYVel / SUBSTEPS;
					for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
						if (abs_c((linelist[curLine]->startY-linelist[curLine]->endY)/(linelist[curLine]->startX-linelist[curLine]->endX))>3) continue;
						if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
							vcolCheck = vcolCheck || (closestX == playerX) || abs_c((closestY - playerY) / (closestX - playerX))>0.5;
							if (!vcolCheck) continue;
							playerY = closestY + (closestY < playerY ? 10 : -10) * abs_c(sin(atan2(playerY - closestY,playerX - closestX)));
							if (closestY > playerY) jumpableFor = 25;
						}
					}
					if (tcolCheck && !vcolCheck) {
						playerY += abs_c(playerXVel / SUBSTEPS) * 2;
						for (curLine = levelStart[level]; curLine < levelEnd[level]; curLine++) {
							if (abs_c((linelist[curLine]->startY-linelist[curLine]->endY)/(linelist[curLine]->startX-linelist[curLine]->endX))>3) continue;
							if (lineCircle(linelist[curLine]->startX, linelist[curLine]->startY, linelist[curLine]->endX, linelist[curLine]->endY, playerX, playerY, 10)) {
								tcolCheck = (closestX == playerX) || abs_c((closestY - playerY) / (closestX - playerX))>0.5;
								vcolCheck = vcolCheck || tcolCheck;
								if (!tcolCheck) continue;
								playerY = closestY + (closestY < playerY ? 10 : -10) * abs_c(sin(atan2(playerY - closestY,playerX - closestX)));
								if (closestY > playerY) jumpableFor = 25;
							}
						}
						if (!vcolCheck) playerY -= abs_c(playerXVel / SUBSTEPS) * 2;
					}
					if (vcolCheck) {
						playerYVel = 0;
					} else if (jumpableFor) jumpableFor--;
					if (kDown & SCE_CTRL_CROSS) {
						jumpFor = 25;
					}
					else if (jumpFor) jumpFor--;
					if (jumpableFor && jumpFor) {
						playerYVel = xAdd * sqrt(42.3) * ((kHeld&SCE_CTRL_DOWN) ? -2 : -1);
						playerY -= abs_c(playerXVel) + 1;
						jumpableFor = 0;
						jumpFor = 0;
					}
					if (jumpableFor) rotSpd = ((playerX - oX) > 0 ? 0.1 : -0.1) * sqrt((playerX - oX) * (playerX - oX) + (playerY - oY) * (playerY - oY) * (jumpableFor ? 1 : 0));
					else rotSpd /= pow(1.1, 1/13.0);
					rot += rotSpd;
					cX += constrain(playerX, (SCREEN_WIDTH/scaleFactor) / 2 + bounds[level][0], bounds[level][2] - (SCREEN_WIDTH/scaleFactor) / 2) * 0.06;
					cX /= 1.06;
					if ((SCREEN_WIDTH/scaleFactor)/2 + bounds[level][0] > bounds[level][2] - (SCREEN_WIDTH/scaleFactor)/2) cX = bounds[level][0] + bounds[level][2] / 2;
					cY += constrain(playerY, (SCREEN_HEIGHT/scaleFactor) / 2 + bounds[level][1], bounds[level][3] - (SCREEN_HEIGHT/scaleFactor) / 2) * 0.06;
					cY /= 1.06;
					for (curLine = koStart[level]; curLine < koEnd[level]; curLine++) {
						if (lineCircle(linelistKO[curLine]->startX, linelistKO[curLine]->startY, linelistKO[curLine]->endX, linelistKO[curLine]->endY, playerX, playerY, 10)) 
							goto exitLoopLevel;
					}
					if (playerY > bounds[level][3]) goto exitLoopLevel;
					if (pointCircle(endPoint[level][0], endPoint[level][1], playerX, playerY, 12)) goto winMainLevel;
				}
				break;
				{
					winMainLevel:
					if (highScores[level] == 0 || levelTimer < highScores[level]) {
						highScores[level] = levelTimer;
						updateSave = true;
					}
					animID = enteredAnim;
					frames = 0;
					float x = max(endPoint[level][0] - cX + (SCREEN_WIDTH/scaleFactor) / 2, (SCREEN_WIDTH/scaleFactor) - (endPoint[level][0] - cX + (SCREEN_WIDTH/scaleFactor) / 2));
					float y = max(endPoint[level][1] - cY + (SCREEN_HEIGHT/scaleFactor) / 2, (SCREEN_HEIGHT/scaleFactor) - (endPoint[level][1] - cY + (SCREEN_HEIGHT/scaleFactor) / 2));
					float dist = sqrt(x * x + y * y);
					while (2 + frames * 10/6.0f < dist) {
						frames+=6;
						// Start Render
						vita2d_start_drawing();
						vita2d_clear_screen();
						// Draw Level
						drawLevel();
						// Draw Player
						vita2d_draw_fill_circle((playerX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
											(playerY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
											10 * scaleFactor, clrBlack);
						vita2d_draw_fill_circle((playerX - cX + (SCREEN_WIDTH/scaleFactor) / 2 + (cos(rot) * 5))*scaleFactor,
											(playerY - cY + (SCREEN_HEIGHT/scaleFactor) / 2 + (sin(rot) * 5))*scaleFactor,
											3 * scaleFactor, clrPlayer);
						// Draw Timer
						vita2d_draw_rectangle(0, 0, timerBlockOffset, 21.75f*scaleFactor, clrBlack);
						vita2d_draw_fill_circle(timerBlockOffset, 0, 21.75f*scaleFactor, clrBlack);
						drawString(to_str((levelTimer / 60.0f) / SUBSTEPS), 3*scaleFactor, 18*scaleFactor, 0.55f*scaleFactor, 2.0f*scaleFactor, clrWhite); 
						// Funni Animation
						vita2d_draw_fill_circle((endPoint[level][0] - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
											(endPoint[level][1] - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor,
											(2 + frames * 10/6.0f) * scaleFactor, clrPlayer);
						// Done Rendering!
						vita2d_end_drawing();
						vita2d_swap_buffers();
						vita2d_set_vblank_wait(1);
					}
					level++;
					if (level >= levels || goTo == toMenu) {
						level = 0;
						gameState = menu;
					}
					hasStarted = false;
					goto startFrame;
				}
				{
					exitLoopLevel:
					playerY = constrain(playerY, bounds[level][1], bounds[level][3]);
					if ((SCREEN_WIDTH/scaleFactor)/2 + bounds[level][0] > bounds[level][2] - (SCREEN_WIDTH/scaleFactor)/2)
						playerX = constrain(playerX, bounds[level][0] + (bounds[level][2] - (SCREEN_WIDTH/scaleFactor)) / 2, bounds[level][0] + (bounds[level][2] + (SCREEN_WIDTH/scaleFactor)) / 2);
					else
						playerX = constrain(playerX, bounds[level][0], bounds[level][2]);
					// Log It
				//	log << "Oof! Died after " << to_str(levelTimer/360.0f) << " seconds on level " << level << std::endl;
					animID = ded;
					frames = 0;
					while (frames < 24) {
						frames++;
						// Start Render
						vita2d_start_drawing();
						vita2d_clear_screen();
						// Draw Level
						drawLevel();
						// Funni Animation
						for (int i = 0; i++ < frames; ) {
							vita2d_draw_fill_circle((playerX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
												(playerY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor, (i / 24.0f) * 69 * scaleFactor,
												RGBA8(255, (int)floor(200 - 200 * (i / 24.0f)), 0,
															floatTo8Int(0.5 - (i / 48.0f))));
							vita2d_draw_fill_circle((playerX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
												(playerY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor, (i / 24.0f) * 69 * scaleFactor,
												RGBA8(255, 255, 255, floatTo8Int((i / 12.0f) - 1)));
						}
						// Draw Timer
						vita2d_draw_rectangle(0, 0, timerBlockOffset, 21.75f*scaleFactor, clrBlack);
						vita2d_draw_fill_circle(timerBlockOffset, 0, 21.75f*scaleFactor, clrBlack);
						drawString(to_str((levelTimer / 60.0f) / SUBSTEPS), 3*scaleFactor, 18*scaleFactor, 0.55f*scaleFactor, 2.0f*scaleFactor, clrWhite);
						// Done Rendering!
						vita2d_end_drawing();
						vita2d_set_vblank_wait(1);
						vita2d_swap_buffers();
					}
					frames = 0;
					while (frames < 10) {
						frames++;
						// Start Render
						vita2d_start_drawing();
						vita2d_clear_screen();
						// Draw Level
						drawLevel();
						vita2d_draw_rectangle(0, 0, timerBlockOffset, 21.75f*scaleFactor, clrBlack);
						vita2d_draw_fill_circle(timerBlockOffset, 0, 21.75f*scaleFactor, clrBlack);
						drawString(to_str((levelTimer / 60.0f) / SUBSTEPS), 3*scaleFactor, 18*scaleFactor, 0.55f*scaleFactor, 2.0f*scaleFactor, clrWhite);
						// Funni Animation
						vita2d_draw_fill_circle((playerX - cX + (SCREEN_WIDTH/scaleFactor) / 2)*scaleFactor,
												(playerY - cY + (SCREEN_HEIGHT/scaleFactor) / 2)*scaleFactor, 69 * scaleFactor,
												RGBA8(255, 255, 255, floatTo8Int(1-(frames / 10.0f))));
						// Done Rendering!
						vita2d_end_drawing();
						vita2d_set_vblank_wait(1);
						vita2d_swap_buffers();
					}
					hasStarted = false;
					goto startFrame;
				}
			}
			case menu: {
				if (animID == exitAnim) {
					levelTimer+=6;
					if (levelTimer > 144) {
						gameState = mainLevel;
						animID = enteredAnim;
						hasStarted = false;
						goto startFrame;
					}
				}
				if (!hasStarted) {
    				for (int i = 0; i < levels; i++)
    					levelButtons[i] = new button((i != 0 && (highScores[i] == 0 && highScores[i-1] == 0)) ? "x" : std::to_string(i+1),
    												((i % 6) * 28 + ((SCREEN_WIDTH/scaleFactor)*3/4 - 75)) * scaleFactor, ((i / 6) * 28 + 24) * scaleFactor, 24*scaleFactor, 24*scaleFactor, 0.5f * scaleFactor);
					if (updateSave) saveData(highScores);
					updateSave = false;
					hasStarted = true;
					animTimer = 0;
					currentMenu = mainMenu;
				}
				if (animID == exitAnim) break;
				switch (currentMenu) {
					case mainMenu: {
						if (onButton(menuButtons[0], startTouch.report[0].x/screenXMul, startTouch.report[0].y/screenYMul) && 
							((lastTouch.reportNum > touch.reportNum) && onButton(menuButtons[0], lastTouch.report[0].x/screenXMul, lastTouch.report[0].y/screenYMul))) {
							animID = exitAnim;
							levelTimer = 0;
							level = 0;
							goTo = nextLevel;
						}
						if (onButton(menuButtons[1], startTouch.report[0].x/screenXMul, startTouch.report[0].y/screenYMul) && 
							((lastTouch.reportNum > touch.reportNum) && onButton(menuButtons[1], lastTouch.report[0].x/screenXMul, lastTouch.report[0].y/screenYMul))) {
							currentMenu = levelSelect;
						}
						if (onButton(menuButtons[2], startTouch.report[0].x/screenXMul, startTouch.report[0].y/screenYMul) && 
							((lastTouch.reportNum > touch.reportNum) && onButton(menuButtons[2], lastTouch.report[0].x/screenXMul, lastTouch.report[0].y/screenYMul))) {
							currentMenu = colorPick;
						}
						break;
					}
					case levelSelect: {
						for (int i = 0; i < levels; i++)
							if (onButton(levelButtons[i], startTouch.report[0].x/screenXMul, startTouch.report[0].y/screenYMul) && 
								((lastTouch.reportNum > touch.reportNum) && onButton(levelButtons[i], lastTouch.report[0].x/screenXMul, lastTouch.report[0].y/screenYMul))
								&& !(i != 0 && (highScores[i] == 0 && highScores[i-1] == 0))) {
								animID = exitAnim;
								levelTimer = 0;
								level = i;
								goTo = toMenu;
							}
						if (kUp & SCE_CTRL_CIRCLE) currentMenu = mainMenu;
						break;
					}
					case colorPick: {
						if (touch.reportNum != 0) {
							if ((startTouch.report[0].y/screenYMul) > SCREEN_HEIGHT/2 - 40 * scaleFactor && (startTouch.report[0].y/screenYMul) < SCREEN_HEIGHT/2 - 20 * scaleFactor &&
								(startTouch.report[0].x/screenXMul) > 36 * scaleFactor + SCREEN_WIDTH / 2 && (startTouch.report[0].x/screenXMul) < 184 * scaleFactor + SCREEN_WIDTH / 2) {
								clrPlayer = RGBA8((int)constrain(((touch.report[0].x/screenXMul) - (46 * scaleFactor + SCREEN_WIDTH / 2))*2/scaleFactor, 0, 255), (clrPlayer>>((unsigned int)8) & 0xFF), (clrPlayer>>((unsigned int)16) & 0xFF), 0xff);
							}
							if ((startTouch.report[0].y/screenYMul) > SCREEN_HEIGHT/2 - 10 * scaleFactor && (startTouch.report[0].y/screenYMul) < SCREEN_HEIGHT/2 + 10 * scaleFactor &&
								(startTouch.report[0].x/screenXMul) > 36 * scaleFactor + SCREEN_WIDTH / 2 && (startTouch.report[0].x/screenXMul) < 184 * scaleFactor + SCREEN_WIDTH / 2) {
								clrPlayer = RGBA8((clrPlayer>>((unsigned int)0) & 0xFF), (int)constrain(((touch.report[0].x/screenXMul) - (46 * scaleFactor + SCREEN_WIDTH / 2))*2/scaleFactor, 0, 255), (clrPlayer>>((unsigned int)16) & 0xFF), 0xff);
							}
							if ((startTouch.report[0].y/screenYMul) > SCREEN_HEIGHT/2 + 20 * scaleFactor && (startTouch.report[0].y/screenYMul) < SCREEN_HEIGHT/2 + 40 * scaleFactor &&
								(startTouch.report[0].x/screenXMul) > 36 * scaleFactor + SCREEN_WIDTH / 2 && (startTouch.report[0].x/screenXMul) < 184 * scaleFactor + SCREEN_WIDTH / 2) {
								clrPlayer = RGBA8((clrPlayer>>((unsigned int)0) & 0xFF), (clrPlayer>>((unsigned int)8) & 0xFF), (int)constrain(((touch.report[0].x/screenXMul) - (46 * scaleFactor + SCREEN_WIDTH / 2))*2/scaleFactor, 0, 255), 0xff);
							}
						}
						if (kUp & SCE_CTRL_CIRCLE) {
							saveData(highScores);
							currentMenu = mainMenu;
						}
						break;
					}
				}
				break;
			}
		}
		
		// Start Render
		vita2d_start_drawing();
		vita2d_clear_screen();
		
		// Draw
		switch (gameState) {
			case mainLevel: {
				// Draw Level
				drawLevel();
				// Draw Player
				vita2d_draw_fill_circle(((SCREEN_WIDTH/scaleFactor) / 2 - cX + playerX)*scaleFactor,
									((SCREEN_HEIGHT/scaleFactor) / 2 - cY + playerY)*scaleFactor,
									(animID == -1 ? 10 : min(animTimer * 100, 10)) * scaleFactor, clrBlack);
				vita2d_draw_fill_circle(((SCREEN_WIDTH/scaleFactor) / 2 - cX + playerX + cos(rot) * (animID == -1 ? 5 : min(animTimer * 50, 5)))*scaleFactor,
									((SCREEN_HEIGHT/scaleFactor) / 2 - cY + playerY + sin(rot) * (animID == -1 ? 5 : min(animTimer * 50, 5)))*scaleFactor,
									(animID == -1 ? 3 : min(animTimer * 30, 3)) * scaleFactor, clrPlayer);
				// Draw Timer
				vita2d_draw_rectangle(0, 0, timerBlockOffset, 21.75f*scaleFactor, clrBlack);
				vita2d_draw_fill_circle(timerBlockOffset, 0, 21.75f*scaleFactor, clrBlack);
				drawString(to_str((levelTimer / 60.0f) / SUBSTEPS), 3*scaleFactor, 18*scaleFactor, 0.55f*scaleFactor, 2.0f*scaleFactor, clrWhite);
				if (animID == enteredAnim) vita2d_draw_rectangle(0, 0, (SCREEN_WIDTH), (SCREEN_HEIGHT), clrPlayer & RGBA8(255, 255, 255, floatTo8Int(max(0, 0.4 - animTimer)/0.4)));
				break;
			}
			case menu: {
				switch (currentMenu) {
					case mainMenu: {
						for (int i = 0; i < menuButtonCount; i++)
							drawButton(menuButtons[i], (touch.reportNum != 0 && onButton(menuButtons[i], startTouch.report[0].x/screenXMul, startTouch.report[0].y/screenYMul))?clrRed:clrBlack, 2.0f);
						break;
					}
					case levelSelect: {
						for (int i = 0; i < levels; i++)
							drawButton(levelButtons[i], (touch.reportNum != 0 && onButton(levelButtons[i], startTouch.report[0].x/screenXMul, startTouch.report[0].y/screenYMul))?clrRed:clrBlack, 2.0f);
						break;
					}
					case colorPick: {
						vita2d_draw_fill_circle(SCREEN_WIDTH * 3 / 2, SCREEN_HEIGHT/2, SCREEN_WIDTH, clrPlayer);
						vita2d_draw_fill_circle(46 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 - 30 * scaleFactor, 10 * scaleFactor, clrBlack);
						vita2d_draw_fill_circle(174 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 - 30 * scaleFactor, 10 * scaleFactor, RGBA8(255, 0, 0, 0xFF));
						vita2d_draw_rectangle_gradient(46 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 - 40 * scaleFactor, 128 * scaleFactor, 20 * scaleFactor, clrBlack, RGBA8(255, 0, 0, 0xFF), clrBlack, RGBA8(255, 0, 0, 0xFF));
						vita2d_draw_fill_circle(((clrPlayer>>(unsigned int)0 & 0xFF)/2+46)*scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 - 30 * scaleFactor, 5 * scaleFactor, clrWhite);
						drawLine(((clrPlayer>>(unsigned int)0 & 0xFF)/2+46) * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 - 45 * scaleFactor,
								((clrPlayer>>(unsigned int)0 & 0xFF)/2+46) * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 - 15 * scaleFactor, scaleFactor, clrPlayer);
						vita2d_draw_fill_circle(46 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, 10 * scaleFactor, clrBlack);
						vita2d_draw_fill_circle(174 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, 10 * scaleFactor, RGBA8(0, 255, 0, 0xFF));
						vita2d_draw_rectangle_gradient(46 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 - 10 * scaleFactor, 128 * scaleFactor, 20 * scaleFactor, clrBlack, RGBA8(0, 255, 0, 0xFF), clrBlack, RGBA8(0, 255, 0, 0xFF));
						vita2d_draw_fill_circle(((clrPlayer>>(unsigned int)8 & 0xFF)/2+46)*scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2, 5 * scaleFactor, clrWhite);
						drawLine(((clrPlayer>>(unsigned int)8 & 0xFF)/2+46)*scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 - 15 * scaleFactor,
								((clrPlayer>>(unsigned int)8 & 0xFF)/2+46)*scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 + 5 * scaleFactor, scaleFactor, clrPlayer);
						vita2d_draw_fill_circle(46 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 + 30 * scaleFactor, 10 * scaleFactor, clrBlack);
						vita2d_draw_fill_circle(174 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 + 30 * scaleFactor, 10 * scaleFactor, RGBA8(0, 0, 255, 0xFF));
						vita2d_draw_rectangle_gradient(46 * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 + 20 * scaleFactor, 128 * scaleFactor, 20 * scaleFactor, clrBlack, RGBA8(0, 0, 255, 0xFF), clrBlack, RGBA8(0, 0, 255, 0xFF));
						vita2d_draw_fill_circle(((clrPlayer>>(unsigned int)16 & 0xFF)/2+46) * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 + 30 * scaleFactor, 5 * scaleFactor, clrWhite);
						drawLine(((clrPlayer>>(unsigned int)16 & 0xFF)/2+46) * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 + 15 * scaleFactor,
								((clrPlayer>>(unsigned int)16 & 0xFF)/2+46) * scaleFactor + SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 + 45 * scaleFactor, scaleFactor, clrPlayer);
						break;
					}
				}
				drawString("VECTORIA", SCREEN_WIDTH/4-getWidth("VECTORIA", scaleFactor, 4*scaleFactor)/2 + 13*scaleFactor, SCREEN_HEIGHT/2 + (14 * sin(sin(sin(animTimer * 2.342))) + 13), scaleFactor, 4*scaleFactor, clrBlack);
				drawString("1.0-a2", 2*scaleFactor, SCREEN_HEIGHT - 2*scaleFactor, 0.6f*scaleFactor, 2.0f*scaleFactor, clrBlack);
				if (animID == enteredAnim) vita2d_draw_rectangle(0, 0, (SCREEN_WIDTH), (SCREEN_HEIGHT), clrPlayer & RGBA8(255, 255, 255, floatTo8Int(max(0, 0.4 - animTimer)/0.4)));
				if (animID == gameStart) vita2d_draw_rectangle(0, 0, (SCREEN_WIDTH), (SCREEN_HEIGHT), RGBA8(255, 255, 255, floatTo8Int(max(0, 0.4 - animTimer)/0.4)));
				if (animID == exitAnim) vita2d_draw_rectangle(0, 0, (SCREEN_WIDTH), (SCREEN_HEIGHT), clrPlayer & RGBA8(255, 255, 255, floatTo8Int(levelTimer / 144.0f)));
				break;
			}
		}
		
        if (touch.reportNum != 0) {
        	drawLine(touch.report[0].x/screenXMul, touch.report[0].y/screenYMul,
        		startTouch.report[0].x/screenXMul, startTouch.report[0].y/screenYMul, scaleFactor, clrPlayer);
        }
        
        // Done Rendering!
		vita2d_end_drawing();
		vita2d_swap_buffers();
		vita2d_set_vblank_wait(1);
	}
	
	// End Log
    log.close();
	
	// Save on exit
	saveData(highScores);
	
	return 0;
}