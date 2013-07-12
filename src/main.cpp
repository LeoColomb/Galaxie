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
* main - oF function
* Here is where Galaxie born.
* Initial creation.
*
*/

#include "ofMain.h"
#include "gApp.h"

//========================================================================
int main(){
	ofSetupOpenGL(1580, 1000, OF_FULLSCREEN); // can be OF_WINDOW or OF_FULLSCREEN
	ofRunApp(new galaxieApp());
}
