#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){        
    
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(true);
//    ofEnableSmoothing();

    network.setup();
    network.setShapePtr(vsyn.ag_shapes);
    
    vsyn.initWindowSize();
    vsyn.setup();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    vsyn.update();
    network.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    vsyn.draw();
#ifdef DEBUG_MODE
    ofDrawBitmapString("fps = " + ofToString(ofGetFrameRate()), 10, 20);
#endif
    ofSetColor(255, 0, 0);
    ofDrawBitmapString("fps = " + ofToString(ofGetFrameRate()), 10, 20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    vsyn.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    switch(key){
            
        case 'f':
            ofToggleFullscreen();
            break;
            
            
        case '1':
            setScreenPos(SCREEN_POS_LEFT);
            break;
        case '2':
            setScreenPos(SCREEN_POS_CENTER);
            break;
        case '3':
            setScreenPos(SCREEN_POS_RIGHT);
            break;
            
    }
    

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
    vsyn.initWindowSize();

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
