
//NOTE: All parameters set functions go 0.0-1.0//

#pragma once

#include "ofMain.h"
#include "ofxISF.h"

enum effectType { SHADER_BLUR_ZOOM, SHADER_LENS_DISTORT, SHADER_DOUBLE_IMAGE, SHADER_DISTORTED_TV, SHADER_WAVES, SHADER_TWIRL, SHADER_EXPOSURE, SHADER_COLOR_ADJUST, SHADER_CHROMA_ZOOM, SHADER_SHAKE, SHADER_CONVERGE, SHADER_GLITCH_SHIFT, SHADER_BLUR, SHADER_PIXEL_SHIFTER, SHADER_ZOOM_ISF, SHADER_ROTATE_ISF, SHADER_VHS };

class Shader {
    
public:
    Shader();
    ~Shader();
    void setup(int w, int h, ofTexture &setTexRef);
    void update();
    void draw(ofVec2f translate);
    
    void chainEffect(effectType load);
    void resetTexRed(ofTexture &setTexRef);
    
    //Shader Set //
    
    void setBlurZoom(float zoomAmt, float feedbackAmt, float dryAmt);
    void setLensDistort(float kCubeAmt, float kAmt);
    void setDoubleImage(float hShiftAmt, float vShiftAmt, float mix1Amt, float mix2Amt);
    void setDistortedTv(float noiseAmt, float dist1Amt, float dist2Amt, float speedAmt, float scrollAmt, float scanLineThickness, float scanLineInstensity, float scanlineOffset);
    void setWaves(float distAmt, float freqAmt, float speedAmt);
    void setTwirl(float radius, float amt, ofVec2f center);
    void setExposure(float evAmt);
    void setColorAdjust(float brightAmt,float contrastAmt, float hueAmt, float saturationAmt);
    void setChromaZoom(float zoom, float r, float g, float b, ofVec2f pos);
    void setShake(float magAmt, float rotationAmt, float intensityAmt);
    void setConverge(float horzMagAmt,float vertMagAmt,float colorMagAmt);
    void setGlitchShift(float size, float horizontal, float vertical, ofVec2f offset);
    
    void setBlur(float amt);
    void setVHS( bool autoScan, float xScanLine, float yScanLine, float xScanLineSize, float yScanLineAmt, float grainLevel, bool scanFollow, float analogDist, float bleed, float bleedRange);
    
    void setPixelShifter(float amt);
    void setZoom(float amt);
    void setRotate(float amt);
    
    //Shader Get //
    //note parameter index corresponds left to right from 'set' function//
    
    float getBlurZoomParam(int parameterIndex);
    float getLensDistortParam(int parameterIndex);
    float getDoubleImageParam(int parameterIndex);
    float getDistortedTvParam(int parameterIndex);
    float getWavesParam(int parameterIndex);
    float getTwirlParam(int parameterIndex);
    float getColorAdjustParam(int parameterIndex);
    float getChromaZoomParam(int parameterIndex);
    float getShakeParam(int parameterIndex);
    float getConvergeParam(int parameterIndex);
    float getGlitchShift(int parameterIndex);
    float getBlurParam(int parameterIndex);
    float getVHSParam(int parameterIndex);
    
private:
    
    ofxISF::Chain chain;
    vector<string> filePaths;
    
    string loadWarning;
    string paraIndexWarning;
    
    //SHADER_BLUR_ZOOM//
    bool shaderBlurZoomPass;
    float zoom, feedback, dry;
    
    //SHADER_LENS_DISTORT//
    bool shaderLensDistortPass;
    float kCube, k;
    
    //SHADER_DOUBLE_IMAGE//
    bool shaderDoubleImagePass;
    float hShift, vShift, mix1, mix2;
    
    //SHADER_DISTORED_TV//
    bool shaderDistortTvPass;
    vector<float> distTVParams;
    vector<string> distTVNames;
    
    //SHADER_WAVES//
    bool shaderWavesPass;
    float wavesDist, frequencyDist, speedDist;
    
    //SHADER_TWIRL//
    bool shaderTwirlPass;
    float radiusTwirl, amtTwirl;
    ofVec2f centerTwirl;
    
    //SHADER_EXPOSURE//
    bool shaderExposurePass;
    float ev;
    
    //SHADER_COLOR_ADJUST//
    bool shaderColorAdjustPass;
    float bright, contrast, hue, saturation;
    
    //SHADER_CHROMA_ZOOM//
    bool shaderChromaZoomPass;
    ofVec2f chromaPos;
    vector<float> chromaParams;
    vector<string> chromaNames;
    
    //SHADER_SHAKE//
    bool shaderShakePass;
    float mag, rotation, intensity;

    //SHADER_CONVERGE//
    bool shaderConvergePass;
    float horzMag, vertMag, colorMag;
    
    //SHADER_GLITCH//
    bool shaderGlitchPass;
    float glitchSize, glitchHorz, glitchVert;
    ofVec2f glitchOffset;
    
    //SHADER_VHS//
    bool shaderVHSPass;
    
    
    //SHADER_BLUR//
    bool shaderBlurPass;
    float blurAmt;
    bool scanToggle, scanFollowToggle;
    
    vector<float> shaderVHS_params;
    vector<ofVec4f> shaderVHS_colors;
    vector<string> vhsNames;
    

};



//{
//    "NAME": "autoScan",
//    "TYPE": "bool",
//    "DEFAULT": 1.0
//},
//{
//    "NAME": "xScanline",
//    "TYPE": "float",
//    "DEFAULT": 0.5,
//    "MIN": 0.0,
//    "MAX": 1.0
//},
//{
//    "NAME": "yScanline",
//    "TYPE": "float",
//    "DEFAULT": 0.0,
//    "MIN": 0.0,
//    "MAX": 1.0
//},
//{
//    "NAME": "xScanlineSize",
//    "TYPE": "float",
//    "DEFAULT": 0.25,
//    "MIN": 0.0,
//    "MAX": 1.0
//},
//{
//    "NAME": "yScanlineAmount",
//    "TYPE": "float",
//    "DEFAULT": 0.25,
//    "MIN": -1.0,
//    "MAX": 1.0
//},
//{
//    "NAME": "grainLevel",
//    "TYPE": "float",
//    "DEFAULT": 0.0,
//    "MIN": 0.0,
//    "MAX": 3.0
//},
//{
//    "NAME": "scanFollow",
//    "TYPE": "bool",
//    "DEFAULT": 1.0
//},
//{
//    "NAME": "analogDistort",
//    "TYPE": "float",
//    "DEFAULT": 1.0,
//    "MIN": 0.0,
//    "MAX": 10.0
//},
//{
//    "NAME": "bleedAmount",
//    "TYPE": "float",
//    "DEFAULT": 1.0,
//    "MIN": 0.0,
//    "MAX": 5.0
//},
//{
//    "NAME": "bleedRange",
//    "TYPE": "float",
//    "DEFAULT": 1.0,
//    "MIN": 0.0,
//    "MAX": 2.0
//},
//{
//    "NAME": "colorBleedL",
//    "TYPE": "color",
//    "DEFAULT": [
//                0.8,
//                0.0,
//                0.2,
//                1.0
//                ]
//},
//{
//    "NAME": "colorBleedC",
//    "TYPE": "color",
//    "DEFAULT": [
//                1.0,
//                0.0,
//                0.0,
//                1.0
//                ]
//},
//{
//    "NAME": "colorBleedR",
//    "TYPE": "color",
//    "DEFAULT": [
//                0.8,
//                0.2,
//                0.0,
//                1.0
//                ]
//}
//]
//
//



