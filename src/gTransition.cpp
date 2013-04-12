/****
* GALAXIE
* Interactive Collection of Planets
*
* Leo Colombaro - 2013
* MIT License
*****/

#include "gTransition.h"

//--------------------------------------------------------------
// Particules initialisation
particules::particules(){
	timeNow = ofGetElapsedTimef();	// Get the time now
	randomShX = ofRandomf();		// Get a random number between 0-1
	randomShY = ofRandomf();		// Get a random number between 0-1
	bDirection = true;	// Direction spec
	bMouv = true;		// Mouvement activation
}

//--------------------------------------------------------------
// 
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
		reset();
		if (bMouv)
			bDirection = true;
		else {
			x = 0;
			y = 0;
		}
	}

	if (bDirection){
		x = (randomShX * (ofGetElapsedTimef() - timeNow) * 50);
		y = (randomShY * (ofGetElapsedTimef() - timeNow) * 50);
	} else if (bMouv){
		x -= (randomShX * (ofGetElapsedTimef() - timeNow) * (50));
		y -= (randomShY * (ofGetElapsedTimef() - timeNow) * (50));
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

//--------------------------------------------------------------
//--------------------------------------------------------------
gTransition::gTransition(){
	configStep = 0;

	planetCore1.setArcResolution(100);
	planetCore1.setFilled(true);
	planetCore1.moveTo(0,0);
	planetCore1.arc(0,0,100,100,180,225);
	planetCore1.close();

	planetCore2.setArcResolution(100);
	planetCore2.setFilled(true);
	planetCore2.moveTo(0,0);
	planetCore2.arc(0,0,100,100,225,270);
	planetCore2.close();

	planetCore3.setArcResolution(100);
	planetCore3.setFilled(true);
	planetCore3.moveTo(0,0);
	planetCore3.arc(0,0,100,100,340,0);
	planetCore3.close();

	planetCore4.setArcResolution(100);
	planetCore4.setFilled(true);
	planetCore4.moveTo(0,0);
	planetCore4.arc(0,0,100,100,0,20);
	planetCore4.close();
}

//--------------------------------------------------------------
void gTransition::update(){
	for(int i = 0; i < 100; i++){
		allParticules[i].update(configStep);
	}
}

//--------------------------------------------------------------
void gTransition::draw(){
	for(int i = 0; i < 100; i++){
		allParticules[i].draw();
	}
	ofSetColor(ofColor::white);
	ofCircle(0,0,100);

	ofColor alternColor(ofColor::fromHsb(sinf(ofGetElapsedTimef()/8) * 128 + 128, 255, 255));
	ofColor alternBaW(ofColor::fromHsb(0, 0, sinf(ofGetElapsedTimef()/2) * 128 + 128));

	planetCore1.setColor(alternBaW);
	planetCore1.draw();

	planetCore2.setColor(alternColor);
	planetCore2.draw();

	planetCore3.setColor(alternBaW);
	planetCore3.draw();

	planetCore4.setColor(alternColor);
	planetCore4.draw();
}

//--------------------------------------------------------------
void gTransition::mousePressed(int x, int y, int button){
	configStep++;
	if (configStep == 3){
		configStep = 0;
		changeState("planet");
	}
}

//--------------------------------------------------------------
string gTransition::getName(){
	return "transition";
}