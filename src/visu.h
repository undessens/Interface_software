//
//  visu.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 19/03/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//
#pragma once
//
//#ifndef VISU_H
//#define VISU_H


#include "ofMain.h"
//#include "ofxVoronoi.h"
#include "VisuHandler.h"


class VideoP{
public:
    VideoP();
    VideoP(int scrw,int scrh);
    ~VideoP();
    
    void draw();
    void load();
    
    int curstate,nextstate;
    ofVideoPlayer player;
    int scrw,scrh;
};


class NoiseCircle {
public:
    NoiseCircle();
    ~NoiseCircle();
    NoiseCircle(vector<ofPoint>* attrin,vector<int>* famillyin);//:Visu(attrin){};
    
    vector<ofPoint>* attr;
    vector<int>* familly;
    bool caredfam[3];
    bool isNewBeat,noBeat;
    
    int steps;
    float rayon;
    float currmax;
    float noise;
    int rmax;
    int numcircle ; 
    int thickness;

    int mode;
    
    //    ofMaterial material;
    //    ofLight light;
    //    
    
    void update(int beat,float env);
    void draw();
    void drawFbo(int w,int h);
    
};





class MagicStar{
public:
    MagicStar();
    MagicStar(vector<ofPoint>* attrin,vector<int>* famillyin);
    
    
    void draw();
    
    
    vector<ofPoint>* attr;
    vector<int>* familly;
    // Geometric Parameters
    int internal_diff;
    int space;
    int newSpace;
    int nb_star;
    float angle;
    float newAngle;
       // Attractors
    float Xpos;
    float Ypos;
    
    //Color mode
    bool actualMode;

    
    
};

class Poolerv{
public:
    Poolerv();
    Poolerv(vector<ofPoint>* attrin);
    
    
    void draw(float env,bool isFbo);
    
    
    vector<ofPoint>* attr;
    
    // Geometric Parameters
    ofVec2f curdir;
    int thickness;
    vector<ofVec2f> traj;
    int border;
    int res;
    int amp;
    vector<float> envlop;
    int downsample;
    int downsamplecount;
    int mode;
   
    int bounce;

    
 
    
    
    
};



class MagicRuban{
public:
    MagicRuban();
    MagicRuban(vector<ofPoint>* attrin,vector<int>* famillyin);
    ~MagicRuban();
    
    
    void draw();
    
    ofPoint* rub1;
    ofPoint* rub2;
    void dragSegment(int i, ofPoint point1, ofPoint point2);
    float segLength;
    int num;
    ofPolyline rubBis1;
    ofPolyline rubBis2;
    float gravity;
    //Attractors
    vector<ofPoint>* attr;
    vector<int>* familly;
    ofPoint pos1;
    ofPoint pos2;
    
    
};



class Spider{
public:
    Spider();
    ~Spider();
    Spider(vector<ofPoint>* attrin,vector<int>* famillyin);
    
    vector<ofPoint>* attr;
    vector<int>* familly;

//    ofImage spider1,spider2,spider3;
//    int s1w,s1h,s2w,s2h,s3w,s3h;
//    vector<ofPoint> s1v,s2v,s3v;
//    float noise;
    float count;
    int sub;
    float velocity;

    
    void draw(float audioenv,int inw,int inh);
    
    
};

class MagicPlanet{
public:
	MagicPlanet();
    MagicPlanet(vector<ofPoint>* attrin, vector<int>* familly);
    void draw();
    
    
    // Geometric Parameters
    int nbPlanet;
    float radiusMax;
    float radiusMin;
    float speed;
    float sizePlanet;
    float NewAngle;
    vector<float> anglePlanete;
    
    //Display parameter
    bool isBeat;
    float alphangle;
    
    // Centre of planets
    ofPoint centroid;
    
    //Receive
    vector<ofPoint>* attr;
	vector<int>* familly;
    
};


//#endif