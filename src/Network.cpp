//
//  Network.cpp
//  yaritori
//
//  Created by sonir on 12/23/17.
//
//

#include "Network.hpp"


void Network :: setup(){
    
    cout << "network:setup()" << endl;
    
    receiver.setup(IN_PORT);
    current_msg_string = 0;
    
}

void Network :: update(){
    
//    cout << "Newwork::update" << endl;
    
    // hide old messages
    for(int i = 0; i < NUM_MSG_STRINGS; i++){
        if(timers[i] < ofGetElapsedTimef()){
            msg_strings[i] = "";
        }
    }
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
        // check for mouse moved message
        if(m.getAddress() == "/agent_control"){
            
            string adr = m.getArgAsString(0);
            int agid = m.getArgAsInt(1);
            ag_t *pAg = gismo.getAgent(agid);
            
            if(adr == "/position"){
                
                pAg->posi.x = m.getArgAsFloat(2);
                pAg->posi.y = m.getArgAsFloat(3);
                cout << "POS :: " <<  pAg->posi.x << " , " << pAg->posi.y << endl;
            
            }else if(adr=="/view"){
                
                 pAg->view = m.getArgAsFloat(2);
                cout << "VIEW:: " << pAg->view << endl;
                
                
            }else if(adr=="/mov"){
                
                 pAg->mov = m.getArgAsFloat(2);
                cout << "MOV:: " << pAg->mov << endl;
                
            }
            
            
            
        }
        else{
            // unrecognized message: display on the bottom of the screen
            string msg_string;
            msg_string = m.getAddress();
            msg_string += ": ";
            for(int i = 0; i < m.getNumArgs(); i++){
                // get the argument type
                msg_string += m.getArgTypeName(i);
                msg_string += ":";
                // display the argument - make sure we get the right type
                if(m.getArgType(i) == OFXOSC_TYPE_INT32){
                    msg_string += ofToString(m.getArgAsInt32(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
                    msg_string += ofToString(m.getArgAsFloat(i));
                }
                else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
                    msg_string += m.getArgAsString(i);
                }
                else{
                    msg_string += "unknown";
                }
            }
            // add to the list of strings to display
            msg_strings[current_msg_string] = msg_string;
            timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
            current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
            // clear the next line
            msg_strings[current_msg_string] = "";
        }
        
    }
    
}
