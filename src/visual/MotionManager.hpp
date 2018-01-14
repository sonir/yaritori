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


class MotionManager : public Event {
public:
    MotionManager();
    AgentMotion agent[AG_MAX];
    int soloCount = 0;
    bool soloID[AG_MAX];
    
    void invertColor();
    void solo(int _id, int act);
    void addSolo(int _id);
    void deleteSolo(int _id);
    void draw();
    void drawAll();
    void drawSolo();
    
    //Methods to set pointer;
    inline void setGismoPtr(GismoManager* _gismo) {
        gismo = _gismo;
    }
    inline void setShapePtr(ag_shape_t* _pShapes) {
        pShapes = _pShapes;
    }
    
private:
    GismoManager* gismo;
    ag_shape_t* pShapes;
    //A2PLineManager lines;
    
    LineDrawer interactLine[AG_MAX];
    ofShader shader;

};



#endif /* MotionManager_hpp */
