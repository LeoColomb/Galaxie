#include "gInitialisation.h"

//--------------------------------------------------------------
gInitZone::gInitZone() {
	isFixed = false;
	x = (ofGetWidth() / 2);
	y = (ofGetHeight() / 2);
}

//--------------------------------------------------------------
void gInitZone::update(int xM, int yM) {
	x = xM;
	y = yM;
}

//--------------------------------------------------------------
void gInitZone::draw() {
	ofFill();
	if (!isFixed) {
		ofSetColor(ofColor::red);
		ofSetCircleResolution(50);
		ofCircle(x,y,100);
		return;
	}
	ofSetColor(ofColor::red);
	ofCircle(x,y,100);
}

//--------------------------------------------------------------
void gInitZone::fixed() {
	isFixed = true;
	x = 0;
	y = 0;
}

//--------------------------------------------------------------
string gInitZone::getName() {
	return "init";
}