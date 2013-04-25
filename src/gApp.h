/****
*   ___   __   __     __   _  _ ____ ____
*  / __) /__\ (  )   /__\ ( \/ (_  _( ___)
* ( (_-./(__)\ )(__ /(__)\ )  ( _)(_ )__)
*  \___(__)(__(____(__)(__(_/\_(____(____)
* -- Interactive Collection of Planets --
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
#include <ofxAnimatable/src/ofxAnimatableFloat.h>
#include <ofxSceneManager/src/ofxSceneManager.h>
#include <ofxSimpleSerial/src/ofxSimpleSerial.h>
#include <ofxTimer/src/ofxTimer.h>
#include <ofxCosm/src/ofxCosm.h>

// Load all parts of Galaxie
#include "gInitialisation.h"
#include "gPlanet.h"
#include "gTransition.h"

//========================================================================
class galaxieApp : public ofBaseApp{
public:
	void setup();
	void setupI();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	float CENTER_X, CENTER_Y;
	int planetState;
	bool gInitialized;

	ofxSceneManager * stateGalaxie;

	ofxSimpleSerial arduino;
	void onNewMessage(string & byteReceived);
	string byteReceived;
	int sendedByte;

	ofxTimer userActivity;
};
