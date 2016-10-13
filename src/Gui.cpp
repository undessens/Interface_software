//
//  Gui.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 07/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//



#include "Gui.h"





void Gui::load(ofParameterGroup & pgtmp){

    guiParam.push_back(new ofxPanel());
    guiParam.back()->setDefaultWidth(.98*PARAMW);
    guiParam.back()->setup(pgtmp.getGroup("global"),pgtmp.getGroup("global").getName(),(baseC)*PARAMW);
    
    baseC++;
    int h = guiParam.back()->getHeight() + 10;
    

    guiParam.push_back(new ofxPanel());
    guiParam.back()->setup(pgtmp.getGroup("attrCtl"),pgtmp.getGroup("attrCtl").getName(),(baseC)*PARAMW);
//    guiParam.back()->minimizeAll();
    
    h += guiParam.back()->getHeight() + 10;
    baseC++;
    guiParam.push_back(new ofxPanel());
    guiParam.back()->setup(pgtmp.getGroup("blobsettings"),pgtmp.getGroup("blobsettings").getName(),(baseC)*PARAMW);
//    guiParam.back()->minimizeAll();
    
    h += guiParam.back()->getHeight() + 10;
    baseC++;
    
    guiParam.push_back(new ofxPanel());
    guiParam.back()->setup(pgtmp.getGroup("screensCtl"),pgtmp.getGroup("screensCtl").getName(),(baseC)*PARAMW);
    //    guiParam.back()->minimizeAll();
    
    h += guiParam.back()->getHeight() + 10;
    baseC++;
    
    
    guiScreen.push_back(new ofxPanel());
    guiScreen.back()->setDefaultWidth(ofGetWidth()-30);
    guiScreen.back()->setup(pgtmp.getGroup("screens"),pgtmp.getGroup("screens").getName());
    
    guiScreen.back()->minimizeAll();
    
    
    guiParam.back()->setDefaultWidth(.98*PARAMW);
    
    baseC= 0;
    
    ofParameterGroup pgtmp2 = pgtmp.getGroup("Visu");
    
    
    
    for (int i = 0 ; i< pgtmp2.size();i++){
        int l =  ofGetHeight()/2*int((baseC)*PARAMW/(ofGetWidth()*(4.5/5)));
        int c = PARAMW*((int)(baseC)%(int)(ofGetWidth()/PARAMW));
        
        ofAbstractParameter * p = &pgtmp2.get(i); 
        if(p->type()==typeid(ofParameterGroup).name()){
            guiVisu.push_back(new ofxPanel());
            guiVisu.back()->setup(pgtmp2.getGroup(i),pgtmp2.getName(),c,l);
            guiVisu.back()->minimizeAll();
            guiVisu.back()->getShape();
            baseC++;
    }
    }


}


void Gui::draw(){
    
    if(visuSettings==0){
    for(std::list<ofxPanel*>::iterator ggg = guiParam.begin() ; ggg!=guiParam.end();++ggg){
    (*ggg)->draw();
    }
    }
    else if(visuSettings == 1){
        for(std::list<ofxPanel*>::iterator ggg = guiVisu.begin() ; ggg!=guiVisu.end();++ggg){
            (*ggg)->draw();
        }
    }
    else if(visuSettings == 2){
        for(std::list<ofxPanel*>::iterator ggg = guiScreen.begin() ; ggg!=guiScreen.end();++ggg){
            (*ggg)->draw();
        }

    }
}
