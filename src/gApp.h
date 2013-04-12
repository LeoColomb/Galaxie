/****
* GALAXIE
* Interactive Collection of Planets
*
* Leo Colombaro - 2013
* MIT License
*****
*
* galaxieApp - Main Creation of the Galaxie
*
*
*/

#pragma once

// Include all necessery configs and core
#include "ofMain.h"
#include "gConstants.h"

// Include usefull addons to improve Galaxie
#include "../../addons/ofxStateMachine/src/ofxStateMachine.h"
#include "../../addons/ofxSimpleSerial/src/ofxSimpleSerial.h"
#include "../../addons/ofxCosm/src/ofxCosm.h"
#include "../../addons/ofxTimer/src/ofxTimer.h"

// Load all parts of Galaxie
#include "gInitialisation.h"
#include "gTransition.h"
#include "gPlanet.h"

//========================================================================
class galaxieApp : public ofBaseApp{
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
	int planetState;

	ofxSimpleSerial arduino;
	void onNewMessage(string & byteReceived);
	string byteReceived;
	int sendedByte;

	ofxTimer userActivity;
	gInitZone myZone;
	gPlanet planet;

private:
	itg::ofxStateMachine<dataGalaxie> stateGalaxie;
};
