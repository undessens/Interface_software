//
//  Constants.h
//  allAddonsExample
//
//  Created by Tinmar on 14/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//


#pragma once

//#define LIVEBLUR

#define VISU_OSC_IN 12344
#define VISU_OSC_OUT 12346

#define VISU_OSC_IP_OUT "localhost"



#define MYPARAM(nom,init,min,max) nom.setName(#nom);nom.setMin(min);nom.setMax(max);settings.add(nom);nom=init;

//#define GUIMODE


// Struct for doing PingPong quickly and easy
//
// Because on GPU you can´t write over the texture that you are reading we are
// using to pair of ofFbo attached together on what we call pingPongBuffer 
// Learn more about Ping-Pong at:
//
// http://www.comp.nus.edu/~ashwinna/docs/PingPong_FBO.pdf
// http://www.seas.upenn.edu/~cis565/fbo.htm#setupgl4
//
static bool sortOnZ(ofVec3f a,ofVec3f b){
    return a.z>b.z;
}
static bool sortOnX(ofVec3f a,ofVec3f b){
    return a.x>b.x;
}
static bool sortOnXYZ(ofVec3f a,ofVec3f b){
    return a.z>b.z&&a.x>b.x&&a.y>b.y;
}

class AttrStruct{
public:
    AttrStruct(ofPoint pin ,int typein,int zonein):p(pin),zone(zonein),type (typein){};
    
    ofPoint p;
    int zone;
    int type;
};

static vector<int> getActiveFromInt(int a){
    vector<int> res;
    int i = 0;
    while(a>>i>0){
        if(a>>i & 1){
            res.push_back(i+1);
        }
        i++;
    }
    return res;
}

struct pingPongBuffer {
public:
    void allocate( int _width, int _height, int _internalformat = GL_RGBA, float _dissipation = 1.0f){
        // Allocate
        for(int i = 0; i < 2; i++){
            FBOs[i].allocate(_width,_height, _internalformat );
        }
        
        // Clean
        clear();
        
        // Set everything to 0
        flag = 0;
        swap();
        flag = 0;
    }
    
    void swap(){
        src = &(FBOs[(flag)%2]);
        dst = &(FBOs[++(flag)%2]);
    }
    
    void clear(){
        for(int i = 0; i < 2; i++){
            FBOs[i].begin();
            ofClear(0,255);
            FBOs[i].end();
        }
    }
    
    ofFbo& operator[]( int n ){ return FBOs[n];}
    
    ofFbo   *src;       // Source       ->  Ping
    ofFbo   *dst;       // Destination  ->  Pong
private:
    ofFbo   FBOs[2];    // Real addresses of ping/pong FBO´s  
    int     flag;       // Integer for making a quick swap
};


class Timer{
    
    float startT;
    float time;
    
    void start(float timein){
        startT = ofGetElapsedTimef();
        time = timein>0?timein:0.000001;
    }
    float getSeconds(){
        return ofGetElapsedTimef()-startT;
    }
    float get(){
        return time - (ofGetElapsedTimef()-startT);
    }
    
    float getNorm(){
        return get()*1.0/time;
    }
};


static int computeRatio = 2;

static int FPS = 40;
// screen size

static int scrw = 1280;
static int scrh = 800;


static float calcAngle(ofVec2f cur, ofVec2f next){
    
    float teta;
    
    
    //Normalize
    ofVec2f nCur = cur.normalize();
    ofVec2f nNext = next.normalize();
    ofVec2f orthonCur = ofVec2f(-nCur.y, nCur.x);
    
    float cosTeta = nCur.dot(nNext);
    float sinTeta = orthonCur.dot(nNext);
    
    if(sinTeta>0)teta = acos(cosTeta);
    else teta = -acos(cosTeta);
    
    
    
    return teta;
    
    
}



template <class C> void FreeClear( C & cntr ) {
    for ( typename C::iterator it = cntr.begin(); 
         it != cntr.end(); ++it ) {
    	delete * it;
    }
    cntr.clear();
}

