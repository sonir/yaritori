//
//  MotionManager.hpp
//  yaritori
//
//  Created by Hana on 2018/01/05.
//
//

#ifndef MotionManager_hpp
#define MotionManager_hpp

#include "ofMain.h"
#include "ofxGismo.h"
#include "ag_shape.h"
#include "AgentMotion.hpp"
#include "LineDrawer.hpp"
#include "timed_interpolation.hpp"
#include "Sound.hpp"


class MotionManager : public Event {
public:
    MotionManager();
    AgentMotion agent[AG_MAX];
    int soloCount = 0;
    bool isSolo[AG_MAX];
    void setShapes();
    
    void invertColor();
    void updateSolo();
    void update();
    void solo(int _id, bool status, float duration);
    void addSolo(int _id, float duration);
    void deleteSolo(int _id);
    void draw();
    void drawAgent(ag_t* ag);
    void drawAll();
    void drawSolo();
    void sendOSC(const string adr, param_u* args, int argNum);
    
    
    //Methods to set pointer;
    inline void setGismoPtr(GismoManager* _gismo) {
        gismo = _gismo;
    }
    inline void setShapePtr(ag_shape_t* _pShapes) {
        pShapes = _pShapes;
        setShapes();
    }
    
private:
    GismoManager* gismo;
    ag_shape_t* pShapes;

    
    LineDrawer interactLine[AG_MAX];
    ofShader shader;
    TimedInterpolation soloTimers[AG_MAX];
    
    ofxOscSender sender;
    
    bool bSolo;

};



#endif /* MotionManager_hpp */
