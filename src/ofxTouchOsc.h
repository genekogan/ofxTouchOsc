#pragma once

#include "ofMain.h"
#include "Base64.h"



class ofxTouchOscWidget {
public:
    ofxTouchOscWidget(string name, int x, int y, int w, int h) {
        this->name = name;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        color = "yellow";
    }
    virtual string getXml() { }
    
    string name;
    string color;
    int x, y, w, h;
};


class ofxTouchOscFader : public ofxTouchOscWidget {
public:
    ofxTouchOscFader(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, bool inverted=false, bool centered=false, bool responseRelative=false) : ofxTouchOscWidget(name, x, y, w, h) {
        this->min = min;
        this->max = max;
        this->inverted = inverted ? "true" : "false";
        this->centered = centered ? "true" : "false";
        this->response = responseRelative ? "relative" : "absolute";
        type = (w > h) ? "faderh" : "faderv";
    }
    string getXml() {
        string b64name = base64_encode(reinterpret_cast<const unsigned char*>(name.c_str()), name.length());
        string xml;
        xml += "<control name=\""+b64name+"\" ";
        xml += "x=\""+ofToString(x)+"\" y=\""+ofToString(y)+"\" ";
        xml += "w=\""+ofToString(w)+"\" h=\""+ofToString(h)+"\" color=\""+color+"\" ";
        xml += "scalef=\""+ofToString(min)+"\" scalet=\""+ofToString(max)+"\" type=\""+type+"\" ";
        xml += "response=\""+response+"\" inverted=\""+inverted+"\" centered=\""+centered+"\" >\n";
        xml += "</control>\n";
        return xml;
    }
    
    string type;
    float min, max;
    string inverted, centered, response;
};



class ofxTouchOscPage
{
public:
    ofxTouchOscPage(string name) {
        this->name = name;
        
    }
    
    void addFader(string name, int x, int y, int w, int h) {
        ofxTouchOscFader *widget = new ofxTouchOscFader(name, x, y, w, h);
        widgets.push_back(widget);
    }
    
    string getXml() {
        string b64name = base64_encode(reinterpret_cast<const unsigned char*>(name.c_str()), name.length());
        
        string xml;
        xml += "<tabpage name=\""+b64name+"\" scalef=\"0.0\" scalet=\"1.0\" >\n";
        for (int i=0; i<widgets.size(); i++) {
            xml += widgets[i]->getXml();
        }
        xml += "</tabpage>\n";
        
        return xml;
    }
    
    /*
    void addWidget(WidgetType type) {
        ofxTouchOscWidget *newWidget;
        if      (type == FADERV)
            newWidget = new ofxTouchOscFader(ofxTouchOscFader::VERTICAL);
        else if (type == FADERH)
            newWidget = new ofxTouchOscFader(ofxTouchOscFader::HORIZONTAL);
        widgets.push_back(newWidget);
    }
     */
    
    vector<ofxTouchOscWidget *> widgets;
    string name;
};


class ofxTouchOsc
{
public:
    void setup();
    
    ofxTouchOscPage* addPage(string name) {
        ofxTouchOscPage *newPage = new ofxTouchOscPage(name);
        pages.push_back(newPage);
        return newPage;
    }
    
    string getXml() {
        string xml;
        xml += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        xml += "<layout version=\"13\" mode=\"0\" orientation=\"horizontal\">";
        for (int i=0; i<pages.size(); i++) {
            xml += pages[i]->getXml();
        }
        xml += "</layout>";
        return xml;
    }
    
    void save(string name) {
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

private:
    
    vector<ofxTouchOscPage *> pages;
};

