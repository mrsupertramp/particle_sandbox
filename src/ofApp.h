/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/
#pragma once

#include "ofMain.h"
#include "ofxGui.h"
//#include "ofxMidi.h"
#include "MPD.h"
#include "Swarm.h" 
#include "Particle.h"

#define MAX_SWARMS	10

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void println(string s);

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		
		void generateSwarm();

		void drawBorders();
		
		void overwriteAttributes();
		void overwriteParameters();
		
		ofxButton but_overwriteAttributes;
		ofxButton but_overwriteParameters;
		
		ofxPanel guiAttributes;
		ofxPanel guiParameters;
		
		bool hideGui = false;		
		
		vector <Swarm> swarms;
		Swarm swarm;
		
		Particle particleTemplate;

		int selectedSwarm;

		//--------------------------------------------------------------------
		
		
		//------------------------------------------------------CAMERA--------
		
		//Easy Cam vs ofCamera
		ofEasyCam camera;
		
		//--------------------------------------------------------------------
		
		//-----------------------------------------------------LIGHTING----------
		ofLight pointLight;
		ofLight spotLight;
    	ofLight directionalLight;

		ofMaterial material;


		//-------------------------------------------------------CONTROLER MPD----

		MPD mpd;
		void updateParticleFromMpd();



		//---------------------------------------------------------------------

		bool isMousePressed = false;
		
		//----------------------------------------------------SHOW STATS--------
		bool hideStats = false;
		
		//----------------------------------------------------------------------
		string getBit(int k);
		
	private:

			
};
