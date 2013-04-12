#include "initApp.h"

//--------------------------------------------------------------
initAppZone::initAppZone() {
	isFixed = false;
	x = (ofGetWidth() / 2);
	y = (ofGetHeight() / 2);
	planetCore1.setArcResolution(200);
	planetCore1.setFilled(true);
	planetCore1.setColor(ofColor::green);
	planetCore1.moveTo(0,0);
	planetCore1.arc(0,0,100,100,225,270);
	planetCore1.close();

	planetCore2.setArcResolution(200);
	planetCore2.setFilled(true);
	planetCore2.moveTo(0,0);
	planetCore2.arc(0,0,100,100,180,225);
	planetCore2.setColor(ofColor::blue);
	planetCore2.close();

	planetCore3.setArcResolution(200);
	planetCore3.setFilled(true);
	planetCore3.setColor(ofColor::green);
	planetCore3.moveTo(0,0);
	planetCore3.arc(0,0,100,100,330,0);
	planetCore3.close();

	planetCore4.setArcResolution(200);
	planetCore4.setFilled(true);
	planetCore4.moveTo(0,0);
	planetCore4.arc(0,0,100,100,0,30);
	planetCore4.setColor(ofColor::blue);
	planetCore4.close();

}

//--------------------------------------------------------------
void initAppZone::update(int xM, int yM) {
	x = xM;
	y = yM;
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
	ofColor altern(ofColor::fromHsb(sinf(ofGetElapsedTimef()) * 128 + 128, 255, 255));
	planetCore1.setColor(altern);
	planetCore2.setColor(sin(ofGetElapsedTimef())*255);
	planetCore3.setColor(altern);
	planetCore4.setColor(sin(ofGetElapsedTimef())*255);
	planetCore1.draw();
	planetCore2.draw();
	planetCore3.draw();
	planetCore4.draw();
}

//--------------------------------------------------------------
void initAppZone::fixed() {
	isFixed = true;
	x = 0;
	y = 0;
}

//--------------------------------------------------------------
string initAppZone::getName() {
	return "init";
}