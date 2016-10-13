//
//  metaBalls.cpp
//  MurMur d'Ombre
//
//  Created by martin hermant on 14/02/14.
//
//

#include "metaBalls.h"




metaBalls::metaBalls(VisuHandler * v):VisuClass(v){
    MYPARAM(rayon,0.f,0.f,1.f);
    MYPARAM(curFamilly,0,0,3);
    MYPARAM(alpha,0.f,0.f,1.f);
    MYPARAM(lifeTime,0.f,0.f,400.f);
    MYPARAM(color,ofVec4f(0),ofVec4f(0),ofVec4f(255));
    MYPARAM(mode, 0,0,3);
    MYPARAM(emitrate,1.f,0.f,10.f);
    MYPARAM(noise,.5f,0.f,1.f);
    MYPARAM(noiseR,.0f,0.f,5.f);
    MYPARAM(angle,45.f,0.f,90.f);
    MYPARAM(mass,.0001f,0.f,.5f);
    MYPARAM(drawLines,false,false,true);
    MYPARAM(maxv,0.3f,0.f,0.3f);
    MYPARAM(f,1.f,0.4f,1.f);
    MYPARAM(vInit,.0f,0.00f,.05f);
    MYPARAM(rIn,.0f,0.00f,.3f);
    settings.setName("metaBalls");
    maxsize = 400;

}


void metaBalls::setupData(){
    
    metaBall.loadImage("visu/point.png");
}

void metaBalls::update(int w, int h){

    dpoints =  dad->attr->getType(curFamilly);
    ofVec2f scale(w,h);
    ofSort(dpoints,sortOnX);
    

    switch(mode){
            
        case 0:{
    for (int i = 0 ; i<dpoints.size() ; i++){
        if(i<points.size()){
            points[i].x=points[i].x*alpha + dpoints[i].x*(1.-alpha)*(1-dpoints[i].distance(points[i]));
            points[i].y=points[i].y*alpha + dpoints[i].y*(1.-alpha)*(1-dpoints[i].distance(points[i]));
            points[i].z=points[i].z*alpha + dpoints[i].z*(1.-alpha)*(1-dpoints[i].distance(points[i]));
        }
        else{
            if(points.size() == 0){
                points.push_back(Meta(ofVec3f(0,0),rayon,lifeTime*ofGetFrameRate()));
            }
            else  points.push_back(points.back());
        }
        
    }
    
  int del = points.size() - dpoints.size();  
    
    for (int i = dpoints.size() ;i < points.size() ; i++){
        points[i].lifetime-- ;
        points[i].x=points[i].x*alpha + (1.-alpha);
        points[i].y=points[i].y*alpha + (1.-alpha);
    }
    
    vector<Meta> tmp = points;
    points.clear();
    if(tmp.size()>0){
        for (int i = 0 ; i< tmp.size() ; i++){
        if(tmp[i].lifetime>0)points.push_back(tmp[i]);

    }
        
    }
            break;
    }
        case 1:{
           //Emit
            if(ofGetElapsedTimeMillis()-lastT> 1000./emitrate && dpoints.size()>0){
                ofVec3f v(vInit,0);
                
                ofVec3f tmpv = v;
                float curangle  = angle;
                for (int i = 0 ; i< dpoints.size() ; i++){
                    if(dpoints.size()>1){curangle = tmpv.angle(dpoints[(i+1)%dpoints.size()]-dpoints[i]);}
                    tmpv.rotate(ofRandom(noise)*360+curangle,ofVec3f(0,0,1));
                    points.push_back(Meta(dpoints[i],(ofRandom(noiseR)+1)*rayon,lifeTime,tmpv,i));
                }
                
                lastT = ofGetElapsedTimeMillis();
            }
                                 
            //Gravit
                                 
         for(int j = 0 ; j<points.size(); j++){
             
             for (int i = 0 ; i< dpoints.size() ; i ++){
                 if(points[j].mode==i){
                 float d = dpoints[i].distance(points[j]);
                 float v =std::min(1.f,mass*0.01f/abs(d));
            if(points[j].distance(dpoints[i])>rIn && points[j].v.length()<maxv){
                 ofVec3f l = (dpoints[i]-points[j])/d * v;
                 points[j].v+=l;
                 
//                 if(points[j].v.length()>maxv){
//                     points[j].v = points[j].v.getNormalized()*maxv;
//                     
                 }
                }
                     
             }
                  points[j].v *= f;
         }
            
             
             for(int i = 0 ; i < points.size() ; i++){
                 points[i]+=points[i].v;
                 points[i].lifetime--;
             }
             
             //delete
             vector<Meta> tmp = points;
             points.clear();
             if(tmp.size()>0){
                 ofRectangle rr(0,0,1,1);
                 for (int i = 0 ; i< tmp.size() ; i++){
                     if(tmp[i].lifetime>0)points.push_back(tmp[i]);
                     
                 }    
        
    }
            break;
        }
          
    }
            
            
    

    
}

void metaBalls::draw(int w, int h){
    
    if(points.size()>0){
    ofVec2f scale(w,h);

//        ofClear(0);
        ofEnableAlphaBlending();
        
        ofColor c(color.get().x, color.get().y, color.get().z);
    for(int i = 0 ; i< points.size();i++){
        float al;
//        if(points[i].lifetime>4*lifeTime/5){al = (255.0*(lifeTime-points[i].lifetime)/(4*lifeTime/5));}
//        else
            al=(std::min(255.0,512.0*points[i].lifetime/(lifeTime)));
        ofSetColor(c.r,c.g,c.b,al);
        ofRectangle rect;
        rect.setFromCenter(points[i].x*w, points[i].y*h, points[i].rayon*w, points[i].rayon*h);
        metaBall.draw(rect);
        if(drawLines && i<points.size()-1){
            ofSetLineWidth(2);
            
            ofLine(points[i]*scale,points[i+1]*scale);
        }
    }

 
    }
}
