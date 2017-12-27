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

constexpr int SCREEN_WIDTH = 1280;
constexpr int SCREEN_HEIGHT = 720;
constexpr int CANVAS_WIDTH = SCREEN_WIDTH * 3;
constexpr int CANVAS_HEIGHT = SCREEN_HEIGHT;
constexpr int SCREEN_CENTER = SCREEN_WIDTH * 0.5;

namespace {
    const int NAMED_IND = 10;
}


enum screen_pos_e {
    SCREEN_POS_LEFT,
    SCREEN_POS_CENTER,
    SCREEN_POS_RIGHT,
};

static ofVec2f leftScreen = ofVec2f(0, 0);
static ofVec2f centerScreen = ofVec2f(-SCREEN_WIDTH, 0);
static ofVec2f rightScreen = ofVec2f(-SCREEN_WIDTH * 2, 0);
static ofVec2f targetScreen = leftScreen;

void setScreenPos(screen_pos_e screenPos);
void screenBegin();
void screenEnd();




#endif /* ScreenManager_hpp */
