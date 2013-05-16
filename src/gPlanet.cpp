//
// GALAXIE
// Interactive Collection of Planets
//
// Leo Colombaro - 2013
// MIT License
//

#include "gPlanet.h"

//--------------------------------------------------------------
gPlanet::gPlanet(){
	step = 0;
	galaxieConf.loadFile("planets.xml");

	xivelyTransfert = new ofxXivelyInput(true);
	xivelyTransfert->setApiKey(XIVELY_API_KEY);
	xivelyTransfert->setFeedId(XIVELY_FEED);
	xivelyTransfert->setVerbose(true);
	xivelyTransfert->setMinInterval(5);
	xivelyTransfert->input(OFX_XIVELY_EEML, true);    /// forcing update = ignoring min interval

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
void gPlanet::update(int newStep){
	float playTime;
	if (step >= 0){
		playTime = soundPlay[step].getPosition();
		soundPlay[step].stop();
	} else
		playTime = 0.0;
	soundPlay[newStep].play();
	soundPlay[newStep].setPosition(playTime);
	step = newStep;
	xivelyTransfert->setValue(1, ofRandom(0,100));
	xivelyTransfert->input();
}

//--------------------------------------------------------------
void gPlanet::draw(){
	galaxieConf.pushTag("galaxie");
	galaxieConf.pushTag("planet", thisPlanet);
	galaxieConf.pushTag("structure");
	if (galaxieConf.tagExists("triangles")){
		galaxieConf.pushTag("triangles");
		for (int i = 0; i < galaxieConf.getNumTags("triangle"); i++)
		{
			galaxieConf.pushTag("triangle", i);
			ofPushMatrix();
			ofSetHexColor(galaxieConf.getValue("color", 0));
			if (galaxieConf.tagExists("rotative"))
				ofRotate(sinf(ofGetElapsedTimef())*180);
			ofNoFill();
			if (galaxieConf.tagExists("alternative")){
				ofPoint equilateral[3];
				float angle = 0; // Angle from 0 to 360
				for(int i = 0; i < 3; i++){
					equilateral[i].x = (200) * cos(angle);
					equilateral[i].y = (200) * sin(angle);
					angle += TWO_PI/3;
					ofLogNotice() << equilateral[i].x;
				}
				for(int i = 0; i < 4; i++){
					ofTriangle(equilateral[1], equilateral[2], equilateral[3]);
				}
			} else
				ofTriangle(0,-400,-(600/sinf(PI/3))*cosf(PI/3),200,(600/sinf(PI/3)*cosf(PI/3)),200);
			ofPopMatrix();
			galaxieConf.popTag();
		}
		galaxieConf.popTag();
	}
	if (!galaxieConf.tagExists("rotor")){
		ofPushMatrix();
		ofSetColor(galaxieConf.getValue("rotor:r", 0),galaxieConf.getValue("rotor:g", 0),galaxieConf.getValue("rotor:b", 0));
		ofRotate(ofGetElapsedTimef()*90);
		rotor.draw();
		ofPopMatrix();
	}
	if (!galaxieConf.tagExists("curvor")){
		if (galaxieConf.getAttribute("curvor", "step", 0)-1 == step){
			ofPushMatrix();
			ofSetColor(galaxieConf.getValue("curvor:r", 0),galaxieConf.getValue("curvor:g", 0),galaxieConf.getValue("curvor:b", 0));
			ofRotate(ofGetElapsedTimef()*20);
			curvor.draw();
			ofPopMatrix();
		}
	}
	galaxieConf.popTag();

	ofFill();

	galaxieConf.pushTag("colors");
	ofSetHexColor(galaxieConf.getValue("fondamentale", 0));
	ofCircle(0,0,100);
	ofColor alternColor(ofColor::fromHsb((timeTrigo("sin")/8) * 128 + 128, 255, 255));
	ofColor alternBaW(ofColor::fromHsb(galaxieConf.getValue("part1", 0), 0, (timeTrigo("sin")/2) * 128 + 128));
	galaxieConf.popTag();
	galaxieConf.popTag();
	galaxieConf.popTag();

	planetCore[0].setColor(alternBaW);
	planetCore[1].setColor(alternColor);
	planetCore[2].setColor(alternBaW);
	planetCore[3].setColor(alternColor);

	for (int i = 0; i < 4; i++){
		planetCore[i].draw();
	}
}

//--------------------------------------------------------------
void gPlanet::sceneWillAppear(ofxScene * fromScreen){
	step = -1;
	galaxieConf.pushTag("galaxie");
//	int testddd = getSharedData().selectionPlanet;
	galaxieConf.pushTag("planet"/*, testddd*/);
	for (int i = 0; i < 4; i++){
		soundPlay[i].loadSound("sounds/" + galaxieConf.getValue("sound", "") + "-" + ofToString(i + 1) + ".wav");
		soundPlay[i].setLoop(true);
	}
	galaxieConf.popTag();
	galaxieConf.popTag();
}

//--------------------------------------------------------------
float gPlanet::timeTrigo(string function, float multi, int piTimes){
	if (function == "cos")
		return cosf((ofGetElapsedTimef() * multi) + piTimes * HALF_PI);
	else if (function == "sin")
		return sinf((ofGetElapsedTimef() * multi) + piTimes * HALF_PI);
	else
		return 0;
}

//--------------------------------------------------------------
void gPlanet::interaction(int varianceD){
	if (WITH_ARDUINO)
		proximity = (int)((varianceD * 4));
	else
		proximity = (int)((varianceD * 4) / ofGetWidth());
	if (step != proximity){
		update(proximity);
	}
}

//--------------------------------------------------------------
void gPlanet::mouseMoved(int x, int y){
	interaction(x);
}

//--------------------------------------------------------------
void gPlanet::onNewMessage(string & byteReceived){
	int sendedByte = ofToInt(byteReceived);
	//if (...)
	interaction(sendedByte);
}

//--------------------------------------------------------------
void gPlanet::sceneDidDisappear(ofxScene * toScreen){
	for (int i = 0; i < 4; i++){
		soundPlay[i].unloadSound();
	}
}
