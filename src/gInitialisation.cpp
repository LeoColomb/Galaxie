//
// GALAXIE
// Interactive Collection of Planets
//
// Leo Colombaro - 2013
// MIT License
//

#include "gInitialisation.h"

//--------------------------------------------------------------
gInitZone::gInitZone(){
	isFixed = false;
	x = (ofGetWidth() / 2);
	y = (ofGetHeight() / 2);
}

//--------------------------------------------------------------
void gInitZone::draw(){
	ofFill();
	if (!isFixed){
		ofSetColor(ofColor::red);
		ofCircle(x,y,100);
	} else {
		ofSetColor(ofColor::green);
		ofCircle(0,0,100);
	}
}

//--------------------------------------------------------------
void gInitZone::mousePressed(int x, int y, int button){
	isFixed = true;
}

//--------------------------------------------------------------
void gInitZone::mouseMoved(int xM, int yM){
	x = xM;
	y = yM;
}
