//
//  Performance.cpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#include "Performance.hpp"

posi_t moveOnLine(float fval, float a, float b, float x, float y){
    
    
    posi_t posi;
    
    float diff_x = x - a;
    float diff_y = y - b;
    
    posi.x = ( fval * diff_x ) + a;
    posi.y = ( fval * diff_y ) + b;
    
//    cout << diff_x << " , " << diff_y << endl;
//    cout << "moveOnLine::fval=" << fval << " || " << posi.x << endl;
    return posi;
    
    
}

int count_ring(int now, int max){
    
    now++;
    if (now >= max) return 0;
    else return now;
    
}


void Bullet::bang(){
    
    fade.bang();
    
}


void Bullet::set(int ms){
    
    fade.set(ms);
    
}

posi_t Bullet::update(){
    
    float fval = fade.update();
    return moveOnLine(fval, route.node_a.x, route.node_a.y, route.node_b.x, route.node_b.y);
    
}

posi_t Bullet::update(line_t aLine){
    
    float fval = fade.update();
//    cout << "fval = " << fval << endl;
//    cout << aLine.node_a.x << "," << aLine.node_a.y << " | " << aLine.node_b.x << "," << aLine.node_b.y << endl;
    return moveOnLine(fval, aLine.node_a.x, aLine.node_a.y, aLine.node_b.x, aLine.node_b.y);
    
    
}
