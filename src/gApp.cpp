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

	gInitialized = false;

	stateGalaxie = ofxSceneManager::instance();
	stateGalaxie->addScene(new gInitZone(), INIT);
	stateGalaxie->addScene(new gTransition(), INTERACTION);
	stateGalaxie->addScene(new gPlanet(), PLANET);

	stateGalaxie->setCurtainDropTime(1.0);
	stateGalaxie->setCurtainStayTime(0.0);
	stateGalaxie->setCurtainRiseTime(1.0);

	configControls = 0;
}

//--------------------------------------------------------------
void galaxieApp::setupI(){
	gInitialized = true;
	if (WITH_ARDUINO){
		arduino.enumerateDevices();
		int i = 0;
		while (!arduino.setup(SERIAL_PORT, 31250)){
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
	stateGalaxie->update(0.016666666);
	//if (userActivity.alarm() == true){
	if (WITH_ARDUINO){
		arduino.writeByte(planetState);
	}
	//userActivity.resetAlarm();
	//}
}

//--------------------------------------------------------------
void galaxieApp::draw(){
	if (gInitialized)
		ofTranslate(CENTER_X, CENTER_Y);
	stateGalaxie->draw();
}

//--------------------------------------------------------------
void galaxieApp::onNewMessage(string & byteReceived){
	if (stateGalaxie->getCurrentSceneID() == 2) {
		stateGalaxie->onNewMessage(byteReceived);
		sendedByte = ofToInt(byteReceived);
		cout << sendedByte << "\n";
	}
}

//--------------------------------------------------------------
void galaxieApp::keyPressed(int key){
	if (key == ' ') {
		if (stateGalaxie->getCurrentSceneID() == 3) {
			stateGalaxie->goToScene(INTERACTION);
		}
	} else {
		stateGalaxie->keyPressed(key);
		configControls++;
		if (configControls >= 3) {
			stateGalaxie->goToScene(PLANET);
			configControls = 0;
		}
	}
}

//--------------------------------------------------------------
void galaxieApp::keyReleased(int key){
}

//--------------------------------------------------------------
void galaxieApp::mouseMoved(int x, int y){
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
		configControls++;
		if (configControls >= 3) {
			stateGalaxie->goToScene(PLANET);
			configControls = 0;
		}
		break;
	case 3:
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
