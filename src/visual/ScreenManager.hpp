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
#include "ofxGismo.h"
#include "drawer.hpp"

//Define Structs
typedef struct pos_t {
    
    float x;
    float y;
    
} pos_t;

static bool drawWhiteBack = true;
void invertBackground();

typedef enum{UP, RIGHT, DOWN, LEFT} swap_direction;



class ScreenManager {
public:
    ScreenManager();
    void setup();
    void begin();
    void end();
    void draw();
    
    void setMask(int window, int vertexId, float x, float y);
    void mask();
    
    void swap(int window, swap_direction direction);
    void swap(int window, float x, float y);
    void setSwapDuration(float go, float out, float back);
    //    void setOriginPosition(pos_t o1, pos_t o2, pos_t o3);
    //    void setZoom(int window, pos_t centerPos, float ratio);
    //    void resetScreen(int window);
    
    void drawBackground();
    bool colorState;
    
    void setFullScreen();
    ofColor getDrawColor();
    
private:
    void init();
    void initFbo();
    void initStatus();
    void initMask();
    
    void swap_cal();
    void setEvents();
    
    ofVbo mask_vbo;
    ofIndexType mask_indices[6 * 4 * 3];
    ofVec2f mask_pos[4 * 3];
    ofVec2f mask_verts[8 * 3];
    ofFloatColor mask_cols[8 * 3];
    
    ofFbo fbo;
    ofMesh mesh[3];
    
    pos_t pos[3];  //up-left point of window
    
    //    pos_t centerPos[3];
    //    pos_t centerPos_origin[3]; //standard pos
    //    float ratio[3];
    
    float swapDur_go, swapDur_out, swapDur_back;    //msec
    
    pos_t startPos[3];    //pos when called as start pos
    pos_t endPos[3];
    int state_w[3];
    int state_h[3];
    TimedInterpolation interpolation_w[3];
    TimedInterpolation interpolation_h[3];
};

#endif /* ScreenManager_hpp */
