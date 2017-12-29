//
//  Sound.cpp
//  yaritori
//
//  Created by sonir on 12/22/17.
//
//

#include "Sound.hpp"

Sound::Sound(){
    
    sender.setup(SOUND_HOST,SOUND_PORT);
    count = 0;
    
    //InitAudioBank
    for(int i=0; i<AUDIO_BANK_MAX; i++){
        
        bank[i]=0;
        
    }
    
}


void Sound::set(int audio_id){
    
    if(count >= AUDIO_BANK_MAX){

        update();
        
    }
    
    bank[count]=audio_id;
    count++;
    
}

int Sound::update(){
    
    ofxOscMessage m;
    m.setAddress("/sound_trg");
    
    
    for(int i=0; i<count; i++){
        
        m.addIntArg(bank[i]);
        
    }
    
    if(count !=0){
        count = 0; //reset count
        sender.sendMessage(m,false);
    }
    return 0;
}

int Sound::trigger(void* arg){
    
    int *audio_id = (int *)arg;
    this->set(*audio_id);
    
    return *audio_id;

//    update();
//    return 0;
}

void Sound::reset(){
    
    count = 0;
    
}
