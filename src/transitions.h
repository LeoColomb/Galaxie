#ifndef TRANSITIONS_H_INCLUDED
#define TRANSITIONS_H_INCLUDED

#include "ofMain.h"

class particules {

    public:

        particules();

        void update();
        void draw();
        float x,y;

};

class galaxieTransitions {

    public:

        galaxieTransitions();

        void update(int step);
        void draw();

        vector<particules> allParticules;

};

#endif // TRANSITIONS_H_INCLUDED
