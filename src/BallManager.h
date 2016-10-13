//
//  BallManager.h
//  Balls_and_links
//
//  Created by Conil Aurélien on 03/02/2014.
//
//

#ifndef __Balls_and_links__BallManager__
#define __Balls_and_links__BallManager__
#include "VisuHandler.h"
#include <iostream>
#include "ofMain.h"
#include "Balls.h"


class BallManager : public VisuClass
{
    
public:
    
    
    BallManager(VisuHandler * v);

    
    void changeMode(int & m);
    vector<BouncingBall> listOfBalls;
    void update(int w, int h);
    void draw(int w, int h);
    void calcGrid(int w, int h);
    void explosion(int mode);
    void addBall(ofPoint pos, ofPoint speed, ofColor col, float size);
    void setNum(int);
    
    //Polyline
 
    ofPolyline sizedPolyline;
    ofPoint centroidPoly;
    ofVec2f centroidSpeed;
    
    //Width and heigth
    int globalWidth;
    int globalHeight;

    
    //Grid
    bool useGrid;
    int numCol;
    int numRow;
    bool drawGrid;
    
    //Border
    bool useBorder;
    bool useTor;
    
    //Part
    ofImage imgPart;
    bool drawPart;
    
    //Inside - outside
    bool insideMode;
    
    //Die
    int dieMode;
    ofParameter<int> lifeTime;
    
    //particule Emission
    ofParameter<float> emission;
    ofParameter<bool> usePointEmitter;
    ofParameter<ofVec2f> noiseF;
    ofParameter<ofVec2f> emitter;
    ofParameter<int> mode;
    ofParameter<float> gridForce;
    ofParameter<float> userForce;
    ofParameter<float> gridOpen;
    
    
    //Gravity
    ofVec2f gravity;

    
};

#endif /* defined(__Balls_and_links__BallManager__) */



