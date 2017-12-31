//
//  drawAgents.hpp
//  yaritori
//
//  Created by sonir on 12/10/17.
//
//

#ifndef drawAgents_h
#define drawAgents_h

#include <assert.h>
#include "ofMain.h"
#include "ofxGismo.h"
#include "AgentMotion.hpp"
#include "ScreenManager.hpp"

struct motion_manager_t {
    int width;
    int height;
    AgentMotion agentMotion[AG_MAX];
};


void drawAgents(GismoManager *gismo, motion_manager_t *motion){
    int count = gismo->agents.count;
    ag_t *agents = gismo->getAgents(); //sets agents pointer
    ag_t *ag;
    //gismo->agents.count = 1000;

    
    for(int i =0; i<count; i++){
        
        ag = agents; //Set agent address

//        string condition = "a";
//        ofDrawBitmapString( condition, ag->posi.x, ag->posi.y);
//        int tmp_x = (int)( ag->posi.x * (float)ofGetScreenWidth() );
//        int tmp_y = (int)( ag->posi.y * (float)ofGetScreenHeight() );
//        std::cout << tmp_x << " , " << tmp_y << std::endl;
//        ofDrawBitmapString( "f", 100, 200);
        
        if(ag->active){
            //square(ag->posi.x, ag->posi.y, ag->size, 0.0f, true);
            motion->agentMotion[i].nodes.scale_x = ag->posi.x;
            motion->agentMotion[i].nodes.scale_y = ag->posi.y;
            motion->agentMotion[i].nodes.size = ag->size;
            motion->agentMotion[i].nodes.mov = ag->mov;
            motion->agentMotion[i].width_rate = &gismo->width_rate;
           
            motion->agentMotion[i].update();
            motion->agentMotion[i].draw();

        }
        agents++;
    }
}


#endif /* drawAgents_h */
