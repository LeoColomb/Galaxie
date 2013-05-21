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
	xivelyTransfert->setVerbose(false);
	xivelyTransfert->setMinInterval(5);
	xivelyTransfert->input(OFX_XIVELY_EEML, true);    /// forcing update = ignoring min interval

	float angle = HALF_PI; // Angle from 0 to 360
	for(int i = 0; i < 3; i++){
		equilateral[i].x = (400) * cos(angle);
		equilateral[i].y = (400) * sin(angle);
		angle += TWO_PI/3;
	}

	// Init all forms available
	angle = 0; // Angle from 0 to 360
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

	int value=300;
	for (int i = 0; i < 5; i++) {
		valuesRang[i] = value;
		value -= 300 / 4;
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

	if (newStep == 3 && !bSnapshot){
		img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		string fileName = "snapshot_" + ofToString(ofRandom(1000)) + ".png";
		img.saveImage(fileName);
		ofLogNotice() << "Snapshot: " << fileName << endl;
		bSnapshot = true;
	}

	soundPlay[newStep].play();
	soundPlay[newStep].setPosition(playTime);
	step = newStep;
}

//--------------------------------------------------------------
void gPlanet::draw(){
	ofNoFill();
	galaxieConf.pushTag("galaxie");
	galaxieConf.pushTag("planet", thisPlanet);
	galaxieConf.pushTag("structure");
	if (galaxieConf.tagExists("triangle") && (galaxieConf.getAttribute("triangle", "step", 0) <= step)){
		galaxieConf.pushTag("triangle");
		ofPushMatrix();
		ofSetHexColor(galaxieConf.getValue("color", 0));
		for (int j = 0; j < 4; j++){
			for(int k = 0; k < 3; k++){
				equilateral[k].x += 20 * timeTrigo("cos", 2, j);
				equilateral[k].y += 20 * timeTrigo("sin", 2, j);
			}
			ofTriangle(equilateral[0], equilateral[1], equilateral[2]);
		}
		ofPopMatrix();
		galaxieConf.popTag();
	}
	if (galaxieConf.tagExists("rotor") && galaxieConf.getAttribute("rotor", "step", 0) <= step){
		ofPushMatrix();
		ofSetColor(galaxieConf.getValue("rotor:r", 0),galaxieConf.getValue("rotor:g", 0),galaxieConf.getValue("rotor:b", 0));
		ofRotate(ofGetElapsedTimef()*90);
		rotor.draw();
		ofPopMatrix();
	}
	if (galaxieConf.tagExists("curvor") && galaxieConf.getAttribute("curvor", "step", 0) <= step){
		if (galaxieConf.getAttribute("curvor", "step", 0) - 1 == step){
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
	userActivityStart = ofGetElapsedTimeMillis();
	bSnapshot = false;
	step = -1;
	countChange = 0;
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
	if (step != varianceD){
		update(varianceD);
	}
}

//--------------------------------------------------------------
void gPlanet::mouseMoved(int x, int y){
	interaction((int)((x * 4) / ofGetWidth()));
}

//--------------------------------------------------------------
void gPlanet::onNewMessage(string & byteReceived){
	int sendedByte = ofToInt(byteReceived);
	if (ofInRange(sendedByte, valuesRang[step + 1], valuesRang[step]))
		return;
	else if (sendedByte < valuesRang[step + 1]) {
		if (countChange > 0)
			countChange = 0;
		countChange--;
		if (countChange <= -3) {
			interaction(step + 1);
		} else {
			return;
		}
	}
	else if (sendedByte > valuesRang[step]) {
		if (countChange < 0)
			countChange = 0;
		countChange++;
		if (countChange >= 3) {
			interaction(step - 1);
		} else {
			return;
		}
		countChange = 0;
	}
}

//--------------------------------------------------------------
void gPlanet::sceneDidDisappear(ofxScene * toScreen){
	for (int i = 0; i < 4; i++){
		soundPlay[i].unloadSound();
	}
	xivelyTransfert->setValue(1, ofGetElapsedTimeMillis() - userActivityStart);
	xivelyTransfert->input();
}
