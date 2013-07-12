//
// GALAXIE
// Interactive Collection of Planets
//
// Leo Colombaro - 2013
// MIT License
//

#include "gTransition.h"

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
void gTransition::sceneWillAppear(ofxScene * fromScreen){
	//sharedData::thisSelection = 0;
	configStep = 0;
	for (int i = 0; i < 100; i++){
		allParticules.push_back(particules());
	}
}

//--------------------------------------------------------------
void gTransition::sceneDidDisappear(ofxScene * fromScreen){
	for(int i = 0; i < 100; i++){
		allParticules.pop_back();
	}
}
