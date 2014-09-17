#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // set screen resolution
    touchOsc.setScale(320, 480);
    touchOsc.setDefaultColor(GREEN);
    
    // create a new page
    ofxTouchOscPage *page1 = touchOsc.addPage("myPage");
    
    // set the color for each widget blue
    page1->setDefaultWidgetColor(BLUE);
    
    // arguments for adding any new widget: name, x, y, width, height (0.0->1.0)
    ofxTouchOscFader *fader = page1->addFader("myFader", 0.01, 0.05, 0.9, 0.1);
    fader->setCentered(false);
    fader->setInverted(false);
    fader->setResponseRelative(false);
    
    // faders and rotaries can be set vertical or horizontal.
    // by default, it's horizontal if width>height, and vice-versa
    fader->setHorizontal();
    
    // set individual widget colors
    fader->setColor(YELLOW);

    ofxTouchOscRotary *rotary = page1->addRotary("myRotary", 0.01, 0.18, 0.15, 0.1);
    rotary->setCentered(false);
    rotary->setInverted(false);
    rotary->setResponseRelative(false);
    rotary->setNoRollover(false);
    
    // override default osc address
    rotary->setOscAddress("/mySpecialOscAddress/");
    
    ofxTouchOscLed *led = page1->addLed("myLed", 0.2, 0.18, 0.15, 0.1);

    ofxTouchOscButton *button = page1->addButton("myButton", 0.4, 0.18, 0.15, 0.1);
    button->setLocalOff(false);
    button->setVelocity(false);
    
    ofxTouchOscToggle *toggle = page1->addToggle("myToggle", 0.6, 0.18, 0.15, 0.1);
    toggle->setLocalOff(false);

    ofxTouchOscEncoder *encoder = page1->addEncoder("myEncoder", 0.8, 0.18, 0.15, 0.1);

    ofxTouchOscMultiFader *multifader = page1->addMultiFader("myMultiFader", 0.01, 0.3, 0.3, 0.2);
    multifader->setCentered(false);
    multifader->setInverted(false);
    multifader->setNumber(5);

    ofxTouchOscXy *xy = page1->addXy("myXy", 0.35, 0.3, 0.3, 0.2);
    xy->setInvertedX(false);
    xy->setInvertedY(false);

    ofxTouchOscMultiXy *multixy = page1->addMultiXy("myMultiXy", 0.67, 0.3, 0.3, 0.2);
    multixy->setInvertedX(false);
    multixy->setInvertedY(false);
    
    ofxTouchOscMultiPush *multipush = page1->addMultiPush("myMultiPush", 0.01, 0.63, 0.3, 0.2);
    multipush->setLocalOff(false);
    multipush->setNumberX(5);
    multipush->setNumberY(4);
    
    ofxTouchOscMultiToggle *multitoggle = page1->addMultiToggle("myMultiToggle", 0.35, 0.63, 0.3, 0.2);
    multitoggle->setLocalOff(false);
    multitoggle->setExclusive(false);
    multitoggle->setNumberX(5);
    multitoggle->setNumberY(4);
    
    ofxTouchOscLabel *label = page1->addLabel("myLabel", 0.68, 0.55, 0.25, 0.1);
    label->setLabel("hello");
    label->setTextSize(16);
    label->setOutline(true);
    label->setBackground(false);
    
    ofxTouchOscTime *time = page1->addTime("myLabel", 0.68, 0.65, 0.2, 0.1);
    time->setTextSize(16);
    time->setOutline(false);
    time->setBackground(false);
    time->setShowSeconds(true);
    
    ofxTouchOscBattery *battery = page1->addBattery("myLabel", 0.68, 0.77, 0.2, 0.1);
    battery->setTextSize(16);
    battery->setOutline(true);
    battery->setBackground(true);
    
    // add a new page
    ofxTouchOscPage *page2 = touchOsc.addPage("anotherPage");
    page2->addButton("anotherButton", 0.1, 0.2, 0.5, 0.5);
    page2->addLabel("anotherLabel", 0.15, 0.8, 0.2, 0.1);
    
    // save to file (appears in data folder).
    // it will automatically launch TouchOSC (if you have it installed)
    // and open the layout
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
