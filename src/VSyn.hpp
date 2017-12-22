//
//  VSyn.hpp
//  vSyn
//
//  Created by sonir on 9/8/17.
//
//

#ifndef VSyn_hpp
#define VSyn_hpp

//Set running mode
//#define DEBUG_MODE


//Basics
#include <stdio.h>
#include <cassert>
#include "ofMain.h"
#include "ofxOsc.h"

//Addons
#include "ofxGismo.h"

//vSyn
#include "shape.h"
#include "osc2shape.hpp"
#include "drawer.hpp"
#include "cam_func.hpp"
#include "Particle.hpp"

//Gismo
#include "drawAgents.hpp"

//AudioTriger with OSC
#include "Sound.hpp"



#define PORT 57139
#define NUM_MSG_STRINGS 20

//#define CONTAINER_MAX 128 //Size of Buffer for Shapes
#define CONTAINER_MAX AG_MAX //Size of Buffer for Shapes


class VSyn {
 
    public:
        void setup();
        void update();
        void draw();
        void initWindowSize();
    
        shapeContainer shapes[CONTAINER_MAX];
        ofColor colors[CONTAINER_MAX];
        ofxOscReceiver receiver;
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
        //Particle
        Particle particle;
    
        //CAMERA CONTROL
        ofEasyCam cam;
        bool cam_flg;
        ofVec3f pov;
        ofVec3f look;
    
    
    private:
        void initShapes(int max_num);
        void initColors(int max_num);
        void test(); //Method for Any Test
        //Variables
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        Sound sound; //AudioTrigger with OSC
    
    motion_manager_t motionManager;
    
};

#endif /* VSyn_hpp */
