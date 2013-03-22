#include "planets.h"

//--------------------------------------------------------------
planets::planets() {
}

//--------------------------------------------------------------
void planets::update(int step) {
}

//--------------------------------------------------------------
void planets::draw() {
}

//--------------------------------------------------------------
void planets::select(int selection, int rang) {
}

//--------------------------------------------------------------
void planets::interaction(int varianceD) {
	proximity = (int)(varianceD / 5);
}

//--------------------------------------------------------------
void planets::drawShadow(float x, float y, int z)
{
	ofSetColor(255, 255, 255, 200);
	ofCircle(x, y, 50);
	float xV = x + z / 2.;
	float yV = y + z / 2.;

	ofPushMatrix();
	ofTranslate(x + 0, y + 0, 0);
	ofScale(1, 3, 1);
	shadow->draw(-z / 2., - z / 2., z, z);
	ofPopMatrix();
}