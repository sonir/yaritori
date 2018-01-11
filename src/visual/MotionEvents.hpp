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


class Invert : public Event {
public:
    int trigger(void *args) {
        motionManager->invertColor();
        invertBackground();
        return 1;
    };
    inline void setMotionManagerPtr(MotionManager* pMotion) {
        motionManager = pMotion;
    }
    
private:
    MotionManager* motionManager;
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
};


#endif /* MotionEvents_hpp */
