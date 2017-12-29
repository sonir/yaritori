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
    
    void draw();
    void bang(float posX, float posY);  //define each value as 0. - 1.
    int trigger(void *args);
    
private:
    static constexpr float lineWidth = 0.8; //pixel
    
    static const int NUM = 128; //max num of ripples that can be drawn at once
    
    RippleDrawer ripples[NUM];
};


#endif /* RippleDrawer_hpp */
