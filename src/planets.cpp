#include "planets.h"

//--------------------------------------------------------------
planets::planets() {
}

//--------------------------------------------------------------
void planets::init() {
	for(int i = 0; i < 100; i++) {
		allParticules[i].init();
	}
}

//--------------------------------------------------------------
void planets::update(int step) {
	for(int i = 0; i < 100; i++) {
		allParticules[i].update(step);
	}
	// make a pentagon
	float angle = 0;
	while (angle < TWO_PI ) {
		rotor.lineTo(200*cos(angle), 200*sin(angle));
		rotor.lineTo(150*cos(angle+(TWO_PI / 30)), 150*sin(angle+(TWO_PI / 30)));
		angle += TWO_PI / 15;
	}
	rotor.close();
}

//--------------------------------------------------------------
void planets::draw() {
	for(int i = 0; i < 100; i++) {
		allParticules[i].draw();
	}
	//	if (addTriangle){
	ofPushMatrix();
	ofRotate(sin(ofGetElapsedTimef())*180);
	ofNoFill();
	ofTriangle(0,-400,-(600/sin(PI/3))*cos(PI/3),200,(600/sin(PI/3)*cos(PI/3)),200);
	ofPopMatrix();
	//	if (addRotor){
	ofPushMatrix();
	ofRotate(ofGetElapsedTimef()*90);
	rotor.draw();
	ofPopMatrix();
}

//--------------------------------------------------------------
void planets::select(int selection, int rang) {
}

//--------------------------------------------------------------
void planets::interaction(int varianceD) {
	proximity = (int)(varianceD / 5);
}

//--------------------------------------------------------------
void planets::drawShadow(float x, float y, int z)
{
	ofSetColor(255, 255, 255, 200);
	ofCircle(x, y, 150);
	float xV = x + z / 2.;
	float yV = y + z / 2.;

	ofPushMatrix();
	ofTranslate(x + 0, y + 0, 0);
	ofScale(1, 3, 1);
	shadow->draw(-z / 2., - z / 2., z, z);
	ofPopMatrix();
}