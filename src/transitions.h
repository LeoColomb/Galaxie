#ifndef TRANSITIONS_H_INCLUDED
#define TRANSITIONS_H_INCLUDED

#include "ofMain.h"

class particules {
public:

	particules();

	void init();
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

#endif // TRANSITIONS_H_INCLUDED
