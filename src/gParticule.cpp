//
// GALAXIE
// Interactive Collection of Planets
//
// Leo Colombaro - 2013
// MIT License
//

#include "gParticule.h"

//--------------------------------------------------------------
particules::particules(){
	timeNow = ofGetElapsedTimef();	// Get the time now
	randomShX = ofRandomf();		// Get a random number between 0-1
	randomShY = ofRandomf();		// Get a random number between 0-1
	bDirection = true;	// Direction spec
	bMouv = true;		// Mouvement activation
}

//--------------------------------------------------------------
void particules::reset(){
	x = (randomShX * (ofGetElapsedTimef() - timeNow) * 50);
	y = (randomShY * (ofGetElapsedTimef() - timeNow) * 50);
	timeNow = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void particules::update(int step){
	coloration = step;
}

//--------------------------------------------------------------
void particules::draw(){
	if (ofDist(0, 0, x, y) >= 200){
		reset();
		bDirection = false;
	}
	if (x == 0 || y == 0){
		randomShX = ofRandomf();		// Get a random number between 0-1
		randomShY = ofRandomf();		// Get a random number between 0-1
		reset();
		if (bMouv)
			bDirection = true;
	}

	if (bDirection){
		x = (randomShX * (ofGetElapsedTimef() - timeNow) * 50);
		y = (randomShY * (ofGetElapsedTimef() - timeNow) * 50);
	} else if (bMouv){
		x -= (randomShX * (ofGetElapsedTimef() - timeNow) * (50));
		y -= (randomShY * (ofGetElapsedTimef() - timeNow) * (50));
	} else {
		x = 1;
		y = 1;
	}
	ofFill();
	if (coloration <= 0){
		ofSetColor(ofColor::greenYellow);
	} else {
		ofSetColor(ofColor::mediumVioletRed);
	}
	if (!bMouv){
		ofSetColor(ofColor::greenYellow,1);
	}
	ofCircle(x,y,3);
}
