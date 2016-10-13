//
//  CamHandler.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 12/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "CamHandler.h"


void CamHandler::setup(int * scrwin,int * scrhin,int* zdepthin){
    
    
    scrw = scrwin;
    scrh = scrhin;
    zdepth = zdepthin;
    
    settings.setName("camera");
    camera.setFov(2*ofRadToDeg(atan(*scrh*1.0/(*zdepth))));//50
    camera.setAspectRatio(*scrw*1.0/(*scrh));
//    camera.setupOffAxisViewPortal(ofVec3f(*scrw/2,0,*zdepth/2),ofVec3f(*scrw/2,*scrh/2,*zdepth/2),ofVec3f(*scrw,*scrh/2,*zdepth/2));
    camera.disableOrtho();
    
#ifdef OF_VERSION_MAJOR
    camera.setVFlip(true);
#endif
    
    MYPARAM(alpha,1.f,0.f,1.f);
    MYPARAM(distance,1.f,0.f,2.f);
    MYPARAM(ypr,ofVec3f(0),ofVec3f(0,-90,0),ofVec3f(180,90,360));
    MYPARAM(lookAt,ofVec3f(0.5,0.5,0.5),ofVec3f(0),ofVec3f(1));
    MYPARAM(lookypr,ofVec3f(0),ofVec3f(0,-90,0),ofVec3f(180,90,360));
    MYPARAM(isLooking,false,false,true);

    curdist = distance;
    curypr = ypr;
}

void CamHandler::updateScreenSize(int w, int h){
    camera.setFov(2.0*ofRadToDeg(atan(h*1.0/(*zdepth))));//50
    camera.setAspectRatio(w*1.0/(h));
}


void CamHandler::begin(){
    curdist = distance*1.0*alpha+curdist*(1.0-alpha);
    curypr = ypr.get() * alpha+ curypr*(1-alpha);
    

    if(isLooking){
            camera.orbit(0,0, (*zdepth/2.0),ofVec3f(*scrw,*scrh,*zdepth)/2);
//        ofQuaternion
//        if(abs(lookypr.get().x-curlookypr.x)>340){
//            curlookypr-=ofVec3f(360 + (lookypr.get().x-curlookypr.x),0,0);
//        }
//        if(abs(lookypr.get().y-curlookypr.y)>340){
//            curlookypr-=ofVec3f(0,360+(lookypr.get().y-curlookypr.y),0);
//        }
//        if(abs(lookypr.get().z-curlookypr.z)>340){
//            curlookypr-=ofVec3f(0,0,360+ (lookypr.get().z-curlookypr.z));
//        }
        curlookypr += (lookypr.get()-curlookypr)*1.0*alpha;
        camera.rotateAround(curlookypr.x, ofVec3f(1,0,0), ofVec3f(*scrw,*scrh,*zdepth)*lookAt);
        camera.rotate(curlookypr.x, ofVec3f(1,0,0));
        camera.rotateAround(curlookypr.y, ofVec3f(0,1,0),ofVec3f(*scrw,*scrh,*zdepth)*lookAt);
        camera.rotate(curlookypr.y, ofVec3f(0,1,0));
        camera.rotateAround(curlookypr.z, ofVec3f(0,0,1), ofVec3f(*scrw,*scrh,*zdepth)*lookAt);
        camera.rotate(curlookypr.z, ofVec3f(0,0,1));
    }
    else{
            camera.orbit(curypr.x,curypr.y,curdist * (*zdepth/2.0),ofVec3f(*scrw,*scrh,*zdepth)/2);
         camera.rotate(curypr.z,camera.getLookAtDir());
    }
    
   
    
    camera.begin();
}

void CamHandler::end(){
    camera.end();
}
