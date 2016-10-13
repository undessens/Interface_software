//
//  CircleLine.h
//  MurMurDombre
//
//  Created by Conil Aurélien on 25/02/2014.
//
//
//TODO: make it a visuClass

#ifndef __MurMurDombre__CircleLine__
#define __MurMurDombre__CircleLine__

#include <iostream>
#include "ofMain.h"

#endif /* defined(__MurMurDombre__CircleLine__) */

//---------------------------------------------------------------------
//                              Line
//---------------------------------------------------------------------



class movingline
{
public:
    movingline();
    movingline(ofPoint pos, float angle, float t, float length);
    
    int update();    // return 0 if the visual object is dead
    void draw();
    
private:
    
    ofPoint begin;
    ofPoint end;
    float angle;
    float length;
    float maxLength;
    float thickness;
    bool isBlack;
    
    int life, lifeTime;
    
};

//---------------------------------------------------------------------
//                  River of line
//---------------------------------------------------------------------

class lotOfLine
{
public:
    lotOfLine();
    lotOfLine(ofPoint pos, float angle);
    
    void addLine(ofPoint pos, float angle);
    int update( int channel, float argument);
    void draw();
    
    vector<movingline> obj;
    
    
};

//---------------------------------------------------------------------
//                      Animation Generale
//---------------------------------------------------------------------



class CircleLine {
public:
    CircleLine();
    
    CircleLine(vector<ofPoint>* attrin,vector<int>* famillyin, int w, int h);
    void update(int w, int h);
    void draw(int w, int h);

    vector<ofPoint>* attr;
    vector<int>* familly;

    vector<ofPoint> pointToCircle;
    vector<ofPoint> listOfCentroid;
    vector<ofPoint> listOfTop;
    lotOfLine riverOfLine;
    ofPoint linePos;
    bool isLine;
    bool isCircle;
    float angle;
    
    ofFbo myfbo;

};




    