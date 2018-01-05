#include "ofMain.h"
#include "ofApp.h"
#include "VSyn.hpp"

//========================================================================
int main( ){
//	ofSetupOpenGL(SC_WITDH,SC_HEIGHT,OF_WINDOW);			// <-------- setup the GL context

    ofGLWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.width = WINDOW_WIDTH;
    settings.height = WINDOW_HEIGHT;
    ofCreateWindow(settings);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
