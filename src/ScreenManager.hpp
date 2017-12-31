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
constexpr int WINDOW_WIDTH = 1024;
constexpr int WINDOW_HEIGHT = 728;  //This is 1.0

constexpr int SCREEN_LENGTH_W = 4000;
constexpr int SCREEN_LENGTH_H = 4000;
constexpr int CANVAS_LENGTH_W = 4200 * 4;
constexpr int CANVAS_LENGTH_H = 4200;

constexpr float screen_margin = float((CANVAS_LENGTH_H - SCREEN_LENGTH_H) / CANVAS_LENGTH_H) * 0.5 * WINDOW_HEIGHT; // 4200 / 4200

constexpr int CANVAS_WIDTH = WINDOW_HEIGHT * 3 + screen_margin * 4;
constexpr int CANVAS_HEIGHT = WINDOW_HEIGHT +  screen_margin * 2;
constexpr int SCREEN_CENTER = WINDOW_HEIGHT * 0.5;

//for black box
constexpr int DISPLAY_MARGIN_X = WINDOW_HEIGHT;
constexpr int DISPLAY_MARGIN_W = WINDOW_WIDTH - WINDOW_HEIGHT;

enum screen_pos_e {
    SCREEN_POS_LEFT,
    SCREEN_POS_CENTER,
    SCREEN_POS_RIGHT,
};

static ofVec2f leftScreen = ofVec2f(-screen_margin, screen_margin);
static ofVec2f centerScreen = ofVec2f(-(WINDOW_HEIGHT + screen_margin * 2), screen_margin);
static ofVec2f rightScreen = ofVec2f(-(WINDOW_HEIGHT*2 + screen_margin * 3), screen_margin);


static ofVec2f targetScreen = leftScreen;

void setScreenPos(screen_pos_e screenPos);
void screenBegin();
void screenEnd();




#endif /* ScreenManager_hpp */
