#pragma once

#include "ofMain.h"
#include "Base64.h"


enum TouchOscColor { RED, GREEN, BLUE, YELLOW, PURPLE, GRAY, ORANGE, BROWN, PINK };


/* basic widget class */

class ofxTouchOscWidget {
public:
    ofxTouchOscWidget(string name, float x, float y, float w, float h, TouchOscColor color) {
        this->name = name;
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        setColor(color);
        scaleX = 1.0;
        scaleY = 1.0;
        oscManual = false;
    }
    virtual void setOscAddress(string oscAddress) {
        this->oscAddress = oscAddress;
        oscManual = true;
    }
    virtual void setColor(TouchOscColor color) {
        if      (color == RED)      this->color = "red";
        else if (color == GREEN)    this->color = "green";
        else if (color == BLUE)     this->color = "blue";
        else if (color == YELLOW)   this->color = "yellow";
        else if (color == PURPLE)   this->color = "purple";
        else if (color == GRAY)     this->color = "gray";
        else if (color == ORANGE)   this->color = "orange";
        else if (color == BROWN)    this->color = "brown";
        else if (color == PINK)     this->color = "pink";
    }
    virtual void setScale(float scaleX, float scaleY) {
        this->scaleX = scaleX;
        this->scaleY = scaleY;
    }
    virtual string getXmlInner() {
        xml = "";
        string b64name = base64_encode(reinterpret_cast<const unsigned char*>(name.c_str()), name.length());
        xml += "<control name=\""+b64name+"\" ";
        xml += "type=\""+type+"\" ";
        xml += "x=\""+ofToString((int)(scaleX * x))+"\" y=\""+ofToString((int)(scaleY * y))+"\" ";
        xml += "w=\""+ofToString((int)(scaleX * w))+"\" h=\""+ofToString((int)(scaleY * h))+"\" color=\""+color+"\" ";
        getXml();
        xml += " >\n";
        xml += "</control>\n";
        return xml;
    }
    virtual void getXml() {};

    string xml;

    string type;
    string name;
    string oscAddress;
    string color;
    float x, y, w, h;
    float scaleX, scaleY;
    bool oscManual;
};


/* labels, status displays */

class ofxTouchOscMetaWidget : public ofxTouchOscWidget {
public:
    ofxTouchOscMetaWidget(string name, float x, float y, float w, float h, TouchOscColor color=RED, int textSize=14, bool background=false, bool outline=false) : ofxTouchOscWidget(name, x, y, w, h, color) {
        setTextSize(textSize);
        setBackground(background);
        setOutline(outline);
    }
    virtual void getXml() {
        xml += "size=\""+ofToString(textSize)+"\" background=\""+background+"\" outline=\""+outline+"\" ";
    }
    virtual void setTextSize(int textSize) {this->textSize = textSize;}
    virtual void setBackground(bool background) {this->background = background ? "true" : "false";}
    virtual void setOutline(bool outline) {this->outline = outline ? "true" : "false";}
    
    string background, outline;
    int textSize;
};

class ofxTouchOscLabel : public ofxTouchOscMetaWidget {
public:
    ofxTouchOscLabel(string name, float x, float y, float w, float h, TouchOscColor color=RED, int textSize=14, bool background=false, bool outline=false) : ofxTouchOscMetaWidget(name, x, y, w, h, color, textSize, background, outline) {
        label = name;
        type = (w >= h) ? "labelh" : "labelv";
    }
    virtual void getXml() {
        ofxTouchOscMetaWidget::getXml();
        string labelb64 = base64_encode(reinterpret_cast<const unsigned char*>(label.c_str()), label.length());
        xml += "text=\""+labelb64+"\" ";
    }
    virtual void setLabel(string label) {this->label = label;}
    virtual void setHorizontal() {type = "labelh";}
    virtual void setVertical() {type = "labelv";}
    
    string label;
};

class ofxTouchOscBattery : public ofxTouchOscMetaWidget {
public:
    ofxTouchOscBattery(string name, float x, float y, float w, float h, TouchOscColor color=RED, int textSize=14, bool background=false, bool outline=false) : ofxTouchOscMetaWidget(name, x, y, w, h, color, textSize, background, outline) {
        type = (w >= h) ? "batteryh" : "batteryv";
    }
    virtual void getXml() {
        ofxTouchOscMetaWidget::getXml();
    }
    virtual void setHorizontal() {type = "batteryh";}
    virtual void setVertical() {type = "batteryv";}
};

class ofxTouchOscTime : public ofxTouchOscMetaWidget {
public:
    ofxTouchOscTime(string name, float x, float y, float w, float h, TouchOscColor color=RED, int textSize=14, bool background=false, bool outline=false, bool show_seconds=false) : ofxTouchOscMetaWidget(name, x, y, w, h, color, textSize, background, outline) {
        setShowSeconds(show_seconds);
        type = (w >= h) ? "timeh" : "timev";
    }
    virtual void getXml() {
        ofxTouchOscMetaWidget::getXml();
        xml += "seconds=\""+show_seconds+"\" ";
    }
    virtual void setShowSeconds(bool show_seconds) {this->show_seconds = show_seconds ? "true" : "false";}
    virtual void setHorizontal() {type = "timeh";}
    virtual void setVertical() {type = "timev";}
    
    string show_seconds;
};


/* widgets with numerical values */

class ofxTouchOscNumericWidget : public ofxTouchOscWidget {
public:
    ofxTouchOscNumericWidget(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0) : ofxTouchOscWidget(name, x, y, w, h, color) {
        this->min = min;
        this->max = max;
    }
    virtual void getXml() {
        xml += "scalef=\""+ofToString(min)+"\" scalet=\""+ofToString(max)+"\" ";
        if (oscManual) {
            string oscAddressb64 = base64_encode(reinterpret_cast<const unsigned char*>(oscAddress.c_str()), oscAddress.length());
            xml += "osc_cs=\""+oscAddressb64+"\" ";
        }
    }
    virtual void setRange(float min, float max) { this->min = min; this->max = max; }
    virtual void setMin(float min) { this->min = min; }
    virtual void setMax(float max) { this->max = max; }
    
    float min, max;
};

class ofxTouchOscFader : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscFader(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, bool inverted=false, bool centered=false, bool responseRelative=false) : ofxTouchOscNumericWidget(name, x, y, w, h, color, min, max) {
        setInverted(inverted);
        setCentered(centered);
        setResponseRelative(responseRelative);
        type = (w >= h) ? "faderh" : "faderv";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "response=\""+response+"\" inverted=\""+inverted+"\" centered=\""+centered+"\" ";
    }
    virtual void setHorizontal() {type="faderh";}
    virtual void setVertical() {type="faderv";}
    virtual void setInverted(bool inverted) { this->inverted = inverted ? "true" : "false"; }
    virtual void setCentered(bool centered) { this->centered = centered ? "true" : "false"; }
    virtual void setResponseRelative(bool responseRelative) { this->response = responseRelative ? "relative" : "absolute"; }

    string inverted, centered, response;
};

class ofxTouchOscRotary : public ofxTouchOscFader {
public:
    ofxTouchOscRotary(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, bool inverted=false, bool centered=false, bool responseRelative=false, bool norollover=false) : ofxTouchOscFader(name, x, y, w, h, color, min, max, inverted, centered, responseRelative) {
        setNoRollover(norollover);
        type = (w >= h) ? "rotaryh" : "rotaryv";
    }
    virtual void getXml() {
        ofxTouchOscFader::getXml();
        xml += "norollover=\""+norollover+"\" ";
    }
    virtual void setHorizontal() {type="rotaryh";}
    virtual void setVertical() {type="rotaryv";}
    virtual void setNoRollover(bool norollover) {this->norollover = (norollover) ? "true" : "false"; }
    
    string norollover;
};

class ofxTouchOscLed : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscLed(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0) : ofxTouchOscNumericWidget(name, x, y, w, h, color, min, max) {
        type = "led";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
    }
};

class ofxTouchOscButton : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscButton(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, bool local_off=false, bool velocity=false) : ofxTouchOscNumericWidget(name, x, y, w, h, color, min, max) {
        setLocalOff(local_off);
        setVelocity(velocity);
        type = "push";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "local_off=\""+local_off+"\" velocity=\""+velocity+"\" ";
    }
    virtual void setLocalOff(bool local_off) {this->local_off = local_off ? "true" : "false";}
    virtual void setVelocity(bool velocity) {this->velocity = velocity ? "1" : "0";}
    
    string velocity, local_off;
};

class ofxTouchOscToggle : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscToggle(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, bool local_off=false) : ofxTouchOscNumericWidget(name, x, y, w, h, color, min, max) {
        setLocalOff(local_off);
        type = "toggle";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "local_off=\""+local_off+"\" ";
    }
    virtual void setLocalOff(bool local_off) {this->local_off = local_off ? "true" : "false";}
    
    string local_off;
};

class ofxTouchOscEncoder : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscEncoder(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, bool local_off=false) : ofxTouchOscNumericWidget(name, x, y, w, h, color, min, max) {
        type = "encoder";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
    }
};


class ofxTouchOscXy : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscXy(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, bool inverted_x=false, bool inverted_y=false) : ofxTouchOscNumericWidget(name, x, y, w, h, color, min, max) {
        setInvertedX(inverted_x);
        setInvertedY(inverted_y);
        type = "xy";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "inverted_x=\""+ofToString(inverted_x)+"\" inverted_y=\""+ofToString(inverted_y)+"\" ";
    }
    virtual void setInvertedX(bool inverted_x) { this->inverted_x = inverted_x ? "true" : "false"; }
    virtual void setInvertedY(bool inverted_y) { this->inverted_y = inverted_y ? "true" : "false"; }
    
    string inverted_x, inverted_y;
};


class ofxTouchOscMultiPush : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscMultiPush(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, int number_x=2, int number_y=2, bool local_off=false) : ofxTouchOscNumericWidget(name, x, y, w, h, color, min, max) {
        setLocalOff(local_off);
        setNumberX(number_x);
        setNumberY(number_y);
        type = "multipush";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "number_x=\""+ofToString(number_x)+"\" number_y=\""+ofToString(number_y)+"\" local_off=\""+local_off+"\" ";
    }
    virtual void setLocalOff(bool local_off) {this->local_off = local_off ? "true" : "false";}
    virtual void setNumberX(int number_x) {this->number_x = number_x;}
    virtual void setNumberY(int number_y) {this->number_y = number_y;}
    
    int number_x, number_y;
    string local_off;
};

class ofxTouchOscMultiToggle : public ofxTouchOscMultiPush {
public:
    ofxTouchOscMultiToggle(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, int number_x=2, int number_y=2, bool local_off=false, bool ex_mode=false) : ofxTouchOscMultiPush(name, x, y, w, h, color, min, max) {
        setExclusive(ex_mode);
        type = "multitoggle";
    }
    virtual void getXml() {
        ofxTouchOscMultiPush::getXml();
        xml += "ex_mode=\""+ex_mode+"\" ";
    }
    virtual void setExclusive(bool ex_mode) {this->ex_mode = ex_mode ? "true" : "false";}

    string local_off, ex_mode;
};

class ofxTouchOscMultiFader : public ofxTouchOscNumericWidget {
public:
    ofxTouchOscMultiFader(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, int number=2, bool inverted=false, bool centered=false) : ofxTouchOscNumericWidget(name, x, y, w, h, color, min, max) {
        setNumber(number);
        setInverted(inverted);
        setCentered(centered);
        type = (w >= h) ? "multifaderh" : "multifaderv";
    }
    virtual void getXml() {
        ofxTouchOscNumericWidget::getXml();
        xml += "number=\""+ofToString(number)+"\" inverted=\""+inverted+"\" centered=\""+centered+"\" ";
    }
    virtual void setNumber(int number) {this->number = number;}
    virtual void setInverted(bool inverted) { this->inverted = inverted ? "true" : "false"; }
    virtual void setCentered(bool centered) { this->centered = centered ? "true" : "false"; }

    int number;
    string inverted, centered;
};

class ofxTouchOscMultiXy : public ofxTouchOscXy {
public:
    ofxTouchOscMultiXy(string name, float x, float y, float w, float h, TouchOscColor color=RED, float min=0.0, float max=1.0, bool inverted_x=false, bool inverted_y=false) : ofxTouchOscXy(name, x, y, w, h, color, min, max) {
        type = "multixy";
    }
    virtual void getXml() {
        ofxTouchOscXy::getXml();
    }
};



//-----------------------------------------

class ofxTouchOscPage {
public:
    ~ofxTouchOscPage();
    ofxTouchOscPage(string name, TouchOscColor color=YELLOW);
    void setScale(float scaleX, float scaleY);
    void setDefaultWidgetColor(TouchOscColor color);
    string getXml();
    
    ofxTouchOscLabel* addLabel(string name, float x, float y, float w, float h);
    ofxTouchOscTime* addTime(string name, float x, float y, float w, float h);
    ofxTouchOscBattery* addBattery(string name, float x, float y, float w, float h);
    ofxTouchOscFader* addFader(string name, float x, float y, float w, float h);
    ofxTouchOscRotary* addRotary(string name, float x, float y, float w, float h);
    ofxTouchOscLed* addLed(string name, float x, float y, float w, float h);
    ofxTouchOscButton* addButton(string name, float x, float y, float w, float h);
    ofxTouchOscToggle* addToggle(string name, float x, float y, float w, float h);
    ofxTouchOscEncoder* addEncoder(string name, float x, float y, float w, float h);
    ofxTouchOscXy* addXy(string name, float x, float y, float w, float h);
    ofxTouchOscMultiPush* addMultiPush(string name, float x, float y, float w, float h);
    ofxTouchOscMultiToggle* addMultiToggle(string name, float x, float y, float w, float h);
    ofxTouchOscMultiFader* addMultiFader(string name, float x, float y, float w, float h);
    ofxTouchOscMultiXy* addMultiXy(string name, float x, float y, float w, float h);
    
private:
    vector<ofxTouchOscWidget *> widgets;
    string name;
    float scaleX, scaleY;
    TouchOscColor defaultColor;
};


class ofxTouchOsc {
public:
    ofxTouchOsc();
    ~ofxTouchOsc();
    ofxTouchOscPage* addPage(string name);
    void addPage(ofxTouchOscPage* newPage);
    void setDefaultColor(TouchOscColor color);
    void setScale(float scaleX, float scaleY);
    void save(string name);
    string getXml();
    
private:
    vector<ofxTouchOscPage *> pages;
    float scaleX, scaleY;
    TouchOscColor defaultColor;
    bool customResolution;
};

