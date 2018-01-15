//
//  Bullet.hpp
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

//#ifndef Bullet_hpp
//#define Bullet_hpp

#pragma once

#include <stdio.h>
#include "ofxGismo.h"
#include "Fade.hpp"

typedef struct line_t {
    
    posi_t node_a;
    posi_t node_b;
    
}line_t;



posi_t moveOnLine(float fval, float a, float b, float x, float y);


class Bullet {
    
public:
    Bullet(){
        
        route.node_a.x = 0.5f;
        route.node_a.y = 0.5f;
        route.node_b.x = 1.0f;
        route.node_b.y = 0.0f;
        
        
    }
    
    line_t route;
    Fade fade;
    void bang();
    void set(int ms);
    posi_t update();
    posi_t update(line_t aLine);
    
    
};


// #endif /* Bullet_hpp */
