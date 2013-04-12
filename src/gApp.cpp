/****
* GALAXIE
* Interactive Collection of Planets
*
* Leo Colombaro - 2013
* MIT License
*****/

#include "gApp.h"

//--------------------------------------------------------------
void galaxieApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(ofColor::black);
	ofFill();
	ofEnableAlphaBlending();
	ofSetCircleResolution(100);

	stateGalaxie.addState<gInitZone>();
	stateGalaxie.addState<gTransition>();
	stateGalaxie.addState<gPlanet>();
	stateGalaxie.changeState("init");
}

//--------------------------------------------------------------
void galaxieApp::setupI(){
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
		arduino.startContinuesRead();
		ofAddListener(arduino.NEW_MESSAGE, this, &galaxieApp::onNewMessage);
	}
	userActivity.setup(20000, false);
}

//--------------------------------------------------------------
void galaxieApp::update(){
	//if (userActivity.alarm() == true){
	if (WITH_ARDUINO){
		arduino.writeByte(planetState);
	}
	//userActivity.resetAlarm();
	//}
}

//--------------------------------------------------------------
void galaxieApp::draw(){
	if (!myZone.isFixed){
		return;
	}
	ofTranslate(CENTER_X, CENTER_Y);
}

//--------------------------------------------------------------
void galaxieApp::onNewMessage(string &byteReceived)
{
	sendedByte = ofToInt(byteReceived);
	cout << sendedByte << "\n";
	//if (planetState == 1 || planetState == 2 || planetState == 3){
	//	planet.select(sendedByte, galaxieState);
	//} else if (planetState == 4){
	//	planet.interaction(sendedByte);
	//}
}

//--------------------------------------------------------------
void galaxieApp::keyPressed(int key){
}

//--------------------------------------------------------------
void galaxieApp::keyReleased(int key){
}

//--------------------------------------------------------------
void galaxieApp::mouseMoved(int x, int y ){
}

//--------------------------------------------------------------
void galaxieApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void galaxieApp::mousePressed(int x, int y, int button){
	if(!myZone.isFixed){
		galaxieApp::setupI();
		myZone.fixed();
		CENTER_X = x;
		CENTER_Y = y;
		stateGalaxie.changeState("transition");
	}
	if (!WITH_ARDUINO){
		planet.update(planetState);
		//	if (galaxieState <= 4)
		//		galaxieState++;
		//	else
		//		galaxieState = 1;
		//	planet.interaction(x);
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