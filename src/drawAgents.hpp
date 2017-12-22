//
//  drawAgents.hpp
//  yaritori
//
//  Created by sonir on 12/10/17.
//
//

#ifndef drawAgents_h
#define drawAgents_h

#include "ofMain.h"
#include "ofxGismo.h"
#include "VisualManager.hpp"

void drawAgents(GismoManager *gismo,VisualManager *visualManager){
    
    int count = gismo->agents.count;
    ag_t *agents = gismo->getAgents(); //sets agents pointer
    ag_t *ag;
    //gismo->agents.count = 1000;
    for(int i =0; i<count; i++){
        
        ag = agents; //Set agent address

//        string condition = "a";
        //            ofDrawBitmapString( condition, ag->posi.x, ag->posi.y);
//        int tmp_x = (int)( ag->posi.x * (float)ofGetScreenWidth() );
//        int tmp_y = (int)( ag->posi.y * (float)ofGetScreenHeight() );
//        std::cout << tmp_x << " , " << tmp_y << std::endl;
//        ofDrawBitmapString( "f", 100, 200);
        
        if(ag->active){
            //square(ag->posi.x, ag->posi.y, ag->size, 0.0f, true);
            visualManager->setAgent(i, ag->posi.x, ag->posi.y, ag->size);
        }
        agents++;
        
    }
    visualManager->draw();
    
}

#endif /* drawAgents_h */
