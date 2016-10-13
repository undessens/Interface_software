//
//  Ecrans.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 14/01/14.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "ofMain.h"
#define HOMOGRAPHY
#ifdef HOMOGRAPHY

#include "Warp.h"
#endif

#include "Constants.h"

class Ecran{
public:
    Ecran(){};
    Ecran(int number,vector<ofVec3f> vert, int * scrw,int * scrh,bool isBlob);
    ~Ecran(){FreeClear(vl);};
    
    void calcRectMax();
    void registerParams();
    void updateMatrix(ofVec3f & dummy);
    
    vector<ofVec3f> getVertices();
    vector<ofVec3f> getVerticesNorm();
    int * scrw;
    int * scrh;
    int number;
    ofParameterGroup settings;
    
    ofParameterGroup vertices;
    list<ofParameter<ofVec3f> *> vl;
    ofRectangle rectMax,miniRectMax;
    ofVec2f miniScale;
    
//    ofImage mask;
#ifdef HOMOGRAPHY
    Warp screenWarp;
    Warp miniScreenWarp;
#endif
    
};
