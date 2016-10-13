//
//  CamHandler.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 12/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//
#pragma once


#include "ofMain.h"
#include "Constants.h"


class CamHandler{
    
public:
    
    CamHandler(){};
    
    
    void setup(int * scrw,int * scrh,int* zdepth);
    
    
    void begin();
    void end();
    void updateScreenSize(int w, int h);
    void look(ofVec3f & dumb);
    void orbit(ofVec3f & dumb);
    
    ofCamera camera;
    
    

    
    
    ofParameterGroup settings;
    
    ofParameter<float> distance;
    ofParameter<ofVec3f> lookAt;
    ofParameter<ofVec3f> ypr;
    ofParameter<ofVec3f> lookypr;
    ofParameter<bool> isLooking;
    ofVec3f curypr;
    ofVec3f curlookypr;
    
    ofParameter<float> alpha;
    float curdist;
    
    int * zdepth, * scrw, * scrh;
    
};
