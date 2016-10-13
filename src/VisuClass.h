//
//  VisuClass.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 14/01/14.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//


/*
 
 
every thing is in Boule2gomme.cpp / .h thats the Template!!
 
 
 All visu must(!) override
 
     constructor as constr(visuHandler *v):VisuHandler(v){
     ...local init stuff
     
     every parameter must be register in the visu's parametergroup "settings" as follows:
     
    MYPARAM(nom,init,min,max)   cf  Constants.h
   
     }
 
     update(int w, int h) and draw(int w int h) functions
 

 to call visu handler(called dad) objects : e.g dad->attr->curp (attractors)
 
the desired width and height of screen : ofVec2f size = dad->sizeOfScreen(screenN); 
 
 
 Every visu should be in a specified file, their header Reported in VisuWarper.h!
 
 
 their instanciation come in testApp
 
 visuHandler.add (new class...)
 
And that's all
 
 
by defining GUIMODE in constants.h, it creates the control GUI with every parameters
 
 */



#pragma once
#include "string.h"
#include "ofxOsc.h"
#include "Constants.h"

class VisuHandler;


class VisuClass{
    
public:
    VisuClass();
    virtual ~VisuClass(){ofLogVerbose("base visu destructor");};
    VisuClass(VisuHandler *vh);
    
    void updateVh(VisuHandler* vh);
    virtual void update(int w, int h)=0;
    virtual void draw(int w, int h)=0;
    virtual void registerParam(){};
    virtual void setupData(){};
//    virtual void oscUpdate(ofxOscMessage &m)=0;

    

    ofParameter<int> screenN;
    ofParameter<bool> isActive;
    ofParameter<bool> isMapping;
    ofParameter<bool> recopy;
    ofParameter<bool> isPiping,isMasking;
    
    VisuHandler *dad;
    ofParameterGroup settings;
    bool isHighFPS;
    ofReadOnlyParameter<int, int> beat;
    
    
    
    
};