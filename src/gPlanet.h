/****
* GALAXIE
* Interactive Collection of Planets
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

#include "../../addons/ofxStateMachine/src/ofxStateMachine.h"
#include "../../addons/ofxXmlSettings/src/ofxXmlSettings.h"

//========================================================================
class gPlanet : public itg::ofxState<dataGalaxie>{
public:
	gPlanet();

	void update(int step);
	void draw();
	void select(int selection, int rang);
	void interaction(int variationD);
	void drawShadow(float x, float y, int z);
	void mousePressed(int x, int y, int button);
	string getName();

	ofImage * shadow;				// Special Planet shadow
	ofPolyline rotor, curvor;		// Basic & geometric form for interaction
	ofxXmlSettings galaxieConf;		// Load XML settings for planet conf
	ofSoundPlayer soundPlay;		// Loadable sound: music
	ofPath planetCore1, planetCore2, planetCore3, planetCore4; // Each planetCore represent one part/arc

private:
	int proximity; // Captor sensor interpretation
};

#endif // PLANET_H_INCLUDED
