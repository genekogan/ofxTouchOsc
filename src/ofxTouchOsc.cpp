#include "ofxTouchOsc.h"




//--------
//void ofxTouchOscWidget::setup() {
//}

//--------
//void ofxTouchOscPage::setup() {
    
    
    // 315, 430
    
//}



//--------
void ofxTouchOsc::setup() {

    cout << "======" << endl;
    const std::string s = "base64meHiWorld" ;
    
    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(s.c_str()), s.length());
    std::string decoded = base64_decode(encoded);
    
    std::cout << "encoded: " << encoded << std::endl;
    std::cout << "decoded: " << decoded << std::endl;
    cout << "======" << endl;
    
    
    // 315, 430
    
}
