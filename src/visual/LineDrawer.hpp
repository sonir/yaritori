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
    
    posi_t myPos, targetPos;
    
private:
    void update();
    
    
    float currentPhase, theta;

    ofVec2f verts[TURN_NUM + 2]; // + myPos + targetPos
    ofVbo vbo;
    
    TimedInterpolation interpolation;
    
    float aspect; 
};



#endif /* LineDrawer_hpp */
