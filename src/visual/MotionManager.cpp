//
//  MotionManager.cpp
//  yaritori
//
//  Created by Hana on 2018/01/05.
//
//

#include "MotionManager.hpp"
#include <cassert>

MotionManager::MotionManager() {
    //Reset solo
    for(int i = 0; i < AG_MAX; i++) {
        soloID[i] = false;
    }
    
}

void MotionManager::setShapes() {
    for(int i = 0; i < AG_MAX; i++){
        agent[i].pShape = &pShapes[i];
        agent[i].initVbo();
    }
}

void MotionManager::invertColor() {
    for(int i = 0; i < AG_MAX; i++){
        agent[i].invertColor();
    }
}

void MotionManager::solo(int _id, int act) {
    if(act != 0) {
        addSolo(_id);
    } else {
        deleteSolo(_id);
    }
}

void MotionManager::addSolo(int _id) {
    soloID[_id] = true;
    soloCount++;
}

void MotionManager::deleteSolo(int _id) {
    soloID[_id] = false;
    soloCount--;
}



void MotionManager::drawAll() {
    int count = gismo->agents.count;
    ag_t* agents = gismo->getAgents(); //sets agents pointer
    ag_t* ag;
    
    for(int i = 0; i < count; i++){
        
        ag = agents; //Set agent address
        if(ag->active){
            //square(ag->posi.x, ag->posi.y, ag->size, 0.0f, true);
            agent[i].pAg = ag;
            agent[i].dest.x = ag->posi.x;
            agent[i].dest.y = ag->posi.y;
            
            agent[i].update();
            agent[i].draw();
            
            ofSetColor(255, 0, 0);
            ofDrawBitmapString(i, ag->posi.x * CANVAS_HEIGHT, ag->posi.y * CANVAS_HEIGHT);
            //ofDrawCircle(pAg->posi.x * CANVAS_HEIGHT, pAg->posi.y * CANVAS_HEIGHT, 3);
            
            //Draw interaction
            if(ag->interact_with != -1) {
                int targetID = ag->interact_with;
                ag_t* target = gismo->getAgent(targetID);
                
                if(ag->condition == CHASE && target->condition == RUN) {
                    interactLine[i].myPos.x = agent[i].center.x;
                    interactLine[i].myPos.y = agent[i].center.y;
                    
                    ofSetColor(0);
                    interactLine[i].lineTo(agent[targetID].center.x, agent[targetID].center.y);
                }
            }
        }
        agents++;
    }
}

void MotionManager::drawSolo() {
    int count = gismo->agents.count;
    ag_t* agents = gismo->getAgents(); //sets agents pointer
    ag_t* ag;
    
    for(int i =0; i < AG_MAX; i++){
        if(soloID[i]) {
            ag = &agents[i];
            
            if(ag->active){
                agent[i].pAg = ag;
                agent[i].pShape = &pShapes[i];
                agent[i].dest.x = ag->posi.x;
                agent[i].dest.y = ag->posi.y;
                
                agent[i].update();
                agent[i].draw();
                

                
                //Draw Interaction
                if(ag->interact_with != -1) {
                    int targetID = ag->interact_with;
                    ag_t* target = gismo->getAgent(targetID);
                    
                    if(ag->condition == CHASE && target->condition == RUN) {
                        interactLine[i].myPos.x = agent[i].center.x;
                        interactLine[i].myPos.y = agent[i].center.y;
                        
                        ofSetColor(0);
                        interactLine[i].lineTo(agent[targetID].center.x, agent[targetID].center.y);
                    }
                }

            }
        }
        //agents++;
    }
}


void MotionManager::draw() {
    if(soloCount == 0) {
        drawAll();
    } else {
        drawSolo();
    }
}

