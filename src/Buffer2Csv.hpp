//
//  Buffer2Csv.hpp
//  yaritori
//
//  Created by sonir on 1/31/18.
//
//

#ifndef Buffer2Csv_hpp
#define Buffer2Csv_hpp

#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include "ofxGismo.h"

class Buffer2Csv {
    
    
    public:
    
        Buffer2Csv (){
            
            //event for added agent
            auto f = [&](void* args){ //<- keep this desctiption

                //draw your code
                param_u *params = (param_u *)args;
                exportAgents(gismo.agents.buf,gismo.agents.count);
                
                
            };
            gismo.lambdaAdd("/yaritori/save", f);
            
        }
    
        void exportAgents(ag_t *agents, int index_count);
    
    
        //Variables
        GismoManager& gismo = GismoManager::getInstance();
    
    
    
};

#endif /* Buffer2Csv_hpp */
