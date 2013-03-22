#include "transitions.h"

//--------------------------------------------------------------
particules::particules() {
	x = ofRandom(0, ofGetWidth());
	y = ofRandom(0, ofGetHeight());
}

//--------------------------------------------------------------
void particules::update() {
}

//--------------------------------------------------------------
void particules::draw() {
	ofSetColor(255,0,0);
	ofFill();
	ofEllipse(x,y,25,25);
}

//--------------------------------------------------------------
galaxieTransitions::galaxieTransitions() {
}

//--------------------------------------------------------------
void galaxieTransitions::update(int step) {
	for(int i = 0; i < allParticules.size(); i++) {
		allParticules[i].update();
	}
}

//--------------------------------------------------------------
void galaxieTransitions::draw() {
	for(int i = 0; i < allParticules.size(); i++) {
		allParticules[i].draw();
	}
}