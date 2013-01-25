#ifndef PLANETS_H_INCLUDED
#define PLANETS_H_INCLUDED

#include "ofMain.h"

class planets {

    private:
        int proximity;

    public:
        planets();

        void update(int step);
        void draw();
        void select(int selection, int rang);
        void interaction(int variationD);
        void drawShadow(float x, float y, int z);

        ofImage * shadow;

};

#endif // PLANETS_H_INCLUDED
