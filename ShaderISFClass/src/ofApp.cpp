#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
    

    ofSetWindowTitle("Shader Effects Example");
    ofBackground(ofColor::white);
    
    vid.loadMovie("movie/fingers.mov");
    vid.setLoopState(OF_LOOP_NORMAL);
    vid.play();
    
    //Set up your shader effect chain//
    effect.chainEffect(SHADER_CONVERGE);
    effect.chainEffect(SHADER_CHROMA_ZOOM);
    effect.chainEffect(SHADER_BLUR);
    effect.chainEffect(SHADER_WAVES);
    
    effect.setup(vid.getWidth(), vid.getHeight(), vid.getTextureReference());
    
}

//--------------------------------------------------------------
void ofApp::update() {
    
    effect.update();
    
    vid.update();
    
    float interact1 = ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.0, 1.0);
    float interact2 = ofMap(ofGetMouseY(), 0, ofGetHeight(), 0.0, 1.0);

    effect.setChromaZoom(0.5, interact1, 0.2, interact2, ofVec2f(0.5, 0.5));
    effect.setWaves(interact1, interact2, 0.1);

}

//--------------------------------------------------------------
void ofApp::draw() {
    
    
    effect.draw(ofVec2f(ofGetWidth() * .3, ofGetHeight() * .3));

    
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
