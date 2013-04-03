#include "initApp.h"

//--------------------------------------------------------------
initAppZone::initAppZone() {
	isFixed = false;
	x = (ofGetWidth() / 2);
	y = (ofGetHeight() / 2);
}

//--------------------------------------------------------------
void initAppZone::update(int xM, int yM) {
	x = xM;
	y = yM;
}

//--------------------------------------------------------------
void initAppZone::draw() {
	if (isFixed) {
		ofSetColor(ofColor::gray);
	} else {
		ofSetColor(ofColor::red);
	}
	ofFill();
	ofSetCircleResolution(50);
	ofCircle(x,y,100);
}

//--------------------------------------------------------------
void initAppZone::fixed() {
	isFixed = true;
	x = 0;
	y = 0;
}