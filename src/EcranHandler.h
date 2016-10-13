//
//  EcranHandler.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 06/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#ifndef MurMur_d_Ombre_EcranHandler_h
#define MurMur_d_Ombre_EcranHandler_h
#include "Ecrans.h"
#include "Constants.h"
#include "ofMain.h"
#include "ofxCvBlob.h"
#include "ofxOscParameterSync.h"



class ScreenHandler{
public:  
    
    ScreenHandler();
    ~ScreenHandler(){};
    void setup(int * w, int * h, int z);
    void loadScreensPos();
    void addScreen(vector<ofVec3f> vert);
    void registerParams();
    int getValidScreen(int which);
    void updateBlobScreens(vector<ofxCvBlob> blobs);
    void setupData();
    void loadNewPos(int & p);
    void saveP(bool & s);
    ofRectangle rectOfScreen(int which);
    const ofVec2f sizeOfScreen(const int which);
    void blurmask();
    void drawMask();
    void mapN2S(vector<ofPoint> & p,int s);
    void mapN2S(ofPoint & p,int s);
  
//    void writeFile();
    
    Boolean isEditingScreens;
    
    vector<Ecran *> screenL;
    ofParameterGroup screensParam;
    ofParameterGroup screensCtl;
    ofParameter<int> screenPreset;
    ofParameter<bool> save;
    vector<ofParameter<bool> > mask;
    ofParameter<bool> invertMask;
    
    int * scrw;
    int * scrh;
    int zdepth;
    
    int blobIdx;
    
    ofImage globalMask;
    

    
#ifdef LIVEBLUR
    pingPongBuffer blur;
    ofShader blurX;
    ofShader blurY;
#endif
};

#endif
