//
//  BlobHandler.h
//  MurMur d'Ombre
//
//  Created by martin hermant on 17/02/14.
//
//

#pragma once

#include "EcranHandler.h"
#include "ofxOpenCv.h"
#include "ofxSyphon.h"
#include "Constants.h"
#include "ofMain.h"


class BlobHandler{
    
public:
    
    BlobHandler(){};
    
    
    void setup(int inwin, int inhin,ScreenHandler * sH);
    
    
//    void computePoly();
    void update();
//    void blurblob();
    void compBlob();
    void registerParams();
    void compCache();
    void setupData(ofShader* blurXin,ofShader * blurYin);
    vector<ofVec3f> compCentroid(float w=1,float h=1);
    vector<ofRectangle> compBounds(float w=1, float h=1);
    vector<ofVec3f> compExtrems(float w=1, float h=1);
    
    
    vector<ofPolyline> getBlobs(float w=1,float h=1,bool invx = false,bool invy = false);
    vector<ofPath> getPaths(float w=1,float h = 1,bool invx = false,bool invy = false);

    
    vector<ofVec3f> arms;
    vector<ofVec3f> centroids;
    vector<ofRectangle> boxes;

    int inw,inh;
    
    
    ofxSyphonClient blobClient;
    ofFbo syphonTex;

    ScreenHandler * sH;
    ofShader * blurX;
    ofShader * blurY;
    ofShader threshBW;
    ofxCvContourFinder contourFinder;
    ofPixels pix;

    ofxCvGrayscaleImage gs;
    
    
    vector<ofPolyline> cachedP,lcacheP;

    bool polyCacheDirty;
    int lastw,lasth,lastcw,lastch;
    
    vector<ofxCvBlob> blobs;

    ofParameter<float> vidThreshold;
    ofParameterGroup settings;
    ofParameter<float> minSide, maxSide,maxLengthExtrem;
    ofParameter<int> maxBlobs,polyMaxPoints;
    ofParameter<bool> findHoles,invertBW,invertX,invertY;
    ofParameter<float> simplification,smooth;
    ofParameter<ofVec4f> crop;
    ofParameter<int> screenN;
    ofParameter<ofVec3f> scale,pos;
    ofParameter<bool> isPiping;
};

