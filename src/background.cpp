//
//  background.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 04/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "background.h"



background::background(VisuHandler * v):VisuClass(v){
    MYPARAM(type,0,0,10);
    MYPARAM(followFam,-1,0,3);
    MYPARAM(alpha,0.3f,0.f,1.f);
    MYPARAM(center, ofVec2f(0.5), ofVec2f(-1), ofVec2f(2));
    MYPARAM(color, ofVec4f(255), ofVec4f(0), ofVec4f(255));
    MYPARAM(scale, 1.f,0.f,5.f);
    MYPARAM(ratio, 1.f,0.f,5.f);
    
    MYPARAM(fill,true,false,true);
    settings.setName("background");
    type.addListener(this,&background::typeChanged);
    lastPoint.set(0,0);
    
}

void background::typeChanged(int & i){
    ofDirectory dir("backgrounds");

    if(i>0&&i<dir.listDir())bg.loadImage(dir.getFile(i-1));
}

void background::update(int w, int h){

    
}

void background::draw(int w, int h){
    if(followFam<0)lastPoint.set(0,h/2);
    
    ofFill();
    ofRectangle rect;
    if(fill){
        if(type>0)ofSetColor(bg.getColor(0,0)*ofColor(color.get().x,color.get().y,color.get().z,color.get().w));
        else ofSetColor(color.get().x,color.get().y,color.get().z,color.get().w);
     ofRect(0,0,w,h);
    }
    ofSetColor(color.get().x,color.get().y,color.get().z,color.get().w);
if(followFam<0) rect.setFromCenter(center.get()*ofVec2f(w,h), w*scale, h*scale*ratio);
else{vector<ofVec3f> cur = dad->attr->getType(followFam,w,h);
    if(cur.size()>0){
        lastPoint = cur[0]*alpha + lastPoint*(1.0-alpha);
    }
    rect.setFromCenter(lastPoint*ofVec2f(w,h), w*scale, h*scale*ratio);
}
    if(type>0)
        bg.draw(rect);
    else{
        
        ofRectangle(rect);}
}
