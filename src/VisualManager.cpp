//
//  VisualManager.cpp
//  docking
//
//  Created by Hana on 2017/12/20.
//
//

#include "VisualManager.hpp"

VisualManager::VisualManager() {
//    resetCount();
//    screenWidth = ofGetWidth();
//    screenHeight = ofGetHeight();
//        lineNum = 0;
//        for(int i = 0; i < nodes.nodeNum; i++) {
//            int x = (nodes.node[i].x + nodes.scale_x) * screenWidth;
//            int y = (nodes.node[i].y + nodes.scale_y) * screenHeight;
//            //Node
//            nodePos[i] = ofVec2f(x, y);
//            nodeColors[i] = ofFloatColor(0.1, 0.1, 0.1);
//    
//            //Line
//            for(int j = 0; j < nodes.node[i].connectionNum; j++) {
//                lineIndex[lineNum] = i; //This node
//                colors[lineNum] = ofFloatColor(0.1, 0.1, 0.1);
//                lineNum++;
//    
//                lineIndex[lineNum] = nodes.node[i].connectedTo[j];  //Connected Node
//                colors[lineNum] = ofFloatColor(0.1, 0.1, 0.1);
//                lineNum++;
//            }
//        }
//    
//        nodeVbo.setVertexData(nodePos, nodes.nodeNum, GL_DYNAMIC_DRAW);
//        nodeVbo.setColorData(nodeColors, nodes.nodeNum, GL_DYNAMIC_DRAW);
//    
//        lineVbo.setVertexData(nodePos, nodes.nodeNum, GL_DYNAMIC_DRAW);
//        lineVbo.setIndexData(lineIndex, lineNum, GL_DYNAMIC_DRAW);
//        lineVbo.setColorData(colors, lineNum, GL_DYNAMIC_DRAW);
    
    
//    for(int i = 0; i < VIS_NODE_MAX; i++) {
//        nodePos[i].set(ofRandomWidth(), ofRandomHeight());
//        nodeColors[i] = ofFloatColor(1.0, 1.0, 1.0);
//    }
//    
//    for(int i = 0; i < VIS_LINEINDEX_MAX; i++) {
//        lineIndex[i] = 0;
//        lineColors[i] = ofFloatColor(1.0, 1.0, 1.0);
//    }
//    
//    nodeVbo.setVertexData(nodePos, VIS_NODE_MAX, GL_DYNAMIC_DRAW);
//    nodeVbo.setColorData(nodeColors, VIS_NODE_MAX, GL_DYNAMIC_DRAW);
//
//    lineVbo.setVertexData(nodePos,  VIS_NODE_MAX, GL_DYNAMIC_DRAW);
//    lineVbo.setIndexData(lineIndex, VIS_LINEINDEX_MAX, GL_DYNAMIC_DRAW);
//    lineVbo.setColorData(lineColors, VIS_LINEINDEX_MAX, GL_DYNAMIC_DRAW);
    
    activeAgentsNum = 0;
}

void VisualManager::draw() {
//    nodeVbo.updateVertexData(nodePos, nodePosCount);
//    nodeVbo.updateColorData(nodeColors, nodePosCount);
//    
//    lineVbo.updateVertexData(nodePos,  nodePosCount);
//    lineVbo.updateIndexData(lineIndex, lineIndexCount);
//    lineVbo.updateColorData(lineColors, lineIndexCount);
//    
//    glPointSize(4.0);
//    nodeVbo.draw(GL_POINTS, 0, nodePosCount);
//    glPointSize(1.0);
//    glLineWidth(1.0);
//    lineVbo.drawElements(GL_LINES, lineIndexCount);
//    
//    resetCount();
    
    for(int i = 0; i < AG_MAX; i++) {
        if(visualAgents[i].isActive) {
            visualAgents[i].update();
            visualAgents[i].draw();
        }
    }
}

void VisualManager::setAgent(int index, float x, float y, float size) {
    
    visualAgents[index].nodes.scale_x = x;
    visualAgents[index].nodes.scale_y = y;
    visualAgents[index].nodes.size = size;
    visualAgents[index].isActive = true;

//    AgentVisual & agent = agentVisuals[index];
//    
//    agent.nodes.scale_x = x;
//    agent.nodes.scale_y = y;
//    
//    /* Update Node, Position Array */
//    for(int i = 0; i < agent.nodes.nodeNum; i++) {
//        /* Node */
//        /* Update Phases */
//        agent.nodes.node[i].carPhase += agent.nodes.node[i].carStep * agent.modSpeed;    //Carrier
//        if(M_2XPI < agent.nodes.node[i].carPhase) {
//            agent.nodes.node[i].carPhase = 0.0;
//        }
//        
//        
//        agent.nodes.node[i].modPhase += agent.nodes.node[i].modStep;    //Modulater
//        if(M_2XPI < agent.nodes.node[i].modPhase) {
//            agent.nodes.node[i].modPhase = 0.0;
//        }
//        
//        
//        /* Update Position */
//        float phase = sin(agent.nodes.node[i].carPhase + sin(agent.nodes.node[i].modPhase));  //FM
//        //float phase = (sin(nodes.node[i].carPhase) + sin(nodes.node[i].modPhase))* 0.5;   //
//        //        float phase = sin(nodes.node[i].carPhase) * (sin(nodes.node[i].modPhase) + 1) * 0.5;    //AM
//        
//        float nodeX = (agent.nodes.node[i].velocityX * phase) * VIS_NODE_LENGTH_RANGE_MAX + agent.nodes.node[i].x;
//        float nodeY = (agent.nodes.node[i].velocityY * phase) * VIS_NODE_LENGTH_RANGE_MAX + agent.nodes.node[i].y;
//        
//        /* Position on Screen */
//        int x = (nodeX + agent.nodes.scale_x) * screenWidth;
//        int y = (nodeY + agent.nodes.scale_y) * screenHeight;
//        
//        /* Set Position on Array */
//        nodePos[nodePosCount] = ofVec2f(x, y);
//        nodePosCount++;
//        nodeColors[nodeColorsCount] = ofFloatColor(0.0, 0.0, 0.0);
//        nodeColorsCount++;
//        
//        /*** Line ***/
//        for(int j = 0; j < agent.nodes.node[i].connectionNum; j++) {
//            lineIndex[lineIndexCount] = i; //This node
//            lineColors[lineIndexCount] = ofFloatColor(0.1, 0.1, 0.1);
//            lineIndexCount++;
//            
//            lineIndex[lineIndexCount] = agent.nodes.node[i].connectedTo[j];  //Connected Node
//            lineColors[lineIndexCount] = ofFloatColor(0.1, 0.1, 0.1);
//            lineIndexCount++;
//        }
//    }
    
}

void VisualManager::resetCount() {
//    nodePosCount = 0;
//    nodeColorsCount = 0;
//    lineIndexCount = 0;
//    lineColorsCount = 0;
}

