//
//  AgentMotion.cpp
//  yaritori
//
//  Created by Hana on 2017/12/23.
//
//

#include "AgentMotion.hpp"


//Constant Values
constexpr float NODE_LENGTH_RANGE = 0.005;   //0.003
constexpr float NODE_LENGTH_MIN = 0.003;
constexpr float MOVE_SIZE = 0.1;
constexpr float M_2XPI = M_PI * 2.0;

constexpr float STEP_MAX = M_2XPI * 5.0;
constexpr float STEP_MIN = M_2XPI * 3.0;

constexpr float LINE_WIDTH = 0.5;
constexpr float NODE_SIZE = 4.0;
constexpr float TREMOR_RATIO = 0.125;
constexpr float STAY_RATIO = 1.0 - TREMOR_RATIO;

AgentMotion::AgentMotion() {
    nodes.scale_x = 0.0;
    nodes.scale_y = 0.0;
    
    //nodes.nodeNum = int(ofRandom(10, MAX_NODES));
    nodes.nodeNum = NODES_MAX;
    nodes.mov = 0.5;
    width_rate = 1.0;
    
    
    /* Set Node pos and connection */
    for(int i = 0; i < nodes.nodeNum; i++) {
        nodes.node[i].id = i;
        
        //Set Position
        nodes.node[i].x = ofRandom(-0.5, 0.5);    //Position of each node is currently random
        nodes.node[i].y = ofRandom(-0.5, 0.5);    //Prev :: -0.01, 0.01
        
        //Set Connection
        if(nodes.nodeNum < 3) { //Connections are also random
            nodes.node[i].connectionNum = int(ofRandom(1, 2));
        } else {
            nodes.node[i].connectionNum = int(ofRandom(1, CONNECTION_MAX));
        }
        
        if(i < nodes.nodeNum -1 ) {
            nodes.node[i].connectedTo[0] = (i + 1);
        }
        
        for(int j = 1; j < nodes.node[i].connectionNum; j++) {
            nodes.node[i].connectedTo[j] = int(ofRandom(nodes.nodeNum));
        }
    }
    
    /* Set Modulation */
    for(int i = 0; i < nodes.nodeNum; i++) {
        initModulation(i);
    }
    
    
    /* Vbo */
    lineNum = 0;
    int tmpWidth = ofGetWidth();
    for(int i = 0; i < nodes.nodeNum; i++) {
        int x = (nodes.node[i].x + nodes.scale_x) * tmpWidth;
        int y = (nodes.node[i].y + nodes.scale_y) * tmpWidth;
        //Node
        nodePos[i] = ofVec2f(x, y);
        nodeColors[i] = ofFloatColor(0.0f, 0.0f, 0.0f);
        
        //Line
        for(int j = 0; j < nodes.node[i].connectionNum; j++) {
            lineIndex[lineNum] = i; //This node
            lineColors[lineNum] = ofFloatColor(0.0f, 0.0f, 0.0f);
            lineNum++;
            
            lineIndex[lineNum] = nodes.node[i].connectedTo[j];  //Connected Node
            lineColors[lineNum] = ofFloatColor(0.0f, 0.0f, 0.0f);
            lineNum++;
        }
    }
    
    nodeVbo.setVertexData(nodePos, nodes.nodeNum, GL_DYNAMIC_DRAW);
    nodeVbo.setColorData(nodeColors, nodes.nodeNum, GL_DYNAMIC_DRAW);
    
    lineVbo.setVertexData(nodePos, nodes.nodeNum, GL_DYNAMIC_DRAW);
    lineVbo.setIndexData(lineIndex, lineNum, GL_DYNAMIC_DRAW);
    lineVbo.setColorData(lineColors, lineNum, GL_DYNAMIC_DRAW);
}


void AgentMotion::draw() {
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(getPointSize());
    nodeVbo.draw(GL_POINTS, 0, nodes.nodeNum);
    
    
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(getLineWidth());
    lineVbo.drawElements(GL_LINES, lineNum);
}

/////////////////// UPDATE POSITION /////////////////////

void AgentMotion::updatePhase(int index) {
    /* Update Phases */
    nodes.node[index].carPhase += nodes.node[index].carStep * nodes.mov;    //Carrier
    if(M_2XPI < nodes.node[index].carPhase) {
        nodes.node[index].carPhase = 0.0;
    }
    
    nodes.node[index].modPhase += nodes.node[index].modStep * nodes.mov;    //Modulater
    if(M_2XPI < nodes.node[index].modPhase) {
        nodes.node[index].modPhase = 0.0;
    }
    
    phase = (sin(nodes.node[index].carPhase) + sin(nodes.node[index].modPhase)) * TREMOR_RATIO;   // -0.5 to 0.5
}



/////////////////// UPDATE POSITION /////////////////////
void AgentMotion::updatePosition(int index) {
    /* Update Position */
    ofVec2f nextPos;
    nodeX = (nodes.node[index].velocityX * phase + nodes.node[index].x * STAY_RATIO) * nodes.size;
    nodeY = (nodes.node[index].velocityY * phase + nodes.node[index].y * STAY_RATIO) * nodes.size;
    
    /* Position on Screen */
    //nextPos.x = (nodeX + nodes.scale_x) * SCREEN_HEIGHT * width_rate;
    nextPos.x = (nodeX * CANVAS_HEIGHT) + (nodes.scale_x * CANVAS_WIDTH);
    nextPos.y = (nodeY + nodes.scale_y) * CANVAS_HEIGHT;
    
    nodePos[index] = nextPos; //Set position onto Array
}

void AgentMotion::updatePosition(int index, int &scale) {
    /* Update Position */
    ofVec2f nextPos;
    nodeX = (nodes.node[index].velocityX * phase + nodes.node[index].x * STAY_RATIO) * nodes.size;
    nodeY = (nodes.node[index].velocityY * phase + nodes.node[index].y * STAY_RATIO) * nodes.size;
    
    /* Position on Screen */
    nextPos.x = scale * (nodeX + nodes.scale_x);
    nextPos.y = scale * (nodeY + nodes.scale_y);
    
    nodePos[index] = nextPos; //Set position onto Array
}

void AgentMotion::updatePosition(int index, int &canvasWidth, int &canvasHeight) {
    /* Update Position */
    ofVec2f nextPos;
    nodeX = (nodes.node[index].velocityX * phase + nodes.node[index].x * STAY_RATIO) * nodes.size;
    nodeY = (nodes.node[index].velocityY * phase + nodes.node[index].y * STAY_RATIO) * nodes.size;
    
    /* Position on Screen */
    nextPos.x = canvasWidth * (nodeX + nodes.scale_x);
    nextPos.y = canvasHeight * (nodeY + nodes.scale_y);
    
    nodePos[index] = nextPos; //Set position onto Array
}

/////////////////// UPDATE /////////////////////

void AgentMotion::update() {
    /* Update Node, Position Array */
    for(int i = 0; i < nodes.nodeNum; i++) {
        /*** on each node ***/
        updatePhase(i);
        updatePosition(i);
    }
    
    
    /* Update VBO*/
    nodeVbo.updateVertexData(nodePos, nodes.nodeNum);
    lineVbo.updateVertexData(nodePos, nodes.nodeNum);
}

void AgentMotion::update(int &canvasWidth) {
    /* Update Node, Position Array */
    for(int i = 0; i < nodes.nodeNum; i++) {
        /*** on each node ***/
        updatePhase(i);
        updatePosition(i, canvasWidth);
    }
    
    
    /* Update VBO*/
    nodeVbo.updateVertexData(nodePos, nodes.nodeNum);
    lineVbo.updateVertexData(nodePos, nodes.nodeNum);
}


void AgentMotion::update(int canvasWidth, int canvasHeight) {
    /* Update Node, Position Array */
    for(int i = 0; i < nodes.nodeNum; i++) {
        /*** on each node ***/
        updatePhase(i);
        updatePosition(i, canvasWidth, canvasHeight);
    }
    
    
    /* Update VBO*/
    nodeVbo.updateVertexData(nodePos, nodes.nodeNum);
    lineVbo.updateVertexData(nodePos, nodes.nodeNum);
}

/////////////////// INIT /////////////////////

void AgentMotion::initModulation(int index) {
    ofVec2f vel = ofVec2f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0)).getNormalized();
    
    nodes.node[index].velocityX = vel.x;
    nodes.node[index].velocityY = vel.y;
    
    nodes.node[index].modStep = ofRandom(STEP_MIN, STEP_MAX);
    nodes.node[index].carStep = ofRandom(STEP_MIN, STEP_MAX);
    
    nodes.node[index].modPhase = 0.0;
    nodes.node[index].carPhase = 0.0;
}

float AgentMotion::getPointSize() {
    float pointSize = 4.0;
    if(nodes.size < 0.02) {
        pointSize = 2.0;
    } else if (0.02 <= nodes.size && nodes.size < 0.03) {
        pointSize = 2.5;
    } else if(0.03 <= nodes.size && nodes.size < 0.04) {
        pointSize = 3.0;
    } else if(0.04 <= nodes.size && nodes.size < 0.05) {
        pointSize = 3.5;
    } else {
        pointSize += 8.0 * nodes.size;
    }
    
    
    return pointSize;
}

float AgentMotion::getLineWidth() {
    float lineWidth = 0.5;
    if(nodes.size <= 0.01) {
        lineWidth = 0.05;
    } else if (0.01 < nodes.size && nodes.size < 0.02) {
        lineWidth = 0.1;
    } else if(0.02 <= nodes.size && nodes.size < 0.05) {
        lineWidth = 0.25;
    }
    return lineWidth;
}
