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

#include "../../addons/ofxSceneManager/src/ofxScene.h"
#include "../../addons/ofxXmlSettings/src/ofxXmlSettings.h"

//========================================================================
class gPlanet : public ofxScene{
public:
	gPlanet();

	void update(int newStep);
	void draw();
	void sceneWillAppear(ofxScene * fromScreen);
	void interaction(int variationD);
	void mouseMoved(int x, int y);
	void mousePressed(int x, int y, int button);
	void sceneDidDisappear(ofxScene * toScreen);
	float timeTrigo(string function, float multi = 1);

	ofPolyline rotor, curvor;		// Basic & geometric form for interaction
	ofxXmlSettings galaxieConf;		// Load XML settings for planet conf
	ofSoundPlayer soundPlay[4];		// Loadable sound: music
	ofPath planetCore[4];			// Each planetCore represent one part/arc

private:
	int proximity; // Captor sensor interpretation
	int step;
};

#endif // PLANET_H_INCLUDED
