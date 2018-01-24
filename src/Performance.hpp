//
//  Performance.hpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

//#ifndef Performance_hpp
//#define Performance_hpp

#pragma once

#define PERFORMER_NUM 5
#define POINT_MAX 8

#include <stdio.h>
#include "ofxGismo.h"
#include "Bullet.hpp"

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
int count_ring(int now, int max);

//
typedef enum performer_e { PIANO, TROMBONE, GUITAR, BASS, DRUMS } performer_e;



class Performers : public Event{
    
    public:

        posi_t position[PERFORMER_NUM];
    
        Performers(){ // Constructor
            
            //Init performers positions
            position[PIANO].x = PIANO_X;
            position[PIANO].y = PIANO_Y;

            position[TROMBONE].x = TROMBONE_X;
            position[TROMBONE].y = TROMBONE_Y;
            
            position[GUITAR].x = GUITAR_X;
            position[GUITAR].y = GUITAR_Y;
            
            position[BASS].x = BASS_X;
            position[BASS].y = BASS_Y;

            position[DRUMS].x = DRUMS_X;
            position[DRUMS].y = DRUMS_Y;
            
        }
    
        int trigger(void *args){ //Event for set performers' position
            
            param_u *params = (param_u *)args;
            performer_e perf = (performer_e)params[0].ival;
            position[params[perf].ival].x = params[1].fval;
            position[params[perf].ival].y = params[2].fval;
            
        }

    
};

class PerformanceManager : public Event {
    
    public:

        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        Performers performers;
        pline_t lines[AG_MAX];
        pline_t invertedLines[AG_MAX];
        Bullet bullets[AG_MAX];
        Bullet reverseBullets[AG_MAX];
    
        PerformanceManager (){
            
            gismo.eventAdd("/sjq/setPosition" , &performers);
            gismo.eventAdd("/sjq/atk" , this);
            
            //Example of invoking </setPerformerPosition>
            
                // param_u tmp[3];
                // tmp[0].ival = PIANO;
                // tmp[1].fval = 0.5f;
                // tmp[2].fval = 0.51f;
                // gismo.bang("/setPerformerPosition" , tmp);
            
            //SetupEvents
            auto f = [&](void* args){ //<- keep this desctiption
                //draw your code
                param_u *params = (param_u *)args;
                int bang_id = params[0].ival;
                bullets[bang_id].bang();
            };
            gismo.lambdaAdd("/bullet_bang", f);

            auto f2 = [&](void* args){ //<- keep this desctiption
                //draw your code
                param_u *params = (param_u *)args;
                int bang_id = params[0].ival;
                for(int i=0; i<AG_MAX;i++){
                    
                    if(i%PERFORMER_NUM == bang_id){
                        ag_t *ag = gismo.getAgent(i);
                        if(ag->active) reverseBullets[i].bang();
                    }
                }
                
            };
            gismo.lambdaAdd("/bullet_bang_return", f2);

                
        }
    
        void updateLines();
        void updateLinesInverted();
        void performerBang(performer_e perf);
    
    
        int trigger(void *args){ //Event for set performers' position
            
            param_u *param = (param_u *)args;
            performer_e perf = (performer_e)param->ival;
            performerBang(perf);
            
        }

    
};

//#endif /* Performance_hpp */
