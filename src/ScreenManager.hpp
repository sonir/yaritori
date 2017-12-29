//
//  ScreenManager.hpp
//  viewPortTest
//
//  Created by Hana on 2017/12/25.
//
//

#ifndef ScreenManager_hpp
#define ScreenManager_hpp

#include "ofMain.h"


//Variables for screen position
constexpr int SCREEN_WIDTH = 1024;
constexpr int SCREEN_HEIGHT = 768;  //This is 1.0

constexpr int SCREEN_LENGTH_W = 4000;
constexpr int SCREEN_LENGTH_H = 4000;
constexpr int CANVAS_LENGTH_W = 4200 * 4;
constexpr int CANVAS_LENGTH_H = 4200;

constexpr float screen_margin = float((CANVAS_LENGTH_H - SCREEN_LENGTH_H) / CANVAS_LENGTH_H) * 0.5 * SCREEN_HEIGHT; // 4200 / 4200

constexpr int CANVAS_WIDTH = SCREEN_HEIGHT * 3 + screen_margin * 4;
constexpr int CANVAS_HEIGHT = SCREEN_HEIGHT +  screen_margin * 2;
constexpr int SCREEN_CENTER = SCREEN_WIDTH * 0.5;


//constexpr float screen_ratio = 4.0 / 4.0;
//constexpr int leftscreen_x = screen_margin;
//constexpr int centerScreen_x = sc1_x + screenWidth + screen_margin;
//constexpr int rightScreen_x = sc2_x + screenWidth + screen_margin;


//for black box
constexpr int DISPLAY_MARGIN_X = SCREEN_HEIGHT;
constexpr int DISPLAY_MARGIN_W = SCREEN_WIDTH - SCREEN_HEIGHT;

enum screen_pos_e {
    SCREEN_POS_LEFT,
    SCREEN_POS_CENTER,
    SCREEN_POS_RIGHT,
};

static ofVec2f leftScreen = ofVec2f(screen_margin, screen_margin);
static ofVec2f centerScreen = ofVec2f(leftScreen.x + SCREEN_HEIGHT + screen_margin, screen_margin);
static ofVec2f rightScreen = ofVec2f(centerScreen.x + SCREEN_HEIGHT + screen_margin, screen_margin);

//leftScreen.x = screen_margin;
//leftScreen.y = screen_margin
//centerScreen.x = leftScreen.x + screenWidth + screen_margin;
//centerScreen.y = screen_margin;
//rightScreen.x = centerScreen.x + screenWidth + screen_margin;
//rightScreen.y = screen_margin;


static ofVec2f targetScreen = leftScreen;

void setScreenPos(screen_pos_e screenPos);
void screenBegin();
void screenEnd();




#endif /* ScreenManager_hpp */
