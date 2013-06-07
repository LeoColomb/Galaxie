//
// GALAXIE
// Interactive Collection of Planets
//
// Leo Colombaro - 2013
// MIT License
//

#include "gApp.h"

//--------------------------------------------------------------
void galaxieApp::setup(){
	ofSetFrameRate(75);
	ofEnableAlphaBlending();
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	glLineWidth(3);
	ofBackground(ofColor::black);
	ofSetCircleResolution(100);
	ofFill();

	gInitialized = bSetup = false;

	stateGalaxie = ofxSceneManager::instance();
	stateGalaxie->addScene(new gInitZone(), INIT);
	stateGalaxie->addScene(new gTransition(), INTERACTION);
	stateGalaxie->addScene(new gPlanet(), PLANET);

	stateGalaxie->setCurtainDropTime(1.0);
	stateGalaxie->setCurtainStayTime(0.0);
	stateGalaxie->setCurtainRiseTime(1.0);

	planetState = 0;
	countChange = -1;
}

//--------------------------------------------------------------
void galaxieApp::setupI(){
	gInitialized = true;
	if (WITH_ARDUINO){
		arduino.enumerateDevices();
		int i = 0;
		while (!arduino.setup(SERIAL_PORT, 9600)){
			i++;
			if (i == 5){
				printf("Are you sure you have an Arduino connected?");
				break;
			}
			ofSleepMillis(400);
		}
		arduino.startContinuousRead();
		ofAddListener(arduino.NEW_MESSAGE, this, &galaxieApp::onNewMessage);
	}
}

//--------------------------------------------------------------
void galaxieApp::update(){
	if (stateGalaxie->getCurrentSceneID() == 3 && !bSetup) {
		stateGalaxie->shareData((int)(selection[0] + selection[1] + selection[2]));
		bSetup = true;
	}
	stateGalaxie->update(0.016666666);
	if (WITH_ARDUINO && arduino.isInitialized()){
		arduino.writeByte(planetState);
	}
}

//--------------------------------------------------------------
void galaxieApp::draw(){
	if (gInitialized)
		ofTranslate(CENTER_X, CENTER_Y);
	//ofBackgroundGradient(ofColor::dimGrey, ofColor::black, OF_GRADIENT_CIRCULAR);
	stateGalaxie->draw();
}

//--------------------------------------------------------------
void galaxieApp::onNewMessage(string & byteReceived){
		sendedByte = ofToInt(byteReceived);
		cout << "[Arduino] " << sendedByte << "\n";
		if (sendedByte == 0)
			sendedByte = SENSOR_MAX + 100;
	if (stateGalaxie->getCurrentSceneID() == 3) {
		if (sendedByte < SENSOR_MAX) {
			countChange = 0;
		} else {
			if (countChange >= 0)
				countChange++;
			if (countChange > 20) {
				stateGalaxie->goToScene(INTERACTION);
				countChange = -1;
			}
		}
	}
	stateGalaxie->onNewMessage(byteReceived);
}

//--------------------------------------------------------------
void galaxieApp::keyPressed(int key){
	switch(key) {
	case 'f':
		if (stateGalaxie->getCurrentSceneID() != 2) {
			ofToggleFullscreen();
		}
		break;
	case ' ':
		if (stateGalaxie->getCurrentSceneID() == 3) {
			stateGalaxie->goToScene(INTERACTION);
			planetState = 0;
		}
		break;
	default:
		stateGalaxie->keyPressed(key);
		if (stateGalaxie->getCurrentSceneID() != 3) {
			selection[planetState] = (key - 70) / 3;
			planetState++;
			if (planetState >= 3) {
				bSetup = false;
				stateGalaxie->goToScene(PLANET);
			}
		}
		break;
	}
}

//--------------------------------------------------------------
void galaxieApp::keyReleased(int key){
}

//--------------------------------------------------------------
void galaxieApp::mouseMoved(int x, int y){
	if (!(WITH_ARDUINO && gInitialized))
		stateGalaxie->mouseMoved(x, y);
}

//--------------------------------------------------------------
void galaxieApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void galaxieApp::mousePressed(int x, int y, int button){
	stateGalaxie->mousePressed(x, y, button);
	switch (stateGalaxie->getCurrentSceneID()){
	case 1:
		CENTER_X = x;
		CENTER_Y = y;
		galaxieApp::setupI();
		stateGalaxie->goToScene(INTERACTION);
		break;
	case 2:
		selection[planetState] = (ofGetWidth() / x) * 3;
		planetState++;
		if (planetState >= 3){
			bSetup = false;
			stateGalaxie->goToScene(PLANET);
		}
		break;
	case 3:
		planetState = 0;
		stateGalaxie->goToScene(INTERACTION);
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void galaxieApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void galaxieApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void galaxieApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void galaxieApp::dragEvent(ofDragInfo dragInfo){
}
