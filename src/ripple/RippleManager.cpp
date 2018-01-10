//
//  Ripple.cpp
//  ripple
//
//  Created by Momoha Matsuhashi on 2017/12/09.
//
//

#include "RippleManager.hpp"

RippleManager::RippleManager(){
    init();
    
    colorState = true;
    for(int i = 0; i < NUM; i++){
        ripples[i].isRunning = false;
        ripples[i].colorState = colorState;
    }
}

void RippleManager::initVertices(){
    for(int k = 0; k < NUM; k++){
        for(int j = 0; j < rippleNum; j++){
            for(int i = 0; i < res; i++){
                verts[k * res * rippleNum + j * res + i].set(0.5 * CANVAS_HEIGHT, 0.5 * CANVAS_HEIGHT);
                cols[k * res * rippleNum + j * res + i] = ofFloatColor(0., 0., 0., 1.);
            }
        }
    }
}

void RippleManager::initIndices(){
    //Set indices
    int n = 0;
    for(int k = 0; k < NUM; k++){
        for(int j = 0; j < rippleNum; j++){
            for(int i = 0; i < res - 1; i++){
                indices[n] = k * res * rippleNum + res * j + i;
                n++;
                indices[n] = k * res * rippleNum + res * j + i + 1;
                n++;
            }
            indices[n] = k * res * rippleNum + res * (j+1) - 1;
            n++;
            indices[n] = k * res * rippleNum + res * j;
            n++;
        }
    }
}

void RippleManager::initVbo(){
    initVertices();
    initIndices();
    
    vbo.setIndexData(indices, res * rippleNum * NUM * 2, GL_STATIC_DRAW);
    vbo.setColorData(cols, res * rippleNum * NUM, GL_DYNAMIC_DRAW);
    vbo.setVertexData(verts, res * rippleNum * NUM, GL_DYNAMIC_DRAW);
}

void RippleManager::initStatus(){
    activeNumCounter = 0;
}

void RippleManager::init(){
    initVbo();
    initStatus();
}

void RippleManager::update(){
    for(int i = 0; i < NUM; i++){
        ripples[i].update();
    }
    
    activeNumCounter = 0;
    for(int j = 0; j < NUM; j++){
        if(ripples[j].isRunning == true){
            for(int i = 0; i < res * rippleNum; i++){
                verts[activeNumCounter * res * rippleNum + i] = ripples[j].verts[i];
                cols[activeNumCounter * res * rippleNum + i] = ripples[j].cols[i];
            }
            activeNumCounter++;
        }
    }
    vbo.updateVertexData(verts, res * rippleNum * activeNumCounter);
    vbo.updateColorData(cols, res * rippleNum * activeNumCounter);
}
void RippleManager::draw(){
    update();
    glLineWidth(lineWidth);
    vbo.drawElements(GL_LINES, res * rippleNum * activeNumCounter * 2);
}

void RippleManager::bang(float posX, float posY){
    int index = 0;
    while(ripples[index].isRunning == true){
        index++;
        if(index > NUM){
            index = 0;
            break;
        }
    }
    
    ripples[index].bang(posX, posY);
}

void RippleManager::invert(){
    colorState = !colorState;
    for(int i = 0; i < NUM; i++){
        ripples[i].colorState = colorState;
    }
}

int RippleManager::trigger(void* args) {    // To be called from eventhandler
    float *val = (float *)args;
        
    this->bang(val[0], val[1]);
    
    return 1;
}
