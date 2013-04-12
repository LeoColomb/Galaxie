#ifndef INITAPP_H_INCLUDED
#define INITAPP_H_INCLUDED

#include "ofMain.h"
#include "../../addons/ofxStateMachine/src/ofxStateMachine.h"

#include "constants.h"

class initAppZone : public itg::ofxState<dataGalaxie>{
public:

	initAppZone();

	void update(int xM, int yM);
	void draw();
	void fixed();
	string getName();

	float x,y;
	bool isFixed;
	ofPath planetCore1, planetCore2, planetCore3, planetCore4;
};

#endif // INITAPP_H_INCLUDED
