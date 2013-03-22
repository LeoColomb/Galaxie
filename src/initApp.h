#ifndef INITAPP_H_INCLUDED
#define INITAPP_H_INCLUDED

#include "ofMain.h"
#include "constants.h"

class initAppZone {
public:

	initAppZone();

	void update(int xM, int yM);
	void draw();
	void fixed(int xM, int yM);

	float x,y;

	bool isFixed;
};

#endif // INITAPP_H_INCLUDED
