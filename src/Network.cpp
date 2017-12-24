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
    mouseX = 0;
    mouseY = 0;
    mouseButtonState = "";
    
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
            
            if(adr == "/position"){
                
                int agid = m.getArgAsInt(1);
                float posx = m.getArgAsFloat(2);
                float posy = m.getArgAsFloat(3);
                cout << "POS :: " <<  posx << " , " << posy << endl;
            
            }else if(adr=="/view"){
                
                int agid = m.getArgAsInt(1);
                float view = m.getArgAsFloat(2);
                cout << "VIEW:: " << view << endl;
                
                
            }else if(adr=="/mov"){
                
                int agid = m.getArgAsInt(1);
                float mov = m.getArgAsFloat(2);
                cout << "MOV:: " << mov << endl;
                
                
            }
            
            
            
        }
        else if(m.getAddress() == "/mouse/position"){
            // both the arguments are int32's
            mouseX = m.getArgAsInt32(0);
            mouseY = m.getArgAsInt32(1);
        }
        // check for mouse button message
        else if(m.getAddress() == "/mouse/button"){
            // the single argument is a string
            mouseButtonState = m.getArgAsString(0);
        }
        // check for an image being sent (note: the size of the image depends greatly on your network buffer sizes - if an image is too big the message won't come through )
        else if(m.getAddress() == "/image" ){
            ofBuffer buffer = m.getArgAsBlob(0);
            receivedImage.load(buffer);
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
