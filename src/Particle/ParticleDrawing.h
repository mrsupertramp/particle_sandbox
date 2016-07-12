#pragma once

#include "ofMain.h"
#include "ofParameter.h"

class ParticleDrawing{
	public:
		void draw(ofVec3f pos, ofVec3f dir);
		void drawCircle(ofVec3f pos, ofVec3f dir);
		void drawSphere(ofVec3f pos);
		void drawArrow(ofVec3f from, ofVec3f to);

	private:
		int mode = 0;
		int radius = 10;

};