//
//  Liner.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 04/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "Liner.h"



Liner::Liner(VisuHandler * v):VisuClass(v){
    
    MYPARAM(width,2.f,0.f,10.f);
    MYPARAM(steps,10,1,100);
    MYPARAM(drawCentr, true,false,true);
    MYPARAM(rotAngle,0.f,0.f,5.f);
    MYPARAM(color,ofVec3f(255),ofVec3f(0),ofVec3f(255));
    MYPARAM(alpha,0,0,255);
    settings.setName("Liner");
}


void Liner::update(int w, int h){

    
}

void Liner::draw(int w, int h){

    
    
    vector<ofPolyline> b = dad->bH->getBlobs(w,h);
    ofSetColor(color->x,color->y,color->z,alpha);
    ofSetLineWidth(width);
    for (int i = 0 ; i < b.size(); i ++){
        ofPushMatrix();
        ofPoint centr = b[i].getCentroid2D();
        ofTranslate(centr.x,0);
        
        for (int j = 0 ; j < b[i].size() ; j++){
            
            ofRotateY(3*360*rotAngle/b[i].size());
            
            ofLine(b[i][j]-ofVec2f(centr.x,0),b[i][(j+steps)%(b[i].size())]-ofVec2f(centr.x,0));
            
            if(drawCentr)ofLine(b[i][j]-ofVec2f(centr.x,0),ofVec3f(0,centr.y));
        }
        ofPopMatrix();
    }

}
