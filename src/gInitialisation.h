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
	string getName();

	float x,y;
	bool isFixed;
};

#endif // INITIALISATION_H_INCLUDED
