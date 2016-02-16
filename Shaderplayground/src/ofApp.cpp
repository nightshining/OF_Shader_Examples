#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(255);
    ofDisableArbTex();
    counter = 0;
    
    shaderNames.push_back("plasma");
    shaderNames.push_back("fluid");
    shaderNames.push_back("ink");
    shaderNames.push_back("acid");
    shaderNames.push_back("smoke");
    shaderNames.push_back("water");
    shaderNames.push_back("noise");
    shaderNames.push_back("ripple");
    shaderNames.push_back("rgb");
    
    shadertoy.load("shaders/" + shaderNames[counter]);
    
    img.loadImage("textures/earth.jpg");
    
}

//--------------------------------------------------------------
void ofApp::update(){
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
   
    shadertoy.begin();
    shadertoy.setUniform3f("iResolution", ofGetWidth(), ofGetHeight(), 0.0);
    shadertoy.setUniform1f("iGlobalTime", ofGetElapsedTimef());
    shadertoy.setUniform4f("iMouse", draggedX, draggedY, clickX, clickY);
    shadertoy.setUniformTexture("iChannel0", img, 1);


    shadertoy.setUniform4f("iDate", ofGetYear(), ofGetMonth(), ofGetDay(), ofGetSeconds());
  
    ofRect(0,0, ofGetWidth(), ofGetHeight());
    shadertoy.end();
    


 
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if (key == OF_KEY_UP) {
        
    counter++;
    counter %= shaderNames.size();

    shadertoy.load("shaders/" + shaderNames[counter]);
        cout << "Shader Index: " << counter << endl;
        cout << "Shader Title: " << shaderNames[counter] << endl;
    }
    
    if (key == OF_KEY_DOWN) {
        
        counter--;
        counter %= shaderNames.size();
        
        shadertoy.load("shaders/" + shaderNames[counter]);
        cout << "Shader Index: " << counter << endl;
        cout << "Shader Title: " << shaderNames[counter] << endl;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    draggedX = x * .01;
    draggedY = y * .01;
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    clickX = x;
    clickY = y;
    
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
