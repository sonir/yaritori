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
#include "timed_interpolation.hpp"
#include "screen_setup.h"

//Define Structs
typedef struct pos_t {
    
    float x;
    float y;
    
} pos_t;

static bool drawWhiteBack = true;
void invertBackground();

typedef enum{UP, DOWN, RIGHT, LEFT} swap_direction;

class ScreenManager{
public:
    ScreenManager();
    void begin(int window);
    void end(int window);
    void draw();

    void swap(int window, swap_direction direction);
    void setSwapDuration(float go, float out, float back);
    void setOriginPosition(pos_t o1, pos_t o2, pos_t o3);
    void setZoom(int window, pos_t centerPos, float ratio);
    void resetScreen(int window);
    
    void drawBackground();
    bool colorState;
    
    float swapDur_go, swapDur_out, swapDur_back;    //msec
    void setFullScreen();
    
private:
    void init();
    void initFbo();
    void initStatus();
    void swap_cal();
    
    ofFbo fbo[3];
    ofMesh mesh[3];
//    ofShader shader;
    
    pos_t pos[3];  //up-left point of window
    
    pos_t centerPos[3];
    pos_t centerPos_origin[3]; //standard pos
    float ratio[3];
    
    pos_t startPos[3];    //pos when called as start pos
    pos_t endPos[3];
    int state_w[3];
    int state_h[3];
    TimedInterpolation interpolation_w[3];
    TimedInterpolation interpolation_h[3];
};

#endif /* ScreenManager_hpp */
