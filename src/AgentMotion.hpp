//
//  AgentMotion.hpp
//  yaritori
//
//  Created by Hana on 2017/12/23.
//
//

#ifndef AgentMotion_hpp
#define AgentMotion_hpp

#include "ofMain.h"
#include "ScreenManager.hpp"

//Static Values
constexpr int CONNECTION_MAX = 5;
constexpr int NODES_MAX = 20;
constexpr int LINE_VERTICES_MAX = NODES_MAX * CONNECTION_MAX * 2;

//Each node
struct Node {
    int id;
    float x, y, size;
    float velocityX, velocityY;
    float modStep, carStep;
    float modPhase, carPhase;
    
    int connectionNum;
    int connectedTo[CONNECTION_MAX];
};

//Node container
struct Nodes {
    float scale_x;  //Center
    float scale_y;
    float size;
    Node node[NODES_MAX];
    int nodeNum;
    float mov;
};


class AgentMotion {
public:
    //Methods
    AgentMotion();
    void initModulation(int index);
    
    void draw();
    void update();
    void update(int &canvasWidth);
    void update(int canvasWidth, int canvasHeight);
    void updatePhase(int index);
    void updatePosition(int index);
    void updatePosition(int index, int &scale);
    void updatePosition(int index, int &canvasWidth, int &canvasHeight);
    float getPointSize();
    float getLineWidth();
    
    //Variables
    Nodes nodes;
    int screenWidth, screenHeight;
    bool isActive;
    
private:
    //VBO
    ofVbo nodeVbo, lineVbo;
    ofVec2f nodePos[NODES_MAX];
    ofFloatColor nodeColors[NODES_MAX * CONNECTION_MAX];
    ofIndexType lineIndex[LINE_VERTICES_MAX];
    ofFloatColor lineColors[LINE_VERTICES_MAX];
    
    
    //Variables
    int lineNum;
    float phase, nodeX, nodeY;
};


#endif /* AgentMotion_hpp */
