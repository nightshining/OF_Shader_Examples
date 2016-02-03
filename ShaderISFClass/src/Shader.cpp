#include "Shader.h"

Shader::Shader() {
    
    shaderBlurZoomPass = false;
    shaderLensDistortPass = false;
    shaderDoubleImagePass = false;
    shaderDistortTvPass = false;
    shaderWavesPass = false;
    shaderTwirlPass = false;
    shaderExposurePass = false;
    shaderColorAdjustPass = false;
    shaderChromaZoomPass = false;
    shaderShakePass = false;
    shaderConvergePass = false;
    shaderGlitchPass = false;
    shaderBlurPass = false;
    shaderVHSPass = false;
    
    loadWarning = "Corresponding Shader was never loaded!";
    paraIndexWarning = "This parameter index is out of range";
    
    //Setting up TV Distortion //
    
    int distTVParamTotal = 8;
    distTVParams.resize(distTVParamTotal);
    distTVNames.resize(distTVParamTotal);
    
    //Setting up ChromaZoom//
    
    int chromaParamTotal = 4;
    chromaNames.resize(chromaParamTotal);
    chromaParams.resize(chromaParamTotal);
    
    //Setting up VHS Distortian//
    
    int distVHSParamTotal = 8;
    shaderVHS_params.resize(distVHSParamTotal);
    
    int distVHSColorTotal = 3;
    shaderVHS_colors.resize(distVHSParamTotal);
    
    int distVHSNameTotal = 10;
    vhsNames.resize(distVHSNameTotal);
    
    
}

Shader::~Shader() {
    
}

//--------------------------------------------------------------
void Shader::setup(int w, int h, ofTexture &setTexRef) {
    

    chain.setup(w,h, GL_RGBA);
    
    for (int i = 0; i < filePaths.size(); i++) {
        
        chain.load(filePaths[i]);
        
        cout << "Chain Index " << i << " " << filePaths[i] << endl;
    }
    
    chain.setImage(setTexRef);


}

void Shader::resetTexRed(ofTexture &setTexRef) {
    
        chain.setImage(setTexRef);
}

void Shader::chainEffect(effectType load) {
    
    switch (load) {
        case SHADER_BLUR_ZOOM:
            shaderBlurZoomPass = true;
            filePaths.push_back("shaders/ZoomBlur.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_BLUR_ZOOM void setBlurZoom(float zoomAmt, float feedbackAmt, float dryAmt)");
            break;
        case SHADER_LENS_DISTORT:
            shaderLensDistortPass = true;
            filePaths.push_back("shaders/CubicLensDistortion.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_LENS_DISTORT void setLensDistort(float kCubeAmt, float kAmt);");
            break;
        case SHADER_DOUBLE_IMAGE:
            shaderDoubleImagePass = true;
            filePaths.push_back("shaders/Double Vision.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_DOUBLE_IMAGE void setDoubleImage(float hShiftAmt, float vShiftAmt, float mix1, float mix2);");
            break;
        case SHADER_DISTORTED_TV:
            shaderDistortTvPass = true;
            filePaths.push_back("shaders/Bad TV.fs/Bad TV.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_DISTORTED_TV setDistortedTv(float noiseAmt, float dist1Amt, float dist2Amt, float speedAmt, float scrollAmt, float scanLineThickness, float scanLineInstensity, float scanlineOffset");
            break;
        case SHADER_WAVES:
            shaderWavesPass = true;
            filePaths.push_back("shaders/videowave.fs/videowave.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_WAVES void setWaves(float distAmt, float freqAmt, float speedAmt)");
            break;
        case SHADER_TWIRL:
            shaderTwirlPass = true;
            filePaths.push_back("shaders/Twirl.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_TWIRL void setTwirl(float radius, float amt, float center);");
            break;
        case SHADER_EXPOSURE:
            shaderExposurePass = true;
            filePaths.push_back("shaders/Exposure Adjust.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_EXPOSURE void setExposure(float ev);");
            break;
        case SHADER_COLOR_ADJUST:
            shaderColorAdjustPass = true;
            filePaths.push_back("shaders/Color Controls.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_COLOR_ADJUST void setColorAdjust(float bright, float contrast, float hue, float saturation);");
            break;
        case SHADER_CHROMA_ZOOM:
            shaderChromaZoomPass = true;
            filePaths.push_back("shaders/Chroma Zoom.fs/Chroma Zoom.fs");
            ofLog(OF_LOG_NOTICE,"Access SHADER_CHROMA_ZOOM void setChromaZoom(float zoom, float r, float g, float b, ofVec2f pos);");
            break;
        case SHADER_SHAKE:
            shaderShakePass = true;
            filePaths.push_back("shaders/quake/quake.fs");
             ofLog(OF_LOG_NOTICE,"Access SHADER_SHAKE void setShake(float magAmt, float rotationAmt, float intensityAmt)");
            break;
        case SHADER_CONVERGE:
            shaderConvergePass = true;
            filePaths.push_back("shaders/Convergence.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_CONVERGENCE void setConverge(float horzMag,float vertMag,float colorMag)");
            break;
        case SHADER_GLITCH_SHIFT:
            shaderGlitchPass = true;
            filePaths.push_back("shaders/Glitch Shifter.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_GLITCHSHIFT void setGlitchShift(float size, float horizontal, float vertical)");
            break;
        case SHADER_BLUR:
            shaderBlurPass = true;
            filePaths.push_back("shaders/isf-test.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_BLUR void setBlur(float amt);");
            break;
        case SHADER_PIXEL_SHIFTER:
            filePaths.push_back("shaders/Pixel Shifter.fs"); //finish
            break;
        case SHADER_ZOOM_ISF:
            filePaths.push_back("shaders/zoom.fs"); //finish
            break;
        case SHADER_ROTATE_ISF:
            filePaths.push_back("shaders/3d Rotate.fs/3d Rotate.fs"); //finish
            break;
        case SHADER_VHS:
            shaderVHSPass = true;
            filePaths.push_back("shaders/VHS Glitch.fs");
            ofLog(OF_LOG_NOTICE, "Access SHADER_VHS void setVHS(float amt)");
            break;

        default:
            ofLog(OF_LOG_WARNING, "Not recognized as an EffectType (example: SHADER_BLUR)");
            break;
    }
    

}

//--------------------------------------------------------------
void Shader::update() {
    
    chain.update();

}

//--------------------------------------------------------------
void Shader::draw(ofVec2f translate) {
    
    ofPushMatrix();
    ofSetColor(255);
    ofTranslate(translate);
    chain.draw(0,0);
    ofPopMatrix();
    
}

void Shader::setBlurZoom(float zoomAmt, float feedbackAmt, float dryAmt) {
    
    if (shaderBlurZoomPass) {
        
    string paramFileName = "ZoomBlur";
    string param1 = "zoom";
    string param2 = "feedback";
    string param3 = "dry";
    
    zoom = ofMap(zoomAmt, 0.0, 1.0, -50, 50, true);
    feedback = feedbackAmt;
    dry = dryAmt;
    
    chain.getShader(paramFileName)->setUniform<float>(param1, zoom);
    chain.getShader(paramFileName)->setUniform<float>(param2, feedback);
    chain.getShader(paramFileName)->setUniform<float>(param3, dry);
   
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }
    
}

float Shader::getBlurZoomParam(int parameterIndex) {
    
    if (shaderBlurZoomPass) {
        
        switch (parameterIndex) {
            case 0:
                return zoom;
                break;
            case 1:
                return feedback;
                break;
            case 2:
                return dry;
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }
    
}


void Shader::setLensDistort(float kCubeAmt, float kAmt) {
    
    if (shaderLensDistortPass) {
    string paramFileName = "CubicLensDistortion";
    string param1 = "kcube";
    string param2 = "k";
    
    kCube = ofMap(kCubeAmt, 0.0, 1.0, 0.5, 2.5, true);
    k = ofMap(kAmt, 0.0, 1.0, -1.0, 3.0, true);
    
    chain.getShader(paramFileName)->setUniform<float>(param1, kCube);
    chain.getShader(paramFileName)->setUniform<float>(param2, k);
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }

}

float Shader::getLensDistortParam(int parameterIndex) {
    
    if (shaderLensDistortPass) {
        
        switch (parameterIndex) {
            case 0:
                return kCube;
                break;
            case 1:
                return k;
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }
}

void Shader::setDoubleImage(float hShiftAmt, float vShiftAmt, float mix1Amt, float mix2Amt) {
    
    if (shaderDoubleImagePass) {
    string paramFileName = "Double Vision";
    string param1 = "hShift";
    string param2 = "vShift";
    string param3 = "mixAmount1";
    string param4 = "mixAmount2";
    
    hShift = ofMap(hShiftAmt, 0.0, 1.0, -0.05, 0.05, true);
    vShift = ofMap(vShiftAmt, 0.0, 1.0, -0.05, 0.05, true);
    mix1 = mix1Amt;
    mix2 = mix2Amt;

    
    chain.getShader(paramFileName)->setUniform<float>(param1, hShift);
    chain.getShader(paramFileName)->setUniform<float>(param2, vShift);
    chain.getShader(paramFileName)->setUniform<float>(param3, mix1);
    chain.getShader(paramFileName)->setUniform<float>(param4, mix2);
        
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }

}

float Shader::getDoubleImageParam(int parameterIndex) {
    
    if (shaderDoubleImagePass) {
        
        switch (parameterIndex) {
            case 0:
                return hShift;
                break;
            case 1:
                return vShift;
                break;
            case 2:
                return mix1;
                break;
            case 3:
                return mix2;
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }
}

void Shader::setDistortedTv(float noiseAmt, float dist1Amt, float dist2Amt, float speedAmt, float scrollAmt, float scanLineThickness, float scanLineInstensity, float scanlineOffset ) {
    
    if (shaderDistortTvPass) {
        
        string paramFileName = "Bad TV";
        
        distTVParams[0] = noiseAmt;
        distTVParams[1] = ofMap(dist1Amt, 0.0, 1.0, 0.0, 5.0, true);
        distTVParams[2] = ofMap(dist2Amt, 0.0, 1.0, 0.0, 5.0, true);
        distTVParams[3] = speedAmt;
        distTVParams[4] = scrollAmt;
        distTVParams[5] = ofMap(scanLineThickness, 0.0, 1.0, 0.0, 50.0);
        distTVParams[6] = scanLineThickness;
        distTVParams[7] = scanlineOffset;
        
        distTVNames[0] = "noiseLevel";
        distTVNames[1] = "distortion1";
        distTVNames[2] = "distortion2";
        distTVNames[3] = "speed";
        distTVNames[4] = "scroll";
        distTVNames[5] = "scanLineThickness";
        distTVNames[6] = "scanLineIntensity";
        distTVNames[7] = "scanLineOffset";
        
        for (int i = 0; i < distTVNames.size(); i++) {

        chain.getShader(paramFileName)->setUniform<float>(distTVNames[i], distTVParams[i]);
            
        }
        
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }
}

float Shader::getDistortedTvParam(int parameterIndex) {
    
    if (shaderDistortTvPass && parameterIndex <= distTVParams.size()) {
        
        return distTVParams[parameterIndex];
        
    }
    
    if (!shaderDistortTvPass) {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
    
    } else if (parameterIndex > distTVParams.size()) {
     
        ofLog(OF_LOG_NOTICE, paraIndexWarning);
    }
}

void Shader::setWaves(float distAmt, float freqAmt, float speedAmt) {
    
    if(shaderWavesPass) {
    string paramFileName = "videowave";
    string param1 = "distortion";
    string param2 = "frequency";
    string param3 = "speed";
    
    wavesDist = ofMap(distAmt, 0.0, 1.0, 0.0, 5.0, true);
    frequencyDist = ofMap(freqAmt, 0.0, 1.0, 0.0, 5.0, true);
    speedDist = speedAmt;
    
    chain.getShader(paramFileName)->setUniform<float>(param1, wavesDist);
    chain.getShader(paramFileName)->setUniform<float>(param2, frequencyDist);
    chain.getShader(paramFileName)->setUniform<float>(param3, speedDist);
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }
    
}

float Shader::getWavesParam(int parameterIndex) {
    
    if (shaderWavesPass) {
        
        switch (parameterIndex) {
            case 0:
                return wavesDist;
                break;
            case 1:
                return frequencyDist;
                break;
            case 2:
                return speedDist;
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }
}

void Shader::setTwirl(float radius, float amt, ofVec2f center) {
    
    if (shaderTwirlPass) {
    string paramFileName = "Twirl";
    string param1 = "radius";
    string param2 = "amount";
    string param3 = "center";
    
    radiusTwirl = radius;
    amtTwirl = ofMap(amt, 0.0, 1.0, -10.0, 10.0, true);
    centerTwirl = center;
    
    chain.getShader(paramFileName)->setUniform<float>(param1, radiusTwirl);
    chain.getShader(paramFileName)->setUniform<float>(param2, amtTwirl);
    chain.getShader(paramFileName)->setUniform<ofVec2f>(param3, centerTwirl);

    } else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
    }
}

float Shader::getTwirlParam(int parameterIndex) {
    
    if (shaderTwirlPass) {
        
        switch (parameterIndex) {
            case 0:
                return radiusTwirl;
                break;
            case 1:
                return amtTwirl;
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }
    
}

void Shader::setExposure(float evAmt) {
    
    if (shaderExposurePass) {
        
        string paramFileName = "Exposure Adjust";
        string param1 = "inputEV";
        
        ev = ofMap(evAmt, 0.0, 1.0, -10.0, 10.0, true);
      
        chain.getShader(paramFileName)->setUniform<float>(param1, evAmt);
        
        
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }
    
}

void Shader::setColorAdjust(float brightAmt, float contrastAmt, float hueAmt, float saturationAmt) {
    
    if (shaderColorAdjustPass) {
        
        string paramFileName = "Color Controls";
        string param1 = "bright";
        string param2 = "contrast";
        string param3 = "hue";
        string param4 = "saturation";
        
        bright = ofMap(brightAmt, 0.0, 1.0, -1.0, 1.0, true);
        contrast = ofMap(contrastAmt, 0.0, 1.0, -4.0, 4.0, true);
        hue = ofMap(hueAmt, 0.0, 1.0, -1.0, 1.0, true);
        saturation = ofMap(saturationAmt, 0.0, 1.0, 0.0, 4.0, true);
        

    chain.getShader(paramFileName)->setUniform<float>(param1, bright);
    chain.getShader(paramFileName)->setUniform<float>(param2, contrast);
    chain.getShader(paramFileName)->setUniform<float>(param3, hue);
    chain.getShader(paramFileName)->setUniform<float>(param4, saturation);
        
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }
}

float Shader::getColorAdjustParam(int parameterIndex) {
    
    if (shaderColorAdjustPass) {
        
        switch (parameterIndex) {
            case 0:
                return bright;
                break;
            case 1:
                return contrast;
                break;
            case 2:
                return hue;
                break;
            case 3:
                return saturation;
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }
}

void Shader::setChromaZoom(float zoom, float r, float g, float b, ofVec2f pos) {
    
    if (shaderChromaZoomPass) {
        
        string paramFileName = "Chroma Zoom";
        
        chromaNames[0] = "master_zoom";
        chromaNames[1] = "red_zoom";
        chromaNames[2] = "green_zoom";
        chromaNames[3] = "blue_zoom";
        
        chromaParams[0] = ofMap(zoom, 0.0, 1.0, 0.0, 2.0, true);
        chromaParams[1] = ofMap(r, 0.0, 1.0, 1.0, 1.5, true);
        chromaParams[2] = ofMap(g, 0.0, 1.0, 1.0, 1.5, true);
        chromaParams[3] = ofMap(b, 0.0, 1.0, 1.0, 1.5, true);
        
    
        for (int i = 0; i < chromaParams.size(); i++) {
            
            chain.getShader(paramFileName)->setUniform<float>(chromaNames[i], chromaParams[i]);
            }
        
        string parameter5 = "center";
        chromaPos = pos;
        chain.getShader(paramFileName)->setUniform<ofVec2f>(parameter5, pos);
        
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }

}

float Shader::getChromaZoomParam(int parameterIndex) {
    
    if (shaderChromaZoomPass) {
        
        switch (parameterIndex) {
            case 0:
                return chromaParams[0];
                break;
            case 1:
                return chromaParams[1];
                break;
            case 2:
                return chromaParams[2];
                break;
            case 3:
                return chromaParams[3];
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }
}

void Shader::setShake(float magAmt, float rotationAmt, float intensityAmt) {
    
    if (shaderShakePass) {
        
        string paramFileName = "quake";
        
        string param1 = "magnitude";
        string param2 = "rotation";
        string param3 = "intensity";
        
        mag = ofMap(magAmt, 0.0, 1.0, 0.0, 2.0, true);
        rotation = rotationAmt;
        intensity = intensityAmt;
        
        chain.getShader(paramFileName)->setUniform<float>(param1, mag);
        chain.getShader(paramFileName)->setUniform<float>(param2, rotation);
        chain.getShader(paramFileName)->setUniform<float>(param3, intensity);
    
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }
}
float Shader::getShakeParam(int parameterIndex) {
    
    if (shaderShakePass) {
        
        switch (parameterIndex) {
            case 0:
                return mag;
                break;
            case 1:
                return rotation;
                break;
            case 2:
                return intensity;
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }
}

void Shader::setConverge(float horzMagAmt,float vertMagAmt,float colorMagAmt) {
    
    if (shaderConvergePass) {
        
        string paramFileName = "Convergence";
        string param1 = "horizontal_magnitude";
        string param2 = "vertical_magnitude";
        string param3 = "color_magnitude";
        
        horzMag = horzMagAmt;
        vertMag = vertMagAmt;
        colorMag = ofMap(colorMagAmt, 0.0, 1.0, 0.0, 2.0, true);
        
        chain.getShader(paramFileName)->setUniform<float>(param1, horzMag);
        chain.getShader(paramFileName)->setUniform<float>(param2, vertMag);
        chain.getShader(paramFileName)->setUniform<float>(param3, colorMag);

        
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
    }
}

float Shader::getConvergeParam(int parameterIndex) {
        
        if (shaderConvergePass) {
            
            switch (parameterIndex) {
                case 0:
                    return horzMag;
                    break;
                case 1:
                    return vertMag;
                    break;
                case 2:
                    return colorMag;
                    break;
                default:
                    ofLog(OF_LOG_NOTICE, paraIndexWarning);
                    break;
            }
            
        }   else {
            
            ofLog(OF_LOG_NOTICE, loadWarning);
            
        }
}

void Shader::setGlitchShift(float size, float horizontal, float vertical, ofVec2f offset) {
    
    if (shaderGlitchPass) {
        
        string paramFileName = "Glitch Shifter";
        string param1 = "glitch_size";
        string param2 = "glitch_horizontal";
        string param3 = "glitch_vertical";
        string param4 = "offset";
        
        glitchSize = ofMap(size, 0.0, 1.0, 0.0, 0.5, true);
        glitchHorz = horizontal;
        glitchVert = vertical;
        glitchOffset = offset;
        
        chain.getShader(paramFileName)->setUniform<float>(param1, glitchSize);
        chain.getShader(paramFileName)->setUniform<float>(param2, glitchHorz);
        chain.getShader(paramFileName)->setUniform<float>(param3, glitchVert);
        chain.getShader(paramFileName)->setUniform<ofVec2f>(param4, glitchOffset);
        
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
    }
}

float Shader::getGlitchShift(int parameterIndex) {
    
    
    if (shaderConvergePass) {
        
        switch (parameterIndex) {
            case 0:
                return glitchSize;
                break;
            case 1:
                return glitchHorz;
                break;
            case 2:
                return glitchVert;
                break;
            default:
                ofLog(OF_LOG_NOTICE, paraIndexWarning);
                break;
        }
        
    }   else {
        
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }

}


void Shader::setBlur(float amt) {
    
    if (shaderBlurPass) {
   
        string paramFileName = "isf-test";
        string paramSettingName = "blurAmount";
        blurAmt = ofMap(amt, 0.0, 1.0, 0.0, 1.0, true);
        chain.getShader(paramFileName)->setUniform<float>(paramSettingName, blurAmt);
    
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }
}

float Shader::getBlurParam(int parameterIndex) {
    
    if (shaderBlurPass) {
        
    switch (parameterIndex) {
        case 0:
            return blurAmt;
            break;
        default:
            ofLog(OF_LOG_NOTICE, paraIndexWarning);
            break;
    }
        
    }   else {
     
        ofLog(OF_LOG_NOTICE, loadWarning);
        
    }

}


void Shader::setVHS( bool autoScan, float xScanLine, float yScanLine, float xScanLineSize, float yScanLineAmt, float grainLevel, bool scanFollow, float analogDist, float bleed, float bleedRange) {
    
    if (shaderVHSPass) {
        
        string paramFileName = "VHS Glitch";
        
        vhsNames[0] = "autoScan";
        vhsNames[1] = "xScanline";
        vhsNames[2] = "yScanline";
        vhsNames[3] = "xScanlineSize";
        vhsNames[4] = "yScanlineAmount";
        vhsNames[5] = "grainLevel";
        vhsNames[6] = "scanFollow";
        vhsNames[7] = "analogDistort";
        vhsNames[8] = "bleedAmount";
        vhsNames[9] = "bleedRange";
        
        
        scanToggle = autoScan;
        chain.getShader(paramFileName)->setUniform<bool>(vhsNames[0], scanToggle);
        
        shaderVHS_params[1] = xScanLine;
        shaderVHS_params[2] = yScanLine;
        shaderVHS_params[3] = xScanLineSize;
        shaderVHS_params[4] = ofMap(yScanLineAmt, 0.0, 1.0, -1.0, 1.0, true);
        shaderVHS_params[5] = ofMap(grainLevel, 0.0, 1.0, 0.0, 3.0, true);
        
        for (int i = 1; i < 6; i++) {
            
            chain.getShader(paramFileName)->setUniform<float>(vhsNames[i], shaderVHS_params[i]);
            
        }
        
        scanFollowToggle = scanFollow;
        chain.getShader(paramFileName)->setUniform<bool>(vhsNames[6], scanFollowToggle);
        
        shaderVHS_params[6] = ofMap(analogDist, 0.0, 1.0, 0.0, 10.0, true);
        shaderVHS_params[7] = ofMap(bleed, 0.0, 1.0, 0.0, 5.0, true);
        shaderVHS_params[8] = ofMap(bleedRange, 0.0, 1.0, 0.0, 2.0, true);
        
        for (int i = 7; i < 10; i++) {
            
            chain.getShader(paramFileName)->setUniform<float>(vhsNames[i], shaderVHS_params[i - 1]);

        }

        //Note: couldn't figure out why the ISF type Color doesn't match a ofVec4f//
//        shaderVHS_colors[0] = colorBleedL;
//        shaderVHS_colors[1] = colorBleedC;
//        shaderVHS_colors[2] = colorBleedR;
//        
//        
//        chain.getShader(paramFileName)->setUniform<ofVec4f>(vhsNames[10], shaderVHS_colors[0]);
//        chain.getShader(paramFileName)->setUniform<ofVec4f>(vhsNames[11], shaderVHS_colors[1]);
//        chain.getShader(paramFileName)->setUniform<ofVec4f>(vhsNames[12], shaderVHS_colors[2]);
//        
        
    } else {
        
        ofLog(OF_LOG_WARNING, loadWarning);
        
    }
}






