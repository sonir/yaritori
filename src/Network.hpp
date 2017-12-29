//
//  Network.hpp
//  yaritori
//
//  Created by sonir on 12/23/17.
//
//

#ifndef Network_hpp
#define Network_hpp

#include <stdio.h>
#include "ofxOsc.h"
#include "ofxGismo.h"

// listen on port 12345
#define IN_PORT 56138
#define NUM_MSG_STRINGS 20



#endif /* Network_hpp */

class Network {
    
    public:
        ofxOscReceiver sender;
        void setup();
        void update();
    
        ofTrueTypeFont font;
        ofxOscReceiver receiver;
        
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
        
        int mouseX, mouseY;
        string mouseButtonState;
        
        ofImage receivedImage;

    
    private:
        GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
        //GismoManager& gismo = GismoManager::getInstance(); //Pointer for gismoManager instance
    
    
};