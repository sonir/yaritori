//
//  VisualAgent.cpp
//  yaritori
//
//  Created by Hana on 2017/12/22.
//
//

#include "VisualAgent.hpp"

VisualAgent::VisualAgent() {
    screenWidth = ofGetWidth();
    screenHeight = ofGetHeight();
    
    nodes.scale_x = 0.0;
    nodes.scale_y = 0.0;
    
    nodes.nodeNum = int(ofRandom(4, MAX_NODES));
    
    /* Set Node pos and connection */
    for(int i = 0; i < nodes.nodeNum; i++) {
        nodes.node[i].id = i;
        //Set Position
        nodes.node[i].x = ofRandom(-0.01, 0.01);    //Position of each node is currently random
        nodes.node[i].y = ofRandom(-0.01, 0.01);
        
        //Set Connection
        if(nodes.nodeNum < 3) { //Connections are also random
            nodes.node[i].connectionNum = int(ofRandom(1.0, 2));
        } else {
            nodes.node[i].connectionNum = int(ofRandom(1.0, MAX_CONNECTION));
        }
        
        if(i < nodes.nodeNum -1 ) {
            nodes.node[i].connectedTo[0] = (i + 1);
        }
        
        for(int j = 1; j < nodes.node[i].connectionNum; j++) {
            nodes.node[i].connectedTo[j] = int(ofRandom(nodes.nodeNum));
        }
    }
    
    /* Each node */
    for(int i = 0; i < nodes.nodeNum; i++) {
        ofVec2f vel = ofVec2f(ofRandom(-0.5, 0.5), ofRandom(-0.5, 0.5)).getNormalized();
        
        nodes.node[i].velocityX = vel.x;
        nodes.node[i].velocityY = vel.y;
        
        nodes.node[i].modStep = ofRandom(M_2XPI * 0.003, M_2XPI * 0.005);
        nodes.node[i].carStep = ofRandom(M_2XPI * 0.003, M_2XPI * 0.005);
        
        nodes.node[i].modPhase = 0.0;
        nodes.node[i].carPhase = 0.0;
    }
    
    
    /* Vbo */
    lineNum = 0;
    for(int i = 0; i < nodes.nodeNum; i++) {
        int x = (nodes.node[i].x + nodes.scale_x) * screenWidth;
        int y = (nodes.node[i].y + nodes.scale_y) * screenHeight;
        //Node
        nodePos[i] = ofVec2f(x, y);
        nodeColors[i] = ofFloatColor(0.1, 0.1, 0.1);
        
        //Line
        for(int j = 0; j < nodes.node[i].connectionNum; j++) {
            lineIndex[lineNum] = i; //This node
            colors[lineNum] = ofFloatColor(0.1, 0.1, 0.1);
            lineNum++;
            
            lineIndex[lineNum] = nodes.node[i].connectedTo[j];  //Connected Node
            colors[lineNum] = ofFloatColor(0.1, 0.1, 0.1);
            lineNum++;
        }
    }
    
    nodeVbo.setVertexData(nodePos, nodes.nodeNum, GL_DYNAMIC_DRAW);
    nodeVbo.setColorData(nodeColors, nodes.nodeNum, GL_DYNAMIC_DRAW);
    
    lineVbo.setVertexData(nodePos, nodes.nodeNum, GL_DYNAMIC_DRAW);
    lineVbo.setIndexData(lineIndex, lineNum, GL_DYNAMIC_DRAW);
    lineVbo.setColorData(colors, lineNum, GL_DYNAMIC_DRAW);
    
    isActive = false;
    modSpeed = 0.5;
}


void VisualAgent::draw() {
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(3.0);
    nodeVbo.draw(GL_POINTS, 0, nodes.nodeNum);
    
    glPointSize(0.5);
    glLineWidth(0.5);
    lineVbo.drawElements(GL_LINES, lineNum);
}


void VisualAgent::update() {
    /* Control Move */
    
    //Center
    //nodes.scale_x += (ofNoise(nodes.node[0].modPhase * nodes.nodeNum) - 0.5) * 0.0001;
    //nodes.scale_y += (ofNoise(nodes.node[0].carPhase * nodes.nodeNum) - 0.5) * 0.0001;
    
    
    /* Update Node, Position Array */
    for(int i = 0; i < nodes.nodeNum; i++) {
        /* Node */
        /* Update Phases */
        nodes.node[i].carPhase += nodes.node[i].carStep;    //Carrier
        if(M_2XPI < nodes.node[i].carPhase) {
            nodes.node[i].carPhase = 0.0;
        }
        
        
        nodes.node[i].modPhase += nodes.node[i].modStep;    //Modulater
        if(M_2XPI < nodes.node[i].modPhase) {
            nodes.node[i].modPhase = 0.0;
        }
        
        
        /* Update Position */
        float phase = sin(nodes.node[i].carPhase + sin(nodes.node[i].modPhase));  //FM
        //float phase = (sin(nodes.node[i].carPhase) + sin(nodes.node[i].modPhase)) * 0.5;   // -1.0 to 1.0
        
        float nodeX = (nodes.node[i].velocityX * phase) * nodes.size + nodes.node[i].x;
        float nodeY = (nodes.node[i].velocityY * phase) * nodes.size + nodes.node[i].y;
        
        
        /* Position on Screen */
        int x = (nodeX + nodes.scale_x) * screenWidth;
        int y = (nodeY + nodes.scale_y) * screenWidth;
        
        //Set position on Array
        nodePos[i] = ofVec2f(x, y);
    }
    
    
    /* Update VBO*/
    nodeVbo.updateVertexData(nodePos, nodes.nodeNum);
    lineVbo.updateVertexData(nodePos, nodes.nodeNum);
    
}





