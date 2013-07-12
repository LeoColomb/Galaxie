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
* gParticule
*
*/

#ifndef PARTICULE_H_INCLUDED
#define PARTICULE_H_INCLUDED

#include "ofMain.h"

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

#endif // PARTICULE_H_INCLUDED
