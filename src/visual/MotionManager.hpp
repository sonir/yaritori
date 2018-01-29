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
    
//    void invertColor();
    void setColor(float c);
    void setEvents();
    
    void updateSolo();
    void update();
    void solo(int _id, bool status, float duration = 1.0);
    void addSolo(int _id, float duration);
    void deleteSolo(int _id);
    void draw();
    void drawAgent(ag_t* ag);
    void drawAll();
    void drawSolo();
    void sendOSC(const string adr, param_u* args, int argNum);
    bool isSoloMode();
    void setTremble(animation_mode_e state);
    
    void addNode(ofVec2f pos);
    void addEdge(ofVec2f node_a, ofVec2f node_b);
    float aspect;
    
    
    //Methods to set pointer;
//    inline void setGismoPtr(GismoManager* _gismo) {
//        gismo = _gismo;
//    }
    inline void setShapePtr(ag_shape_t* _pShapes) {
        pShapes = _pShapes;
        setShapes();
    }
    
private:
    GismoManager& gismo = GismoManager::getInstance();
    ag_shape_t* pShapes;

    
    LineDrawer interactLine[AG_MAX];
    LineDrawer debugLine;
    ofShader shader;
    TimedInterpolation soloTimers[AG_MAX];
    
    ofxOscSender sender;
    
    bool bSolo;
    
    ofVbo nodeVbo, edgeVbo;
    ofVec2f nodePos[NODE_MAX * AG_MAX];
    ofFloatColor nodeColors[NODE_MAX * AG_MAX];
    ofVec2f edgePos[NODE_MAX * AG_MAX];
    ofIndexType edgeIndices[EDGE_MAX * 2 * AG_MAX];
    ofFloatColor edgeColors[EDGE_MAX * 2 * AG_MAX];

};



#endif /* MotionManager_hpp */
