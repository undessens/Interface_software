//
//  Balls.h
//  Balls_and_links
//
//  Created by Conil Aurélien on 03/02/2014.
//
//

#ifndef __Balls_and_links__Balls__
#define __Balls_and_links__Balls__


#include <iostream>
#include "ofMain.h"

class BouncingBall
{
    
public:
    
    BouncingBall();
    BouncingBall( ofPoint pos, ofVec2f speed );
    BouncingBall( ofPoint pos, ofVec2f speed , float size, ofColor col, ofImage* img,bool* useGridi,int* numCol,int* numRow,
                 bool* useBorderi, bool* useTori,ofParameter<float>* gridForcei,ofParameter<float>* userForce,ofParameter<float>* gridOpen,
                 bool* insideModei, int* dieMode, int lifeTimein, ofPoint* poly, ofVec2f* speedcentroid, ofVec2f* gravityin );
    
    int update(ofPolyline poly, int w, int h);
    void draw(int w, int h);
    
    ofPoint pos;
    ofPoint origin;
    ofVec2f speed;
    
    ofPoint* centroid;
    ofVec2f* centroidSpeed;
    ofVec2f normal;
    ofColor color;
    
    float size;
    float thresh;
    
    bool bounce;
    
    bool dieAfterBounce;
    bool moveHere( ofPoint pos, ofPoint speed);
    bool isVisible;
    
    //From mother
    //Grid
    bool* useGrid;
    int* numCol;
    int* numRow;
    
    //Border
    bool* useBorder;
    bool* useTor;
    
    //Lock grid
    ofParameter<float>* gridForce;
    ofParameter<float>* userForce;
    ofParameter<float>* gridOpen;
    
    //imageg
    ofImage* imgPart;
    //
    bool* insideMode;
    
    //die
    int * dieMode;
    int lifeTime;
    
    //Gravity
    ofVec2f* gravity;
    
    
};
#endif /* defined(__Balls_and_links__Balls__) */



