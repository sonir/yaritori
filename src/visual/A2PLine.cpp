//
//  A2PLine.cpp
//  a2pLine
//
//  Created by Hana on 2018/01/07.
//
//

#include "A2PLine.hpp"

////////////////// Node ///////////////////////

A2PNode::A2PNode() {
    timer.ready();
}

void A2PNode::bang(float duration) {
    timer.bang(duration);
}

void A2PNode::update() {
    float time = timer.get();
    
    pos.x = (end.x - begin.x) * time + begin.x;
    pos.y = (end.y - begin.y) * time + begin.y;
}


////////////////// Line ///////////////////////

void A2PLine::setup(float x, float y) {
    begin.x = x;
    begin.y = y;
}

void A2PLine::setDest(float x, float y) {
    end.x = x;
    end.y = y;
}

void A2PLine::bang(float duration) {
    node.bang(duration);
}

void A2PLine::update() {
    node.begin = begin;
    node.end = end;
    node.update();
}


////////////////// Manager ///////////////////////

A2PLineManager::A2PLineManager() {
    
    for(int i = 0; i < AG_MAX * 2; i++) {
        if(i < AG_MAX) {
            nodeColors[i] = ofFloatColor(0.0, 0.0, 0.0);
        }
        
        lineColors[i] = ofFloatColor(0.0, 0.0, 0.0);
    }
    
    nodenum = 0;
    nodes.setVertexData(nodeVerts, AG_MAX, GL_DYNAMIC_DRAW);
    nodes.setColorData(nodeColors, AG_MAX, GL_DYNAMIC_DRAW);
    
    lineVertCount = 0;
    lines.setVertexData(lineVerts, AG_MAX*2, GL_DYNAMIC_DRAW);
    lines.setColorData(lineColors, AG_MAX*2, GL_DYNAMIC_DRAW);
}

void A2PLineManager::addLine(A2PLine &newLine) {
    newLine.update();
    //ADD line
    //Begin
    ofVec2f pos;
    pos.x = newLine.begin.x * CANVAS_HEIGHT;
    pos.y = newLine.begin.y * CANVAS_HEIGHT;
    lineVerts[lineVertCount] = pos;
    lineVertCount++;
    //end
    pos.x = newLine.end.x * CANVAS_HEIGHT;
    pos.y = newLine.end.y * CANVAS_HEIGHT;
    lineVerts[lineVertCount] = pos;
    lineVertCount++;
    
    //Add node
    if(newLine.node.isRunning()) {
        pos.x = newLine.node.pos.x * CANVAS_HEIGHT;
        pos.y = newLine.node.pos.y * CANVAS_HEIGHT;
        nodeVerts[nodenum] = pos;
        nodenum++;
    }
}

void A2PLineManager::draw() {
    

//    nodes.updateVertexData(nodeVerts, nodenum);
    lines.updateVertexData(lineVerts, lineVertCount);
    
    
//    glEnable(GL_POINT_SMOOTH);
//    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glEnable(GL_BLEND);
//    glPointSize(8.0);
//    nodes.draw(GL_POINTS, 0, nodenum);
    
    ofSetCircleResolution(16);
    ofSetColor(0);
    for(int i = 0; i < nodenum; i++) {
        ofDrawCircle(nodeVerts[i], 6.0);
    }
    
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glLineWidth(2.0);
    lines.draw(GL_LINES, 0, lineVertCount);
    
    lineVertCount = 0;
    nodenum = 0;
}
