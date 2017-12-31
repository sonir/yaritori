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
    
    void setup();
    void draw();
    
    float centerX, centerY;
    bool isRunning;


private:
    void setSpeed();
    void updateVertex(float sp);
    
    float r_speed;

    static const int res = 64;
    static constexpr float theta = 2. * PI * 0.015625;   // / 64
    
    static const int rippleNum = 2;
    
    ofVec2f verts[res * rippleNum];
    ofIndexType indices[res * rippleNum * 2];
    ofFloatColor cols[res * rippleNum];
    ofVbo vbo;  //1 ripple <-> 1 vbo
    
    static constexpr float fadeOutRatio = 0.4;
    static constexpr float speed = 4.;  //pixel
    
    static constexpr float durMin = 700; //msec
    static constexpr float durMax = 2800;   //1300
    
    float dur;  //Duration
    
    float lag[rippleNum];
    
    static constexpr float lagMin = 0.1;    //1. <-> dur
    static constexpr float lagMax = 0.15;
    
    float sp_noise[rippleNum];
    
    static constexpr float sp_noiseMin = 1.5;
    static constexpr float sp_noiseMax = 1.7;
    
    TimedInterpolation interpolation;
    float currentTime;
    
    float aspect;   //aspect ratio
};

#endif /* RippleDrawer_hpp */
