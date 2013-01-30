#pragma once

#include "ofMain.h"
#include "constants.h"

#include "ofxSimpleSerial.h"
#include "ofxTimer.h"
#include "ofxCosm.h"

#include "initApp.h"
#include "transitions.h"
#include "planets.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void setupI();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        int CENTER_X;
        int CENTER_Y;

        int galaxieState;

		initAppZone myZone;
		galaxieTransitions showTransition;
		planets planet;

        ofxSimpleSerial arduino;
   		void onNewMessage(string & byteReceived);

		string byteReceived;
		int sendedByte;

		ofxTimer userActivity;

};
