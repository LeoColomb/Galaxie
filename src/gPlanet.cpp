/****
* GALAXIE
* Interactive Collection of Planets
*
* Leo Colombaro - 2013
* MIT License
*****/

#include "gPlanet.h"

//--------------------------------------------------------------
gPlanet::gPlanet(){
	galaxieConf.loadFile("planets.xml");

	// Init all forms available
	float angle = 0; // Angle from 0 to 360
	while (angle < TWO_PI ) {
		rotor.lineTo(200*cos(angle), 200*sin(angle));
		rotor.lineTo(150*cos(angle+(TWO_PI / 30)), 150*sin(angle+(TWO_PI / 30)));
		angle += TWO_PI / 15;
	}
	rotor.close();
	angle = 0;
	while (angle <= TWO_PI+(TWO_PI / 12) ) {
		curvor.curveTo(200*cos(angle), 200*sin(angle));
		curvor.curveTo(150*cos(angle+(TWO_PI / 28)), 150*sin(angle+(TWO_PI / 28)));
		angle += TWO_PI / 14;
	}

	// Init parts of central zone: planet core
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
void gPlanet::update(int step){
	// make a pentagon
	soundPlay.loadSound("sounds/" + galaxieConf.getValue("planet:sound:part" + ofToString(step), "") + ".mp3");
	soundPlay.setLoop(true);
	//soundPlay.play();
	soundPlay.setPosition(0.5f); //Back to center
}

//--------------------------------------------------------------
void gPlanet::draw(){
	galaxieConf.pushTag("planet");
	galaxieConf.pushTag("structure");
	if (galaxieConf.tagExists("triangle")){
		ofPushMatrix();
		ofSetColor(galaxieConf.getValue("triangle:r", 0),galaxieConf.getValue("triangle:g", 0),galaxieConf.getValue("triangle:b", 0));
		ofRotate(sin(ofGetElapsedTimef())*180);
		ofNoFill();
		ofTriangle(0,-400,-(600/sin(PI/3))*cos(PI/3),200,(600/sin(PI/3)*cos(PI/3)),200);
		ofPopMatrix();
	}
	if (galaxieConf.tagExists("rotor")){
		ofPushMatrix();
		ofSetColor(galaxieConf.getValue("rotor:r", 0),galaxieConf.getValue("rotor:g", 0),galaxieConf.getValue("rotor:b", 0));
		ofRotate(ofGetElapsedTimef()*90);
		rotor.draw();
		ofPopMatrix();
	}
	if (galaxieConf.tagExists("curvor")){
		ofPushMatrix();
		ofSetColor(galaxieConf.getValue("curvor:r", 0),galaxieConf.getValue("curvor:g", 0),galaxieConf.getValue("curvor:b", 0));
		ofRotate(ofGetElapsedTimef()*20);
		curvor.draw();
		ofPopMatrix();
	}
	galaxieConf.popTag();
	galaxieConf.popTag();

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
void gPlanet::select(int selection, int rang){
}

//--------------------------------------------------------------
void gPlanet::interaction(int varianceD){
	proximity = (int)(varianceD / 5);
}

//--------------------------------------------------------------
void gPlanet::drawShadow(float x, float y, int z){
	ofSetColor(255, 255, 255, 200);
	ofCircle(x, y, 150);
	float xV = x + z / 2.;
	float yV = y + z / 2.;

	ofPushMatrix();
	ofTranslate(x + 0, y + 0, 0);
	ofScale(1, 3, 1);
	shadow->draw(-z / 2., - z / 2., z, z);
	ofPopMatrix();
}

//--------------------------------------------------------------
string gPlanet::getName(){
	return "planet";
}

//--------------------------------------------------------------
void gPlanet::mousePressed(int x, int y, int button){
	changeState("transition");
}