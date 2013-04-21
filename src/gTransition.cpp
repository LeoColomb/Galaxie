//
// GALAXIE
// Interactive Collection of Planets
//
// Leo Colombaro - 2013
// MIT License
//

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

//--------------------------------------------------------------
//--------------------------------------------------------------
gTransition::gTransition(){
	configStep = 0;

	for (int i = 0; i < 4; i++){
		planetCore[i].setArcResolution(100);
		planetCore[i].setFilled(true);
		planetCore[i].moveTo(0,0);
	}

	planetCore[0].arc(0,0,100,100,180,225);
	planetCore[1].arc(0,0,100,100,225,270);
	planetCore[2].arc(0,0,100,100,340,0);
	planetCore[3].arc(0,0,100,100,0,20);
	for (int i = 0; i < 4; i++){
		planetCore[i].close();
	}

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

	planetCore[0].setColor(alternBaW);
	planetCore[1].setColor(alternColor);
	planetCore[2].setColor(alternBaW);
	planetCore[3].setColor(alternColor);

	for (int i = 0; i < 4; i++){
		planetCore[i].draw();
	}
	
}

//--------------------------------------------------------------
void gTransition::mousePressed(int x, int y, int button){
	selection[configStep] = x;
	configStep++;
	if (configStep == 3){
		int result = (int)(selection[0] + selection[1] + selection[2])/100;
		thisSelection = result;
	}
}

//--------------------------------------------------------------
void gTransition::sceneWillAppear(ofxScene * fromScreen){
	thisSelection = 0;
	configStep = 0;
}
