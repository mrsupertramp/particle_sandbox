#pragma once

#include "ofMain.h"
#include <stdio.h>
#include "ofxMidi.h"


class MPD: public ofxMidiListener{
	public:
		void setup();

		void newMidiMessage(ofxMidiMessage& eventArgs);

		bool newDataAvailable;

		ofxMidiMessage midiMessage;

		ofxMidiIn midiIn;


	private:


};