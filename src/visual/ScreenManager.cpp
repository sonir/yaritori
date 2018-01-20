//
//  ScreemManager.cpp
//  viewPortTest
//
//  Created by Hana on 2017/12/25.
//
//

#include "ScreenManager.hpp"


void invertBackground() {
    drawWhiteBack = !drawWhiteBack;
}

ScreenManager::ScreenManager(){
    for(int i = 0; i < 3; i++){
        pos[i].x = 0;
        pos[i].y = 0.;
    }
    
    init();
    setEvents();
}


void ScreenManager::setup() {
    
    ofSetWindowShape(APP_WIDTH, APP_HEIGHT);
    initCanvasSize(APP_WIDTH, APP_HEIGHT);
    //    vsyn.initWindowSize();
}

void ScreenManager::init(){
    initFbo();
    initStatus();
    initMask();
    
    colorState = true;
}

void ScreenManager::setEvents() {
    
    auto swapEvent = [&](void* args) {
        param_u* params = (param_u *)args;
        int id = params[0].ival;
        float x = params[1].fval;
        float y = params[2].fval;
        
        this->swap(id, x, y);
        
    };
    
    auto maskEvent = [&](void* args) {
        param_u* params = (param_u *)args;
        int window = params[0].ival;
        int vertexId = params[1].ival;
        float x = params[2].fval;
        float y = params[3].fval;
    };
    
    
    GismoManager& gismo = GismoManager::getInstance();
    gismo.lambdaAdd("/swap", swapEvent);
    gismo.lambdaAdd("/masp", maskEvent);
    
}

void ScreenManager::initFbo(){
    fbo.allocate(ORIGINAL_WIDTH, ORIGINAL_HEIGHT);
    
    for(int i = 0; i < 3; i++){
        mesh[i].addVertex(ofVec2f(0, 0));
        mesh[i].addVertex(ofVec2f(DISPLAY_WIDTH, 0));
        mesh[i].addVertex(ofVec2f(DISPLAY_WIDTH, DISPLAY_HEIGHT));
        mesh[i].addVertex(ofVec2f(0, DISPLAY_HEIGHT));
        mesh[i].addVertex(ofVec2f(0, 0));
        
        mesh[i].setupIndicesAuto();
        mesh[i].setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    }
    
    mesh[0].addTexCoord(ofVec2f(MARGIN_W, MARGIN_H));
    mesh[0].addTexCoord(ofVec2f(MARGIN_W + DISPLAY_WIDTH, MARGIN_H));
    mesh[0].addTexCoord(ofVec2f(MARGIN_W + DISPLAY_WIDTH, MARGIN_H + DISPLAY_HEIGHT));
    mesh[0].addTexCoord(ofVec2f(MARGIN_W, MARGIN_H + DISPLAY_HEIGHT));
    mesh[0].addTexCoord(ofVec2f(MARGIN_W, MARGIN_H));
    
    mesh[1].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + DISPLAY_WIDTH, MARGIN_H));
    mesh[1].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + DISPLAY_WIDTH * 2, MARGIN_H));
    mesh[1].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + DISPLAY_WIDTH * 2, MARGIN_H + DISPLAY_HEIGHT));
    mesh[1].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + DISPLAY_WIDTH, MARGIN_H + DISPLAY_HEIGHT));
    mesh[1].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + DISPLAY_WIDTH, MARGIN_H));
    
    mesh[2].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + MARGIN_1 + DISPLAY_WIDTH * 2, MARGIN_H));
    mesh[2].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + MARGIN_1 + DISPLAY_WIDTH * 3, MARGIN_H));
    mesh[2].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + MARGIN_1 + DISPLAY_WIDTH * 3, MARGIN_H + DISPLAY_HEIGHT));
    mesh[2].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + MARGIN_1 + DISPLAY_WIDTH * 2, MARGIN_H + DISPLAY_HEIGHT));
    mesh[2].addTexCoord(ofVec2f(MARGIN_W + MARGIN_0 + MARGIN_1 + DISPLAY_WIDTH * 2, MARGIN_H));
}

void ScreenManager::initStatus(){
    //    pos_t tmp[3];
    //    tmp[0].x = (DISPLAY_WIDTH * 0.5 + MARGIN_W) / ORIGINAL_WIDTH;
    //    tmp[0].y = 0.5;
    //    tmp[1].x = (DISPLAY_WIDTH * 1.5 + MARGIN_W + MARGIN_0) / ORIGINAL_HEIGHT;
    //    tmp[1].y = 0.5;
    //    tmp[2].x = (DISPLAY_WIDTH * 2.5 + MARGIN_W + MARGIN_0 + MARGIN_1) / ORIGINAL_WIDTH;
    //    tmp[2].y = 0.5;
    
    for(int i = 0; i < 3; i++){
        //        centerPos_origin[i] = tmp[i];
        //        centerPos[i] = centerPos_origin[i];
        //        ratio[i] = 1.0;
        
        startPos[i].x = 0.;
        startPos[i].y = 0.;
        endPos[i].x = 0.;
        endPos[i].y = 0.;
        state_w[i] = 0;
        state_h[i] = 0;
    }
    
    swapDur_go = 500;   //msec
    swapDur_out = 100;
    swapDur_back = 700;
}

void ScreenManager::initMask(){
    int n = 0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            mask_indices[n] = i*8 + j;
            n++;
            mask_indices[n] = i*8 + j + 1;
            n++;
            mask_indices[n] = i*8 + j + 4;
            n++;
            mask_indices[n] = i*8 + j + 1;
            n++;
            mask_indices[n] = i*8 + j + 4;
            n++;
            mask_indices[n] = i*8 + j + 5;
            n++;
        }
        mask_indices[n] = i*8 + 3;
        n++;
        mask_indices[n] = i*8;
        n++;
        mask_indices[n] = i*8 + 7;
        n++;
        mask_indices[n] = i*8;
        n++;
        mask_indices[n] = i*8 + 7;
        n++;
        mask_indices[n] = i*8 + 4;
        n++;
    }
    
    for(int i = 0; i < 3; i++){
        mask_pos[i * 4].set(0, 0);
        mask_pos[i * 4 + 1].set(DISPLAY_WIDTH, 0);
        mask_pos[i * 4 + 2].set(DISPLAY_WIDTH, DISPLAY_WIDTH);
        mask_pos[i * 4 + 3].set(0, DISPLAY_WIDTH);
    }
    
    for(int i = 0; i < 3; i++){
        mask_verts[i * 8].set(DISPLAY_WIDTH * i, 0);
        mask_verts[i * 8 + 1].set(DISPLAY_WIDTH * (i + 1), 0);
        mask_verts[i * 8 + 2].set(DISPLAY_WIDTH * (i + 1), DISPLAY_HEIGHT);
        mask_verts[i * 8 + 3].set(DISPLAY_WIDTH * i, DISPLAY_HEIGHT);
        
        mask_verts[i * 8 + 4].set(mask_pos[i * 4]);
        mask_verts[i * 8 + 5].set(mask_pos[i * 4 + 1]);
        mask_verts[i * 8 + 6].set(mask_pos[i * 4 + 2]);
        mask_verts[i * 8 + 7].set(mask_pos[i * 4 + 3]);
    }
    
    for(int i = 0; i < 24; i++){
        mask_cols[i] = ofFloatColor(0, 0, 0);
    }
    
    mask_vbo.setVertexData(mask_verts, 4 * 6, GL_DYNAMIC_DRAW);
    mask_vbo.setColorData(mask_cols, 24, GL_STATIC_DRAW);
    mask_vbo.setIndexData(mask_indices, 6 * 6 * 2, GL_STATIC_DRAW);
}

void ScreenManager::begin(){
    fbo.begin();
    ofClear(0);
    drawBackground();
}

void ScreenManager::end(){
    fbo.end();
}

//void ScreenManager::setOriginPosition(pos_t p1, pos_t p2, pos_t p3){
//    swap_cal();
//
//    pos[0] = p1;
//    pos[1] = p2;
//    pos[2] = p3;
//}

//void ScreenManager::setZoom(int window, pos_t p, float r){
//    centerPos[window] = p;
//    ratio[window] = r;
//}

//void ScreenManager::resetScreen(int window){
//    centerPos[window] = centerPos_origin[window];
//    ratio[window] = 1.0;
//}

void ScreenManager::setMask(int window, int vertexId, float x, float y){
    mask_pos[window * 4 + vertexId].set(x + DISPLAY_WIDTH, y * DISPLAY_HEIGHT);
}

void ScreenManager::mask(){
    for(int i = 0; i < 3; i++){
        mask_verts[i * 8 + 4].set(mask_pos[i * 4] + ofVec2f(DISPLAY_WIDTH * i, 0));
        mask_verts[i * 8 + 5].set(mask_pos[i * 4 + 1] + ofVec2f(DISPLAY_WIDTH * i, 0));
        mask_verts[i * 8 + 6].set(mask_pos[i * 4 + 2] + ofVec2f(DISPLAY_WIDTH * i, 0));
        mask_verts[i * 8 + 7].set(mask_pos[i * 4 + 3] + ofVec2f(DISPLAY_WIDTH * i, 0));
    }
    mask_vbo.updateVertexData(mask_verts, 24);
    mask_vbo.drawElements(GL_TRIANGLES, 72);
}

void ScreenManager::draw(){
    swap_cal();
    
    fbo.getTexture().bind();
    for(int i = 0; i < 3; i++){
        ofPushMatrix();
        ofTranslate(DISPLAY_WIDTH * i, 0);
        ofTranslate(pos[i].x, pos[i].y);
        mesh[i].draw();
        ofPopMatrix();
    }
    fbo.getTexture().unbind();
    
    mask();
}

void ScreenManager::drawBackground(){
    if(drawWhiteBack == true) {
        ofBackground(255);
    }else{
        ofBackground(0);
    }
}

void ScreenManager::setSwapDuration(float go, float out, float down){
    swapDur_go = go;
    swapDur_out = out;
    swapDur_back = down;
}

void ScreenManager::swap(int window, swap_direction direction){
    startPos[window] = pos[window];
    
    switch(direction){
        case UP:
            endPos[window].y = -DISPLAY_HEIGHT;
            state_h[window] = 1;
            interpolation_h[window].bang(swapDur_go);
            break;
        case DOWN:
            endPos[window].y = DISPLAY_HEIGHT;
            state_h[window] = 1;
            interpolation_h[window].bang(swapDur_go);
            break;
        case RIGHT:
            endPos[window].x = DISPLAY_WIDTH;
            state_w[window] = 1;
            interpolation_w[window].bang(swapDur_go);
            break;
        case LEFT:
            endPos[window].x = -DISPLAY_WIDTH;
            state_w[window] = 1;
            interpolation_w[window].bang(swapDur_go);
            break;
    }
}

void ScreenManager::swap(int window, float x, float y) {
    pos[window].x = x * DISPLAY_WIDTH;
    pos[window].y = y * DISPLAY_HEIGHT;
}

void ScreenManager::swap_cal(){
    for(int i = 0; i < 3; i++){
        switch(state_w[i]){
            case 1:
                pos[i].x = (endPos[i].x - startPos[i].x) * cos(PI * 0.5 * interpolation_w[i].get()) - (endPos[i].x - startPos[i].x);
                break;
            case 2:
                break;
            case 3:
                pos[i].x = (endPos[i].x - startPos[i].x) * cos(PI * 0.5 * (1.0 - interpolation_w[i].get())) - (endPos[i].x - startPos[i].x);
                break;
            default:
                break;
        }
        switch(state_h[i]){
            case 1:
                pos[i].y = (endPos[i].y - startPos[i].y) * cos(PI * 0.5 * interpolation_h[i].get()) - (endPos[i].y - startPos[i].y);
                break;
            case 2:
                break;
            case 3:
                pos[i].y = (endPos[i].y - startPos[i].y) * cos(PI * 0.5 * (1.0 - interpolation_h[i].get())) - (endPos[i].y - startPos[i].y);
                break;
            default:
                break;
        }
        
        if(interpolation_w[i].get() == 1.0){
            switch(state_w[i]){
                case 1: //go
                    interpolation_w[i].bang(swapDur_out);
                    state_w[i] = 2;
                    break;
                case 2: //out
                    interpolation_w[i].bang(swapDur_back);
                    startPos[i].x = pos[i].x;
                    endPos[i].x = 0.;
                    state_w[i] = 3;
                    break;
                case 3: //back8
                    state_w[i] = 0;
                    break;
                default:
                    break;
            }
        }
        if(interpolation_h[i].get() == 1.0){
            switch(state_h[i]){
                case 1: //go
                    interpolation_h[i].bang(swapDur_out);
                    state_h[i] = 2;
                    break;
                case 2: //out
                    interpolation_h[i].bang(swapDur_back);
                    startPos[i].y = pos[i].y;
                    endPos[i].y = 0.;
                    state_h[i] = 3;
                    break;
                case 3: //back
                    state_h[i] = 0;
                    break;
                default:
                    break;
            }
        }
    }
}

void ScreenManager::setFullScreen() {
    ofSetFullscreen(true);
    ofSetWindowShape(APP_WIDTH, APP_HEIGHT);
    ofSetWindowPosition(0, MASTER_HEGHT); //y: height of mbpr display
}

ofColor ScreenManager::getDrawColor() {
    if(drawWhiteBack) {
        return ofColor(0);
    } else {
        return ofColor(255);
    }
}
