//
//  Shape2Agent.cpp
//  yaritori
//
//  Created by sonir on 1/11/18.
//
//

#include "Shape2Agent.hpp"

ag_t shape2Agent(ag_shape_t shape){
    
    ag_t ag;
    initAgentActive(&ag);
    
    ag.view = shape.edge_count * V_FIX;
    ag.size = shape.node_count * S_FIX;
    if (shape.node_count !=0){
        ag.mov = ( NODE_AVG / shape.node_count ) * M_FIX;
    } else {

        ag.mov = ( (NODE_AVG * 2) * M_FIX );
        
    }
    
    cout << "view: " << ag.view << endl;
    cout << "size: " << ag.size << endl;
    cout << "mov: " << ag.mov << endl;
    cout << "----" << endl;
    
    return ag;
    
    
}