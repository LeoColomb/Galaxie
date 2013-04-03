#include "transitions.h"

//--------------------------------------------------------------
particules::particules() {
}

void particules::init() {
	ofSetColor(0,255,0);
	timeNow = ofGetElapsedTimef();
	randomShX = ofRandomf();
	randomShY = ofRandomf();
	bDirection = true;
	bMouv = true;
}

void particules::reset() {
	x = (randomShX * (ofGetElapsedTimef() - timeNow) * 50);
	y = (randomShY * (ofGetElapsedTimef() - timeNow) * 50);
	timeNow = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void particules::update(int step) {
	if (step == 4)
	{
		reset();
		bMouv = false;
		bDirection = false;
	}
	else
		bMouv = true;
	colored = ofRandom(step, 5)-step;
}

//--------------------------------------------------------------
void particules::draw() {
	if (ofDist(0, 0, x, y) >= 200)
	{
		reset();
		bDirection = false;
	}
	if (x == 0 || y == 0)
	{
		reset();
		if (bMouv)
			bDirection = true;
		else
		{
			x = 0;
			y = 0;
		}
	}

	if (bDirection)
	{
		x = (randomShX * (ofGetElapsedTimef() - timeNow) * 50);
		y = (randomShY * (ofGetElapsedTimef() - timeNow) * 50);
	}
	else if (bMouv)
	{
		x -= (randomShX * (ofGetElapsedTimef() - timeNow) * (50));
		y -= (randomShY * (ofGetElapsedTimef() - timeNow) * (50));
	}
	ofFill();
	if (colored <= 0)
	{
		ofSetColor(ofColor::greenYellow);
	} else
	{
		ofSetColor(ofColor::mediumVioletRed);
	}
	if (!bMouv)
	{
		ofSetColor(ofColor::greenYellow,1);
	}
	ofCircle(x,y,3);
}