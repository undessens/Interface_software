//
//  Easer.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 08/02/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#include "ofConstants.h"
#include "ofMain.h"

class Easelem {
    
    public :
    ofVec3f value;
    int familly;
    int time;
    
    Easelem(ofVec3f valuein,int familly, int time);
    
    
};

class Easer1 {
    
public:
    vector<Easelem> result;
    vector<Easelem> buf;
    //vector<float> result;
    float maxdist;
    int ttl;

    float lp;
    bool isLinking;
    
    
    Easer1();
    Easer1(int ttl,float lp=0,bool isLinking=false,float maxdist=0);
    ~Easer1();
    

    vector<Easelem> update(vector<Easelem> x);
    


    
    
};




