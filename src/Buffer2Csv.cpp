//
//  Buffer2Csv.cpp
//  yaritori
//
//  Created by sonir on 1/31/18.
//
//

#include "Buffer2Csv.hpp"

using namespace std;

void Buffer2Csv:: exportAgents(ag_t *agents ,  int index_count){
    
    
    ofstream log;
    log.open("0-agents.csv" , ios_base::trunc);
    
    log << "agid" << "," << "active" << "," << "posi.x" << "," << "posi.y" << "," << "size" << "," << "view" << "," << "mov" << "," << "condition" << "," << "spd.x" << "," << "spd.y" << "," << "interact_with" << endl;
    
    for(int i=0; i<index_count; i++){
        
        ag_t *elm = agents;
        log << elm->agid << "," << elm->active << "," << elm->posi.x << "," << elm->posi.y << "," << elm->size << "," << elm->view << "," << elm->mov << "," << elm->condition << "," << elm->spd.x << "," << elm->spd.y << "," << elm->interact_with << "," << endl;
        
        
        agents++;
//        cout << i << endl;
        
    }
    
    log.close();
//    cout << "CMD :: " << system("mv 0-agents.csv ../../data/.") << endl;
    cout << "CMD1 :: " << system("sh mv_agent.sh") << endl;
    cout << "CMD2 :: " << system("pwd") << endl;
    cout << "CMD3 :: " << system("ls") << endl;
    
    
}
