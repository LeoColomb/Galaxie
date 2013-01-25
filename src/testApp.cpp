#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    ofSetVerticalSync(true);
    ofEnableSmoothing();
    ofFill();
    ofBackground(ofColor::black);
    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void testApp::setupI(){
    galaxieState = 1;

    //--
    arduino.enumerateDevices();
    arduino.setup(SERIAL_PORT, 31250);
    ofSleepMillis(2000);
    arduino.startContinuesRead();
    ofAddListener(arduino.NEW_MESSAGE, this, &testApp::onNewMessage);

    //--
    userActivity.setAlarm(20000);
}

//--------------------------------------------------------------
void testApp::update(){
    showTransition.update(galaxieState);
    //if (userActivity.alarm() == true){
    arduino.writeByte(galaxieState);
    //userActivity.resetAlarm();
    //}
}

//--------------------------------------------------------------
void testApp::draw(){
    //--

    //--
    showTransition.draw();

    //--
    myZone.draw();

    //--
}

//--------------------------------------------------------------
void testApp::onNewMessage(string &byteReceived)
{
    sendedByte = ofToInt(byteReceived);
    cout << sendedByte << "\n";
        if (galaxieState == 1 || galaxieState == 2 || galaxieState == 3) {
            planet.select(sendedByte, galaxieState);
        } else if (galaxieState == 4) {
            planet.interaction(sendedByte);
        }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    if (!myZone.isFixed) {
        myZone.update(x, y);
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    if(!myZone.isFixed)  {
        testApp::setupI();
        myZone.fixed(x, y);
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
