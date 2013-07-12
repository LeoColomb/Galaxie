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
		curvor.curveTo(300*cos(angle), 300*sin(angle));
		curvor.curveTo(250*cos(angle+(TWO_PI / 28)), 250*sin(angle+(TWO_PI / 28)));
		angle += TWO_PI / 14;
	}
	angle = 0;
	while (angle <= TWO_PI+(TWO_PI / 12) ) {
		rayon.curveTo(300*cos(angle), 300*sin(angle));
		rayon.curveTo(150*cos(angle+(TWO_PI / 28))*10, 150*sin(angle+(TWO_PI / 28))*10);
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

	int value = SENSOR_MAX;
	for (int i = 0; i < 5; i++) {
		valuesRang[i] = value;
		value -= SENSOR_MAX / 4;
	}

	for (int i = 0; i < 5; i++){
		allParticules.push_back(particules());
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

	if (newStep == 2 && step == 3 && !bSnapshot){
		makeScreenshot.start();
		makeScreenshot.lock();
		makeScreenshot.screen.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		makeScreenshot.unlock();
		bSnapshot = true;
		makeScreenshot.stop();
	}

	soundPlay[newStep].play();
	soundPlay[newStep].setPosition(playTime);
	step = newStep;
}

//--------------------------------------------------------------
void gPlanet::draw(){
	ofNoFill();
	galaxieConf.pushTag("structure");
	for (int i = 0; i < galaxieConf.getNumTags("element"); i++) {
		galaxieConf.pushTag("element", i);
		if (galaxieConf.getValue("step", 0) <= step) {
			ofSetHexColor(ofHexToInt(galaxieConf.getValue("color", "")));
			ofPushMatrix();
			ofTranslate(0, 0, sinf(ofGetElapsedTimef()));
			ofRotate(ofGetElapsedTimef() * galaxieConf.getValue("rotation", 0));
			switch (galaxieConf.getValue("type", 0)) {
			case 0: // Triangle
				for (int j = 0; j < 4; j++){
					for(int k = 0; k < 3; k++){
						equilateral[k].x += 20 * timeTrigo("cos", 2, j);
						equilateral[k].y += 20 * timeTrigo("sin", 2, j);
					}
					ofTriangle(equilateral[0], equilateral[1], equilateral[2]);
				}
				break;
			case 1: // Rotor
				rotor.draw();
				break;
			case 2: // Curvor
				curvor.draw();
				break;
			case 3: // Rayon
				rayon.draw();
				break;
			case 4: // Particules
				for(int i = 0; i < allParticules.size(); i++){
					allParticules[i].draw();
				}
				break;
			default:
				break;
			}
			ofPopMatrix();
		}
		galaxieConf.popTag();
	}
	galaxieConf.popTag();

	ofFill();

	galaxieConf.pushTag("colors");
	ofSetHexColor(ofHexToInt(galaxieConf.getValue("fondamentale", "")));

	ofCircle(0,0,100);

	ofColor alternColor(ofColor::fromHsb((timeTrigo("sin")/8) * 128 + 128, 255, 255));
	ofColor alternBaW(ofColor::fromHsb(galaxieConf.getValue("part", 0), 78, (timeTrigo("sin")/2) * 110 + 100));
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
}

//--------------------------------------------------------------
float gPlanet::timeTrigo(string function, float multi, int piTimes){
	if (function == "cos")
		if (multi >= 0)
			return cosf((ofGetElapsedTimef() * multi) + piTimes * HALF_PI);
		else
			return cosf((ofGetElapsedTimef() / -multi) + piTimes * HALF_PI);
	else if (function == "sin")
		if (multi >= 0)
			return sinf((ofGetElapsedTimef() * multi) + piTimes * HALF_PI);
		else
			return sinf((ofGetElapsedTimef() / -multi) + piTimes * HALF_PI);
	else
		return 0;
}

//--------------------------------------------------------------
void gPlanet::interaction(int varianceD){
	if (step != varianceD){
		update(varianceD);
	}
	countChange = 0;
}

//--------------------------------------------------------------
void gPlanet::mouseMoved(int x, int y){
	interaction((int)((x * 4) / ofGetWidth()));
}

//--------------------------------------------------------------
void gPlanet::onNewMessage(string & byteReceived){
	int sendedByte = ofToInt(byteReceived);
			if (sendedByte == 0)
			sendedByte = SENSOR_MAX + 100;

	if (ofInRange(sendedByte, valuesRang[step + 1], valuesRang[step])) {
		countChange = 0;
		return;
	} else if (sendedByte < valuesRang[step + 1]) {
		if (countChange < 0)
			countChange = 0;
		countChange++;
		if (countChange >= 5)
			interaction(step + 1);
	}
	else if (sendedByte > valuesRang[step]) {
		if (countChange > 0)
			countChange = 0;
		countChange--;
		if (countChange <= -5) {
			if (step > 0)
				interaction(step - 1);
		}
	}
}

//--------------------------------------------------------------
void gPlanet::sceneDidDisappear(ofxScene * toScreen){
	for (int i = 0; i < 4; i++){
		soundPlay[i].unloadSound();
	}
	xivelyTransfert->setValue(1, ofGetElapsedTimeMillis() - userActivityStart);
	xivelyTransfert->input();
	galaxieConf.popTag();
	galaxieConf.popTag();
	for (int i = 0; i < allParticules.size(); i++){
		allParticules.pop_back();
	}
}

//--------------------------------------------------------------
void gPlanet::shareData(int data){
	galaxieConf.pushTag("galaxie");
	galaxieConf.pushTag("planet", ofRandom(galaxieConf.getNumTags("planet")));
	for (int i = 0; i < 4; i++){
		soundPlay[i].loadSound("sounds/" + galaxieConf.getValue("sound", "") + "-" + ofToString(i + 1) + ".wav");
		soundPlay[i].setLoop(true);
	}
}
