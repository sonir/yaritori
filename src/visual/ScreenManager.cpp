//
//  ScreemManager.cpp
//  viewPortTest
//
//  Created by Hana on 2017/12/25.
//
//

#include "ScreenManager.hpp"

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
        this->setMask(window, vertexId, x, y);
    };
    
    auto trimEvent = [&](void* args) {
        param_u* params = (param_u *)args;
        int window = params[0].ival;
        float x = params[1].fval;
        float y = params[2].fval;
        this->setTrimPos(window, x, y);
    };
    
    auto resetTrimEvent = [&](void* args) {
        param_u* params = (param_u *)args;
        int window = params[0].ival;
        this->resetTrimPos(window);
    };
    
    auto bgColorEvent = [&](void* args) {
        param_u* params = (param_u *)args;
        float c = params[0].fval;
        this->setBackground(c);
    };
    
    auto timedInvertEvent = [&](void* args) {
        if(timerOn) {
            param_u* params = (param_u *)args;
            float duration = params[0].fval;
            invertTimer.ready();
            invertOnNext = true;
            invertState = false;
            timerOn = false;
            nextDuration = duration;
        } else {
            param_u* params = (param_u *)args;
            float duration = params[0].fval;
            this->invertTimer.bang(duration * 1000.0);
            invertState = true;
            timerOn = true;
        }
    };
    
    auto invertEvent = [&](void* args) {
        param_u* params = (param_u *)args;
        invertState = params[0].bval;
        if(timerOn) timerOn = false;
    };
    
    auto shakeEvent = [&](void* args) {
        param_u* params = (param_u *)args;
        int window = params[0].ival;
        int velX = params[1].ival;
        int velY = params[2].ival;
        
        
        
        if(window == 0) {
            for (int i = 0; i < WINDOW_NUM; i++) {
                switch (velY) {
                    case 1:
                        shake(i, UP);
                        break;
                    case -1:
                        shake(i, DOWN);
                        break;
                    default:
                        break;
                }
                
            }
        } else {
            switch (velY) {
                case 1:
                    shake(window-1, UP);
                    break;
                case -1:
                    shake(window-1, DOWN);
                    break;
                default:
                    break;
            }
        }
    };
    
    
    GismoManager& gismo = GismoManager::getInstance();
    gismo.lambdaAdd("/sc_posi", swapEvent);
    gismo.lambdaAdd("/mask", maskEvent);
    gismo.lambdaAdd("/trim", trimEvent);
    gismo.lambdaAdd("/resetTrim", resetTrimEvent);
    gismo.lambdaAdd("/bgColor", bgColorEvent);
    gismo.lambdaAdd("/visual/timed_invert", timedInvertEvent);
    gismo.lambdaAdd("/invert", invertEvent);
    gismo.lambdaAdd("/visual/shake", shakeEvent);
    
}

void invertBackground() {
    drawWhiteBack = !drawWhiteBack;
}



void ScreenManager::setAllColor(float bgColor) {
    
    GismoManager& gismo = GismoManager::getInstance();
    if(bgColor == BACKGROUND_INVERT_COLOR) {
        //Reset Colors for solo;
        param_u param;
        param.fval = ANIMATION_INVERT_COLOR;
        gismo.lambdaBang("/rippleColor", &param);
        gismo.lambdaBang("/agentColor", &param);
        gismo.lambdaBang("/performanceColor", &param);
        
        param.fval = BACKGROUND_INVERT_COLOR;
        gismo.lambdaBang("/bgColor", &param);
    } else {
        //Reset Colors for solo;
        param_u param;
        param.fval = ANIMATION_DEFAULT_COLOR;
        gismo.lambdaBang("/rippleColor", &param);
        gismo.lambdaBang("/agentColor", &param);
        gismo.lambdaBang("/performanceColor", &param);
        
        param.fval = BACKGROUND_DEFAULT_COLOR;
        gismo.lambdaBang("/bgColor", &param);
    }
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
    
#ifdef DEBUG_MODE_SCREEN
    ofSetWindowShape(DISPLAY_WIDTH, DISPLAY_HEIGHT);
#else
    ofSetWindowShape(APP_WIDTH, APP_HEIGHT);
#endif
    
    initCanvasSize(ORIGINAL_WIDTH, ORIGINAL_HEIGHT);    //Tell original width and original height to vsyn
    invertTimer.ready();
    invertState = false;
    timerOn = false;
    invertOnNext = false;
}

void ScreenManager::init(){
    initFbo();
    initStatus();
    initMask();
    
    colorState = true;
}

void ScreenManager::initFbo(){
    fbo.allocate(ORIGINAL_WIDTH, ORIGINAL_HEIGHT);
}

void ScreenManager::initStatus(){
    for(int i = 0; i < 3; i++){
        startPos[i].x = 0.;
        startPos[i].y = 0.;
        endPos[i].x = 0.;
        endPos[i].y = 0.;
        state_w[i] = 0;
        state_h[i] = 0;
    }
    
    shakeDur_go = SHAKE_DEFAULT_TIME_OUT;   //msec
    shakeDur_out = SHAKE_DEFAULT_TIME_STAY;
    shakeDur_back = SHAKE_DEFAULT_TIME_IN;
    
    for(int i = 0; i < 3; i++){
        resetTrimPos(i);
    }
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
        mask_pos[i * 4 + 2].set(DISPLAY_WIDTH, DISPLAY_HEIGHT);
        mask_pos[i * 4 + 3].set(0, DISPLAY_HEIGHT);
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
#ifdef DEBUG_MODE_SCREEN
        mask_cols[i] = ofFloatColor(0, 0, 0, 100);
#else
        mask_cols[i] = ofFloatColor(0, 0, 0, 255);
#endif
    }
    
    mask_vbo.setVertexData(mask_verts, 4 * 6, GL_DYNAMIC_DRAW);
    mask_vbo.setColorData(mask_cols, 24, GL_STATIC_DRAW);
    mask_vbo.setIndexData(mask_indices, 6 * 6 * 2, GL_STATIC_DRAW);
}

void ScreenManager::setTrimPos(int window, float x, float y){
    texture_diffPos_x[window] = x * ORIGINAL_WIDTH;
    texture_diffPos_y[window] = y * ORIGINAL_WIDTH;
    
    texture_pos_x[window] = texture_originPos_x[window] + texture_diffPos_x[window];
    texture_pos_y[window] = texture_originPos_y[window] + texture_diffPos_y[window];
}

void ScreenManager::resetTrimPos(int window){
    texture_diffPos_x[window] = 0.;
    texture_diffPos_y[window] = 0.;
    
    texture_pos_x[window] = texture_originPos_x[window] + texture_diffPos_x[window];
    texture_pos_y[window] = texture_originPos_y[window] + texture_diffPos_y[window];
}

void ScreenManager::setMask(int window, int vertexId, float x, float y){
    mask_pos[window * 4 + vertexId].set(x * DISPLAY_WIDTH, y * DISPLAY_HEIGHT);
}

void ScreenManager::maskUpdate(){
#ifdef DEBUG_MODE_SCREEN
    for(int i = 0; i < 3; i++){
        mask_verts[i * 8].set(texture_pos_x[i], texture_pos_y[i]);
        mask_verts[i * 8 + 1].set(texture_pos_x[i] + DISPLAY_WIDTH, texture_pos_y[i]);
        mask_verts[i * 8 + 2].set(texture_pos_x[i] + DISPLAY_WIDTH, texture_pos_y[i] + DISPLAY_HEIGHT);
        mask_verts[i * 8 + 3].set(texture_pos_x[i], texture_pos_y[i] + DISPLAY_HEIGHT);
        
        mask_verts[i * 8 + 4].set(mask_pos[i * 4] + ofVec2f(texture_pos_x[i], texture_pos_y[i]));
        mask_verts[i * 8 + 5].set(mask_pos[i * 4 + 1] + ofVec2f(texture_pos_x[i], texture_pos_y[i]));
        mask_verts[i * 8 + 6].set(mask_pos[i * 4 + 2] + ofVec2f(texture_pos_x[i], texture_pos_y[i]));
        mask_verts[i * 8 + 7].set(mask_pos[i * 4 + 3] + ofVec2f(texture_pos_x[i], texture_pos_y[i]));
    }
#else
    for(int i = 0; i < 3; i++){
        mask_verts[i * 8 + 4].set(mask_pos[i * 4] + ofVec2f(DISPLAY_WIDTH * i, 0));
        mask_verts[i * 8 + 5].set(mask_pos[i * 4 + 1] + ofVec2f(DISPLAY_WIDTH * i, 0));
        mask_verts[i * 8 + 6].set(mask_pos[i * 4 + 2] + ofVec2f(DISPLAY_WIDTH * i, 0));
        mask_verts[i * 8 + 7].set(mask_pos[i * 4 + 3] + ofVec2f(DISPLAY_WIDTH * i, 0));
    }
#endif
    
}

void ScreenManager::mask(){
    mask_vbo.updateVertexData(mask_verts, 24);
    mask_vbo.drawElements(GL_TRIANGLES, 72);
}

void ScreenManager::begin(){
    
    //Invert
    if(timerOn) {
        float invDur = invertTimer.get();
        if(invDur < 1.0) {
            invertState = true;
        } else if(1.0 <= invDur) {
            invertState = false;
            timerOn = false;
        }else {
            invertState = false;
        }
    }
    
    if(invertState) {
        setAllColor(0.0);
    } else {
        setAllColor(BACKGROUND_DEFAULT_COLOR);
    }
    
    if(invertOnNext) {
        invertTimer.bang(nextDuration * 1000.0);
        invertState = true;
        timerOn = true;
        invertOnNext = false;
    }
    
    
    fbo.begin();
    ofClear(0);
    drawBackground();
}

void ScreenManager::end(){
    fbo.end();
}

void ScreenManager::draw(){
    maskUpdate();
    
    ofBackground(0);
    
#ifdef DEBUG_MODE_SCREEN   //Debug mode
    float fix_ORIGINAL_WIDTH = 1920;
    float aspect = fix_ORIGINAL_WIDTH / ORIGINAL_WIDTH;
    float fix_ORIGINAL_HEIGHT = ORIGINAL_HEIGHT * aspect;
    
    ofPushMatrix();
    ofTranslate(0, 300);
    ofScale(aspect, aspect);
    fbo.draw(0, 0, ORIGINAL_WIDTH, ORIGINAL_HEIGHT);
    
    ofSetColor(255, 0, 0);
    ofNoFill();
    for(int i = 0; i < 3; i++){
        ofDrawBitmapString(ofToString(i), texture_pos_x[i], texture_pos_y[i]);
        ofDrawRectangle(texture_pos_x[i], texture_pos_y[i], DISPLAY_WIDTH, DISPLAY_HEIGHT);
    }
    
    ofFill();
    mask();
    ofPopMatrix();
    
#else   //Normal mode
    shake_cal();
    
    for(int i = 0; i < 3; i++){
        ofPushMatrix();
        ofTranslate(DISPLAY_WIDTH * i, 0);
        
        float x, y, w, h, sx, sy, sw, sh;
        if(pos[i].x > 0) {
            x = pos[i].x;
            w = DISPLAY_WIDTH - pos[i].x;
            sx = texture_pos_x[i];
            sw = DISPLAY_WIDTH - pos[i].x;
        }else{
            x = 0;
            w = DISPLAY_WIDTH + pos[i].x;
            sx = texture_pos_x[i] - pos[i].x;
            sw = DISPLAY_WIDTH + pos[i].x;
        }
        if(pos[i].y > 0) {
            y = pos[i].y;
            h = DISPLAY_HEIGHT - pos[i].y;
            sy = texture_pos_y[i];
            sh = DISPLAY_HEIGHT - pos[i].y;
        }else{
            y = 0;
            h = DISPLAY_HEIGHT + pos[i].y;
            sy = texture_pos_y[i] - pos[i].y;
            sh = DISPLAY_HEIGHT + pos[i].y;
        }
        
        fbo.getTexture().drawSubsection(x, y, w, h, sx, sy, sw, sh);
        ofPopMatrix();
    }
    
    mask();
#endif
}

void ScreenManager::setBackground(float c) {
    bgColor = c;
}

void ScreenManager::drawBackground(){
    ofBackground(ofFloatColor(bgColor));
}

void ScreenManager::setShakeDuration(float go, float out, float down){
    shakeDur_go = go;
    shakeDur_out = out;
    shakeDur_back = down;
}

void ScreenManager::shake(int window, shake_direction_e direction){
    startPos[window] = pos[window];
    
    switch(direction){
        case UP:
            endPos[window].y = -DISPLAY_HEIGHT;
            state_h[window] = 1;
            interpolation_h[window].bang(shakeDur_go);
            break;
        case DOWN:
            endPos[window].y = DISPLAY_HEIGHT;
            state_h[window] = 1;
            interpolation_h[window].bang(shakeDur_go);
            break;
        case RIGHT:
            endPos[window].x = DISPLAY_WIDTH;
            state_w[window] = 1;
            interpolation_w[window].bang(shakeDur_go);
            break;
        case LEFT:
            endPos[window].x = -DISPLAY_WIDTH;
            state_w[window] = 1;
            interpolation_w[window].bang(shakeDur_go);
            break;
    }
}

float ScreenManager::getSwapCurve(float val) {
    float result = 0.;
    
    if(val < 0.5) {
        result = val * 0.5;
    } else {
        result = val * 1.5 - 0.5;
    }
    
    //result = pow(val, 3.0);
    
    return result;
}

void ScreenManager::swap(int window, float x, float y) {
    pos[window].x = x * DISPLAY_WIDTH;
    pos[window].y = y * DISPLAY_HEIGHT;
}

void ScreenManager::shake_cal(){
    float ratio = 0.0;
    for(int i = 0; i < 3; i++){
        switch(state_w[i]){
            case 1:
                ratio = getSwapCurve(interpolation_w[i].get());
                pos[i].x = (endPos[i].x - startPos[i].x) * cos(PI * 0.5 * ratio) - (endPos[i].x - startPos[i].x);
                break;
            case 2:
                break;
            case 3:
                ratio = getSwapCurve(interpolation_w[i].get());
                pos[i].x = (endPos[i].x - startPos[i].x) * cos(PI * 0.5 * (1.0 - interpolation_w[i].get())) - (endPos[i].x - startPos[i].x);
                break;
            default:
                break;
        }
        switch(state_h[i]){
            case 1:
                ratio = getSwapCurve(interpolation_h[i].get());
                pos[i].y = (endPos[i].y - startPos[i].y) * cos(PI * 0.5 * ratio) - (endPos[i].y - startPos[i].y);
                break;
            case 2:
                break;
            case 3:
                ratio = getSwapCurve(interpolation_h[i].get());
                pos[i].y = (endPos[i].y - startPos[i].y) * cos(PI * 0.5 * (1.0 - interpolation_h[i].get())) - (endPos[i].y - startPos[i].y);
                break;
            default:
                break;
        }
        
        if(interpolation_w[i].get() == 1.0){
            switch(state_w[i]){
                case 1: //go
                    interpolation_w[i].bang(shakeDur_out);
                    state_w[i] = 2;
                    break;
                case 2: //out
                    interpolation_w[i].bang(shakeDur_back);
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
                    interpolation_h[i].bang(shakeDur_out);
                    state_h[i] = 2;
                    break;
                case 2: //out
                    interpolation_h[i].bang(shakeDur_back);
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
    ofSetWindowPosition(MASTER_WIDTH, 0); //y: height of mbpr display
}

void ScreenManager::setFullScreenConfig() {
    ofSetWindowShape(APP_WIDTH, APP_HEIGHT);
    ofSetWindowPosition(MASTER_WIDTH, 0); //y: height of mbpr display
}

ofColor ScreenManager::getDrawColor() {
    if(drawWhiteBack) {
        return ofColor(0);
    } else {
        return ofColor(255);
    }
}
