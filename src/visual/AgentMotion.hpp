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
#include "ofxGismo.h"
#include "ag_shape.h"
#include "A2PLine.hpp"


struct vec2 {
    float x;
    float y;
};

class AgentMotion {
public:
    //Methods
    AgentMotion();
    void resetShape();
    void initModulation();
    void initVbo();
    
    void draw();
    void update();
    void updatePhase();
    void updatePosition();
    void updateIndex();
    void updateColors();
    float getPointSize();
    float getLineWidth();
    
    void setShapePtr(ag_shape_t *shapePtr);
    
    //event
    void invertColor();
    
    //Variables
    ag_shape_t shape;
    ag_shape_t* pShape;
    int screenWidth, screenHeight;
    bool isActive;
    float size;
    float width_rate;
    float mov;
    vec2 center;
    float centerX ,centerY;
    
    //Interaction
    A2PLine interaction;

private:
    //VBO
    ofVbo nodeVbo, edgeVbo;
    ofVec2f nodePos[NODE_MAX];
    ofFloatColor nodeColors[NODE_MAX];
    ofIndexType edgeIndices[EDGE_MAX * 2];
    ofFloatColor edgeColors[EDGE_MAX * 2];
    
    ofShader shader;
    
    //Variables
    float color;
    
    //Modulation
    float velocityX[NODE_MAX];
    float velocityY[NODE_MAX];
    float modStep[NODE_MAX];
    float carStep[NODE_MAX];
    float modPhase[NODE_MAX];
    float carPhase[NODE_MAX];
    float phase[NODE_MAX];
    float grayScale;
    float t;
};




#endif /* AgentMotion_hpp */
