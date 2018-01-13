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


void drawAgents(GismoManager *gismo, float screen_w, float screen_h){
    
    using namespace std;
    
    int count = gismo->agents.count;
    ag_t *agents = gismo->getAgents(); //sets agents pointer
    ag_t *ag;

 
    for(int i =0; i<count; i++){
        
        ag = agents; //Set agent address

        
        if(ag->active){
            square(ag->posi.x, ag->posi.y, ag->size, 0.0f, true);
        }
        agents++;
        
    }
    
    
}



#endif /* drawAgents_h */
