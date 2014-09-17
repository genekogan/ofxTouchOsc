#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // set screen resolution
    touchOsc.setScale(320, 480);
    
    ofxTouchOscPage *newPage = touchOsc.addPage("myPage");
    
    // set the color for each widget blue
    newPage->setDefaultWidgetColor(BLUE);

    ofxTouchOscFader *fader = newPage->addFader("myFader", 0.01, 0.05, 0.9, 0.1);
    fader->setCentered(false);
    fader->setInverted(false);
    fader->setResponse(false);
    
    // set individual widget colors
    fader->setColor(YELLOW);

    ofxTouchOscRotary *rotary = newPage->addRotary("myRotary", 0.01, 0.18, 0.15, 0.1);
    rotary->setCentered(false);
    rotary->setInverted(false);
    rotary->setResponse(false);
    rotary->setNoRollover(true);
    
    ofxTouchOscLed *led = newPage->addLed("myLed", 0.2, 0.18, 0.15, 0.1);

    ofxTouchOscButton *button = newPage->addButton("myButton", 0.4, 0.18, 0.15, 0.1);
    button->setLocalOff(false);
    button->setVelocity(false);
    
    ofxTouchOscToggle *toggle = newPage->addToggle("myToggle", 0.6, 0.18, 0.15, 0.1);
    toggle->setLocalOff(false);
    
    ofxTouchOscMultiFader *multifader = newPage->addMultiFader("myMultiFader", 0.01, 0.3, 0.3, 0.2);
    multifader->setCentered(false);
    multifader->setInverted(false);
    multifader->setNumber(5);
    
    ofxTouchOscMultiXy *multixy = newPage->addMultiXy("myMultiXy", 0.5, 0.3, 0.3, 0.2);
    multixy->setInvertedX(false);
    multixy->setInvertedY(false);
    
    ofxTouchOscMultiPush *multipush = newPage->addMultiPush("myMultiPush", 0.01, 0.63, 0.3, 0.2);
    multipush->setLocalOff(false);
    multipush->setNumberX(5);
    multipush->setNumberY(4);
    
    ofxTouchOscMultiToggle *multitoggle = newPage->addMultiToggle("myMultiToggle", 0.5, 0.63, 0.3, 0.2);
    multitoggle->setLocalOff(false);
    multitoggle->setExclusive(false);
    multitoggle->setNumberX(5);
    multitoggle->setNumberY(4);
        
    // save to file (appears in data folder)
    touchOsc.save("myTouchOscLayout");
    
    // or grab the raw xml
    string xml = touchOsc.getXml();
    cout << xml << endl;

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
