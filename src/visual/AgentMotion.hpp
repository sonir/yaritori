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
#include "animation_setup.hpp"
#include "ofxGismo.h"
#include "ag_shape.h"



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
    void updateCenter();
    void updatePosition();
    void updateIndex();
    void updateColors();
    float getPointSize();
    float getLineWidth();
    void move(float x, float y);
    
    void setShapePtr(ag_shape_t *shapePtr);
    
    //event
    void invertColor();
    void setColor(float c);
    
    
    //Variables
    ag_shape_t shape;
    ag_shape_t* pShape;
    ag_t* pAg;
    int screenWidth, screenHeight;
    bool isActive;
    float size;
    float width_rate;
    ofVec2f center, dest;
    float centerX ,centerY;
    

private:
    //VBO
    ofVbo nodeVbo, edgeVbo;
    ofVec2f nodePos[NODE_MAX];
    ofFloatColor nodeColors[NODE_MAX];
    ofIndexType edgeIndices[EDGE_MAX * 2];
    ofFloatColor edgeColors[EDGE_MAX * 2];
    
    //ofShader shader;
    float aspect;
    
    //Variables
    float color;
    
    //Modulation
    static constexpr int MOD_NUM = 7;
    float velocityX[NODE_MAX];
    float velocityY[NODE_MAX];
    float modStep[MOD_NUM];
    float carStep[MOD_NUM];
    float modPhase[MOD_NUM];
    float carPhase[MOD_NUM];
    float phase[MOD_NUM];
    float sizeMod;
    float grayScale;
    float t;
    float size_t;
};




#endif /* AgentMotion_hpp */
