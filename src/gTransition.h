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
* gTransition -
*
*
*/

#ifndef TRANSITIONS_H_INCLUDED
#define TRANSITIONS_H_INCLUDED

#include "ofMain.h"
#include "gConstants.h"
#include "gParticule.h"

#include <ofxSceneManager/src/ofxScene.h>

//========================================================================
class gTransition : public ofxScene{
public:
	gTransition();

	void update();
	void draw();
	void sceneWillAppear(ofxScene * fromScreen);
	void sceneDidDisappear(ofxScene * fromScreen);

	int configStep;

	ofPath planetCore[4];
	vector<particules> allParticules;
};

#endif // TRANSITIONS_H_INCLUDED
