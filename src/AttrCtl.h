//
//  AttrCtl.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 23/03/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "BlobHandler.h"
#include "ofMain.h"
#include "Constants.h"


#define MAXATTRACTORS 16



class AttrCtl{
    
    public :
    AttrCtl();
    
    void registerParam();

    
    float attrotate;

    bool attrmirorx[3];
    bool attrmirory[3];
    
    
    vector<AttrStruct> lastA;
    vector<AttrStruct> destA;

    vector<AttrStruct> smoothedA;
    vector<AttrStruct> staticA;

    
    
    void addPoints(vector<ofPoint> curcentroids,int type);
    void update();
    void smooth();
    void staticpoints();
    void timedPoints();
    
    void clearPoints();
    void zoneChanged(ofVec4f & dumb);
    
    vector<ofPoint> getType(int f,float w = 1,float h = 1,int zone = 0);
    vector<ofPoint> getAll();
    
    ofParameterGroup settings;
    ofParameter<float> zoffset;
    ofParameter<ofVec4f> zonefamilly3;
    ofParameter<ofVec4f> zonefamilly1;
    ofParameter<ofVec4f> zonefamilly2;
     vector<ofRectangle> zones;
    ofParameter<int> attrmirrorx;
    ofParameter<int> attrmirrory;
    ofParameter<int> attrmirrorz;
    ofParameter<bool> isAttr,invx,invy;

};