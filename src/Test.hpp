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
//#include "Fade.hpp"

class Test {

    public:
        Test(Sound *pSnd);
        void setup();
        void run();
        void update();
    
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        Sound *sound;
//        Fade fade;
    
};




#endif /* Test_hpp */
