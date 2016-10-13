//
//  Liner.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 04/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "VisuHandler.h"



class Liner:public VisuClass{
public:
    
    Liner(VisuHandler * v);
    ~Liner(){};
    
    void draw(int w, int h);
    void update(int w, int h);
    ofParameter<float> width,alpha;
    ofParameter<int> steps;
    ofParameter<bool> drawCentr;
    ofParameter<float> rotAngle;
    ofParameter<ofVec3f> color;

    
    
};




