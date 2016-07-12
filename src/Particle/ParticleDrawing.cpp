#include "ParticleDrawing.h"

void ParticleDrawing::draw(ofVec3f pos, ofVec3f dir){
	switch(mode) {
		case 0:
			drawCircle(pos, dir);
			break;
		case 1:
			drawSphere(pos);
			break;
	}
}

void ParticleDrawing::drawSphere(ofVec3f pos)
{
	ofSpherePrimitive sphere;
	sphere.setResolution(20);
	ofPushMatrix();
	ofTranslate(pos);
	ofSetColor(255);
	//sphere.drawWireframe();
	sphere.draw();

	ofPopMatrix();
}

void ParticleDrawing::drawCircle(ofVec3f pos, ofVec3f dir)
{
	ofFill();

	ofPushMatrix();
	ofSetColor(0);
	
	ofTranslate(pos);
	
	ofVec3f normal = dir;
	normal.normalize();
	
	float rotationAmount;
	ofVec3f rotationAngle;
	ofQuaternion rotation;
	
	ofVec3f axis(0, 0, 1);
	rotation.makeRotate(axis, normal);
	rotation.getRotate(rotationAmount, rotationAngle);
	ofRotate(rotationAmount, rotationAngle.x, rotationAngle.y, rotationAngle.z);
	ofDrawCircle(ofVec3f(0,0,0), radius);
	
	ofPopMatrix();
	

		
		//ofDrawLine(getPosition(),prevPtr->getPosition());
}

void ParticleDrawing::drawArrow(ofVec3f from, ofVec3f to)
{
	ofSetColor(30);
	
	//draw arrow with p1,p2,p3 and tip at p2
	
	float size = from.distance(to) * 0.3;
	if (size > 50)
		size = 50;
	ofVec3f dirNorm = to - from;
	dirNorm.normalize();
	
	ofVec3f toTheLeft = dirNorm.getRotated( 90, ofVec3f( 0, 0, 1 ) );
	ofVec3f toTheRight = dirNorm.getRotated( -90, ofVec3f( 0, 0, 1 ) );
	
	ofVec3f p1 = to - dirNorm*radius - dirNorm*size*0.7 + toTheRight*size*0.3;
	ofVec3f p2 = to - dirNorm*radius;
	ofVec3f p3 = to - dirNorm*radius - dirNorm*size*0.7 + toTheLeft*size*0.3;
	
	ofDrawLine(p1,p2);
	ofDrawLine(p3,p2);
	ofDrawLine(from, p2);
}