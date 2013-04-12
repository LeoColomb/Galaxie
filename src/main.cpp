/****
 * GALAXIE
 * Interactive Collection of Planets
 *
 * Leo Colombaro - 2013
 * MIT License
 ****
 *
 * main - oF function
 * Here is where Galaxie born.
 * Initial creation.
 *
 */

#include "ofMain.h"
#include "galaxieApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main(){
	ofAppGlutWindow window;
	ofSetupOpenGL(&window, 1280, 1024, OF_WINDOW); // can be OF_WINDOW or OF_FULLSCREEN
	ofRunApp( new galaxieApp());
}