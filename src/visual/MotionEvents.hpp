//
//  MotionEvents.hpp
//  yaritori
//
//  Created by Hana on 2018/01/05.
//
//

#ifndef MotionEvents_hpp
#define MotionEvents_hpp

#include "MotionManager.hpp"
#include "RippleManager.hpp"


class Invert : public Event {
public:
    int trigger() {
        motionManager->invertColor();
        rippleManager->invert();
        invertBackground();
        return 1;
    };
    inline void setMotionManagerPtr(MotionManager* pMotion) {
        motionManager = pMotion;
    }
    inline void setRippleManagerPtr(RippleManager* pRipple) {
        rippleManager = pRipple;
    }
    
private:
    MotionManager* motionManager;
    RippleManager* rippleManager;
};

class Solo : public Event {
public:
    int trigger(void *arg) {
        int* id = (int *)arg;
        motionManager->solo(id[0], id[1]);
        return 1;
    };
    inline void setMotionManagerPtr(MotionManager* pMotion) {
        motionManager = pMotion;
    }
    
private:
    MotionManager* motionManager;
};


class MotionEvents : public Event {
public:
    Invert invert;
    Solo solo;
    inline void setMotionManagerPtr(MotionManager* pMotion) {
        invert.setMotionManagerPtr(pMotion);
        solo.setMotionManagerPtr(pMotion);
    }
    inline void setRippleManagerPtr(RippleManager* pRipple) {
        invert.setRippleManagerPtr(pRipple);
    }
};


#endif /* MotionEvents_hpp */
