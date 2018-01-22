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
    
    void setWindowPlace(int window, float x, float y);
    void resetWindowPlace(int window);
    
    void setMask(int window, int vertexId, float x, float y);
    void mask();
    
    void swap(int window, swap_direction direction);
    void swap(int window, float x, float y);
    void setSwapDuration(float go, float out, float back);
    
    void drawBackground();
    bool colorState;
    
    void setFullScreen();
    ofColor getDrawColor();
    
    float width, height;
    
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
    ofVec2f texture_originPos[3];
    
    pos_t pos[3];  //up-left point of window
    
    
    float swapDur_go, swapDur_out, swapDur_back;    //msec
    
    pos_t startPos[3];    //pos when called as start pos
    pos_t endPos[3];
    int state_w[3];
    int state_h[3];
    TimedInterpolation interpolation_w[3];
    TimedInterpolation interpolation_h[3];
};

#endif /* ScreenManager_hpp */
