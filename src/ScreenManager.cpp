//
//  ScreemManager.cpp
//  viewPortTest
//
//  Created by Hana on 2017/12/25.
//
//

#include "ScreenManager.hpp"


void setScreenPos(screen_pos_e screenPos) {
    switch (screenPos) {
        case SCREEN_POS_LEFT:
            targetScreen = leftScreen;
            break;
        case SCREEN_POS_CENTER:
            targetScreen = centerScreen;
            break;
        case SCREEN_POS_RIGHT:
            targetScreen = rightScreen;
            break;
        default:
            break;
    }
}

void screenBegin() {
    ofPushMatrix();
    ofTranslate(targetScreen);
}


void screenEnd() {
    
    ofPopMatrix();
    
    ofSetColor(0);
    ofDrawRectangle(DISPLAY_MARGIN_X, 0, DISPLAY_MARGIN_W, SCREEN_HEIGHT);
    
}

