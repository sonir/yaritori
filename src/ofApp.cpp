#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(true);
//    ofEnableSmoothing();
    vsyn.initWindowSize();
    vsyn.setup();
}

//--------------------------------------------------------------
void ofApp::update(){

    vsyn.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    vsyn.draw();
//    ofDrawBitmapString("fps = " + ofToString(ofGetFrameRate()), 10, 20);

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    switch(key){
            
        case 'f':
            ofToggleFullscreen();
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
