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
    float distance = ofDist(myPos.x, myPos.y, targetPos.x, targetPos.y) * ofDist(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    float max_width;
    
    turn_num = int(ofMap(distance, 0., DISPLAY_HEIGHT, 2., TURN_NUM_MAX));
    max_width = ofMap(distance, 0., DISPLAY_HEIGHT, minR, maxR);
    
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
            x = myPos.x * ORIGINAL_WIDTH;
            y = myPos.y * ORIGINAL_HEIGHT;
        }else if(i == turn_num + 1){
            x = targetPos.x * ORIGINAL_WIDTH;
            y = targetPos.y * ORIGINAL_HEIGHT;
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
            
            x = (myPos.x + (targetPos.x - myPos.x) * dist) * ORIGINAL_WIDTH + r * cos(th) * ORIGINAL_HEIGHT;
            y = (myPos.y + (targetPos.y - myPos.y) * dist) * ORIGINAL_HEIGHT + r * sin(th) * ORIGINAL_HEIGHT;
        }
        verts[i].set(x, y);
    }
    
    preCurrentPhase = currentPhase;
}

void LineDrawer::lineTo(float target_x, float target_y){
    targetPos.x = target_x;
    targetPos.y = target_y;
    
    update();
    
    glLineWidth(0.02);
    vbo.updateColorData(cols, turn_num + 2);
    vbo.updateVertexData(verts, turn_num + 2);
    vbo.draw(GL_LINE_STRIP, 0, turn_num + 2);
}

void LineDrawer::invert(){
    colorState = !colorState;
}
