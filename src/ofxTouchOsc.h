#pragma once

#include "ofMain.h"
#include "Base64.h"


enum WidgetType { FADERV, FADERH };


class ofxTouchOscWidget {
public:
    ofxTouchOscWidget() {
    }
    virtual string get() { }
    int x, y, w, h;
};


class ofxTouchOscFader : public ofxTouchOscWidget {
public:
    enum Orientation { VERTICAL, HORIZONTAL };
    ofxTouchOscFader(Orientation orientation) {
        this->orientation = orientation;
    }
    string get() { }
    Orientation orientation;
};



class ofxTouchOscPage
{
public:
    ofxTouchOscPage() {
        
    }
    void addWidget(WidgetType type) {
        ofxTouchOscWidget *newWidget;
        if      (type == FADERV)
            newWidget = new ofxTouchOscFader(ofxTouchOscFader::VERTICAL);
        else if (type == FADERH)
            newWidget = new ofxTouchOscFader(ofxTouchOscFader::HORIZONTAL);
        widgets.push_back(newWidget);
    }
    
    vector<ofxTouchOscWidget *> widgets;
};


class ofxTouchOsc
{
public:
    void setup();
    ofxTouchOscPage* addPage() {
        ofxTouchOscPage *newPage = new ofxTouchOscPage();
        pages.push_back(newPage);
        return newPage;
    }
    
    vector<ofxTouchOscPage *> pages;
};

