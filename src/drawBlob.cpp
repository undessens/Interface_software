//
//  drawBlob.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 02/03/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "drawBlob.h"


drawBlob::drawBlob(VisuHandler * v):VisuClass(v){

    MYPARAM(drawZones,false,false,true);
    MYPARAM(invertx,false,false,true);
    MYPARAM(inverty,false,false,true);

    MYPARAM(pos,ofVec3f(0.5),ofVec3f(0),ofVec3f(1));
    MYPARAM(alphapos,.3f,0.f,1.f);
    MYPARAM(scale,ofVec2f(1),ofVec2f(0),ofVec2f(2));
    MYPARAM(color,ofVec3f(255),ofVec3f(0),ofVec3f(255));
    MYPARAM(alpha,255.f,0.f,255.f);
    
    
    
    settings.setName("drawBlob");
}


void drawBlob::update(int w, int h){
    
    realPos = alphapos*pos+realPos*(1-alphapos);
//    paths = dad->bH->getPaths(w*scale->x , h*scale->y,invertx,inverty);
    lastScreenN = screenN;

    
}

void drawBlob::draw(int w, int h){
    

   

       paths = dad->bH->getPaths(scale->x*w , scale->y*h,invertx,inverty); 
    
    ofPushMatrix();
    
    ofTranslate(w*(realPos.x-scale->x/2.),h*(realPos.y-scale->y/2.), (realPos.z-0.5)*dad->zdepth);
    for(int i  = 0 ; i< paths.size();i++){
        ofPath pp =paths[i];
        /* ************** Attention ************
        TODO COCO
         changement de derniere minute pour afficher 
         la silhouette en noir sans changer
         tout en laissant le silhouette en blanc
         pour l'effet sur les particules a travers le pipe
         
        */
        pp.setFillColor(ofColor(color->x,color->y,color->z,alpha));
        if(pp.getOutline().size()>0 && pp.getOutline()[0].size()>0)
            pp.draw();
    }
    
    
    ofPopMatrix();
    
 }

