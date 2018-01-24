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

    GismoManager& gismo = GismoManager::getInstance();
    int flg = 0;
    
    switch(key){
            
        case 'f':
            ofToggleFullscreen();
            break;
        case 'a':
            flg = 1;
//            gismo.bang("/bullet_bang", &num);
//            vsyn.performanceManager.bullets[0].bang();
            break;
        case 's':
            flg=2;
            //vsyn.performanceManager.reverseBullets[1].bang();
            break;
            
    
    }
    
    
    
    if(flg==1)
    {
        int num = 0;
        gismo.bang("/bullet_bang", &num);
        
    }else if(flg==2){
        
        int num = 2;
        gismo.bang("/bullet_bang_return", &num);
        
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
