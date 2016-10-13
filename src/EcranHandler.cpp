//
//  EcranHandler.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 06/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "EcranHandler.h"


ScreenHandler::ScreenHandler(){
screensParam.setName("screens");
    screenPreset = 0;
    screenPreset.setMin(-1);
    screenPreset.setMax(10);

    screenPreset.setSerializable(false);

    
}

void ScreenHandler::setupData(){
        screenPreset.addListener(this, &ScreenHandler::loadNewPos);
        save.addListener(this, &ScreenHandler::saveP);
#ifdef LIVEBLUR
    blurX.load("","shaders/blurXa.frag");
    blurY.load("","shaders/blurYa.frag");
    blurX.setUniform1f("blurAmnt", 10);
    blurY.setUniform1f("blurAmnt", 10);
    blur.allocate(*scrw,*scrh,GL_RGB32F);
    float * pos = new float[*scrw * *scrh*3];
    for (int x = 0; x < *scrw; x++){
        for (int y = 0; y < *scrh; y++){
            int i = *scrw * y + x;
            
            pos[i*3 + 0] = 0;
            pos[i*3 + 1] = 0;
            pos[i*3 + 2] = 0;
        }
    }
    
    // Load this information in to the FBO´s texture
    blur.src->getTextureReference().loadData(pos, *scrw,*scrh, GL_RGB);
    blur.dst->getTextureReference().loadData(pos, *scrw,*scrh, GL_RGB);
    delete pos;
#endif
}




void ScreenHandler::updateBlobScreens(vector<ofxCvBlob> blobs){
//    int  idx = 0;
//        for (  vector<Ecran *>::iterator it = screenL.begin(); it != screenL.end(); ++it ) {
//            if(idx>blobIdx){  delete * it;}
//            idx++;
//       
//    }
//
//    
//    screenL.resize(blobIdx);
//    for(int i =0; i <blobs.size() ; i++){
//        screenL.push_back(new Ecran(blobIdx+i,blobs[i].pts,scrw,scrh,true));
//        screenL.back()->registerParams();
//    }
    
    
}




void ScreenHandler::setup(int * win, int * hin, int zin){
    scrw=win;
    scrh = hin;
    zdepth=zin;
    screensParam.setName("screens");
    
    

    vector<ofVec3f> vertglob;
    vertglob.push_back(ofVec2f(0,0));
    vertglob.push_back(ofVec2f(1,0));
    vertglob.push_back(ofVec2f(1,1));
    vertglob.push_back(ofVec2f(0,1));
    
    for (int i = 0 ; i< 5 ; i++){
    addScreen(vertglob);
    }

    
    

}

void ScreenHandler::addScreen(vector<ofVec3f> vert){
    screenL.push_back(new Ecran(screenL.size(),vert,scrw,scrh,false));
}

void ScreenHandler::registerParams(){

    screensCtl.clear();
    
    
    screenPreset.setName("screenPreset");
    screenPreset = 0;
    screenPreset.setSerializable(false);
    screensCtl.add(screenPreset);
    
    save.setName("save");
    save=false;
    save.setSerializable(false);
    screensCtl.add(save);
    
    
    invertMask.setName("invertMask");
    invertMask=false;
    screensCtl.add(invertMask);
    
    
    for (int i = 0 ; i < screenL.size() ; i ++ ){
        ofParameter<bool> mask;
        mask.setName("mask"+ofToString(i));
        mask = false;
        screensCtl.add(mask);
    }
    
    
    


    screensCtl.setName("screensCtl");

    
screensParam.clear();
    for(int i = 0 ;i< screenL.size();i++){
        screenL[i]->registerParams();
        screensParam.add(screenL[i]->settings);  
    }
    
    
    screensParam.setName("screens");
    
    
    
    
    int a = 0;
    loadNewPos(a);
}

int ScreenHandler::getValidScreen(int which){
    int k = 1;
    int idx = which%10;
    int res = -1;
    if(which>=0){
    do{

        if(idx<screenL.size()){
            if(res==-1) res = idx;
            else res +=k *idx;
            }
        
        k*=10;
        idx = (which/k) %10;
    }while(idx>0);
    }
    return res;
}

ofRectangle ScreenHandler::rectOfScreen(int which){
int k = 1;
int idx = which%10;
ofRectangle res;

do{
    if(idx<screenL.size()){

        if(k==1)res = screenL[idx]->rectMax;
            else res.growToInclude(screenL[idx]->rectMax);
                }
    idx = (which/(k*10)) %10;
    k++;
}while(idx>0);

return res;

}

const ofVec2f ScreenHandler::sizeOfScreen(const int which){
    ofRectangle tmp = rectOfScreen(which);
    return ofVec2f(tmp.width,tmp.height);
}




void ScreenHandler::drawMask(){
    ofColor curCol;

    if(!invertMask)curCol.set(255);
    else curCol.set(0);
    for (int i = 1 ; i < screenL.size();i++){
        if(screensCtl.getBool("mask"+ofToString(i))){
        ofPath tmpP;
            tmpP.setFillColor(curCol);
        vector<ofVec3f> vert = screenL[i]->getVertices();
        for(int j = 0 ; j<vert.size();j++){
            tmpP.lineTo(vert[j]);
        }
        if(vert.size()>100)tmpP.simplify();
        tmpP.close();
        tmpP.draw();
    }
    }
    
}


void ScreenHandler::mapN2S(vector<ofPoint> & p,int s){
    ofRectangle rr = rectOfScreen(getValidScreen(s));
    for(int i = 0 ; i < p.size();i++){
        
        p[i].x = ofMap(p[i].x,0,1,rr.getMinX()*1.0/(*scrw),rr.getMaxX()*1.0/(*scrw));
        p[i].y = ofMap(p[i].y,0,1,rr.getMinY()*1.0/(*scrh),rr.getMaxY()*1.0/(*scrh));
    }
}
void ScreenHandler::mapN2S(ofPoint & p,int s){
    ofRectangle rr = rectOfScreen(getValidScreen(s));

        
        p.x = ofMap(p.x,0,1,rr.getMinX()*1.0/(*scrw),rr.getMaxX()*1.0/(*scrw));
        p.y = ofMap(p.y,0,1,rr.getMinY()*1.0/(*scrh),rr.getMaxY()*1.0/(*scrh));
    
}



void ScreenHandler::loadNewPos(int & num){

    
        string abspath = ofToDataPath("Xml/pecrans"+ofToString(num)+".xml");
        ofLogWarning("loading screen from local : " + abspath);
        ofXml xml;
        
        xml.load(abspath);
        xml.deserialize(screensParam);
    

 

}
    
void ScreenHandler::saveP(bool & s){
    if(s){
        
        ofFileDialogResult filep = ofSystemSaveDialog("pecrans0.xml","save screen preset");
        
        string abspath =filep.getPath();// ofToDataPath("Xml/pecrans"+ofToString(screenPreset)+".xml");
        ofLogWarning("saving screen local : " + abspath);
        ofXml xml;
        
        
        xml.serialize(screensParam);
        cout << xml.save(abspath) << endl;
    }
}



void ScreenHandler::blurmask(){

}


void ScreenHandler::loadScreensPos(){
    
    
    
    ofXml eS;
    if(eS.load("Xml/pecrans0.xml")){
        ofLogWarning("loading : Xml/pecrans0.xml");
        int nS = eS.getNumChildren();
        vector<ofVec3f> vert;
        
        for (int n = 0 ; n<nS;n++){
            eS.setToChild(n);
            
            int nP = eS.getNumChildren();
            eS.setToChild(0);
            for (int i = 0 ; i<nP;i++){
                ofVec3f curpoint(0,0);
                curpoint.x = eS.getFloatValue("x");
                curpoint.y = eS.getFloatValue("y");
                curpoint.z = eS.getFloatValue("z");
                vert.push_back(curpoint); 
                eS.setToSibling();
            }
            
            addScreen(vert);
            eS.setToParent();
            eS.setToParent();
            vert.clear();
            
        }
    }
    else{
        
        cout<<"No screen Loaded from Xml"<<endl;
        
    }
    
    
    
    //    blurmask();    //delete tmpPath;
    //    blobIdx = screenL.size();
    //    for (int i = 0 ; i < screenL.size() ; i ++ ){
    //        ofParameter<bool> mask;
    //        mask.setName("mask"+ofToString(i));
    //        screensCtl.add(mask);
    //    }
    
}

