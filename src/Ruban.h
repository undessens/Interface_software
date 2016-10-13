//
//  Ruban.h
//  MursMurentDombres
//
//  Created by Aurélien Conil on 16/08/13.
//
//

#ifndef __MursMurentDombres__Ruban__
#define __MursMurentDombres__Ruban__

//#define OSCSEND

#include <iostream>
#include <vector.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "VisuHandler.h"

//------------------------------------------------------------------------------

class Spring{
    
public:
    
    Spring();
    Spring(float xpos, float ypos, float m, float g, float i, float stiff);
    
    float vx, vy; // The x- and y-axis velocities
    float x, y; // The x- and y-coordinates
    float gravity;
    float mass;
    float initialSize;
    float radius;
    float stiffness;
    float damping;
    
    void update(ofPoint p);
    void draw(ofPoint p);
    
    
    
    
};

//-----------------------------------------------------------------------------

class ruban 
{
public:
    ruban();
    ruban(ofPoint pos, float stiffness, int length );

    
    int update(ofPoint control, int channel, float argument,ofVec3f velout);    // return 0 if the visual object is
    void draw(ofColor color);
    
    int chelou;
    
    //Attractors
    ofPoint pos1;
    ofPoint pos2;
    
    //Speed meter
    float speedDiff;
    bool stillMoving;
    bool strong;
    ofColor pointCol;
    
    //Ruban
    int nbSpring;
    vector<Spring> rub1;
    vector<Spring> rub2;
    ofPath mypath;
    
    //change Parameter
    void changeStiffness( float stif);
    void changeLength(float length);

        
};

//------------------------------------------------------------------------------

class ColorRuban :public VisuClass{
public:
//    ColorRuban();
    ColorRuban(VisuHandler* v);
//    ~ColorRuban(){};
//    ColorRuban(vector<ofPoint>* attrin, vector<int>* famillyin);

//Herited
    void setup(){};
    void update(int w, int h){update(0,0,w,h);};
    void draw(int w, int h);
    
    void init(ofPoint pos, ofPoint angle);
    int update(int channel, float argument, int w, int h);
    
    ruban ruban1;
    
    ofParameter<bool> onPause;
    ofParameter<bool> isHidden;
    ofParameter<int> familly;
    ofParameter<ofVec3f> color,vout;
    ofParameter<int> alpha;
    ofParameter<float> timestep,stiffness, length;
    ofParameter<int> curFamilly;
    
    void changeStiffness(float &f);
    void changeLength(float &f);
    
#ifdef OSCSEND
    ofxOscSender musicSender;
    bool setupb;
#endif
    
};

#endif /* defined(__MursMurentDombres__Ruban__) */
