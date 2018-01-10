//
//  RippleDrawer.hpp
//  ripple
//
//  Created by moha with hana on 2017/12/30.
//
//

#ifndef RippleDrawer_hpp
#define RippleDrawer_hpp

#include "ofMain.h"
#include "timed_interpolation.hpp"
#include "ofxGismo.h"
#include "ScreenManager.hpp"

class RippleDrawer{
public:
    RippleDrawer();
    
    void initVertices();
    void initStatus();
    void init();
    void update();
    void bang(float x, float y);
    
    float centerX, centerY;
    bool isRunning;
    bool colorState;
    
    static const int res = 64;
    static const int rippleNum = 2;
    
    ofVec2f verts[res * rippleNum];
    ofIndexType indices[res * rippleNum * 2];
    ofFloatColor cols[res * rippleNum];

private:
    void updateColor();
    void updateVertex();
    
    static constexpr float theta = 2. * PI * 0.015625;   // / 64
    
    float radius;    //1. <-> CANVAS_HEIGHT
    static constexpr float r_Min = 0.5;
    static constexpr float r_Max = 0.55;
    
    float duration; //sec
    static constexpr float durMin = 0.5;
    static constexpr float durMax = 1.2;
    
    float lag[rippleNum];    //1. <-> duration
    static constexpr float lagMin = 0.1;
    static constexpr float lagMax = 0.25;
    
    float sp_noise[rippleNum];   //conf of speed for second ripple
    static constexpr float sp_noiseMin = 1.5;
    static constexpr float sp_noiseMax = 1.7;
    
    static constexpr float fadeOutRatio = 0.4;  //1 <-> duration
    
    TimedInterpolation interpolation;   //return 0. to 1. during "duration"
    float currentTime;
    float currentRadius;
    
    float aspect;   //aspect ratio, acquired from gismomanager
};

#endif /* RippleDrawer_hpp */
