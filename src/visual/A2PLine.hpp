//
//  A2PLine.hpp
//  a2pLine
//
//  Created by Hana on 2018/01/07.
//
//

#ifndef A2PLine_hpp
#define A2PLine_hpp

#include "ofMain.h"
#include "timed_interpolation.hpp"
#include "ScreenManager.hpp"
#include "ofxGismo.h"


class A2PNode : public Event {
public:
    //Method
    A2PNode();
    void bang(float duration);
    void update();
    
    inline bool isRunning() {
        return !timer.waiting;
    }
    
    int trigger(void *args) {
        float* duration = (float *)args;
        this->bang(*duration);
        return 1;
    }
    
    //Variable
    posi_t begin, end, pos;
    float time;
    
private:
    TimedInterpolation timer;
};

class A2PLine : public Event {
public:
    //Method
    void setup(float x, float y);
    void update();
    void setDest(float x, float y);
    void bang(float duration);
    
    inline bool isRunning() {
        return node.isRunning();
    }
    
    int trigger(void *args) {
        float* posArray = (float *)args;
        
        begin.x = posArray[0];
        begin.y = posArray[1];
        
        end.x = posArray[2];
        end.y = posArray[3];
        
        return 1;
    }
    
    //Variables
    posi_t begin, end;
    A2PNode node;
};


class A2PLineManager {
public:
    A2PLineManager();
    void addLine(A2PLine& newLine);
    void draw();

private:
    
    //to draw line
    
    int lineVertCount;
    ofVbo lines;
    ofVec2f lineVerts[AG_MAX * 2];
    ofFloatColor lineColors[AG_MAX * 2];
    
    int nodenum;
    ofVbo nodes;
    ofVec2f nodeVerts[AG_MAX];
    ofFloatColor nodeColors[AG_MAX];
};


#endif /* A2PLine_hpp */
