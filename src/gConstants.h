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
* gConstants - Configuration data
*
*
*/

#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

// Arduino Configuration
#define WITH_ARDUINO	true
#define SERIAL_PORT     "COM3"

// Xively Parameters
#define WITH_XIVELY		false
#define XIVELY_API_KEY	"ASdIxEjsiUFxwfNVxByvJo7oQhySAKw3WE01K2VGcDBiQT0g"
#define XIVELY_FEED 	126791

enum gStates{ 
	INIT = 1,
	INTERACTION,
	PLANET
};

#endif // CONSTANTS_H_INCLUDED
