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
    
    //InitAudioBank
    for(int i=0; i<AUDIO_BANK_MAX; i++){
        
        bank[i]=0;
        
    }
    
}


void Sound::set(int audio_id){
        
    //Check audio_id is available
    if (audio_id >= AUDIO_BANK_MAX) return;
    else bank[audio_id] = 1;
    
    
}

int Sound::update(){
    
    ofxOscMessage m;
    m.setAddress("/sound_trg");
    
    
    for(int i=0; i<AUDIO_BANK_MAX; i++){
        
        m.addIntArg(bank[i]);
        
    }
    
    sender.sendMessage(m,false);
    resetBank();
    return 0;
}

int Sound::trigger(void* arg){
    
    int *audio_id = (int *)arg;
    int tmp = *audio_id;
    this->set(tmp);
    
    return *audio_id;

//    update();
//    return 0;
}


void Sound::resetBank(){
    
    for(int i=0;i<AUDIO_BANK_MAX; i++){
        
        bank[i]=0;
        
    }
    
}

void Sound::reset(){
    
    
}


bool Sound::bankIsEmpty(){
    
    
    for(int i=0; i<AUDIO_BANK_MAX;i++) if(bank[i]!=0) return false;

    return true;
    
}
