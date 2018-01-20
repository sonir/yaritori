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
#define DEBUG_MODE
#define DUMMY_AG_A_NUM 12//1000
#define DUMMY_AG_B_NUM 5//1000

#define PERFORMANCE_MODE
#define GISMO_UPDATE_INTERVAL 0.033

//SCREEN SETUP
#define SC_WITDH 1024
#define SC_HEIGHT 768

//OSC
#define PORT 57139
#define NUM_MSG_STRINGS 20

//#define CONTAINER_MAX 128 //Size of Buffer for Shapes
#define CONTAINER_MAX AG_MAX*128 //Size of Buffer for Shapes



/// Includes ///

//Basics
#include <stdio.h>
#include <cassert>
#include "ofMain.h"

//Addons
#include "ofxOsc.h"
//Gismo
#include "ofxGismo.h"

//vSyn
#include "shape.h"
#include "osc2shape.hpp"
#include "drawer.hpp"
#include "cam_func.hpp"
#include "Particle.hpp"


/// Yaritori Modules ///

// Receiving message from network
#include "Network.hpp"

//Convert from shape_t to agent
#include "Shape2Agent.hpp"

//Test Class
#include "Test.hpp"

//Metro
#include "Metro.hpp"

//AudioTriger with OSC
#include "Sound.hpp"

//Drawing
#include "drawAgents.hpp"
#include "DrawPerformance.hpp"
#include "DrawAgentsWithChar.hpp"

//Sound
#include "SoundTrigger.hpp"


class VSyn : public Event {
 
    public:
        void setup();
        void update();
        void draw();
        void initWindowSize();
        int trigger(void *args){
            
            ag_shape_t *tmp = (ag_shape_t *)args;
            ag_shape_t tmp2 = *tmp;
            addAgShape(tmp2);
            //make sound
            int index = gismo.agents.count;
            sound_t snd = shape2sound(tmp2, index); //Song genre and song with the shape and ag_id
            soundTrigger.sounds[index]= snd; //Store sound int sound buffer
            
        }

    
        shapeContainer shapes[CONTAINER_MAX];
        ofColor colors[CONTAINER_MAX];
        ofxOscReceiver receiver;
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
        //ScreenManagement
        int screen_w;
        int screen_h;
    
        //Particle
        Particle particle;
    
        //CAMERA CONTROL
        ofEasyCam cam;
        bool cam_flg;
        ofVec3f pov;
        ofVec3f look;
    
        //For Performance
        PerformanceManager performanceManager;
        //DrawPerformance drawPerformance;
        line_t aLine;
        Bullet *bullet;
        Metro *metro;

    
    
    private:
        void initShapes(int max_num);
        void initColors(int max_num);
        void test(); //Method for Any Test
        //Variables
        Test *myTest; //Test Instance
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        DrawAgentsWithChar drawAgentsWithChar;
        Sound sound; //AudioTrigger with OSC
    
        //CCMA
        //To store the received shape
        ag_shape_t ag_shapes[AG_MAX];
        int ag_shapes_count = 0;
        void addAgShape(ag_shape_t shape);
    
        //Sound
        SoundTrigger soundTrigger;
    
};

#endif /* VSyn_hpp */
