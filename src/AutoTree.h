//
//  AutoTree.h
//  MursMurentDombres
//
//  Created by Aurélien Conil on 16/08/13.
//
//

#ifndef __MursMurentDombres__AutoTree__
#define __MursMurentDombres__AutoTree__
#include "VisuHandler.h"


#include <iostream>
#include "ofMain.h"
#include <vector.h>

class Branche{
    
    
public:
    
    Branche();
    Branche( ofPoint b, float a, int l, int total, bool isClock, ofImage* img);
    
    ofPoint begin;
    ofPoint end;
    float angle;
    float length;
    float finalLength;
    int totalLength;
    
    void draw();
    void update(ofPolyline poly, bool mode);
    
    bool isGrowing;
    bool isChildCreated;
    float lifeTime;
    
    int lastTimeBouncing;
    
    bool clockWise;
    
    ofImage* leaf;
    
    
};

//------------------------- Animation principale -----------------------


class AutoTree : public VisuClass{
public:
    AutoTree();
    AutoTree(VisuHandler * v);
    AutoTree(int w, int h, bool autostart, ofPath* pathin);
    
    void update(int w, int h);
    void draw(int w, int h);
    void setupData();
    
    void createBranche(ofPoint p, float a, int l,int tot,  bool isEnd);
    void resetAll( bool &isReset);
    void startStop(bool & start);
    void init();
    void clear();
    void addNewPoint(bool &newPoint);
    void switchMode(bool &isInside);
    
    vector<Branche> list;
    ofFbo myfbo;
    
    int width, height;
    
    int count;
    int introPhase;
   
    ofImage imagePart;
    
    ofParameter<ofVec2f> pointToBegin;
    ofParameter<bool> initTrig;
    ofParameter<bool> addTrig;
    ofParameter<bool> addPoint;
    ofParameter<bool> debugMode;
    ofParameter<bool> reset;
    ofParameter<bool> insideMode;
    
};



#endif /* defined(__MursMurentDombres__AutoTree__) */
