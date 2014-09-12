#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    touchOsc.setup();
    
    
    
    ofxTouchOscPage *newPage = touchOsc.addPage();
    newPage->addWidget(FADERV);
    
    
    
    ofFile file("index.xml", ofFile::WriteOnly);

    file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
    file << "<layout version=\"9\" mode=\"0\" orientation=\"vertical\">";
    file << "<tabpage name=\"MQ==\">";
    file << "<control name=\"cHVzaDE=\" x=\"3\" y=\"3\" w=\"275\" h=\"65\" color=\"green\" scalef=\"0.0\" scalet=\"1.0\" type=\"push\" local_off=\"false\" >";
    file << "<midi var =\"x\" type=\"1\" channel=\"1\" data1=\"24\" data2f=\"0\" data2t=\"127\" />";
    file << "</control>";
    file << "<control name=\"cHVzaDM=\" x=\"3\" y=\"71\" w=\"275\" h=\"65\" color=\"green\" scalef=\"0.0\" scalet=\"1.0\" type=\"push\" local_off=\"false\" >";
    file << "<midi var =\"x\" type=\"1\" channel=\"1\" data1=\"26\" data2f=\"0\" data2t=\"127\" />";
    file << "</control>";
    file << "</tabpage>";
    file << "</layout>";

    file.close();
    
//    string cmd = "zip -r "+ofToString(ofToDataPath("thisme.zip"))+" \""+ofToDataPath("index.xml")+"\"";
    //string cmd = "cd "+ofToString(ofToDataPath(""));
    
    //string cmd = "cd "+ofToString(ofToDataPath("")) + " & open "+ofToDataPath("index.xml");
    //string cmd = "cd "+ofToString(ofToDataPath("")) + "; open index.xml";
    
    string cmd = "cd "+ofToString(ofToDataPath("")) + "; zip -r myLayout7.touchosc index.xml";
    
    
    
    
    cout << cmd << endl;
    cout << ofSystem(cmd);
 

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
