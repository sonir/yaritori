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
    
    myPos.x = 0.25;
    myPos.y = 0.5;
    
    for(int i = 0; i < TURN_NUM_MAX + 2; i++){
        verts[i].set(0.5 * BASE_WIDTH, 0.5 * BASE_HEIGHT);
        cols[i].set(0., 0., 0., 1.);
    }
    
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
}



void LineDrawer::update(){
    float distance = ofDist(myPos.x * BASE_WIDTH, myPos.y * BASE_HEIGHT, targetPos.x * BASE_WIDTH, targetPos.y * BASE_HEIGHT);
    float max_width;
    
    turn_num = int(ofMap(distance, 0., DISPLAY_HEIGHT, 2., TURN_NUM_MAX));
    
    max_width = size;
    if(max_width > maxR){
        max_width = maxR;
    }
    if(max_width < minR){
        max_width = minR;
    }
    
    currentPhase = interpolation.get();
    
    if(currentPhase == 1.){
        interpolation.bang();
    }
    
    theta = atan2(targetPos.y - myPos.y, targetPos.x - myPos.x);
    
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
            x = myPos.x * BASE_HEIGHT;
            y = myPos.y * BASE_HEIGHT;
        }else if(i == turn_num + 1){
            x = targetPos.x * BASE_HEIGHT;
            y = targetPos.y * BASE_HEIGHT;
        }else{
            if(preCurrentPhase < 0.5){
                dist = 1. / turn_num * (i-1 + 2 * preCurrentPhase);
            }else{
                dist = 1. / turn_num * (i-1 + 2 * (preCurrentPhase - 0.5));
            }
            if(dist < 0.3){
                r = max_width * dist * 3.3333;
            }else{
                r = max_width * (1. - dist) * 1.4286;
            }

            x = (myPos.x + (targetPos.x - myPos.x) * dist) * BASE_WIDTH + r * cos(th) * BASE_HEIGHT;
            y = (myPos.y + (targetPos.y - myPos.y) * dist) * BASE_HEIGHT + r * sin(th) * BASE_HEIGHT;
        }
        verts[i].set(x, y);
    }
    
    preCurrentPhase = currentPhase;
}

void LineDrawer::lineTo(float target_x, float target_y, float _size){
    targetPos.x = target_x;
    targetPos.y = target_y;
    
    size = _size;
    
    update();
    
    glLineWidth(0.02);
    
}

void LineDrawer::invert(){
    colorState = !colorState;
}
