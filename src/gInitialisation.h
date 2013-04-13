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
* gInitialisation - Defined repere
* Let's start in a good way.
*
*/

#ifndef INITIALISATION_H_INCLUDED
#define INITIALISATION_H_INCLUDED

#include "ofMain.h"
#include "gConstants.h"

#include "../../addons/ofxStateMachine/src/ofxStateMachine.h"

class gInitZone : public itg::ofxState<dataGalaxie>{
public:
	gInitZone();

	void update(int xM, int yM);
	void draw();
	void fixed();
	void mouseMoved(int x, int y);
	string getName();

	float x, y;
	bool isFixed;
};

#endif // INITIALISATION_H_INCLUDED
