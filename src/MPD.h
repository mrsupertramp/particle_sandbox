#pragma once

#include "ofMain.h"
#include <stdio.h>
#include "ofxMidi.h"


class MPD{
	public:
		void setup();

		//void newMessage(ofxMidiEventArgs &args);

	private:
		ofxMidiIn midiIn;
		ofxMidiMessage midiMessage; 
};