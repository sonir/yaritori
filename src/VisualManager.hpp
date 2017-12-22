//
//  VisualManager.hpp
//  docking
//
//  Created by Hana on 2017/12/20.
//
//

#ifndef VisualManager_hpp
#define VisualManager_hpp

#include "ofxGismo.h"
#include "ofMain.h"
#include "VisualAgent.hpp"

static constexpr long VIS_NODE_MAX = AG_MAX * MAX_NODES;
static constexpr long VIS_LINEINDEX_MAX = AG_MAX * MAX_NODES * MAX_CONNECTION * 2;
constexpr float VIS_NODE_LENGTH_RANGE_MAX = 0.005;

class VisualManager {
public:
    VisualManager();
    void update();
    void draw();
    void setAgent(int index, float x, float y, float size);
    void resetCount();
    
private:
    VisualAgent visualAgents[AG_MAX];
    int activeAgentsNum;
    
    //VBO
//    ofVbo nodeVbo, lineVbo;
//    int nodePosCount, nodeColorsCount, lineIndexCount, lineColorsCount;
//    ofVec2f nodePos[VIS_NODE_MAX];
//    ofFloatColor nodeColors[VIS_NODE_MAX];
//    ofIndexType lineIndex[VIS_LINEINDEX_MAX];
//    ofFloatColor lineColors[VIS_LINEINDEX_MAX];
//    int screenWidth, screenHeight;
};


#endif /* VisualManager_hpp */
