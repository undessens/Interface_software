//
//  Baton.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 14/01/14.
//  Copyright 2014 __MyCompanyName__. All rights reserved.
//

#include "Baton.h"



//Baton::Baton(VisuHandler * v):VisuClass(v){
//    
//    
//
//};


void Baton::setup(){
    
    
    
    
    
    noBeat=true;    
    
    
    maxsize=30;
    
    velocity=30*ofVec3f(1,1,1);
    thickness=curthickness=30;
    stain.loadImage("visu/stainwl.gif");
    stainw=stain.getWidth();
    stainh=stain.getHeight();
    
//    alpha;
//    settings.add(alpha);
    MYPARAM(alpha,100,0,200);
    MYPARAM(mode,0,0,4);
    MYPARAM(thickness,20,0,300);
    MYPARAM(velocity,ofVec3f(1,0,0),ofVec3f(-INFINITY),ofVec3f(+INFINITY));
    MYPARAM(maxsize,20,0,100);
//    settings.add(thickness=ofParameter<int>("thickness",100));
//    settings.add(mode=ofParameter<int>("mode",1));
//    settings.add(velocity=ofParameter<ofVec3f>("velocity",ofVec3f(1,0,0)));
//    settings.add(maxsize=ofParameter<int>("size",4));
    
    //Global name
    settings.setName("baton");
    
}
//Baton::Baton(){
//    
//}
Baton::Baton(VisuHandler * dad):VisuClass(dad){

    setup();
//    material.setShininess( 10 );
//    // the light highlight of the material //
//	material.setSpecularColor(ofColor(255.f, 255.f, 255.f, 255.f));
//    material.setDiffuseColor(ofColor(250.f,10.f,10.f));
//   // material.setEmissiveColor(ofColor(0,255.f,0));
//    
//
//    
//    light.setPointLight();
//   // light.orbit(0,0,10,center);
//    light.setDiffuseColor( ofColor(255.f,255.f,255.f));
//    
//    // specular color, the highlight/shininess color //
//	light.setSpecularColor( ofColor(255.f, 0.f, 255.f));
//    
//    
//    light.setAttenuation( 1.f, 0.f, 0.f );
}


void Baton::update(VisuHandler * dad){
    attr=&dad->attr->destA;
    ofVec2f size =    dad->sH->sizeOfScreen(screenN);
    ofVec3f center = size/2;
    int width = size.x;
    int height = size.y;
    //light.orbit(45,45,100,center);
    //    light.setPosition(center);
    //    light.setAttenuation( 1.f, 0.f, 0.f );
    
    int nattr = MIN(2,attr->size());
    if(nattr>0){
        if(env>-1){
            curthickness=env*thickness/100.0;
        }
        else{ curthickness=thickness;}
        if(noBeat&&beat==1){
            if(curthickness>0){
                if(nattr>0){
                    stainl.insert(stainl.begin(),ofVec2f(attr->at(0).p.x*width,attr->at(0).p.y*height));
                    
                    if(nattr>1){
                        stainl.insert(stainl.begin(),ofVec2f(attr->at(1).p.x*width,attr->at(1).p.y*height));
                    }
                }
            }
            noBeat=false;
        }
        else if(!noBeat&&beat==0){
            noBeat=true;
        }
        
        
        if(nattr==2){
            ofVec2f attr1=ofVec2f(attr->at(0).p.x*width,attr->at(0).p.y*height);
            ofVec2f attr2=ofVec2f(attr->at(1).p.x*width,attr->at(1).p.y*height);
            orientation.insert(orientation.begin(),ofDegToRad((attr2-attr1).angle(ofVec2f(0,-1))));
            poly.insert(poly.begin(),attr1);
            poly2.insert(poly2.begin(),attr2);  
        }
        else if(nattr==1){
            if(poly.size()==0){
                orientation.insert(orientation.begin(),(ofGetElapsedTimeMillis()/500)%6);
                poly.insert(poly.begin(),ofVec2f(attr->at(0).p.x*width,attr->at(0).p.y*height));
                
                poly2.insert(poly2.begin(),ofVec2f(width,height));
            }
            else{
                orientation.insert(orientation.begin(),(ofGetElapsedTimeMillis()/500)%6);
                poly.insert(poly.begin(),ofVec2f(attr->at(0).p.x*width,attr->at(0).p.y*height));
                poly2.insert(poly2.begin(),poly2.front());
            }
        }
        //    else{
        //        if(poly.size()>0){
        //            poly.insert(poly.begin(),poly.front());
        //            poly2.insert(poly2.begin(),poly2.front());
        //            orientation.insert(orientation.begin(),1.57);
        //        }
        //    }
    }
    
    if(poly.size()>maxsize||(poly.size()>1&&(width<poly.back().x<0||height<poly.back().y<0||(300< poly.back().z && poly.back().z < -500)))){
        poly.pop_back();
        poly2.pop_back();
        orientation.pop_back();
    }
    if(stainl.size()>0&&(stainl.back().x>width||stainl.size()>10)){
        stainl.pop_back();
    }
    
    for(int i=0;i<stainl.size();i++){
        stainl[i]+=velocity;
    }
    
    for(int i=0;i<poly.size();i++){
        poly[i]+=velocity;
        poly2[i]+=velocity;
        
    }
    
    
}


void Baton::draw(VisuHandler * dad){
    
    
    ofPushStyle();
    //  ofPushMatrix();
    
    // ofSetColor(0,0,0);
    //    ofEnableLighting();
    //    light.enable();
    //    light.customDraw();
    //    material.begin();
    ofFill();
    
    
    // ofBox(light.getPosition(),30);
    ofPath polyline,polyline2;
    
    polyline.setColor(ofColor(255,255,255,alpha));
    polyline2.setColor(ofColor(255,255,255,alpha));
    
    //polyline.setMode(ofPath::POLYLINES);
    ///polyline.setStrokeWidth(thickness);
    polyline.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    polyline2.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
    switch (mode){
        case 0:
            
            for(int i =0;i<poly.size();i++){
                
                polyline.curveTo(ofVec3f(poly[i].x+curthickness*sin(orientation[i]),poly[i].y+curthickness*cos(orientation[i]),poly[i].z));
                polyline2.curveTo(ofVec3f(poly2[i].x+curthickness*sin(orientation[i]),poly2[i].y+curthickness*cos(orientation[i]),poly[i].z));
            }
            
            for(int i =poly.size()-1;i>=0;i--){
                polyline.curveTo(ofVec3f(poly[i].x-curthickness*sin(orientation[i]),poly[i].y-curthickness*cos(orientation[i]),poly[i].z));
                polyline2.curveTo(ofVec3f(poly2[i].x-curthickness*sin(orientation[i]),poly2[i].y-curthickness*cos(orientation[i]),poly[i].z));    
            }
            
            
            for(int i=0;i<stainl.size();i++){
                stain.draw(stainl[i].x-stainw/2,stainl[i].y-stainh/2,stainl[i].z);
            }
            
            
            if(poly.size()>1){
                polyline.draw();
                polyline2.draw();
            }
            break;    
            
            
            
        case 1:
            
            ofSetLineWidth(thickness);
            for(int i=0;i<poly.size();i++){
                polyline.clear();
                ofVec2f curvec = poly2[i]-poly[i];
                curvec.normalize();
                curvec*=curthickness;
                
                
                polyline.curveTo(poly[i]-curvec.getRotated(90)-curvec);
                polyline.curveTo(poly[i]+curvec.getRotated(90)-curvec);
                polyline.curveTo(poly[i]+2*curvec.getRotated(90));
                
                
                polyline.curveTo(poly2[i]+2*curvec.getRotated(90));
                polyline.curveTo(poly2[i]+curvec.getRotated(90)+curvec);
                
                polyline.curveTo(poly2[i]-curvec.getRotated(90)+curvec);
                polyline.curveTo(poly2[i]-2*curvec.getRotated(90));
                
                polyline.curveTo(poly[i]-2*curvec.getRotated(90));
                polyline.curveTo(poly[i]-curvec.getRotated(90)-curvec);
                polyline.curveTo(poly[i]+2*curvec.getRotated(90));
                polyline.draw();
                
            }
            break;
        default:
            break;
    }
    //    light.disable();
    //    ofDisableLighting();
    //    material.end();
    // //   ofPopMatrix();
    ofPopStyle();
    
}

//
//void Baton::drawFbo(int w, int h){
//    ofPushStyle();
//    //  ofPushMatrix();
//    
//    // ofSetColor(0,0,0);
//    ofFill();
//    int width = ofGetWidth();
//    int height=ofGetHeight();
//    
//    ofPath polyline,polyline2;
//    
//    polyline.setColor(0);
//    polyline2.setColor(0);
//    
//    //polyline.setMode(ofPath::POLYLINES);
//    ///polyline.setStrokeWidth(thickness);
//    
//    polyline.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
//    polyline2.setPolyWindingMode(OF_POLY_WINDING_NONZERO);
//    //polyline.setFilled(true);
//    switch(mode){
//        case 0:
//            for(int i =0;i<poly.size();i++){
//                
//                polyline.curveTo(ofVec2f(w*1.0/width*(poly[i].x+curthickness*sin(orientation[i])),h*(1-1.0/height*(poly[i].y+curthickness*cos(orientation[i])))));
//                polyline2.curveTo(ofVec2f(w*1.0/width*(poly2[i].x+curthickness*sin(orientation[i])),h*(1-1.0/height*(poly2[i].y+curthickness*cos(orientation[i])))));
//            }
//            
//            for(int i =poly.size()-1;i>=0;i--){
//                polyline.curveTo(ofVec2f(w*1.0/width*(poly[i].x-curthickness*sin(orientation[i])),h*(1-1.0/height*(poly[i].y-curthickness*cos(orientation[i])))));
//                polyline2.curveTo(ofVec2f(w*1.0/width*(poly2[i].x-curthickness*sin(orientation[i])),h*(1-1.0/height*(poly2[i].y-curthickness*cos(orientation[i])))));    
//            }
//            
//            if(poly.size()>1){
//                polyline.draw();
//                polyline2.draw();
//            }
//            
//            break;
//        case 1:
//            for(int i=0;i<poly.size();i++){
//                polyline.curveTo(w*1.0/width*poly[i].x,h*(1-1.0/height*poly[i].y));
//            }
//            for(int i=poly.size()-1;i>=0;i--){
//                polyline.curveTo(w*1.0/width*poly2[i].x,h*(1-1.0/height*poly2[i].y));
//            }
//            
//            polyline.draw();
//            
//            break;
//    } 
//    
//    //    
//    //   ofPopMatrix();
//    ofPopStyle();
//    
//}

