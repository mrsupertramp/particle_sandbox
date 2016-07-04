#include "MPD.h"

void MPD::setup()
{

	ofSetVerticalSync(true);
	ofBackground(255, 255, 255);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	// print input ports to console
	midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	midiIn.openPort(1);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add ofApp as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(false);
}

void MPD::newMidiMessage(ofxMidiMessage& msg)
{
	if (msg.channel == 1) {
		cout << "channel: " << midiMessage.channel;

		cout << " pitch: " << midiMessage.pitch;

		cout << " velocity: " << midiMessage.velocity;
		cout << " control: " << midiMessage.control;
		cout << " value: " << midiMessage.value << endl;
		midiMessage = msg;
		newDataAvailable = true;
	}
}