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
	planetCore.setArcResolution(100);
	planetCore.setFillColor(ofColor::blue);
	planetCore.arc(0,0,100,100,0,180);
	planetCore.close();
}

//--------------------------------------------------------------
void initAppZone::draw() {
	ofFill();
	if (!isFixed) {
		ofSetColor(ofColor::red);
		ofSetCircleResolution(50);
		ofCircle(x,y,100);
		return;
	}
	ofSetColor(ofColor::red);
	ofCircle(x,y,100);
	ofSetColor(ofColor::blue);
	planetCore.draw();
}

//--------------------------------------------------------------
void initAppZone::fixed() {
	isFixed = true;
	x = 0;
	y = 0;
}