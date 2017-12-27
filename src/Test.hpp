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

class Test {

    public:
        Test(Sound *pSnd);
        void setup();
        void run();
        void update();
    
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        Sound *sound;
    
};




#endif /* Test_hpp */
