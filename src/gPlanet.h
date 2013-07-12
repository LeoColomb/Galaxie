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
* gPlanet - Show a selected planet
* After selection, choose a planet and load respective config
* and draw it on the screen.
*
*/

#ifndef PLANET_H_INCLUDED
#define PLANET_H_INCLUDED

#include "ofMain.h"
#include "gConstants.h"
#include "gParticule.h"

#include <ofxSceneManager/src/ofxScene.h>
#include <ofxXmlSettings/src/ofxXmlSettings.h>
#include <ofxXively/src/ofxXively.h>
#include <ofxTiming/src/ofxTiming.h>
#include <ofxTimer/src/ofxTimer.h>

//========================================================================
class snapshot : public ofThread{
public:
	void threadedFunction() {
		lock();
		unlock();
		fileName = "Snapshot_" + ofToString(ofGetHours()) + "_" + ofToString(ofGetMinutes()) + ".png";
		screen.saveImage(fileName);
		ofLogNotice() << "Snapshot: " << fileName << endl;
	}
	void start(){
		startThread(true, false); // blocking, verbose
	}
	void stop(){
		stopThread();
	}

	ofImage screen;
	string fileName;
};

//========================================================================
class gPlanet : public ofxScene{
public:
	gPlanet();

	void update(int newStep);
	void draw();
	void sceneWillAppear(ofxScene * fromScreen);
	void interaction(int variationD);
	void mouseMoved(int x, int y);
	void onNewMessage(string & byteReceived);
	void sceneDidDisappear(ofxScene * fromScreen);
	float timeTrigo(string function, float multi = 1, int piTimes = 0);
	void shareData(int data);

	ofPolyline rotor, curvor, rayon;// Basic & geometric form for interaction
	ofPoint equilateral[3];
	ofxXmlSettings galaxieConf;		// Load XML settings for planet conf
	ofSoundPlayer soundPlay[4];		// Loadable sound: music
	ofPath planetCore[4];			// Each planetCore represent one part/arc
	vector<particules> allParticules;
	ofxXivelyInput* xivelyTransfert;
	FadeTimer globalFade;
	snapshot makeScreenshot;

	long userActivityStart;
	int valuesRang[5];
	int countChange;

private:
	int proximity; // Captor sensor interpretation
	int step;
	bool bSnapshot;
};

#endif // PLANET_H_INCLUDED
