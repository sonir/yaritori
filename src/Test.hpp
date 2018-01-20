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
#include "ag_shape.h"
#include "Sound.hpp"
#include "Shape2Agent.hpp"
#include "Performance.hpp"
#include "getArraySize.h"
#include "SoundTrigger.hpp"


class Test {

    public:
        Test(Sound *pSnd);
        void setup();
        void run();
        void runSubTest(void* args);
        void update();
    
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        Sound *sound;
//        SoundTrigger soundTest;
    
    
        int arg1;
        int arg2;
    
};




#endif /* Test_hpp */
