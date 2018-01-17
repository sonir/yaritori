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
        isSolo[i] = false;
        soloTimers[i].ready();
        agent[i].setVboPtr(&vbo);
    }
    
    //OSC
    sender.setup(SOUND_HOST, SOUND_PORT);
    
    //TEST Osc Send
    param_u params[4];
    params[0].fval = 1.0f;
    params[1].ival = 87;
    params[2].bval = true;
    params[3].ival = 87;
    
    sendOSC("/foo", params, 4);
    
    nodeNum = 0;
    edgeNum = 0;
    fColor = 0.0f;
    soloCount = 0;
    
//    nodeVbo.setVertexData(vbo.nodePos, NODE_MAX * AG_MAX, GL_DYNAMIC_DRAW);
//    edgeVbo.setColorData(vbo.nodeColors, NODE_MAX * AG_MAX, GL_DYNAMIC_DRAW);
//    
//    
//    edgeVbo.setVertexData(vbo.edgePos, EDGE_MAX * 2 * AG_MAX, GL_DYNAMIC_DRAW);
//    edgeVbo.setColorData(vbo.edgeColors, EDGE_MAX * 2 * AG_MAX, GL_DYNAMIC_DRAW);
}

void MotionManager::setShapes() {
    for(int i = 0; i < AG_MAX; i++){
        agent[i].pShape = &pShapes[i];
        agent[i].initVbo();
    }
}

void MotionManager::invertColor() {
    if( fColor == 0.0) {
        fColor = 1.0;
    } else {
        fColor = 0.0;
    }
    
    ofFloatColor color = ofFloatColor(fColor, fColor, fColor);
    for(int i = 0; i < AG_MAX; i++){
        agent[i].fColor = fColor;
        agent[i].color = color;
        agent[i].updateColors();
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
    soloTimers[_id].bang(duration);
    soloCount++;
}

void MotionManager::deleteSolo(int _id) {
    isSolo[_id] = false;
    soloCount--;
}


void MotionManager::updateSolo() {
    for(int i = 0; i < AG_MAX; i++){
        if(isSolo[i]) {
            float val = soloTimers[i].get();
            if (1.0 <= val) {
                deleteSolo(i);
            }
        }
    }
}

void MotionManager::update() {
    if(0 < soloCount) {
        updateSolo();
        if(bSolo == false) {    //if solo turns on
            
            param_u params[1];
            params[0].fval = 1.0f;
            sendOSC("/solo_sound", params, 1);
            
            bSolo = true;
        }
    } else {
        if(bSolo == true) { //if solo turns off
            param_u params[1];
            params[0].fval = 0.0f;
            sendOSC("/solo_sound", params, 1);
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
            agent[i].dest.x = ag->posi.x;
            agent[i].dest.y = ag->posi.y;
            
            agent[i].update();
            agent[i].draw();
            
//            ofSetColor(255, 0, 0);
//            ofDrawBitmapString(i, ag->posi.x * CANVAS_HEIGHT, ag->posi.y * CANVAS_HEIGHT);
//            ofDrawCircle(pAg->posi.x * CANVAS_HEIGHT, pAg->posi.y * CANVAS_HEIGHT, 3);
            
            //Draw interaction
            if(ag->interact_with != -1) {
                int targetID = ag->interact_with;
                ag_t* target = gismo.getAgent(targetID);
                
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
    int count = gismo.agents.count;
    ag_t* agents = gismo.getAgents(); //sets agents pointer
    ag_t* ag;
    

    
    for(int i =0; i < count; i++){
        
        ag = &agents[i];
        
        if(ag->active){
            agent[i].pAg = ag;
            agent[i].pShape = &pShapes[i];
            agent[i].dest.x = ag->posi.x;
            agent[i].dest.y = ag->posi.y;
            agent[i].center.x = ag->posi.x;
            agent[i].center.y = ag->posi.y;

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
    
    vbo.nodeNum = 0;
    
    if(soloCount == 0) {
        drawAll();
    } else {
        drawSolo();
    }
    
//    ofSetColor(ofFloatColor(color));
//    nodeVbo.updateVertexData(vbo.nodePos, vbo.nodeNum);
//    nodeVbo.updateColorData(vbo.nodeColors,  vbo.nodeNum);
//    nodeVbo.draw(GL_POINTS, 0, vbo.nodeNum);
    
    
    shader.setAttribute1f(GLint location, <#float v1#>)
}

void MotionManager::sendOSC(const string adr, param_u* args,  int numArgs) {
    ofxOscMessage m;
    m.setAddress(adr);
    for(int i = 0; i < numArgs; i++) {
        m.addFloatArg(args[i].fval);
    }
    sender.sendMessage(m, false);
}



