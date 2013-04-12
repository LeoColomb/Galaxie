#pragma once

#include "ofMain.h"
#include "constants.h"

#include "../../addons/ofxStateMachine/src/ofxStateMachine.h"
#include "../../addons/ofxSimpleSerial/src/ofxSimpleSerial.h"
#include "../../addons/ofxTimer/src/ofxTimer.h"
#include "../../addons/ofxCosm/src/ofxCosm.h"

#include "initApp.h"
#include "transitions.h"
#include "planets.h"

class testApp : public ofBaseApp{
public:
	void setup();
	void setupI();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	float CENTER_X;
	float CENTER_Y;

	int galaxieState;

	initAppZone myZone;
	planets planet;

	ofxSimpleSerial arduino;
	void onNewMessage(string & byteReceived);

	string byteReceived;
	int sendedByte;

	ofxTimer userActivity;

private:
	itg::ofxStateMachine<dataGalaxie> stateGalaxie;
};
