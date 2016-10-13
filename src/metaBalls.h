//
//  metaBalls.h
//  MurMur d'Ombre
//
//  Created by martin hermant on 14/02/14.
//
//

#pragma once

#include "ofMain.h"
#include "VisuHandler.h"



class Meta : public ofVec3f{
public:
    Meta(ofPoint p, float r, int lifeTime):ofVec3f(p),rayon(r),lifetime(lifeTime){};
    Meta(ofPoint p, float r, int lifeTime,ofVec3f vin,int modin):ofVec3f(p),rayon(r),lifetime(lifeTime),v(vin),mode(modin){};
    float rayon;
    int lifetime;
    ofVec3f v;
    int mode;

    
    
    
    
};


class metaBalls:public VisuClass{
public:
    
    metaBalls(VisuHandler * v);
    ~metaBalls(){};
    
    void draw(int w, int h);
    void update(int w, int h);
    void setupData();
    
    
    ofParameter<float> rayon,alpha,theta,rIn;
    ofParameter<int> curFamilly,mode;
    ofParameter<ofVec4f> color;
    vector<ofVec3f>  dpoints;
    vector<Meta>  points;
    ofParameter<float> lifeTime,emitrate,noise,noiseR,angle,mass,f;
    ofParameter<bool> drawLines;
    ofParameter<float> maxv;
    ofParameter<float> vInit;
    ofImage metaBall;
    
    unsigned long lastT;
    int maxsize;

    
};







