//
//  LineDrawer.cpp
//  ccma_line
//
//  Created by Momoha Matsuhashi on 2018/01/05.
//
//

#include "LineDrawer.hpp"

LineDrawer::LineDrawer(){
    currentPhase = 0.;
    interpolation.setDuration(cycle);
    interpolation.bang();
    
    fromPos.x = 0.25;
    fromPos.y = 0.5;
    
    size = 1.0;
    
    for(int i = 0; i < TURN_NUM_MAX + 2; i++){
        verts[i].set(0.5 * ORIGINAL_HEIGHT, 0.5 * ORIGINAL_HEIGHT);
        cols[i].set(0., 0., 0., 1.);
    }
    
    vbo.setVertexData(verts, TURN_NUM_MAX + 2, GL_DYNAMIC_DRAW);
    vbo.setColorData(cols, TURN_NUM_MAX + 2, GL_DYNAMIC_DRAW);
    
    GismoManager& gismo = GismoManager::getInstance();
    aspect = gismo.width_rate;
    
    colorState = true;
    setEvents();
}

void LineDrawer::setEvents() {
    GismoManager& gismo = GismoManager::getInstance();
    
    auto colorEvent = [&](void* args){ //<- keep this desctiption
        param_u* params = (param_u *)args;
        float c = params[0].fval;
        
        this->setColor(c);
    };
    
    gismo.lambdaAdd("/lineColor", colorEvent);
}

void LineDrawer::setColor(float c) {
    color = ofFloatColor(c);
    
    for(int i = 0; i < TURN_NUM_MAX + 2; i++){
        cols[i] = color;
    }
    
    vbo.updateColorData(cols, TURN_NUM_MAX + 2);
}



void LineDrawer::update(){
    float distance = ofDist(fromPos.x, fromPos.y, toPos.x, toPos.y) * ofDist(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    float max_width;
    
    turn_num = int(ofMap(distance, 0., DISPLAY_HEIGHT, 2., TURN_NUM_MAX));
    max_width = ofMap(distance, 0., DISPLAY_HEIGHT, minR, maxR) * size;
    
    currentPhase = interpolation.get();
    
    if(currentPhase == 1.){
        interpolation.bang();
    }
    
    theta = atan2(toPos.y - fromPos.y, toPos.x - fromPos.x);
    
    float x, y;
    float r;
    float th;
    float dist;
    for(int i = 0; i < turn_num + 2; i++){
        
        if(preCurrentPhase < 0.5){
            th = theta + PI * 0.5 + PI * (i-1);
        }else{
            th = theta + PI * 1.5 + PI * (i-1);
        }
        if(i == 0){
            x = fromPos.x * ORIGINAL_WIDTH;
            y = fromPos.y * ORIGINAL_HEIGHT;
        }else if(i == turn_num + 1){
            x = toPos.x * ORIGINAL_WIDTH;
            y = toPos.y * ORIGINAL_HEIGHT;
        }else{
            if(preCurrentPhase < 0.5){
                dist = 1. / turn_num * (i-1 + 2 * preCurrentPhase);
            }else{
                dist = 1. / turn_num * (i-1 + 2 * (preCurrentPhase - 0.5));
            }
            if(dist < PEAK){
                r = max_width * dist * 3.3333;
            }else{
                r = max_width * (1. - dist) * 1.4286;
            }
            
            x = (fromPos.x + (toPos.x - fromPos.x) * dist) * ORIGINAL_WIDTH + r * cos(th) * ORIGINAL_HEIGHT;
            y = (fromPos.y + (toPos.y - fromPos.y) * dist) * ORIGINAL_HEIGHT + r * sin(th) * ORIGINAL_HEIGHT;
        }
        verts[i].set(x, y);
    }
    
    preCurrentPhase = currentPhase;
}

void LineDrawer::lineTo(float fromPos_x, float fromPos_y, float toPos_x, float toPos_y, float sz){
    fromPos.x = fromPos_x;
    fromPos.y = fromPos_y;
    toPos.x = toPos_x;
    toPos.y = toPos_y;
    
    size = sz;
    
    update();
}

void LineDrawer::invert(){
    colorState = !colorState;
}
