//
//  Performance.cpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#include "Performance.hpp"



int count_ring(int now, int max){
    
    now++;
    if (now >= max) return 0;
    else return now;
    
}


void PerformanceManager::updateLines(){
    
    ag_t *agents = gismo.getAgents();
    
    for(int i=0; i<AG_MAX; i++){
        
        lines[i].node_a = &performers.position[i%PERFORMER_NUM];        
        lines[i].node_b = &agents[i].posi;
        
    }
    
}

