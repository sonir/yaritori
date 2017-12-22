//
//  Sound.hpp
//  yaritori
//
//  Created by sonir on 12/22/17.
//
//

#ifndef Sound_hpp
#define Sound_hpp

#define SOUND_HOST "localhost"
#define SOUND_PORT 56137
#define AUDIO_BANK_MAX 8

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGismo.h"

class Sound : public Event {
    
public:
    Sound();
    void set(int audio_id); //Set audio_trigger in event buffer
    int update(); //send all trigger in event buffer and refresh event buffer
    ofxOscSender sender;
    int bank[AUDIO_BANK_MAX];
    int count;
    int trigger();
    
private:
    
    
};


#endif /* Sound_hpp */
