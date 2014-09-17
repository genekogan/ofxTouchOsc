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
    
    virtual string get() {
        xml = "";
        string b64name = base64_encode(reinterpret_cast<const unsigned char*>(name.c_str()), name.length());
        xml += "<control name=\""+b64name+"\" ";
        xml += "type=\""+type+"\" ";
        xml += "x=\""+ofToString(x)+"\" y=\""+ofToString(y)+"\" ";
        xml += "w=\""+ofToString(w)+"\" h=\""+ofToString(h)+"\" color=\""+color+"\" ";
        getXml();
        xml += " >\n";
        xml += "</control>\n";
        return xml;
    }
    
    virtual void getXml() {};
    
    string type;
    string xml;
    string name;
    string color;
    int x, y, w, h;
};





//-------------

class ofxTouchOscNumericWidget : public ofxTouchOscWidget {
public:
    ofxTouchOscNumericWidget(string name, int x, int y, int w, int h, float min=0.0, float max=1.0) : ofxTouchOscWidget(name, x, y, w, h) {
        this->min = min;
        this->max = max;
    }
    virtual void getXml() {
        xml += "scalef=\""+ofToString(min)+"\" scalet=\""+ofToString(max)+"\" ";
    }
    float min, max;
};

class ofxTouchOscFader : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscFader(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, bool inverted=false, bool centered=false, bool responseRelative=false) : ofxTouchOscNumericWidget(name, x, y, w, h, min, max) {
        this->inverted = inverted ? "true" : "false";
        this->centered = centered ? "true" : "false";
        this->response = responseRelative ? "relative" : "absolute";
        type = (w >= h) ? "faderh" : "faderv";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "response=\""+response+"\" inverted=\""+inverted+"\" centered=\""+centered+"\" ";
    }
    string inverted, centered, response;
};

class ofxTouchOscRotary : public ofxTouchOscFader {
public:
    ofxTouchOscRotary(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, bool inverted=false, bool centered=false, bool responseRelative=false, bool norollover=false) : ofxTouchOscFader(name, x, y, w, h, min, max, inverted, centered, responseRelative) {
        this->norollover = (norollover) ? "true" : "false";
        type = (w >= h) ? "rotaryh" : "rotaryv";
    }
    virtual void getXml() {
        ofxTouchOscFader::getXml();
        xml += "norollover=\""+norollover+"\" ";
    }
    string norollover;
};





class ofxTouchOscLed : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscLed(string name, int x, int y, int w, int h, float min=0.0, float max=1.0) : ofxTouchOscNumericWidget(name, x, y, w, h, min, max) {
        type = "led";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
    }
};
class ofxTouchOscButton : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscButton(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, bool local_off=false, bool velocity=false) : ofxTouchOscNumericWidget(name, x, y, w, h, min, max) {
        this->velocity = velocity ? "1" : "0";
        this->local_off = local_off ? "true" : "false";
        type = "push";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "local_off=\""+local_off+"\" velocity=\""+velocity+"\" ";
    }
    string velocity, local_off;
};
class ofxTouchOscToggle : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscToggle(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, bool local_off=false) : ofxTouchOscNumericWidget(name, x, y, w, h, min, max) {
        this->local_off = local_off ? "true" : "false";
        type = "toggle";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "local_off=\""+local_off+"\" ";
    }
    string local_off;
};


class ofxTouchOscMultiPush : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscMultiPush(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, int number_x=2, int number_y=2, bool local_off=false) : ofxTouchOscNumericWidget(name, x, y, w, h, min, max) {
        this->local_off = local_off ? "true" : "false";
        this->number_x = number_x;
        this->number_y = number_y;
        type = "multipush";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "number_x=\""+ofToString(number_x)+"\" number_y=\""+ofToString(number_y)+"\" local_off=\""+local_off+"\" ";
    }
    int number_x, number_y;
    string local_off;
};
class ofxTouchOscMultiToggle : public ofxTouchOscMultiPush {
public:
    ofxTouchOscMultiToggle(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, int number_x=2, int number_y=2, bool local_off=false, bool ex_mode=false) : ofxTouchOscMultiPush(name, x, y, w, h, min, max) {
        this->ex_mode = ex_mode ? "true" : "false";
        type = "multitoggle";
    }
    virtual void getXml() {
        ofxTouchOscMultiPush::getXml();
        xml += "ex_mode=\""+ex_mode+"\" ";
    }
    string local_off, ex_mode;
};

class ofxTouchOscMultiFader : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscMultiFader(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, int number=2, bool inverted=false, bool centered=false) : ofxTouchOscNumericWidget(name, x, y, w, h, min, max) {
        this->number = number;
        this->inverted = inverted ? "true" : "false";
        this->centered = centered ? "true" : "false";
        type = (w >= h) ? "multifaderh" : "multifaderv";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "number=\""+ofToString(number)+"\" inverted=\""+inverted+"\" centered=\""+centered+"\" ";
    }
    int number;
    string inverted, centered;
};

class ofxTouchOscMultiXy : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscMultiXy(string name, int x, int y, int w, int h, float min=0.0, float max=1.0, bool inverted_x=false, bool inverted_y=false) : ofxTouchOscNumericWidget(name, x, y, w, h, min, max) {
        this->inverted_x = inverted_x ? "true" : "false";
        this->inverted_y = inverted_y ? "true" : "false";
        type = "multixy";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "inverted_x=\""+ofToString(inverted_x)+"\" inverted_y=\""+ofToString(inverted_y)+"\" ";
    }
    string inverted_x, inverted_y;
};



//-------------

class ofxTouchOscPage {
public:
    ofxTouchOscPage(string name);
    
    void addFader(string name, int x, int y, int w, int h);
    void addRotary(string name, int x, int y, int w, int h);
    void addLed(string name, int x, int y, int w, int h);
    void addButton(string name, int x, int y, int w, int h);
    void addToggle(string name, int x, int y, int w, int h);
    void addMultiPush(string name, int x, int y, int w, int h);
    void addMultiToggle(string name, int x, int y, int w, int h);
    void addMultiFader(string name, int x, int y, int w, int h);
    void addMultiXy(string name, int x, int y, int w, int h);
    
    string getXml();
    
private:
    vector<ofxTouchOscWidget *> widgets;
    string name;
};



class ofxTouchOsc {
public:
    ofxTouchOscPage* addPage(string name);
    string getXml();
    void save(string name);
    
private:
    vector<ofxTouchOscPage *> pages;
};

