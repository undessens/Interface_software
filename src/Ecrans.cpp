//
//  Ecrans.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 14/01/14.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//

#include "Ecrans.h"

Ecran::Ecran(int number,vector<ofVec3f> vert,int * scrwin, int * scrhin,bool isBlob):number(number){

    scrw = scrwin;
    scrh = scrhin;
    vertices.setName("vertices");
    if(!isBlob){vertices.setSerializable(true);};
    for (int i = 0 ; i < vert.size();i++){
         
        vl.push_back(new ofParameter<ofVec3f>());
        if(isBlob) vl.back()->set(vert[i]/ofVec2f(320,240));
        else vl.back()->set(vert[i]);
        vl.back()->setName("p"+ofToString(i));
        vl.back()->setMin(ofVec3f(0));
        vl.back()->setMax(ofVec3f(1));
//        vertices.add(*vl.back());
        
    
    }
    
    settings.setName("screen"+ofToString(number));
//    settings.add(vertices);
    
    
    calcRectMax();
    
#ifdef HOMOGRAPHY
    screenWarp=Warp();
    screenWarp.setSrc(ofPoint(0,0), ofPoint(rectMax.width,0), ofPoint(rectMax.width,rectMax.height), ofPoint(0,rectMax.height));
    ofVec2f scale(*scrw,*scrh);
    if(vert.size()!=4);//ofLogWarning("more/less than 4 vertices for screen : "+ofToString(number));
    else screenWarp.setDst(vert[0]*scale,vert[1]*scale,vert[2]*scale, vert[3]*scale);
    
    screenWarp.updateMatrix();
#endif

//    createMask();
}




vector<ofVec3f> Ecran::getVerticesNorm(){
    vector<ofVec3f> res;
    for (std::list<ofParameter<ofVec3f> *>::iterator vv(vl.begin()); vv !=  vl.end(); ++vv){
        res.push_back(**vv);
    }
    return res;
}

vector<ofVec3f> Ecran::getVertices(){
    vector<ofVec3f> res;
    ofVec2f scale(*scrw,*scrh);
    for (std::list<ofParameter<ofVec3f> *>::iterator vv(vl.begin()); vv !=  vl.end(); ++vv){
        
        res.push_back(**vv );
//        cout<<vertices.getName()+ofToString((**vv).get().x)<<endl;
    }
    for (int i = 0 ; i< res.size();i++){
        res[i]*=scale;
    }
    return res;
}


void Ecran::updateMatrix(ofVec3f & dummy){
    vector<ofVec3f> vert = getVertices();
    calcRectMax();
    screenWarp.setSrc(ofPoint(0,0), ofPoint(rectMax.width,0), ofPoint(rectMax.width,rectMax.height), ofPoint(0,rectMax.height));
    screenWarp.setDst(vert[0],vert[1],vert[2], vert[3]);
    screenWarp.updateMatrix();
    
    miniScreenWarp.setSrc(ofPoint(0,0), ofPoint(miniRectMax.width,0), ofPoint(miniRectMax.width,miniRectMax.height), ofPoint(0,miniRectMax.height));
    miniScreenWarp.setDst(miniScale *vert[0],miniScale*vert[1],miniScale*vert[2], miniScale*vert[3]);
    miniScreenWarp.updateMatrix();
//    calcRectMax();
    
}


void Ecran::registerParams(){
    
    for(std::list<ofParameter<ofVec3f>*>::iterator vv(vl.begin()); vv !=  vl.end(); ++vv){
        (*vv)->removeListener(this,&Ecran::updateMatrix);
    }
    
    vertices.clear();
    vertices.setName("vertices");
    
    for (std::list<ofParameter<ofVec3f>* >::iterator vv(vl.begin()); vv !=  vl.end(); ++vv){
        (*vv)->setSerializable(true);
        vertices.add(**vv);
        if(vl.size()==4){
            (*vv)->addListener(this,&Ecran::updateMatrix);
        }
    }
    settings.setName("screen"+ofToString(number));
    settings.add(vertices);
}

void Ecran::calcRectMax(){
    int minX = 99999;
    int minY = 99999;
    
    int maxX = -99999;
    int maxY = -99999;
    
    miniScale = ofVec2f(320.0/(*scrw),240.0/(*scrh));
    vector<ofVec3f> vert = getVertices();
    for( int i = 0 ; i<  vert.size() ; i++ ){
        ofVec3f tmp = vert[i];
        if(tmp.x<minX){minX = tmp.x;}
        else if(tmp.x>maxX){maxX = tmp.x;}
        
        if(tmp.y<minY){minY = tmp.y;}
        else if(tmp.y>maxY){maxY = tmp.y;}
    }
    miniRectMax = ofRectangle(minX*miniScale.x, minY*miniScale.y, (maxX-minX)*miniScale.x, (maxY-minY)*miniScale.y);

    rectMax = ofRectangle(minX, minY, maxX-minX, maxY-minY);
    }

