#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofEnableSmoothing();
	ofBackground(ofColor::black);
	ofFill();
	ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::setupI(){
	planet.init();
	galaxieState = 1;

	if (WITH_ARDUINO){
		arduino.enumerateDevices();
		int i = 0;
		while (!arduino.setup(SERIAL_PORT, 31250)){
			i++;
			if (i == 5){
				cout << "Are you sure you have Arduino connected?\n";
				break;
			}
			ofSleepMillis(400);
		}
		arduino.startContinuesRead();
		ofAddListener(arduino.NEW_MESSAGE, this, &testApp::onNewMessage);
	} else {
	}

	//--
	userActivity.setup(20000, false);
}

//--------------------------------------------------------------
void testApp::update(){
	//if (userActivity.alarm() == true){
	if (WITH_ARDUINO){
		arduino.writeByte(galaxieState);
	}
	//userActivity.resetAlarm();
	//}
}

//--------------------------------------------------------------
void testApp::draw(){
	//--
	if (!myZone.isFixed)
	{
		myZone.draw();
		return;
	}
	//--
	ofTranslate(CENTER_X, CENTER_Y);
	planet.draw();
	//--
	myZone.draw();
}

//--------------------------------------------------------------
void testApp::onNewMessage(string &byteReceived)
{
	sendedByte = ofToInt(byteReceived);
	cout << sendedByte << "\n";
	if (galaxieState == 1 || galaxieState == 2 || galaxieState == 3){
		planet.select(sendedByte, galaxieState);
	} else if (galaxieState == 4){
		planet.interaction(sendedByte);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	if (!myZone.isFixed){
		myZone.update(x, y);
	}
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	if(!myZone.isFixed){
		testApp::setupI();
		myZone.fixed();
		CENTER_X = x;
		CENTER_Y = y;
	}
	if (!WITH_ARDUINO){
		planet.update(galaxieState);
		if (galaxieState <= 4)
			galaxieState++;
		else
			galaxieState = 1;
		planet.interaction(x);
	}
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
}