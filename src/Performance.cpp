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
    
    return posi;
    
    
}
