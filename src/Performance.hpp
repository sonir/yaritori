//
//  Performance.hpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#ifndef Performance_hpp
#define Performance_hpp

#define PERFORMER_NUM 5
#define POINT_MAX 8

#include <stdio.h>
#include "ofxGismo.h"
#include "Fade.hpp"

//DRAWING PARAMS
#define SIZE_OF_PERFORMER_INDICATE 0.01f

//SETUP PERFORMERS POSITION
#define PIANO_X 0.0f
#define PIANO_Y 0.0f
#define TROMBONE_X 0.25f
#define TROMBONE_Y 0.25f
#define GUITAR_X 0.5f
#define GUITAR_Y 0.5f
#define BASS_X 0.75f
#define BASS_Y 0.75f
#define DRUMS_X 1.0f
#define DRUMS_Y 1.0f



//Function Prototypes
posi_t moveOnLine(float fval, float a, float b, float x, float y);
int count_ring(int now, int max);

//
typedef enum performer_e { PIANO, TROMBONE, GUITAR, BASS, DRUMS } performer_e;

typedef struct line_t {
    
    posi_t node_a;
    posi_t node_b;
    
}line_t;


class Bullet {
    
    public:
        Bullet(){
            
            route.node_a.x = 0.5f;
            route.node_a.y = 0.5f;
            route.node_b.x = 1.0f;
            route.node_b.y = 0.0f;
            
            
        }
        line_t route;
        Fade fade;
        void bang();
        void set(int ms);
        posi_t update();
        posi_t update(line_t aLine);
    
    
};

class Performers : public Event{
    
    public:

        agent_buf_t pfm;
    
        Performers(){ // Constructor
            
            //Init performers positions
            initAgentActive(&pfm.buf[PIANO]);
            pfm.buf[PIANO].posi.x = PIANO_X;
            pfm.buf[PIANO].posi.y = PIANO_Y;

            initAgentActive(&pfm.buf[TROMBONE]);
            pfm.buf[TROMBONE].posi.x = TROMBONE_X;
            pfm.buf[TROMBONE].posi.y = TROMBONE_Y;
            
            initAgentActive(&pfm.buf[GUITAR]);
            pfm.buf[GUITAR].posi.x = GUITAR_X;
            pfm.buf[GUITAR].posi.y = GUITAR_Y;
            
            initAgentActive(&pfm.buf[BASS]);
            pfm.buf[BASS].posi.x = BASS_X;
            pfm.buf[BASS].posi.y = BASS_Y;

            initAgentActive(&pfm.buf[DRUMS]);
            pfm.buf[DRUMS].posi.x = DRUMS_X;
            pfm.buf[DRUMS].posi.y = DRUMS_Y;
            
            pfm.count = PERFORMER_NUM;
            
            
        }
    
        int trigger(void *args){ //Event for set performers' position
            
            param_u *params = (param_u *)args;
            performer_e perf = (performer_e)params[0].ival;
            pfm.buf[params[perf].ival].posi.x = params[1].fval;
            pfm.buf[params[perf].ival].posi.y = params[2].fval;
            
        }

    
};

class PerformanceManager {
    
    public:

        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        Performers performers;
        line_t lines[AG_MAX];
        Bullet bullets[AG_MAX];
    
        PerformanceManager (){
            
            gismo.eventAdd("/setPerformerPosition" , &performers);
            
            //Demo to invoking set
            // param_u tmp[3];
            // tmp[0].ival = PIANO;
            // tmp[1].fval = 0.5f;
            // tmp[2].fval = 0.51f;
            // gismo.bang("/setPerformerPosition" , tmp);
            
        }
    
    
};

#endif /* Performance_hpp */
