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
    
    for(int i = 0; i < NUM + 2; i++){
        verts[i].set(0.5 * CANVAS_HEIGHT, 0.5 * CANVAS_HEIGHT);
    }
    
    vbo.setVertexData(verts, NUM + 2, GL_DYNAMIC_DRAW);
}

void LineDrawer::update(){
    if(currentPhase == 1.){
        interpolation.bang();
    }
    currentPhase = interpolation.get();
    
    theta = atan2(targetPos.y - myPos.y, targetPos.x - myPos.x);
    
    for(int i = 0; i < NUM + 2; i++){
        float x, y;
        float r;
        float th;
        
        if(currentPhase < 0.5){
            th = theta + PI * 0.5 + PI * (i-1);
        }else{
            th = theta + PI * 1.5 + PI * (i-1);
            
        }
        if(i == 0){
            if(currentPhase < 0.5){
                r = 4. * maxR * (0.25 - currentPhase);
            }else{
                r = -4. * maxR * (0.25 - (currentPhase - 0.5));
            }
            x = myPos.x + r * cos(theta + PI * 0.5);
            y = myPos.y + r * sin(theta + PI * 0.5);
        }else if(i == NUM + 1){
            x = targetPos.x;
            y = targetPos.y;
        }else{
            float dist;
            if(currentPhase < 0.5){
                dist = 1. / NUM * (i-1 + 2 * currentPhase);
            }else{
                dist = 1. / NUM * (i-1 + 2 * (currentPhase - 0.5));
            }
            r = maxR * (1. - dist);
            
            x = myPos.x + (targetPos.x - myPos.x) * dist + r * cos(th);
            y = myPos.y + (targetPos.y - myPos.y) * dist + r * sin(th);
        }
        verts[i].set(x * CANVAS_HEIGHT, y * CANVAS_HEIGHT);
    }
}

void LineDrawer::lineTo(float target_x, float target_y){
    targetPos.x = target_x;
    targetPos.y = target_y;
    
    update();
    
    glLineWidth(0.02);
    ofSetColor(0, 0, 0);
    vbo.updateVertexData(verts, NUM + 2);
    vbo.draw(GL_LINE_STRIP, 0, NUM + 2);
}
