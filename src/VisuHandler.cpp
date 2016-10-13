//
//  VisuHandler.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 14/08/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//


#define MAXSCREENUNION 5

#include "VisuHandler.h"

VisuHandler::VisuHandler(){
    
    
}


void VisuHandler::setup(AttrCtl *attrctl,BlobHandler* bHin, int inwin, int inhin, int zdepthin, int * scrwin, int * scrhin,ScreenHandler * sHin){
    
    
    allParams.clear();
    allParams.setName("Visu");
    
    
    zdepth = zdepthin;
    inw=inwin;
    inh= inhin;
    scrw=scrwin;
    scrh=scrhin;
    beat=0;
    attr = attrctl;
    
    //    sharedImg.push_back(ofImage("images/background.png"));
    
    
    sH = sHin;
    
    bH = bHin;
    
    
    
    
    
    
}




VisuClass * VisuHandler::get(const string & name){
    for (int i = 0; i< visuList.size() ; i++){
        if(visuList[i]->settings.getName()==name) return visuList[i];
    }
    
    return NULL;  
}



void VisuHandler::update(){
    
//    sH->updateBlobScreens(bH->blobs);
    
    for(int i = 0;i<visuList.size();i++){
        if((visuList[i]->isActive||visuList[i]->isPiping)&&!visuList[i]->isHighFPS){
            ofRectangle curS = sH->rectOfScreen(visuList[i]->screenN);
            visuList[i]->update(curS.width,curS.height);
        }
    }
    
    
}


void VisuHandler::updateHighFPS(){
    
    
    for(int i = 0;i<visuList.size();i++){
        if(visuList[i]->isActive&&visuList[i]->isHighFPS){
            ofRectangle curS = sH->rectOfScreen(visuList[i]->screenN);
            visuList[i]->update(curS.width,curS.height);
        }
    }
    
    
}




ofImage * VisuHandler::getSharedImg(int i){
    if(i>sharedImg.size())return;
    return &sharedImg[i];
}



void VisuHandler::registerParams(){
    bH->registerParams();
    attr->registerParam();
    
    
    
    for(int i = 0 ; i< visuList.size();i++){
        visuList[i]->registerParam();
        allParams.add(visuList[i]->settings);
    }
    
    
    
}


const void VisuHandler::printallp(ofParameterGroup p){
    for (int i = 0 ; i<p.size();i++){
        cout<<p[i].getName()+ofToString(i)<<endl;
        if(p.type()==typeid(ofParameterGroup).name()){
            printallp(p);
            
            
        }
    } 
}

void VisuHandler::setupData(){
     pipePP.allocate(inw, inh);
    for (int i = 0 ; i< visuList.size() ; i++){
        visuList[i]->setupData();
    }
}

const void VisuHandler::draw(int mode){
    
    
    
    ofSetColor(255,255,255,255);
    for (int i = 0 ; i<visuList.size();i++){
        
        ofPushMatrix();
        ofPushView();
        ofPushStyle();
        
        if(mode==0)ofTranslate(0,0,zdepth/2);
        
        bool isOk = false;
        
        if(!visuList[i]->isMasking){
            switch (mode){
                case 0:
                    if(visuList[i]->isActive){isOk=true;}
                    break;
                    
                case 1:
                    if(visuList[i]->isPiping){ isOk=true;}
                    break;
                default:
                    break;
                    
            }      
            
        }
        else if (mode == 2) {isOk=true;}
        
        
        if(isOk){
            int validScreen = sH->getValidScreen(visuList[i]->screenN);
            if(validScreen>=0){
                if(mode!=2)ofEnableAlphaBlending();
                if(mode == 1)ofDisableAlphaBlending();
                if(visuList[i]->recopy){
                    int curn = validScreen%10;
                    do{
                        ofRectangle curR;                      
                        
                            if(mode == 1){
                                curR=sH->screenL[curn]->miniRectMax;  
                                 if (visuList[i]->isMapping) sH->screenL[curn]->miniScreenWarp.loadMat();
                            }
                            else{
                                curR = sH->screenL[curn]->rectMax;
                            if (visuList[i]->isMapping) sH->screenL[curn]->screenWarp.loadMat();   
                            }
                        if(!visuList[i]->isMapping) ofTranslate(curR.x,curR.y);
                        
                        visuList[i]->draw(curR.width,curR.height);
                        
                        if (visuList[i]->isMapping){
                            if (mode == 1){
                             sH->screenL[curn]->miniScreenWarp.unloadMat();      
                            }
                            else{
                               sH->screenL[curn]->screenWarp.unloadMat();  
                            }
                        }
                        else ofTranslate(-curR.x,-curR.y);
                        validScreen/=10;
                        curn = validScreen%10;
                    }while (curn>0);
                    
                }
                else{
                    
                    ofRectangle curR = sH->rectOfScreen(validScreen);
                    if (visuList[i]->isMapping&&validScreen<sH->screenL.size())
                        {if(mode == 1){sH->screenL[validScreen]->screenWarp.loadMat();}
                    else{sH->screenL[validScreen]->miniScreenWarp.loadMat();}
                    }
                    else ofTranslate(curR.x,curR.y);
                    
                    visuList[i]->draw(curR.width,curR.height);
                    
                    if (visuList[i]->isMapping&&validScreen<sH->screenL.size())
                        {if(mode == 1){sH->screenL[validScreen]->screenWarp.unloadMat();}
                    else{sH->screenL[validScreen]->miniScreenWarp.unloadMat();}
                    }
                    else ofTranslate(-curR.x,-curR.y);
                    
                }
                
                
            }
            
        }
        ofPopStyle();
        ofPopView();
        ofPopMatrix();
        
        
    }
    
    
    ofSetColor(255);
    
    
    
}

ofParameterGroup * VisuHandler::getParamPtr(){
    return &allParams;
}



void VisuHandler::addVisu(VisuClass * v){
    visuList.push_back(v);
}


void VisuHandler::updateScreenSize(){
    
    
    for (int i = 0 ; i< sH->screenL.size();i++){
        sH->screenL[i]->calcRectMax();
    }
}






