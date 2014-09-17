#include "ofxTouchOsc.h"



ofxTouchOscPage::ofxTouchOscPage(string name) {
    this->name = name;
}

void ofxTouchOscPage::addFader(string name, int x, int y, int w, int h) {
    ofxTouchOscFader *widget = new ofxTouchOscFader(name, x, y, w, h);
    widgets.push_back(widget);
}
void ofxTouchOscPage::addRotary(string name, int x, int y, int w, int h) {
    ofxTouchOscRotary *widget = new ofxTouchOscRotary(name, x, y, w, h);
    widgets.push_back(widget);
}
void ofxTouchOscPage::addLed(string name, int x, int y, int w, int h) {
    ofxTouchOscLed *widget = new ofxTouchOscLed(name, x, y, w, h);
    widgets.push_back(widget);
}
void ofxTouchOscPage::addButton(string name, int x, int y, int w, int h) {
    ofxTouchOscButton *widget = new ofxTouchOscButton(name, x, y, w, h);
    widgets.push_back(widget);
}
void ofxTouchOscPage::addToggle(string name, int x, int y, int w, int h) {
    ofxTouchOscToggle *widget = new ofxTouchOscToggle(name, x, y, w, h);
    widgets.push_back(widget);
}
void ofxTouchOscPage::addMultiPush(string name, int x, int y, int w, int h) {
    ofxTouchOscMultiPush *widget = new ofxTouchOscMultiPush(name, x, y, w, h);
    widgets.push_back(widget);
}
void ofxTouchOscPage::addMultiToggle(string name, int x, int y, int w, int h) {
    ofxTouchOscMultiToggle *widget = new ofxTouchOscMultiToggle(name, x, y, w, h);
    widgets.push_back(widget);
}
void ofxTouchOscPage::addMultiFader(string name, int x, int y, int w, int h) {
    ofxTouchOscMultiFader *widget = new ofxTouchOscMultiFader(name, x, y, w, h);
    widgets.push_back(widget);
}
void ofxTouchOscPage::addMultiXy(string name, int x, int y, int w, int h) {
    ofxTouchOscMultiXy *widget = new ofxTouchOscMultiXy(name, x, y, w, h);
    widgets.push_back(widget);
}


string ofxTouchOscPage::getXml() {
    string b64name = base64_encode(reinterpret_cast<const unsigned char*>(name.c_str()), name.length());
    
    string xml;
    xml += "<tabpage name=\""+b64name+"\" scalef=\"0.0\" scalet=\"1.0\" >\n";
    for (int i=0; i<widgets.size(); i++) {
        xml += widgets[i]->get();
        cout << i << " " << widgets[i]->name << endl;
    }
    xml += "</tabpage>\n";
    return xml;
}



ofxTouchOscPage* ofxTouchOsc::addPage(string name) {
    ofxTouchOscPage *newPage = new ofxTouchOscPage(name);
    pages.push_back(newPage);
    return newPage;
}

string ofxTouchOsc::getXml() {
    string xml;
    xml += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    xml += "<layout version=\"13\" mode=\"0\" orientation=\"horizontal\">";
    for (int i=0; i<pages.size(); i++) {
        xml += pages[i]->getXml();
    }
    xml += "</layout>";
    return xml;
}

void ofxTouchOsc::save(string name) {
    ofFile file("index.xml", ofFile::WriteOnly);
    file << getXml();
    file.close();
    string cmd;
    cmd += "cd "+ofToString(ofToDataPath("")) + ";";
    cmd += "zip -r "+name+".touchosc index.xml;";
    cmd += "rm index.xml;";
    cmd += "open "+name+".touchosc;";
    ofSystem(cmd);
}