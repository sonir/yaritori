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
    
//    shader.load("", "shader/invert.frag");
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
    
    GismoManager& gismo = GismoManager::getInstance();
    gismo.lambdaAdd("/swap", swapEvent);
    
}

void ScreenManager::initFbo(){
    for(int i = 0; i < 3; i++){
        fbo[i].allocate(SCREEN_WIDTH, SCREEN_HEIGHT);
        
        mesh[i].addVertex(ofVec2f(0, 0));
        mesh[i].addVertex(ofVec2f(SCREEN_WIDTH, 0));
        mesh[i].addVertex(ofVec2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        mesh[i].addVertex(ofVec2f(0, SCREEN_HEIGHT));
        mesh[i].addVertex(ofVec2f(0, 0));
        
        mesh[i].setupIndicesAuto();
        
        mesh[i].setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
        
        mesh[i].addTexCoord(ofVec2f(0, 0));
        mesh[i].addTexCoord(ofVec2f(SCREEN_WIDTH, 0));
        mesh[i].addTexCoord(ofVec2f(SCREEN_WIDTH, SCREEN_HEIGHT));
        mesh[i].addTexCoord(ofVec2f(0, SCREEN_HEIGHT));
        mesh[i].addTexCoord(ofVec2f(0, 0));

    }
}

void ScreenManager::initStatus(){
    pos_t tmp[3];
    tmp[0].x = (SCREEN_WIDTH * 0.5 + MARGIN) / ORIGINAL_HEIGHT;
    tmp[0].y = 0.5;
    tmp[1].x = (SCREEN_WIDTH * 1.5 + MARGIN * 2.) / ORIGINAL_HEIGHT;
    tmp[1].y = 0.5;
    tmp[2].x = (SCREEN_WIDTH * 2.5 + MARGIN * 3.) / ORIGINAL_HEIGHT;
    tmp[2].y = 0.5;
    
    for(int i = 0; i < 3; i++){
        centerPos_origin[i] = tmp[i];
        centerPos[i] = centerPos_origin[i];
        ratio[i] = 1.0;
        
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


void ScreenManager::begin(int window){
    fbo[window].begin();
    ofClear(0);
    drawBackground();
    ofPushMatrix();
    ofTranslate(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.5);
    ofScale(ratio[window], ratio[window]);
    ofTranslate(-centerPos[window].x * ORIGINAL_HEIGHT, -centerPos[window].y * ORIGINAL_HEIGHT);
//    ofSetColor(255, 0, 0);
//    ofDrawCircle(centerPos[window].x  * VSYN_WIDTH, centerPos[window].y * VSYN_HEIGHT, 50);
//    ofNoFill();
//    ofDrawRectangle(0, 0, VSYN_WIDTH, VSYN_HEIGHT);
//    ofFill();
}

void ScreenManager::end(int window){
    ofPopMatrix();
    fbo[window].end();
}
void ScreenManager::setOriginPosition(pos_t p1, pos_t p2, pos_t p3){
    swap_cal();
    
    pos[0] = p1;
    pos[1] = p2;
    pos[2] = p3;
}

void ScreenManager::setZoom(int window, pos_t p, float r){
    centerPos[window] = p;
    ratio[window] = r;
}

void ScreenManager::resetScreen(int window){
    centerPos[window] = centerPos_origin[window];
    ratio[window] = 1.0;
}

void ScreenManager::draw(){
    ofBackground(0);
        
    swap_cal();
    
    ofSetColor(255, 255, 255);
    

    for(int i = 0; i < 3; i++){
    
        fbo[i].getTexture().bind();

        ofPushMatrix();
        ofTranslate(DISPLAY_WIDTH * i, 0);
        ofTranslate(pos[i].x, pos[i].y);
        if(pos[i].x < 0){
            fbo[i].getTexture().drawSubsection(-pos[i].x, 0, SCREEN_WIDTH + pos[i].x, SCREEN_HEIGHT, 1., 1.);
        }else{
            fbo[i].getTexture().drawSubsection(0, 0, SCREEN_WIDTH - pos[i].x , SCREEN_HEIGHT, 1., 1.);
        }
        ofPopMatrix();
    
        fbo[i].getTexture().unbind();
        
//        ofPushMatrix();
//        ofTranslate(DISPLAY_WIDTH * i, 0);
//        ofTranslate(pos[i].x, pos[i].y);
//        shader.begin();
//        shader.setUniformTexture("texture", fbo[i].getTexture(), 0);
//        shader.setUniform1f("colorState", colorState);
//        fbo[i].draw(0, 0);
//        shader.end();
//        ofPopMatrix();

    }
    
    //mask
    ofSetColor(0);
    ofDrawRectangle(0, 0, ORIGIN_0_W, DISPLAY_HEIGHT);
    ofDrawRectangle(ORIGIN_0_W + SCREEN_WIDTH, 0, (DISPLAY_WIDTH - (SCREEN_WIDTH + ORIGIN_0_W)) + ORIGIN_1_W, DISPLAY_HEIGHT);
    ofDrawRectangle(DISPLAY_WIDTH + ORIGIN_1_W + SCREEN_WIDTH, 0, (DISPLAY_WIDTH - (SCREEN_WIDTH + ORIGIN_1_W)) + ORIGIN_2_W, DISPLAY_HEIGHT);
    ofDrawRectangle(DISPLAY_WIDTH * 2 + ORIGIN_2_W + SCREEN_WIDTH, 0, DISPLAY_WIDTH - (SCREEN_WIDTH + ORIGIN_2_W), DISPLAY_HEIGHT);
//    ofDrawRectangle(0, 0, APP_WIDTH, (APP_HEIGHT - SCREEN_HEIGHT) * 0.5);
//    ofDrawRectangle(0, APP_HEIGHT - (APP_HEIGHT - SCREEN_HEIGHT) * 0.5, APP_WIDTH, (APP_HEIGHT - SCREEN_HEIGHT) * 0.5);
}

void ScreenManager::drawBackground(){
    if(drawWhiteBack == true) {
        ofSetColor(255);
        ofDrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }else{
        ofSetColor(0);
        ofDrawRectangle(0, 0, ORIGINAL_HEIGHT, ORIGINAL_HEIGHT);
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
            endPos[window].y = -SCREEN_HEIGHT;
            state_h[window] = 1;
            interpolation_h[window].bang(swapDur_go);
            break;
        case DOWN:
            endPos[window].y = SCREEN_HEIGHT;
            state_h[window] = 1;
            interpolation_h[window].bang(swapDur_go);
            break;
        case RIGHT:
            endPos[window].x = SCREEN_WIDTH;
            state_w[window] = 1;
            interpolation_w[window].bang(swapDur_go);
            break;
        case LEFT:
            endPos[window].x = -SCREEN_WIDTH;
            state_w[window] = 1;
            interpolation_w[window].bang(swapDur_go);
            break;
    }
}

void ScreenManager::swap(int window, float x, float y) {
    pos[window].x = x * SCREEN_WIDTH;
    pos[window].y = y * SCREEN_HEIGHT;
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


