#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	//ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

    
     ofGLFWWindowSettings settings;
     //settings.setGLVersion(4, 5);
     settings.width = SCREEN_WIDTH;
     settings.height = SCREEN_HEIGHT;
     settings.windowMode = OF_WINDOW;
     auto window = ofCreateWindow(settings);
     
     ofRunApp(window, std::make_shared<ofApp>());
     ofRunMainLoop();
    
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofRunApp(new ofApp());

}
