//
//  CamWiggler.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 29/08/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//
#pragma once
#include "ofMain.h"

class CamWiggler {
public:
    CamWiggler();
    float amplitude;
    float frequency;
    float damp;
    float zoomdamp;
    float zoomamplitude;
    float randPhase;
    float speedPhase; 
    bool isWiggling;
    bool iszWiggling;
    int sourcetime;
    
    
    int x;
    int y;
    float z;
    
    
    void update(int beat);
    
};
