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
#define SERIAL_PORT     "COM5"

// Cosm Parameters
#define WITH_COSM	false
#define COSM_API_KEY	"XXXX-YYYY"
#define COSM_FEED	"ZZZZ"

// Data shared between states
class dataGalaxie{
public:
	int planetState;
	int lastUpdate;
};

#endif // CONSTANTS_H_INCLUDED
