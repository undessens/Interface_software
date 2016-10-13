//
//  drawBlob.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 02/03/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "VisuHandler.h"




class drawBlob:public VisuClass{
public:
    
    drawBlob(VisuHandler * v);
    ~drawBlob(){};
    
    

    ofParameter<ofVec3f> pos,color;
    ofParameter<ofVec2f> scale;
    ofParameter<bool> invertx,inverty;
    ofParameter<float> alpha;
    
    ofParameter<float> alphapos;
    

    ofParameter<bool> drawZones,isMasking;

    void draw(int w, int h);
    void update(int w, int h);
    
    ofVec3f realPos;
    vector<ofPath> paths;
    
    int lastScreenN;
    
    
    
};







