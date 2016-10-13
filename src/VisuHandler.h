//
//  VisuHandler.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 14/08/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//
#pragma once
//#ifndef VISU_HANDLER
//#define VISU_HANDLER
#ifndef GUIMODE
#define syphon
#endif


#ifdef  syphon
//#include "ofxSyphon.h"
//#include "ofxOpenCv.h"
#endif
#include "ofMain.h"


#include "BlobHandler.h"

#include "AttrCtl.h"
#include "Constants.h"
#include "ofxOscParameterSync.h"

#include "VisuClass.h"
#include "Ecrans.h"
#include "ofXml.h"
#include "EcranHandler.h"



class VisuHandler{
    
    
public:
    
    VisuHandler();
    ~VisuHandler(){FreeClear(visuList);};
    
    
    void addVisu(VisuClass * v);
    void setup(AttrCtl *attrctl,BlobHandler* bHin,int inw,int inh,int zdepthin,int * scrw,int * scrh,ScreenHandler * sH);
    void update();
    void updateHighFPS();
    const void draw(int mode);
    void setupData();
    void registerParams();
    void saveState(string & s);
    void loadState(string & s);
    ofParameterGroup * getParamPtr();
    void updateScreenSize();
    
    VisuClass * get(const string & name);

    void loadScreensPos();
    const void printallp(ofParameterGroup p);
    int zdepth;
    int inw,inh,* scrw,* scrh;
    
    int beat;
    float audioenv;
    bool visufollowcam;
    
    AttrCtl* attr;
    
    
    
    BlobHandler* bH;
    

    
    ScreenHandler * sH;
    
    vector<ofImage> sharedImg;
    ofImage* getSharedImg(int i);
    
    vector<VisuClass*> visuList;
//protected:
    
    ofParameterGroup allParams;
    ofxOscParameterSync paramSync;
    
  
    pingPongBuffer pipePP;


    
};

