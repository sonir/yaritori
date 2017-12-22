//
//  Event.hpp
//  yaritori
//
//  Created by sonir on 12/22/17.
//
//

#ifndef Event_hpp
#define Event_hpp

#include <stdio.h>
#include <iostream>
//#include "EventHandler.hpp"

class Event {
  
    public:
        virtual void set();
        virtual int trigger();
        virtual int trigger(void* args);
    
};


#endif /* Event_hpp */
