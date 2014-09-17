#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofxTouchOscPage *newPage = touchOsc.addPage("mypa32");
    newPage->addFader("fad", 0, 20, 50, 50);
    newPage->addRotary("rot", 0, 80, 50, 50);
    newPage->addLed("led", 0, 130, 50, 50);
    newPage->addButton("but", 0, 180, 50, 50);
    newPage->addToggle("tog", 0, 230, 50, 50);
    newPage->addMultiFader("mp", 100, 30, 150, 150);
    newPage->addMultiXy("mt", 100, 230, 150, 150);

    
    string xml = touchOsc.getXml();
    cout << xml << endl;
    
    touchOsc.save("another");
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
