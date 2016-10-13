//
//  Particles.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 04/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "VisuHandler.h"
#include "drawBlob.h"
#define PVISU
#define PIMG
//#define PFBO


#define PMOD

#ifdef PMOD
//#include "ofxAssimpModelLoader.h"

#endif



class Force {
    
public:
    Force();
    Force(string namein,bool isAttr=false);
    ~Force(){
//        FreeClear(pl);
    };
    
    void updateShader();
    ofShader getShader();
    
    string name;
    ofParameterGroup settings;
    vector<ofAbstractParameter *> pl;
    ofShader shader;
    ofParameter<bool> isActive;
    ofParameter<int> attrFamilly,attrZone;
    template<typename ParameterType>
    void addParameter(string name,ParameterType v,ParameterType min,ParameterType max);

};


class Particles:public VisuClass{
public:
//    Particles();
    Particles(VisuHandler * v);
    ~Particles(){
        FreeClear(forces);
        ofLogVerbose("derived destruction : " + ofToString(settings.getName()));
    };
    
    vector<Force *> forces;
   

    void setup();
    void draw(int w,int h);
    void update(int w, int h);
    
    void registerParam();
    void changeGrad(int & i);

#ifdef PFBO
    ofFbo finaldraw;
#endif
//    ofFbo distance;
#ifdef PIMG
    ofImage partImg;
#endif

    
    
    void initFbo();
    void initFbo(int w, int h);
    void changeNum(int & num);
    void setupData();

#ifdef PMOD
    vector<ofPoint> readObj(string path,bool sort = false);
    void changeOrigins(int & type);
    ofParameter<int> origintype;
#endif
    int lastw,lasth;
    
    ofFbo origins;
    ofShader updatePos;
    ofShader updateRender;

    ofParameter<float>      timeStep;

    ofParameter<int>        numParticles ;
    pingPongBuffer          velPingPong;
    pingPongBuffer          posPingPong;
    
    
    ofParameter<float>      particleSize;
    ofParameter<float>      alphaparticle;
    ofParameter<ofVec3f>    partcolor;
    ofParameter<int>        gradtype;
    ofParameter<float>      mingrad;
    ofParameter<float>      maxgrad;
    ofParameter<int>        gradNum;
    ofParameter<bool> map2blob;
    
    
    int lastnumParticles;
    
    
    int textureRes;
    ofVec2f  textureRes2;
    int textureRes3;
    
    ofImage gradient;
    bool noReset;
    

    
};







template<typename ParameterType>
void Force::addParameter(string name,ParameterType v,ParameterType min,ParameterType max){
    ofParameter<ParameterType> * p = new ofParameter<ParameterType>();
    p->setName(name);
    p->setMin(min);
    p->setMax(max);
    *p=v;
//    cout<<p->type()<<endl;
    settings.add(*p);
    pl.push_back(p);
}





