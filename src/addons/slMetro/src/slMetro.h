//
//  Metro.h
//  printAgent
//
//  Created by isana137 on 2/5/14.
//
//

#ifndef __slMetro__
#define __slMetro__

#include <iostream>
#include "ofUtils.h"
//include "print_config.h"
//#include "ofMain.h"

class slMetro {
    
    
    public:
    
        //Methods
        slMetro(float f_sec);
        void set(float val);
        bool alart();
        float progress();
        float remain();
        void resetStart();
    
        //Variables
        float start;
        float interval;
        int fps;
//        slMetro *metro;

};


#endif /* defined(__printAgent__Metro__) */
