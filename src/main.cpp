#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 2);
    settings.width = 3840;	//1280
    settings.height = 2040;	//720
    ofCreateWindow(settings);
    ofRunApp(new ofApp());
}
