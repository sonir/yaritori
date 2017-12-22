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

//Constant Values
constexpr float NODE_LENGTH_RANGE = 0.005;   //0.003
constexpr float NODE_LENGTH_MIN = 0.003;
constexpr float MOVE_SIZE = 0.1;
constexpr float M_2XPI = M_PI * 2.0;
constexpr int CONNECTION_MAX = 5;
constexpr int NODES_MAX = 20;
constexpr int LINE_VERTICES_MAX = NODES_MAX * CONNECTION_MAX * 2;
constexpr float STEP_MAX = M_2XPI * 0.005;
constexpr float STEP_MIN = M_2XPI * 0.003;

constexpr float LINE_WIDTH = 0.5;
constexpr float NODE_SIZE = 4.0;
constexpr float TREMOR_RATIO = 0.125;
constexpr float STAY_RATIO = 1.0 - TREMOR_RATIO;


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
};


class AgentMotion {
public:
    //Methods
    AgentMotion();
    void initModulation(int index);
    
    void draw();
    void update(int &screenWidth);
    void updatePhase(int index);
    void updatePosition(int index, int &screenWidth);
    
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
