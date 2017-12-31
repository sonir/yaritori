//
//  RippleDrawer.cpp
//  ripple
//
//  Created by moha with hana on 2017/12/30.
//

#include "RippleDrawer.hpp"

RippleDrawer::RippleDrawer(){
    //Set default duration
    //dur = (durMax - durMin) * frand() + durMin;
    dur = durMax;
    
    //set indices
    int n = 0;
    for(int j = 0; j < rippleNum; j++){
        for(int i = 0; i < res - 1; i++){
            indices[n] = res * j + i;
            n++;
            indices[n] = res * j + i + 1;
            n++;
        }
        indices[n] = res * (j+1) - 1;
        n++;
        indices[n] = res * j;
        n++;
    }
    
    for(int j = 0; j < rippleNum; j++){
        lag[0] = 0.;    //lag time that makes delay of each ripple
        sp_noise[0] = 1.;    //coef that acts speed defined
        for(int i = 1; i < rippleNum; i++){
            //lag[i] = ofRandom(lagMin, lagMax);
            lag[i] = (lagMax - lagMin) * frand() + lagMin;
            
            //sp_noise[i] = ofRandom(sp_noiseMin, sp_noiseMax);
            sp_noise[i] = (sp_noiseMax - sp_noiseMin) * frand() + sp_noiseMin;
        }
    }
        
    vbo.setIndexData(indices, res * rippleNum * 2, GL_STATIC_DRAW);
    vbo.setColorData(cols, res * rippleNum, GL_DYNAMIC_DRAW);
    vbo.setVertexData(verts, res * rippleNum, GL_DYNAMIC_DRAW);
    
    interpolation.bang(dur);    //msec
    
    GismoManager& gismo = GismoManager::getInstance();
    aspect = gismo.width_rate;
}

void RippleDrawer::setup(){
    for(int j = 0; j < rippleNum; j++){
        for(int i = 0; i < res; i++){
            verts[res * j + i].set(ofVec2f(centerX * CANVAS_HEIGHT, centerY * CANVAS_HEIGHT * aspect));
        }
    }
}

void RippleDrawer::draw(){
    if(isRunning == true){
        currentTime = interpolation.get();  //0. - 1.
        if(currentTime < 1.0){
            float alpha;
            if(currentTime < 1. - fadeOutRatio){
                alpha = 1.f;
            }else{
                alpha = - (currentTime - (1. - fadeOutRatio)) / fadeOutRatio + 1.;
            }
            
            for(int j = 0; j < rippleNum; j++){
                for(int i = 0; i < res; i++){
                    cols[j * res + i] = ofFloatColor(0., 0., 0., alpha);
                }
            }
            vbo.updateColorData(cols, res * rippleNum);

            setSpeed();
            updateVertex(r_speed);
            
            vbo.updateVertexData(verts, res * rippleNum);
            vbo.drawElements(GL_LINES, res * 2 * rippleNum);
            
        }else{
            isRunning = false;
        }
    }
}

void RippleDrawer::setSpeed(){
    r_speed = speed * (1. - currentTime);   //v
//    r_speed = speed;
//    if(interpolation.get() > 0.3){
//        r_speed = speed * (0.7 - (interpolation.get() - 0.3));
//    }
}

void RippleDrawer::updateVertex(float sp){
    for(int j = 0; j < rippleNum; j++){
        for(int i = 0; i < res; i++){
            float th = theta * i;
            ofVec2f diff = ofVec2f(sp * cos(th), sp * sin(th));
            
            if(currentTime - lag[j] > 0){
                verts[j * res + i].set(verts[j * res + i] + diff * sp_noise[j]);
            }
        }
    }

}
