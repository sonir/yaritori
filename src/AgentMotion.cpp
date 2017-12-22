//
//  AgentMotion.cpp
//  yaritori
//
//  Created by Hana on 2017/12/23.
//
//

#include "AgentMotion.hpp"


AgentMotion::AgentMotion() {
    nodes.scale_x = 0.0;
    nodes.scale_y = 0.0;
    
    //nodes.nodeNum = int(ofRandom(10, MAX_NODES));
    nodes.nodeNum = NODES_MAX;
    
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
    glPointSize(NODE_SIZE);
    nodeVbo.draw(GL_POINTS, 0, nodes.nodeNum);
    
    glLineWidth(LINE_WIDTH);
    lineVbo.drawElements(GL_LINES, lineNum);
}

void AgentMotion::updatePhase(int index) {
    /* Update Phases */
    nodes.node[index].carPhase += nodes.node[index].carStep;    //Carrier
    if(M_2XPI < nodes.node[index].carPhase) {
        nodes.node[index].carPhase = 0.0;
    }
    
    nodes.node[index].modPhase += nodes.node[index].modStep;    //Modulater
    if(M_2XPI < nodes.node[index].modPhase) {
        nodes.node[index].modPhase = 0.0;
    }
    
    phase = (sin(nodes.node[index].carPhase) + sin(nodes.node[index].modPhase)) * TREMOR_RATIO;   // -0.5 to 0.5
}



void AgentMotion::updatePosition(int index, int &screenWidth) {
    /* Update Position */
    ofVec2f nextPos;
    nodeX = (nodes.node[index].velocityX * phase + nodes.node[index].x * STAY_RATIO) * nodes.size;
    nodeY = (nodes.node[index].velocityY * phase + nodes.node[index].y * STAY_RATIO) * nodes.size;
    
    /* Position on Screen */
    nextPos.x = screenWidth * (nodeX + nodes.scale_x);
    nextPos.y = screenWidth * (nodeY + nodes.scale_y);
    
    nodePos[index] = nextPos; //Set position onto Array
}

void AgentMotion::update(int &screenWidth) {
    /* Update Node, Position Array */
    for(int i = 0; i < nodes.nodeNum; i++) {
        /*** on each node ***/
        updatePhase(i);
        updatePosition(i, screenWidth);
    }
    
    
    /* Update VBO*/
    nodeVbo.updateVertexData(nodePos, nodes.nodeNum);
    lineVbo.updateVertexData(nodePos, nodes.nodeNum);
}


void AgentMotion::initModulation(int index) {
    ofVec2f vel = ofVec2f(ofRandom(-1.0, 1.0), ofRandom(-1.0, 1.0)).getNormalized();
    
    nodes.node[index].velocityX = vel.x;
    nodes.node[index].velocityY = vel.y;
    
    nodes.node[index].modStep = ofRandom(STEP_MIN, STEP_MAX);
    nodes.node[index].carStep = ofRandom(STEP_MIN, STEP_MAX);
    
    nodes.node[index].modPhase = 0.0;
    nodes.node[index].carPhase = 0.0;
}

