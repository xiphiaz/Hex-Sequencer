#include "ofMain.h"
#include "testApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){

    
    ofAppGlutWindow window;
    window.setGlutDisplayString("rgba double samples>=8 depth"); //antialiasing
//    ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
	ofSetupOpenGL(&window, 1920,1080, OF_FULLSCREEN);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}