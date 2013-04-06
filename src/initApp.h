#ifndef INITAPP_H_INCLUDED
#define INITAPP_H_INCLUDED

#include "ofMain.h"

class initAppZone {
public:

	initAppZone();

	void update(int xM, int yM);
	void draw();
	void fixed();

	float x,y;

	bool isFixed;

	ofPath planetCore1, planetCore2;
};

#endif // INITAPP_H_INCLUDED
