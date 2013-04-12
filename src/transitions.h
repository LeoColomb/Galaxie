#ifndef TRANSITIONS_H_INCLUDED
#define TRANSITIONS_H_INCLUDED

#include "ofMain.h"
#include "../../addons/ofxStateMachine/src/ofxStateMachine.h"

#include "constants.h"


class particules : public itg::ofxState<dataGalaxie>{
public:

	particules();

	void init();
	void reset();
	void update(int step);
	void draw();
	void mousePressed(int x, int y, int button);
	string getName();
	float x,y;

	int colored;
	int randomNeg;
	float randomShX;
	float randomShY;
	int timeNow;
	bool bDirection;
	bool bMouv;
};

#endif // TRANSITIONS_H_INCLUDED
