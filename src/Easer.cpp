//
//  Easer.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 08/02/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//


#include "Easer.h"

Easelem::Easelem(ofVec3f valuein,int famillyin,int timein){
    value=valuein;
    familly=famillyin;
    time=timein;
}


Easer1::Easer1(int ttlin,float lpin,bool isLinkingin,float maxdistin){
    //x.clear();

    lp=lpin;
    ttl=ttlin;

    isLinking=isLinkingin;
    maxdist=maxdistin;
    buf.clear();
    result.clear();

    
 
    
}


vector<Easelem> Easer1::update(vector<Easelem> xin){
    vector<Easelem> xintmp;
    result.clear();
    
    
    //get rid of doubles in new list : 2*maxdist
    bool addelem=true;
    for(int l=0;l<xin.size();l++){
        addelem=true;
        for(int k=0;k<xin.size();k++){
            if(k!=l&&(xin[l].value-xin[k].value).length()<2*maxdist){
                addelem=false;
                break;
            }
        }
        if(addelem){
            xintmp.push_back(xin[l]);
        }

    }
    
    if(ttl>0){ 
    // track
    for(int k=0;k<xintmp.size();k++){
        bool isadded=false;
        for(int j=0;j<buf.size();j++){
            if(k==0){
                buf[j].time--;   ///update time at first pass
            }
            if((buf[j].value-xintmp[k].value).length()<maxdist){
                buf[j].time+=2; // if its the same elem : increase time
                buf[j].time=MIN(buf[j].time, ttl);
                if(buf[j].time>=0){
                buf[j].value=buf[j].value*lp+xintmp[k].value*(1-lp);
                if(!isLinking){
                    buf[j].familly=xintmp[k].familly;
                }
                result.push_back(buf[j]);
                isadded=true;
                break;
                }
            }
        }
        
        if(!isadded){
            buf.push_back(Easelem(xintmp[k].value,xintmp[k].familly,-ttl));
        }
        
    }
    }
    else{
        
        result=xin;
    }
    
    
    
    return result;



}

