//
//  rippleDrawer.hpp
//  ripple_1
//
//  Created by Momoha Matsuhashi on 2017/12/12.
//
//

#ifndef RippleManager_hpp
#define RippleManager_hpp

#include "ofMain.h"
#include "RippleDrawer.hpp"
#include "ofxGismo.h"

class RippleManager : public Event {
public:
    RippleManager();
    void setEvents();
    void setColor(float c);
    
    void initVertices();
    void initIndices();
    void initVbo();
    void initStatus();
    void init();
    
    void update();
    void draw();
    
    void bang(float posX, float posY);  //define each value as 0. - 1.
    int trigger(void *args);     // To be called from eventhandler
    
    void invert();
    
    
private:
    static constexpr float lineWidth = 0.8; //pixel
    
    static const int res = 64;
    static const int rippleNum = 2;
    static const int NUM = 3000; //max num of ripples that can be drawn at once
    
    bool colorState;    //true: black, false: white(ripples)
    float color;
    
    int activeNumCounter;
    
    RippleDrawer ripples[NUM];
    
    ofVec2f verts[res * rippleNum * NUM];
    ofIndexType indices[res * rippleNum * NUM * 2];
    ofFloatColor cols[res * rippleNum * NUM];
    ofVbo vbo;
};


#endif /* RippleDrawer_hpp */
