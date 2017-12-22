//
//  VisualAgent.hpp
//  yaritori
//
//  Created by Hana on 2017/12/22.
//
//

#ifndef VisualAgent_hpp
#define VisualAgent_hpp

#include "ofMain.h"

//Static Values
constexpr float NODE_LENGTH_RANGE = 0.005;   //0.003
constexpr float NODE_LENGTH_MIN = 0.003;
constexpr float MOVE_SIZE = 0.1;
constexpr float M_2XPI = M_PI * 2.0;
constexpr int MAX_CONNECTION = 5;
constexpr int MAX_NODES = 20;
constexpr float VIS_MAX_CYCLE = M_PI * 100.0;

//Each node
struct Node {
    int id;
    float x, y;
    float size;
    float theta;
    float velocityX, velocityY;
    float modStep, carStep;
    float modPhase, carPhase;
    
    int connectionNum;
    int connectedTo[MAX_CONNECTION];
};

//Node container
struct Nodes {
    float scale_x;  //Center
    float scale_y;
    float size;
    Node node[MAX_NODES];
    int nodeNum;
};


class VisualAgent {
public:
    VisualAgent();
    void update();
    void draw();
    float modSpeed;
    Nodes nodes;
    bool isActive;
    
private:
    //VBO
    ofVbo nodeVbo, lineVbo;
    
    ofVec2f nodePos[MAX_NODES];
    ofIndexType lineIndex[MAX_NODES * MAX_CONNECTION];
    ofFloatColor colors[MAX_NODES * MAX_CONNECTION];
    ofFloatColor nodeColors[MAX_NODES * MAX_CONNECTION];
    
    //Variables
    int screenWidth, screenHeight;
    int lineNum;
    
    //Move
    float modX, modY, carrierX, carrierY;
};

#endif /* VisualAgent_hpp */
