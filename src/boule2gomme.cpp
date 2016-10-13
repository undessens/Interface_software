//
//  boule2gomme.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 04/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "boule2gomme.h"



boule2gomme::boule2gomme(VisuHandler * v):VisuClass(v){
    MYPARAM(drawZones,false,true,false);
    MYPARAM(drawSyphon,false,true,false);
    MYPARAM(drawPipe,false,true,false);
    MYPARAM(drawAttr,false,true,false);

    settings.setName("boule2gomme");
}


void boule2gomme::update(int w, int h){

    
}

void boule2gomme::draw(int w, int h){

    

    ofSetColor(255);
    if(drawSyphon) dad->bH->syphonTex.draw(0,0);
    
    if(drawPipe)dad->pipePP.src->draw(0,0);
    
    if(drawAttr){
        int rayon = 30;
    ofVec2f scale(w,h);

    ofSetColor(255,0,0);
//    ofRect(0,0,w,h);
 
        for (int j = 0 ; j< 3 ; j++){
    vector <ofVec3f> opoints = dad->attr->getType(j,w,h);
    for(int i = 0 ; i<opoints.size();i++){
        ofSetColor(j==0?255:0, j==1?255:0, j==2?255:0);
        ofNoFill();
        ofEllipse(opoints[i],rayon,rayon);
    }
        }
    }
    ofRect(50,50,50,50);

    
    if(drawZones){
            
        for(int i = 0 ; i < dad->attr->zones.size() ; i++){
            ofNoFill();
            ofSetColor(i==0?255:0,i==1?255:0,i==2?255:0);
            ofRectangle rr =dad->attr->zones[i];
            rr.x*=w;
            rr.y*=h;
            rr.scale(w,h);
            ofRect(rr);
        }
    }

    


}
