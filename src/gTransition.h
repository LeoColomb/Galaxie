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

#include "../../addons/ofxStateMachine/src/ofxStateMachine.h"

//========================================================================
class particules{
public:
	particules();

	void reset();
	void update(int step);
	void draw();

	float x, y;
	float randomShX;
	float randomShY;
	int coloration;
	int randomNeg;
	int timeNow;
	bool bDirection;
	bool bMouv;
};

class gTransition : public itg::ofxState<dataGalaxie>{
public:
	gTransition();

	void update();
	void draw();
	void mousePressed(int x, int y, int button);
	string getName();

	int configStep;

	ofPath planetCore[4];
	particules allParticules[100];
};

#endif // TRANSITIONS_H_INCLUDED
