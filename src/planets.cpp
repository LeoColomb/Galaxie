#include "planets.h"

//--------------------------------------------------------------
planets::planets() {
	//for(int i = 0; i < 100; i++) {
	//	allParticules[i].init();
	//}
	galaxieConf.loadFile("planets.xml");
	float angle = 0;
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
}

//--------------------------------------------------------------
void planets::init() {
}

//--------------------------------------------------------------
void planets::update(int step) {
	//for(int i = 0; i < 100; i++) {
	//	allParticules[i].update(step);
	//}
	// make a pentagon
	soundPlay.loadSound("sounds/" + galaxieConf.getValue("planet:sound:part" + ofToString(step), "") + ".mp3");
	soundPlay.setLoop(true);
	//soundPlay.play();
	soundPlay.setPosition(0.5f); //Back to center
}

//--------------------------------------------------------------
void planets::draw() {
	//for(int i = 0; i < 100; i++) {
	//	allParticules[i].draw();
	//}
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
}

//--------------------------------------------------------------
void planets::select(int selection, int rang) {
}

//--------------------------------------------------------------
void planets::interaction(int varianceD) {
	proximity = (int)(varianceD / 5);
}

//--------------------------------------------------------------
void planets::drawShadow(float x, float y, int z)
{
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
string planets::getName(){
	return "planet";
}

//--------------------------------------------------------------
void planets::mousePressed(int x, int y, int button){
	changeState("transitions");
}