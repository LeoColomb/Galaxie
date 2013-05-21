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

#include <ofxSceneManager/src/ofxScene.h>
#include <ofxXmlSettings/src/ofxXmlSettings.h>
#include <ofxXively/src/ofxXively.h>
#include <ofxTiming/src/ofxTiming.h>
#include <ofxTimer/src/ofxTimer.h>

//========================================================================
class gPlanet : public ofxScene{
public:
	gPlanet();

	friend void selectPlanet();

	void update(int newStep);
	void draw();
	void sceneWillAppear(ofxScene * fromScreen);
	void interaction(int variationD);
	void mouseMoved(int x, int y);
	void onNewMessage(string & byteReceived);
//	void sceneWillDisappear(ofxScene * toScreen);
	void sceneDidDisappear(ofxScene * fromScreen);
	float timeTrigo(string function, float multi = 1, int piTimes = 0);

	ofPolyline rotor, curvor;		// Basic & geometric form for interaction
	ofPoint equilateral[3];
	ofxXmlSettings galaxieConf;		// Load XML settings for planet conf
	ofSoundPlayer soundPlay[4];		// Loadable sound: music
	ofPath planetCore[4];			// Each planetCore represent one part/arc
	ofxXivelyInput* xivelyTransfert;
	FadeTimer globalFade;

	long userActivityStart;
	int thisPlanet;
	int valuesRang[5];
	int countChange;

private:
	int proximity; // Captor sensor interpretation
	int step;
	ofImage img;
	bool bSnapshot;		
};

#endif // PLANET_H_INCLUDED
