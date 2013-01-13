#include "initApp.h"

initAppZone::initAppZone() {
        isFixed = false;
        x = (ofGetWidth() / 2);
        y = (ofGetHeight() / 2);
}

void initAppZone::update(int xM, int yM) {
        x = xM;
        y = yM;
}

void initAppZone::draw() {
        ofSetColor(255,0,0);
        ofFill();
        ofEllipse(x,y,200,200);
}

void initAppZone::fixed(int xM, int yM) {
        ofSetColor(0);
        isFixed = true;
}
