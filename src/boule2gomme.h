//
//  boule2gomme.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 04/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "VisuHandler.h"




class boule2gomme:public VisuClass{
public:
    
    boule2gomme(VisuHandler * v);
    ~boule2gomme(){};
    
    ofParameter<bool> drawZones,drawSyphon,drawPipe,drawAttr;

    
    void draw(int w, int h);
    void update(int w, int h);
    
    
};




