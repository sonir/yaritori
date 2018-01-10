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
    for(int i = 0; i < AG_MAX; i++) {
        soloID[i] = false;
    }
}

void MotionManager::invertColor() {
    for(int i = 0; i < AG_MAX; i++){
        agent[i].invertColor();
    }
}

void MotionManager::solo(int _id) {
    if(soloID[_id]) {
        deleteSolo(_id);
    } else {
        addSolo(_id);
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
    
    for(int i =0; i < count; i++){
        
        ag = agents; //Set agent address
        if(ag->active){
            //square(ag->posi.x, ag->posi.y, ag->size, 0.0f, true);
            agent[i].pShape = &pShapes[i];
            agent[i].center.x = ag->posi.x;
            agent[i].center.y = ag->posi.y;
            
//            ofSetColor(255, 0, 0);
//            ofSetCircleResolution(12);
//            ofDrawCircle(ag->posi.x * CANVAS_HEIGHT, ag->posi.y * CANVAS_HEIGHT, 4);
            
            agent[i].size = ag->size;
            agent[i].mov = ag->mov;
            //motion->agent[i].width_rate = gismo->width_rate;
            agent[i].update();
            agent[i].draw();
            
//            if (agent[i].interaction.node.isRunning()) {
//                agent[i].interaction.begin = ag->posi;
//                agent[i].interaction.end.x = 0.5;
//                agent[i].interaction.end.y = 0.5;
//                lines.addLine(agent[i].interaction);
//                if(!agent[i].interaction.isRunning()){
//                    agent[i].interaction.bang(1000);
//                }
//            }
            
            
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
                //square(ag->posi.x, ag->posi.y, ag->size, 0.0f, true);
                
//                agent[i].setShapePtr(&pShapes[i]);
                agent[i].pShape = &pShapes[i];
                agent[i].center.x = ag->posi.x;
                agent[i].center.y = ag->posi.y;
                agent[i].size = ag->size;
                agent[i].mov = ag->mov;
                //motion->agent[i].width_rate = gismo->width_rate;
                agent[i].update();
                agent[i].draw();
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
    lines.draw();
}
