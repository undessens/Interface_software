

#pragma once
#include "ofMain.h"

class Warp {
public:
    Warp();
    ~Warp();
    
    void setup();
    void setSrc(ofPoint p0,ofPoint p1,ofPoint p2,ofPoint p3);
    void setDst(ofPoint p0,ofPoint p1,ofPoint p2,ofPoint p3);
    
    void loadMat();
    void unloadMat();
    
    void updateMatrix();
    
    void drawControlPoints();

    int isOverCtl(ofPoint p);

        void saveFile(string name);
    void loadFile(string name);
private:
    ofPoint dstPoint[4] ;
    ofPoint srcPoint [4];

    int ctlRadius;
//    ofMatrix4x4 homoMat;
    float * glMat;
};
