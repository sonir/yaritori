//
//  Ripple.cpp
//  ripple
//
//  Created by Momoha Matsuhashi on 2017/12/09.
//
//

#include "RippleManager.hpp"

RippleManager::RippleManager(){    
    for(int i = 0; i < NUM; i++){
        ripples[i].isRunning = false;
    }
}

void RippleManager::draw(){
    glLineWidth(lineWidth);
    for(int i = 0; i < NUM; i++){
        ripples[i].draw();
    }
}

void RippleManager::bang(float posX, float posY){
    int index = 0;
    while(ripples[index].isRunning){
        index++;
    }
    ripples[index] = RippleDrawer();
    ripples[index].isRunning = true;
    ripples[index].centerX = posX;
    ripples[index].centerY = posY;
    ripples[index].setup();
}

int RippleManager::trigger(void* args) {
    float *val = (float *)args;
        
    this->bang(val[0], val[1]);
    
    return 1;
}
