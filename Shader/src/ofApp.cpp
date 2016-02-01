#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    

    ofSetWindowTitle("Shader Effects Example");
    ofBackground(ofColor::white);
    
    vid.loadMovie("movie/fingers.mov");
    vid.setLoopState(OF_LOOP_NORMAL);
    vid.play();
    
    //Set up your shader effect chain//
    effect.chainEffect(SHADER_GLITCH_SHIFT);
    
    effect.setup(vid.getWidth(), vid.getHeight(), vid.getTextureReference());
    
    counter = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
    
    effect.update();
    float interact1 = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.0, 1.0);
    float interact2 = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0.0, 1.0);
    
    

    vid.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    
    
    effect.draw(ofVec2f(ofGetWidth() * .3, ofGetHeight() * .3));

    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if ( key == OF_KEY_UP) {
        
        counter++;
        counter %= 4;
    }
    
    if ( key == OF_KEY_DOWN) {
        
        counter--;
        counter %= 4;
        
    }

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
