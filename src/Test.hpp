//
//  Test.hpp
//  yaritori
//
//  Created by sonir on 12/27/17.
//
//

#ifndef Test_hpp
#define Test_hpp

#include <stdio.h>
#include <cassert>
#include "ofxGismo.h"
#include "Sound.hpp"
#include "drawAgents.hpp"
#include "RippleManager.hpp"


class Test {

    public:
        Test(Sound *pSnd, RippleManager *pRipple);
        void setup();
        void run();
        void runVisualTest(visual_container_t* visual);
        void update();
    void invert();
    
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        Sound *sound;
    
        RippleManager *ripple;
        
    
};




#endif /* Test_hpp */
