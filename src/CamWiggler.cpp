//
//  CamWiggler.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 29/08/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#include "CamWiggler.h"


CamWiggler::CamWiggler(){
    amplitude = 65;
    damp=7;
    zoomdamp=50;
    zoomamplitude = 0;
    frequency=5;
    isWiggling=false;
    iszWiggling=false;
    speedPhase=0;
    randPhase=0;
    x=0;
    y=0;
    z=1;
    
    
    
}

void CamWiggler::update(int beat){
    if(beat>0&&isWiggling==false){//&&iszWiggling==false){
        isWiggling=true;
        iszWiggling=true;
        sourcetime=ofGetElapsedTimeMillis();
        randPhase = ofRandom(360)*(2*PI)/360;
        
    }
    
    if(isWiggling||iszWiggling){
        float t=(ofGetElapsedTimeMillis()-sourcetime)/1000.0;
        float amp = amplitude * (1.0-(t*1.0*damp)*(t*1.0*damp));// amplitude*(1.0/(t*damp+1));
        float zoomamp = zoomamplitude * (1.0-t*zoomdamp);
        x=amp*sin(2.0*PI*frequency*(t+randPhase));
        y=amp*cos(2.0*PI*frequency*(t*(1+speedPhase)+randPhase));//+ofRandom(randPhase))));
        z=1.0+zoomamp*sin(2.0*PI*frequency*t);
        if(amp<1){
            x=0;
            y=0;
            isWiggling=false;
        }
        if(zoomamp<0.01){
            z=1;
            iszWiggling=false;
        }
    }
    
}
