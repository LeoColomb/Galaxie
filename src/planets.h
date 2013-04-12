#ifndef PLANETS_H_INCLUDED
#define PLANETS_H_INCLUDED

#include "ofMain.h"
#include "../../addons/ofxXmlSettings/src/ofxXmlSettings.h"
#include "../../addons/ofxStateMachine/src/ofxStateMachine.h"

#include "constants.h"


class planets : public itg::ofxState<dataGalaxie>{
private:
	int proximity;

public:
	planets();

	void init();
	void update(int step);
	void draw();
	void select(int selection, int rang);
	void interaction(int variationD);
	void drawShadow(float x, float y, int z);
	string getName();
	void mousePressed(int x, int y, int button);

	ofImage * shadow;
	ofPolyline rotor;
	ofPolyline curvor;

	ofxXmlSettings galaxieConf;
	ofSoundPlayer soundPlay;
};

#endif // PLANETS_H_INCLUDED
