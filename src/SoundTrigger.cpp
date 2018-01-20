//
//  SoundTrigger.cpp
//  yaritori
//
//  Created by sonir on 1/20/18.
//
//

#include "SoundTrigger.hpp"

sound_t shape2sound(ag_shape_t shape, int ag_id){
    
    sound_t snd;
    
    if ( shape.node_count>GENRE0 ){
        
        snd.genre = 5;
        
    }else if( shape.node_count>GENRE1 ){

        snd.genre = 4;
        
    }else if( shape.node_count>GENRE2 ){

        snd.genre = 3;
        
    }else if( shape.node_count>GENRE3 ){

        snd.genre = 2;
        
    }else if( shape.node_count>GENRE4 ){

        snd.genre = 1;
        
    }else if( shape.node_count>GENRE5 ){

        snd.genre = 0;
        
    }else if( shape.node_count<GENRE5 ){
        
        snd.genre = 0;
        
    }
    
    snd.song = ag_id%1000;
    
    return snd;
    
    
}


sound_t ag2sound(ag_t *ag, sound_t *snd){
    

    snd->slice = (int)ag->condition;

    int ival;
    float fval;

    switch(ag->condition){
            
        case CALM:
            ival = 0;
            fval = EF_VAL_CALM;
            break;
            
        case RUN:
            ival = 1;
            fval = EF_VAL_RUN;
            break;
            
        case CHASE:
            ival = 2;
            fval = EF_VAL_CHASE;
            break;
            
        case DMG:
            ival = 3;
            fval = EF_VAL_DMG;
            break;
            
        case DEATH:
            ival = 4;
            fval = EF_VAL_DEATH;
            break;
            
    }
    //Set slice with condition
    snd->slice = ival;
    //Set the efval according to condition
    snd->effect_val = fval;
    
}

//soundTrigger
void SoundTrigger::trigger(void *args){
        
    param_u *params = (param_u *)args;
    
    ofxOscMessage m;
    m.setAddress("/sound/set");
    m.addIntArg(params[0].ival); //Set GenreID
    m.addIntArg(params[1].ival); //set SongID
    m.addIntArg(params[2].ival); //set SliceID
    m.addFloatArg(params[3].fval); //set Effect val
    //Send Created Message
    sender.sendMessage(m,false);

    
    
    
}

//void SoundTrigger::triggerWithAgent(void *args){
//    
//    
//    
//}


