/****
* GALAXIE
* Interactive Collection of Planets
*
* Leo Colombaro - 2013
* MIT License
*****/

#include "gInitialisation.h"

//--------------------------------------------------------------
gInitZone::gInitZone(){
	isFixed = false;
	x = (ofGetWidth() / 2);
	y = (ofGetHeight() / 2);
}

//--------------------------------------------------------------
void gInitZone::update(int xM, int yM){
	x = xM;
	y = yM;
}

//--------------------------------------------------------------
void gInitZone::draw(){
	ofFill();
	if (!isFixed){
		ofSetColor(ofColor::red);
		ofCircle(x,y,100);
		return;
	}
	ofSetColor(ofColor::red);
	ofCircle(x,y,100);
}

//--------------------------------------------------------------
void gInitZone::fixed(){
	isFixed = true;
	x = 0;
	y = 0;
}

//--------------------------------------------------------------
void gInitZone::mouseMoved(int x, int y){
	update(x, y);
}

//--------------------------------------------------------------
string gInitZone::getName(){
	return "init";
}