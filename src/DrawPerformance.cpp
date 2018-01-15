//
//  DrawPerformance.cpp
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

#include "DrawPerformance.hpp"

//
//  drawPerformance.hpp
//  yaritori
//
//  Created by sonir on 1/14/18.
//
//

#ifndef drawPerformance_h
#define drawPerformance_h



void drawCirclesWithPositions (posi_t *positions, int position_num, float size){
    
    
    for(int i=0; i<position_num;i++){
        
        circle(positions[i].x, positions[i].y, size, false);
    }

    
}


void drawLines (pline_t *lines, int line_num, float width){
    
    
    for(int i=0; i<line_num;i++){
        
        pline_t *tmp = &lines[i];
        line(tmp->node_a->x, tmp->node_a->y, tmp->node_b->x , tmp->node_b->y, width);
    
    }
    
    
}

void drawBullets(pline_t *lines, Bullet *bullets, int bullets_num){
    
    
    
}


void drawPerformance(PerformanceManager *pPerformance){
    
    GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
    
    drawCirclesWithPositions(pPerformance->performers.position, PERFORMER_NUM, SIZE_OF_PERFORMER_INDICATE);
    drawLines(pPerformance->lines, AG_MAX, 0.1f);
    drawBullets(pPerformance->lines , pPerformance->bullets, AG_MAX);

    
}


#endif /* drawPerformance_h */
