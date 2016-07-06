/*
COPYRIGHT ENRICO STEINFELD. ALL RIGHTS RESERVED
*/

#include "ofApp.h"

string ofApp::getBit(int k)
{
	string s;
		for (int i=0; i<22; ++i){
		if (k & (1 << i)) {
			s = "1" + s;
		} else {
			s = "0" + s;
		}
	}
	return s;
}

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetVerticalSync(true);
	//ofEnableSmoothing();
	ofEnableDepthTest();
	ofSetFrameRate(60);

	ofSetSmoothLighting(true);

	swarm.setup();
	particleTemplate.velocity = ofVec3f(ofRandomf(),ofRandomf(),ofRandomf());
		
	//-------------------------------------------------------------------------GUI----------
	
	but_overwriteAttributes.addListener(this, &ofApp::overwriteAttributes);
	but_overwriteParameters.addListener(this, &ofApp::overwriteParameters);
	
	guiAttributes.setup(particleTemplate.attributes.group, "Attributes", 5,5);
	guiAttributes.add(but_overwriteAttributes.setup("Overwrite"));
	
	guiParameters.setup(particleTemplate.parameters.group, "Parameters", 5, 200);
	guiParameters.add(but_overwriteParameters.setup("Overwrite"));

		
	//---------------------------------------------------------------------------------------
	

	//-------------------------------------CAMERA--------------
	camera.setDistance(100);
	
	//---------------------------------------------------------
	//-------------------------------------------LIGHTS-------------

	pointLight.setDiffuseColor( ofColor(255.f, 255.f, 255.f));
    
    // specular color, the highlight/shininess color //
	pointLight.setSpecularColor( ofColor(255.f, 255.f, 255.f));
    pointLight.setPosition(0, 0, 0);
    
    // shininess is a value between 0 - 128, 128 being the most shiny //
	material.setShininess( 64 );


	//---------------------------------------CONTROLLER MPD------------

	mpd.setup();

	//----------------------------------------------------------------
	
	//----------------------------STATIC PARTICLES---------------
	int num = 400;
	for (unsigned int i=0; i<num; ++i){
		//spherical
		float a1 = ofRandom(0, TWO_PI);
		float a2 = ofRandom(0, TWO_PI);
		
		float dist = ofRandom(1800, 2500);
		ofVec3f pos( dist*cos(a1)*cos(a2), dist*sin(a1)*cos(a2), dist*sin(a2));
		/*
		staticParticles.push_back(Particle(&staticParticles, 0, pos, ofVec3f(0,0,0)));
		staticParticles[i].lookAt(ofVec3f(0, 0, 0));
		staticParticles[i].color = ofColor(0, 50);
		staticParticles[i].setRadius(6);
		*/
	}	
	//----------------------------------------------------------

}

//---------------------------------------------------------------------------------------

//--------------------------------------------------------------
void ofApp::update()
{
	swarm.update();
	if (mpd.newDataAvailable) {
		updateParticleFromMpd();
		mpd.newDataAvailable = false;
	}

}

//--------------------------------------------------------------
void ofApp::draw()
{	
	camera.begin();
	//ofBackground(240);
	ofBackground(10);
	//ofPushMatrix();
	//ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
	/*
	ofDisableDepthTest();
	for (unsigned int i=0; i<staticParticles.size(); ++i){
		staticParticles[i].draw(-staticParticles[i].getPosition());
	}git
	*/
	
	
	ofEnableDepthTest();
	ofEnableLighting();

	//ofEnableAlphaBlending();
	//glEnable(GL_DEPTH_TEST); 

	pointLight.enable();
	material.begin();


	//drawBorders();		//TODO: fix alpha blending issue
	swarm.draw();
	
	//ofDrawAxis(32);
	//ofPopMatrix();

	material.end();
	// turn off lighting //
    ofDisableLighting();
	camera.end();
	
	if (!hideGui) {
		ofDisableDepthTest();
		guiAttributes.draw();
		guiParameters.draw();
	}
	
	if (!hideStats) {
		ofSetColor(0);
		ofDrawBitmapString("framerate: " + ofToString(ofGetFrameRate()),ofGetWidth() - 160, 20);
	}
}
//--------------------------------------------------------------


//--------------------------------------------------------------GUI FUNCTIONS------------

void ofApp::overwriteAttributes()
{
	swarm.overwriteAttributes(particleTemplate);
}

void ofApp::overwriteParameters()
{
	swarm.overwriteParameters(particleTemplate);
}

void ofApp::drawBorders()
{
	//ofPushMatrix();
	//ofTranslate(paraBorderX->x,paraBorderY->x,paraBorderZ->x);
	//ofBoxPrimitive box(paraBorderX->y-paraBorderX->x, paraBorderY->y-paraBorderY->x, paraBorderZ->y-paraBorderZ->x);
	/*box.setSideColor(0, ofColor(0,30));
	box.setSideColor(1, ofColor(0,30));
	box.setSideColor(2, ofColor(0,30));
	box.setSideColor(3, ofColor(0,30));
	box.setSideColor(4, ofColor(0,30));
	*/
	/*
	ofMesh sideXYMin;
	sideXYMin.addVertex(ofVec3f(paraBorderX->x,paraBorderY->x,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->y,paraBorderY->x,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->y,paraBorderY->y,paraBorderZ->x));
	sideXYMin.addVertex(ofVec3f(paraBorderX->x,paraBorderY->y,paraBorderZ->x));
	
	ofSetColor(20,20);
	sideXYMin.draw();
	//box.draw();
	ofPopMatrix();
	*/
}

//---------------------------------------------------------------------------


void ofApp::updateParticleFromMpd()
{
	int pitch = mpd.midiMessage.pitch;
	int vel = mpd.midiMessage.velocity;
	int control = mpd.midiMessage.control;
	int value = mpd.midiMessage.value;
	/*
	*	auf dem mpd kann ausgewählt werden wohin die parameter/attributes geladen werden
	*	-> zu einem der Swarms; zu allen; für die nächsten generierten Partikel

	switch (mpd.midiMessage.control) {
		case 2:
			nextParticle.parameters.color_diff_mult = ofMap(value,1,127,0.0,1.0);
			break;
		case 3:
			nextParticle.parameters.collision_mult = ofMap(value,1,127,0.0,1.0);
			break;
		case 4:
			nextParticle.parameters.drag = ofMap(value,1,127,0.0,1.0);
			break;
		case 5:
			nextParticle.parameters.mass = ofMap(value,1,127,0.01,4.0);
			break;
		case 6:
			nextParticle.parameters.spring_stiffness = ofMap(value,1,127,0.0,4.0);
			break;
		case 7:
			nextParticle.parameters.spring_damping = ofMap(value,1,127,0.0,1.0);
			break;
	}
	overwriteParameters();
	*/
}

void ofApp::keyPressed(int key)
{

	switch (key) {
		case 'f':
			ofToggleFullscreen();
			break;


	}

	if (key == '1') {
		
	} else if (key == '2') {
	} else if (key == '3') {
	} else if (key == '4') {
	} else if (key == ' ') {
		overwriteAttributes();
		overwriteParameters();
	} else if (key == 'h') {
		hideGui = !hideGui;
	} else if (key == 's') {
		hideStats = !hideStats;
	} else if (key == 'k') {
		if (swarm.getNumParticles() > 0)
	   		swarm.eliminateParticle(0);
	} else {
		swarm.generateParticle(particleTemplate);
		//cout << getBit(particles[particles.size()-1].attributes.bits) << endl;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	isMousePressed = true;
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	isMousePressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
