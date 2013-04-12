/****
* GALAXIE
* Interactive Collection of Planets
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

	float x,y;
	int colored;
	int randomNeg;
	float randomShX;
	float randomShY;
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

	ofPath planetCore1, planetCore2, planetCore3, planetCore4;
	particules allParticules[100];
};

#endif // TRANSITIONS_H_INCLUDED
