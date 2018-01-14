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

constexpr float STEP_MAX = M_2XPI * 6.0f;
constexpr float STEP_MIN = M_2XPI * 4.0f;

//About length
constexpr float LINE_WIDTH = 0.5;
constexpr float NODE_SIZE = 4.0;
constexpr float TREMOR_RATIO = 0.21f;
constexpr float STAY_RATIO = 1.0 - TREMOR_RATIO;
constexpr float MOV_FIX = 0.012;

constexpr float dx = 0.0166f;

constexpr int PHASE_ENABLE = 3;

AgentMotion::AgentMotion() {
    color = 0.0;
    width_rate = 1.0f;
    size = 0.03;
    mov = 0.01;
    pShape = &this->shape;
    
    resetShape();
    initModulation();
    initVbo();
    
    shader.load("shader/shader.vert", "shader/shader.frag");
}

void AgentMotion::resetShape() {
    center.x = frand()-0.5;
    center.y = frand()-0.5;
    

    shape.node_count = 64;
    shape.edge_count = 32;
    
    for(int i = 0; i < NODE_MAX; i++) {
        shape.nodes[i].x = frand() - 0.5;
        shape.nodes[i].y = frand() - 0.5;

    }
    
    for (int i = 0; i <  shape.edge_count; i++) {
        shape.edges[i].node_id_a = 0;
        shape.edges[i].node_id_b = 1;
    }
    
    pShape = &this->shape;
    
}

void AgentMotion::initModulation() {
//    ofVec2f vel = ofVec2f(frand() * 2.0 - 1.0, frand() * 2.0 - 1.0).getNormalized();
    
    for(int i = 0; i < NODE_MAX; i++) {
        ofVec2f vel = ofVec2f(frand() * 2.0 - 1.0, frand() * 2.0 - 1.0).getNormalized();
        velocityX[i] = vel.x;
        velocityY[i] = vel.y;
        
        modStep[i] = (STEP_MAX - STEP_MIN) * frand() + STEP_MIN;
        carStep[i] = (STEP_MAX - STEP_MIN) * frand() + STEP_MIN;
        
        carPhase[i] = 0.0;
        carStep[i] = 0.0;
    }
    t = 0.0f;
}


void AgentMotion::initVbo() {
    for(int i = 0; i < pShape->node_count; i++) {
        ofVec2f pos;
        pos.x = ( center.x + (pShape->nodes[i].x * size)) * CANVAS_HEIGHT;
        pos.y = ( center.y + (pShape->nodes[i].y * size)) * CANVAS_HEIGHT;
        
        nodePos[i] = pos;
        nodeColors[i] = ofFloatColor(color);
    }
    
    for (int i = 0; i < pShape->edge_count; i++) {
        int edge_index = i*2;
        edgeIndices[edge_index] = pShape->edges[i].node_id_a;
        edgeIndices[edge_index+1] = pShape->edges[i].node_id_b;
        edgeColors[edge_index] = ofFloatColor(color);
        edgeColors[edge_index+1] = ofFloatColor(color);
    }
    
    nodeVbo.setVertexData(nodePos, NODE_MAX, GL_DYNAMIC_DRAW);
    nodeVbo.setColorData(nodeColors, NODE_MAX, GL_DYNAMIC_DRAW);

    edgeVbo.setVertexData(nodePos, NODE_MAX, GL_DYNAMIC_DRAW);
    edgeVbo.setColorData(edgeColors, EDGE_MAX * 2, GL_DYNAMIC_DRAW);
    edgeVbo.setIndexData(edgeIndices, EDGE_MAX*2, GL_DYNAMIC_DRAW);
}

void AgentMotion::updateColors() {
    for(int i = 0; i < pShape->node_count; i++) {
        nodeColors[i] = ofFloatColor(color);
    }
    
    for (int i = 0; i < pShape->edge_count * 2; i += 2) {
        int edge_index = i * 0.5;
        edgeColors[i] = ofFloatColor(color);
        edgeColors[i+1] = ofFloatColor(color);
    }
    
    nodeVbo.updateColorData(nodeColors, pShape->node_count);
    edgeVbo.updateColorData(edgeColors, pShape->edge_count);
}

void AgentMotion::updatePhase() {
    // Update Phases
    for(int i = 0; i < pShape->node_count; i++) {
        carPhase[i] += carStep[i] * mov * MOV_FIX;    //Carrier
        if(M_2XPI < carPhase[i]) {
            carPhase[i] = 0.0;
        }

        modPhase[i] += modStep[i] * mov * MOV_FIX;    //Modulater
        if(M_2XPI < modPhase[i]) {
            modPhase[i] = 0.0;
        }

        phase[i] = (sin(carPhase[i]) + sin(modPhase[i])) * 0.5 * TREMOR_RATIO;
    }
}



void AgentMotion::updatePosition() {
    for(int i = 0; i < pShape->node_count; i++) {
        //Modulation by CPU
        float nodeX = (pShape->nodes[i].x + velocityX[i] * phase[i % PHASE_ENABLE ]) * size;
        float nodeY = (pShape->nodes[i].y + velocityY[i] * phase[i % PHASE_ENABLE ]) * size;

        ofVec2f pos;
        pos.x = (center.x + nodeX) * CANVAS_HEIGHT;
        pos.y = (center.y + nodeY) * CANVAS_HEIGHT;
        
        
        //Modulation by Shader
//        ofVec2f pos;
//        pos.x = ( center.x + (pShape->nodes[i].x * size)) * CANVAS_HEIGHT;
//        pos.y = ( center.y + (pShape->nodes[i].y * size)) * CANVAS_HEIGHT;

    
        nodePos[i] = pos;
    }
    nodeVbo.updateVertexData(nodePos, pShape->node_count);
    edgeVbo.updateVertexData(nodePos, pShape->node_count);
}

void AgentMotion::updateIndex() {
    for (int i = 0; i < pShape->edge_count; i++) {
        int edge_index = i*2;
        edgeIndices[edge_index] = pShape->edges[i].node_id_a;
        edgeIndices[edge_index+1] = pShape->edges[i].node_id_b;
        edgeColors[edge_index] = ofFloatColor(color);
        edgeColors[edge_index+1] = ofFloatColor(color);
    }
    edgeVbo.updateIndexData(edgeIndices, pShape->edge_count*2);
}

void AgentMotion::update() {
    t += mov * dx;
    if(M_2XPI < t) {
        t = 0.0f;
        
    }
    updatePhase();
    updatePosition();
    updateIndex();
}

void AgentMotion::draw() {
    
//    shader.begin();
//    shader.setUniform1f("t", t);
//    shader.setUniform1f("color", color);
//    shader.setUniform1i("CANVAS_HEIGHT", CANVAS_HEIGHT);
//    shader.setUniform1f("size", size);
//    shader.setUniform1fv("carStep", carStep);
//    shader.setUniform1fv("modStep", modStep);
//    shader.setUniform1f("centerX", center.x*screenWidth);
//    shader.setUniform1f("centerY", center.y*screenWidth);
    
    if(pShape->node_count != 0) {
//        glEnable(GL_POINT_SMOOTH);
//        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glEnable(GL_BLEND);
        glPointSize(getPointSize());
        nodeVbo.draw(GL_POINTS, 0, pShape->node_count);
        ofSetColor(255, 0, 0);
    }
   
    if(pShape->edge_count != 0) {
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(getLineWidth());
        edgeVbo.drawElements(GL_LINES, pShape->edge_count * 2);
    }
    
//    ofSetCircleResolution(12);
//    ofDrawCircle(center.x * CANVAS_HEIGHT, center.y * CANVAS_HEIGHT, 3);
    
//    shader.end();
}



float AgentMotion::getPointSize() {
    float pointSize = 3.5;
    if(size < 0.02) {
        pointSize = 2.0;
    } else if (0.02 <= size && size < 0.03) {
        pointSize = 2.0;
    } else if(0.03 <= size && size < 0.04) {
        pointSize = 2.5;
    } else if(0.04 <= size && size < 0.05) {
        pointSize = 3.0;
    } else {
        pointSize += 8.0 * size;
    }
    
    return pointSize;
}

float AgentMotion::getLineWidth() {
    float lineWidth = 0.5;
    if(size <= 0.01) {
        lineWidth = 0.05;
    } else if (0.01 < size && size < 0.02) {
        lineWidth = 0.1;
    } else if(0.02 <= size && size < 0.05) {
        lineWidth = 0.25;
    }
    
    return lineWidth;
}

void AgentMotion::setShapePtr(ag_shape_t * shapePtr) {
    pShape = shapePtr;
    
}

void AgentMotion::invertColor() {
    if (color == 1.0) {
        color = 0.0f;
    } else {
        color = 1.0;
    }
    
    this->updateColors();
}




