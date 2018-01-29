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
    soloCount = 0;
    for(int i = 0; i < AG_MAX; i++) {
        isSolo[i] = false;
        soloTimers[i].ready();
        
    }
    
    //OSC
    //sender.setup(SOUND_HOST, SOUND_PORT);
    
    aspect = gismo.width_rate;
    
    setEvents();
}

void MotionManager::setColor(float c) {
    for(int i = 0; i < AG_MAX; i++){
        agent[i].setColor(c);
        interactLine[i].setColor(c);
    }
}


void MotionManager::setEvents() {
    GismoManager& gismo = GismoManager::getInstance();
    
    auto colorEvent = [&](void* args){ //<- keep this desctiption
        param_u* params = (param_u *)args;
        float c = params[0].fval;
        
        this->setColor(c);
    };
    
    gismo.lambdaAdd("/agentColor", colorEvent);
    
    
    auto trembleEvent = [&](void* args){ //<- keep this desctiption
        param_u* params = (param_u *)args;
        int enable = params[0].ival;
        
        if(enable == 1) {
            this -> setTremble(8.0);
        } else {
            this -> setTremble(1.0);
        }
    };
    
    gismo.lambdaAdd("/tremble", trembleEvent);
    
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

void MotionManager::solo(int _id, bool status, float duration) {
    if(status != 0) {
        addSolo(_id, duration);
    } else {
        deleteSolo(_id);
    }
}

void MotionManager::addSolo(int _id, float duration) {
    isSolo[_id] = true;
    soloTimers[_id].bang(duration * 1000.0);
    soloCount++;
    
//    float args[2];
//    ag_t* ag = gismo.getAgent(_id);
//    args[0] = ag->posi.x;
//    args[1] = ag->posi.y;
//    gismo.bang("/ripple", args);
    
//    param_u params[3];
//    params[0].ival = _id;
//    params[1].fval = 1.0;
//    params[2].fval = 1.0;
//    gismo.bang("/ag_ripple", params);
}

void MotionManager::deleteSolo(int _id) {
    isSolo[_id] = false;
    soloCount--;
}


void MotionManager::updateSolo() {
    soloCount = 0;
    for(int i = 0; i < AG_MAX; i++){
        if(isSolo[i]) {
            float val = soloTimers[i].get();
            if (1.0 <= val) {
                deleteSolo(i);
            }
            soloCount++;
        }
    }
}

void MotionManager::update() {
    updateSolo();
    if(0 < soloCount) {
        
        if(bSolo == false) {    //if solo turns on
            param_u params[1];
            params[0].fval = 1.0f;
            //sendOSC("/solo_sound", params, 1);
            
            bSolo = true;
        }
    } else {
        if(bSolo == true) { //if solo turns off
            param_u params[1];
            params[0].fval = 0.0f;
            //sendOSC("/solo_sound", params, 1);
            bSolo = false;
        }
    }
}


void MotionManager::drawAll() {
    
    int count = gismo.agents.count;
    ag_t* agents = gismo.getAgents(); //sets agents pointer
    ag_t* ag;
    
    for(int i = 0; i < count; i++){
        
        ag = agents; //Set agent address
        if(ag->active){
            //square(ag->posi.x, ag->posi.y, ag->size, 0.0f, true);
            agent[i].pAg = ag;
            agent[i].move(ag->posi.x, ag->posi.y);

            agent[i].update();
            agent[i].draw();
            
//            ofSetColor(255, 0, 0);
//            ofDrawBitmapString(i, ag->posi.x * aspect * ORIGINAL_HEIGHT, ag->posi.y * ORIGINAL_HEIGHT);
//            ofDrawCircle(ag->posi.x * ORIGINAL_HEIGHT * aspect, ag->posi.y * ORIGINAL_HEIGHT, 3);
            
            //Draw interaction
            if(ag->interact_with != -1) {
                int targetID = ag->interact_with;
                ag_t* target = gismo.getAgent(targetID);
                
                if(ag->condition == CHASE && target->condition == RUN) {
                    interactLine[i].myPos.x = agent[i].center.x;
                    interactLine[i].myPos.y = agent[i].center.y;
                    interactLine[i].lineTo(agent[targetID].center.x, agent[targetID].center.y);
                    
//                    ofSetColor(0);
//                    interactLine[i].lineTo(ag->posi.x, ag->posi.y, target->posi.x, target->posi.y, ag->size);
//                    interactLine[i].lineTo(ag->center.x, ag->center.y, target->center.x, target->center.y, ag->size);
                }
            }
        }
        agents++;
    }
}

void MotionManager::drawSolo() {
    
    int count = gismo.agents.count;
    ag_t* agents = gismo.getAgents(); //sets agents pointer
    ag_t* ag;
    
    for(int i =0; i < count; i++){
        
        ag = &agents[i];
        
        if(ag->active)  {
            agent[i].pAg = ag;
            agent[i].move(ag->posi.x, ag->posi.y);
            
            agent[i].update();
            
            if(isSolo[i]) {
                agent[i].draw();
            

                //Draw Interaction
                if(ag->interact_with != -1) {
                    int targetID = ag->interact_with;
                    ag_t* target = gismo.getAgent(targetID);
                    
                    if(ag->condition == CHASE && target->condition == RUN) {
                        interactLine[i].myPos.x = agent[i].center.x;
                        interactLine[i].myPos.y = agent[i].center.y;
//
//                        ofSetColor(0);
                        interactLine[i].lineTo(agent[targetID].center.x, agent[targetID].center.y);
//                          interactLine[i].lineTo(ag->posi.x, ag->posi.y, target->posi.x, target->posi.y, ag->size);
//                    interactLine[i].lineTo(ag->center.x, ag->center.y, target->center.x, target->center.y, ag->size);


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
    
//    ofSetColor(ofFloatColor(color));
//    nodeVbo.updateVertexData(vbo.nodePos, vbo.nodeNum);
//    nodeVbo.updateColorData(vbo.nodeColors,  vbo.nodeNum);
//    nodeVbo.draw(GL_POINTS, 0, vbo.nodeNum);
    
}

bool MotionManager::isSoloMode() {
    bool result = false;
    if (soloCount == 0) {
        result = false;
    } else {
        result = true;
    }
    
    return result;
}

void MotionManager::sendOSC(const string adr, param_u* args,  int numArgs) {
    ofxOscMessage m;
    m.setAddress(adr);
    for(int i = 0; i < numArgs; i++) {
        m.addFloatArg(args[i].fval);
    }
    //sender.sendMessage(m, false);
}


void MotionManager::addNode(ofVec2f pos) {
    
}

void MotionManager::addEdge(ofVec2f node_a, ofVec2f node_b) {
    
}

void MotionManager::setTremble(float val) {
    for(int i = 0; i < AG_MAX; i++) {
        agent[i].tremble = val;
        
    }
}


