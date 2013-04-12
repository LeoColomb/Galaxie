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
	string getName();
	void mousePressed(int x, int y, int button);

	ofImage * shadow;
	ofPolyline rotor, curvor;
	ofxXmlSettings galaxieConf;
	ofSoundPlayer soundPlay;
	ofPath planetCore1, planetCore2, planetCore3, planetCore4;

private:
	int proximity;
};

#endif // PLANET_H_INCLUDED
