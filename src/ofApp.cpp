#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){        
    
    ofSetEscapeQuitsApp(false);
    ofSetVerticalSync(true);
//    ofEnableSmoothing();

    network.setup();
    
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
        case 'a':
            vsyn.performanceManager.bullets[0].bang();
            break;
        case 's':
            vsyn.performanceManager.reverseBullets[1].bang();
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
