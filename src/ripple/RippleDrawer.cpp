//
//  RippleDrawer.cpp
//  ripple
//
//  Created by moha with hana on 2017/12/30.
//

#include "RippleDrawer.hpp"

RippleDrawer::RippleDrawer(){
    centerX = 0.f;
    centerY = 0.f;
    init();
    
    GismoManager& gismo = GismoManager::getInstance();
    aspect = gismo.width_rate;
}

void RippleDrawer::initVertices() {
    //init verts
    for(int j = 0; j < rippleNum; j++){
        for(int i = 0; i < res; i++){
            verts[j * res + i].set(centerX * aspect * VSYN_HEIGHT, centerY * VSYN_HEIGHT);
            cols[j * res + i] = ofFloatColor(0., 0., 0., 1.);
        }
    }
}

void RippleDrawer::initStatus() {
    //Set default duration
    duration = ((durMax - durMin) * frand() + durMin) * 1000.;   //sec -> msec
    //Set default radius
    radius = (r_Max - r_Min) * frand() + r_Min;
    
    lag[0] = 0.;
    sp_noise[0] = 1.;
    for(int i = 1; i < rippleNum; i++){
        lag[i] = (lagMax - lagMin) * frand() + lagMin;
        sp_noise[i] = (sp_noiseMax - sp_noiseMin) * frand() + sp_noiseMin;
    }
    currentRadius = 0.;
}

void RippleDrawer::init(){
    initVertices();
    initStatus();
}

void RippleDrawer::updateColor(){
    if(currentTime < 1.0){
        float alpha;
        if(currentTime < 1. - fadeOutRatio){
            alpha = 1.f;
        }else{
            alpha = - (currentTime - (1. - fadeOutRatio)) / fadeOutRatio + 1.;
        }
        
        
        ofFloatColor col;
        if(colorState == true){
            alpha *= RIPPLE_ALPHA_FIX_BLACK;
            col = ofFloatColor(0., 0., 0., alpha);
        }else{
            alpha *= RIPPLE_ALPHA_FIX_WHITE;
            col = ofFloatColor(1., 1., 1., alpha);
        }
        for(int j = 0; j < rippleNum; j++){
            for(int i = 0; i < res; i++){
                cols[j * res + i] = col;
            }
        }
    }
}

void RippleDrawer::updateVertex(){
    for(int j = 0; j < rippleNum; j++){
        //integrate "r_speed = speed * (1. - currentTime);"
        currentRadius = radius * sp_noise[j] * ((currentTime - lag[j]) - 0.5 * (currentTime - lag[j]) * (currentTime - lag[j]));
        for(int i = 0; i < res; i++){
            float th = theta * i;
            if(currentTime - lag[j] > 0){
                float x = centerX * VSYN_HEIGHT * aspect + currentRadius * cos(th) * VSYN_HEIGHT;
                float y = centerY * VSYN_HEIGHT + currentRadius * sin(th) * VSYN_HEIGHT;
                verts[j * res + i].set(x, y);
            }
        }
    }
    
}

void RippleDrawer::update(){
    if(isRunning == true){
        currentTime = interpolation.get();  //0. - 1.
        if(currentTime < 1.0){
            updateColor();
            updateVertex();
        }else{
            isRunning = false;
        }
    }
}

void RippleDrawer::bang(float x, float y) {
    centerX = x;
    centerY = y;
    init();
    
    interpolation.bang(duration);    //msec
    isRunning = true;
}

