//
//  EventHandler.cpp
//  yaritori
//
//  Created by sonir on 12/22/17.
//
//

#include "EventHandler.hpp"

void EventHandler::eventAdd(std::string event_name, Event *pEvent){
    
    events[event_name] = pEvent;
    
}


int EventHandler::bang(string event_name){
    
    if(events[event_name])
    {
        
        Event *tmp = events[event_name];
        return tmp->trigger();
        
    } else {
        
        cout << "ERR :: Unknown event named <" << event_name << "> was invoked." << endl;
        
    }
    
}


int EventHandler::bang(string event_name, void* args){
    
    Event *tmp = events[event_name];
    return tmp->trigger(args);
    
}
