//
//  LineDrawer.hpp
//  ccma_line
//
//  Created by Momoha Matsuhashi on 2018/01/05.
//
//

#ifndef LineDrawer_hpp
#define LineDrawer_hpp

#include "ScreenManager.hpp"
#include "ofMain.h"
#include "timed_interpolation.hpp"
#include "ofxGismo.h"
#include "animation_setup.hpp"


class LineDrawer{
public:
    LineDrawer();
    
    void lineTo(float target_x, float target_y);
    void invert();
    void setColor(float _c);
    void setEvents();
    
    posi_t myPos, targetPos;
    
    bool colorState;
    ofFloatColor color;
    
private:
    void update();
    
    int turn_num;
    float currentPhase, theta;
    
    ofVec2f verts[TURN_NUM_MAX + 2]; // + myPos + targetPos
    ofFloatColor cols[TURN_NUM_MAX + 2];
    ofVbo vbo;
    
    TimedInterpolation interpolation;
    
    float aspect;
};



#endif /* LineDrawer_hpp */
