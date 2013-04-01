#ifndef PLANETS_H_INCLUDED
#define PLANETS_H_INCLUDED

#include "ofMain.h"
#include "transitions.h"

class planets {
private:
	int proximity;

public:
	planets();

	void init();
	void update(int step);
	void draw();
	void select(int selection, int rang);
	void interaction(int variationD);
	void drawShadow(float x, float y, int z);

	ofImage * shadow;
	particules allParticules[100];
	ofPolyline rotor;
};

#endif // PLANETS_H_INCLUDED
