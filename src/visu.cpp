//
//  visu.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 19/03/13.
//  Copyright 2013 __MyCompanyName__. All rights reserved.
//

#include "visu.h"


VideoP::VideoP(){
 
}
VideoP::VideoP(int scrwin, int scrhin){
    scrw=scrwin;
    scrh = scrhin;
    this->load();
    player.setLoopState(OF_LOOP_NORMAL);
}



VideoP::~VideoP(){
    
   
}
void VideoP::load(){
    player.loadMovie("video/mains_2_1.mp4");    
}

void VideoP::draw(){
    if(curstate!=nextstate){
if(nextstate==0)player.setPaused(!player.isPaused());
else if(nextstate==1)player.play();
else if(nextstate>2) player.setPosition(nextstate/100.0);
    curstate = nextstate;
    }
    
     player.update();
    if(player.isFrameNew()){
   
        player.draw(0,0,scrw,scrh);
    }
    
    
}


NoiseCircle::NoiseCircle(){
    
}

NoiseCircle::NoiseCircle(vector<ofPoint>* attrin, vector<int>* famillyin){
    attr=attrin;
    familly = famillyin;
    caredfam[1]=caredfam[0]=true;
    caredfam[2]=false;
    rayon = 2;
    rmax=currmax=200;
    steps = 20;
    thickness= 1;
    numcircle = 40;
    
    mode = 0;
    noise = 0.3;
   
}

void NoiseCircle::update(int beat,float envlop){

    
    if(envlop>0.01){
        currmax = rayon + (rmax-rayon)* envlop/100.0;
    }
    else{
        currmax = rmax;
    }
    
}

void NoiseCircle::draw(){
    
    ofPushStyle();
    ofSetLineWidth(thickness);
    ofSetColor(255);
    for(int i = 0 ; i< attr->size() ; i++)
    {
        if(caredfam[familly->at(i)]){
            for(int n = 0 ; n< numcircle;n++)
            {
                ofPolyline poly;
                if(ofRandomf()>0.5) ofSetColor(255,255,255,ofRandom(150,255));
                else ofSetColor(0,0,0,ofRandom(150,255));
                float r = ofRandom(rayon,currmax);
                for(int k = 0 ; k<steps+4 ; k++)
                {
                    poly.curveTo(attr->at(i)*ofVec2f(ofGetWidth(),ofGetHeight()) + r*ofRandom(1-noise,1+noise)*ofVec2f(1,0).rotate(k*360.0/steps));
                }
                //poly.close();
                poly.draw();
            }
        }
    }
    ofPopStyle();
}


MagicStar::MagicStar(){
    
}
MagicStar::MagicStar(vector<ofPoint>* attrin,vector<int>* famillyin){
    attr=attrin;
    familly=famillyin;
    nb_star=10;
    internal_diff = 25;
    space = 35;
    angle=2.5f;
     actualMode = false;
}



void MagicStar::draw(){
    
    ofPushStyle();
    ofPushMatrix();
    
    
    
    float star_angle=0.3925f;
    
    ofPoint center,point0, point1, point2, point3, point4, point5, point6, point7, point8, point9, point10, point11, point12,point13,point14,point15,point16;
    center = ofPoint( ofGetWidth()/2, ofGetHeight()/2);
    
    int radius1;
    int radius2;
     //Calculation of selected star
    if(attr->size()>1){
        
        ofPoint ce = (attr->at(0)+attr->at(1))/2.0;
        Xpos = ce.x;
        Ypos = ce.y;
        
        ofVec2f vect = attr->at(0)-attr->at(1);
        //ofVec2f(msg.getArgAsFloat(2)-msg.getArgAsFloat(5), msg.getArgAsFloat(3)-msg.getArgAsFloat(6));
        if(familly->at(0)==1){
            vect*=-1;
        }
        
        ofVec2f abs = ofVec2f(1.0f, 0);
        
        newAngle = vect.angle(abs);
        
        vect*=ofVec2f(ofGetWidth(),ofGetHeight());
       // float x = (msg.getArgAsFloat(2) - msg.getArgAsFloat(5))*ofGetWidth();
       // float y  = (msg.getArgAsFloat(3) -msg.getArgAsFloat(6))*ofGetHeight();
        newSpace = vect.length() * 0.1;

        
        
    }
    
    
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    
    //Refresh star shape
    
    float alpha1 = 0.0f;
    angle = angle*(alpha1) + newAngle*(1.0 - alpha1);
       //smoothing
    float alpha3 = 0.7;
    space = space*(alpha3) + newSpace*(1.0 - alpha3);
    
    ofRotateZ(-angle);
    //printf("\nnewspace : %d", newSpace);
    ofSetLineWidth((int)space/6);
    
    
    
    for(int i=0; i<nb_star;i++)
    {
        
        radius1 = space*(1+i);
        radius2 = 2*radius1;
        
        
        
        
        
        point0 = ofPoint( radius1*cos(0), radius1*sin(0));
        point1 = ofPoint( radius2*cos(star_angle), radius2*sin(star_angle));
        point2 = ofPoint( radius1*cos(2*star_angle), radius1*sin(2*star_angle));
        point3 = ofPoint( radius2*cos(3*star_angle), radius2*sin(3*star_angle));
        point4 = ofPoint( radius1*cos(4*star_angle), radius1*sin(4*star_angle));
        point5 = ofPoint( radius2*cos(5*star_angle), radius2*sin(5*star_angle));
        point6 = ofPoint( radius1*cos(6*star_angle), radius1*sin(6*star_angle));
        point7 = ofPoint( radius2*cos(7*star_angle), radius2*sin(7*star_angle));
        point8 = ofPoint( radius1*cos(8*star_angle), radius1*sin(8*star_angle));
        point9 = ofPoint( radius2*cos(9*star_angle), radius2*sin(9*star_angle));
        point10 = ofPoint( radius1*cos(10*star_angle), radius1*sin(10*star_angle));
        point11 = ofPoint( radius2*cos(11*star_angle), radius2*sin(11*star_angle));
        point12 = ofPoint( radius1*cos(12*star_angle), radius1*sin(12*star_angle));
        point13 = ofPoint( radius2*cos(13*star_angle), radius2*sin(13*star_angle));
        point14 = ofPoint( radius1*cos(14*star_angle), radius1*sin(14*star_angle));
        point15 = ofPoint( radius2*cos(15*star_angle), radius2*sin(15*star_angle));
        point16 = ofPoint( radius1*cos(16*star_angle), radius1*sin(16*star_angle));
        
        
        
        if(i==0){
            
            ofPoint pointLine1 = ofPoint( radius2*cos(1*star_angle), radius2*sin(1*star_angle));
            ofPoint pointLine2 = ofPoint( radius2*cos(9*star_angle), radius2*sin(9*star_angle));
            
            //ofLine(pointLine1, pointLine2) ;
            
            
        }
        else{
            
            ofRotateZ( angle/((nb_star-1)*1.0f) );
            
            
            //Martin
            //int sign = (i<nb_star/2?+1.0:-1.0);
            //ofRotateZ(sign*cos(ofGetElapsedTimef()*10)*6);
            //ofRotateZ( angle*(i)*1.0f/(nb_star*1.0f) );
            
        }
        
        if(actualMode)
            ofSetLineWidth((int)6);
        else ofSetLineWidth(2);
        
        ofLine(point0, point1);
        ofLine(point1, point2);
        ofLine(point2, point3);
        ofLine(point3, point4);
        ofLine(point4, point5);
        ofLine(point5, point6);
        ofLine(point6, point7);
        ofLine(point7, point8);
        ofLine(point8, point9);
        ofLine(point9, point10);
        ofLine(point10, point11);
        ofLine(point11, point12);
        ofLine(point12, point13);
        ofLine(point13, point14);
        ofLine(point14, point15);
        ofLine(point15, point16);
        ofLine(point16, point0);
        
        if(actualMode)
            ofSetLineWidth((int)1);
        else ofSetLineWidth(3);
        
        ofLine(ofPoint(0,0), point1);
        //ofLine(ofPoint(0,0), point2);
        ofLine(ofPoint(0,0), point3);
        //ofLine(ofPoint(0,0), point4);
        ofLine(ofPoint(0,0), point5);
        //ofLine(ofPoint(0,0), point6);
        ofLine(ofPoint(0,0), point7);
        //ofLine(ofPoint(0,0), point8);
        ofLine(ofPoint(0,0), point9);
        //ofLine(ofPoint(0,0), point10);
        ofLine(ofPoint(0,0), point11);
        //ofLine(ofPoint(0,0), point12);
        ofLine(ofPoint(0,0), point13);
        //ofLine(ofPoint(0,0), point14);
        ofLine(ofPoint(0,0), point15);
        //ofLine(ofPoint(0,0), point16);
        // ofLine(ofPoint(0,0), point0);
        
        
        
        
    }
    
    

    
    ofPopStyle();
    ofPopMatrix();
    
    
}



Poolerv::Poolerv(){
    
}

Poolerv::Poolerv(vector<ofPoint>* attrin){
    attr= attrin;
    curdir=ofVec2f(1,0);
    thickness=1;

    border = 30;
    res=30;
    downsample=3;
    downsamplecount=0;
    amp=200;
    mode=1;
    
}

void Poolerv::draw(float env,bool isFbo){
    int nattr = MIN(2,attr->size());
    if(nattr>0){
    ofPushMatrix();
    ofPushStyle();

    int rand = 200;
    float latt = 100;
    int w;
    int h;
    if(isFbo){
      w=320;
        
         h= 240;
    }
    else{
    w = ofGetWidth();
     h = ofGetHeight();
    }
    
    int maxenvsize = 125;
    if(env>-1){
        if(downsamplecount>=downsample){
        envlop.insert(envlop.begin(),env*env/10000.0);
        if(envlop.size()>maxenvsize){
            envlop.pop_back();
        }
            downsamplecount=0;
        }
        else{
            downsamplecount++;
        }
    }

    
    
    
    int iter;
    int curthickness;
        int curamp;
    if(isFbo){
        iter = 3;
        curthickness = 40;
        curamp = amp*h/ofGetHeight();
    }
    else{
     iter= 30;   
        curthickness=thickness;
        curamp = amp;
    }
    
    for (int dir = 0 ; dir<=1;dir++){
        
        for(int o = 0 ; o<iter;o++){
            ofVec2f curpoint;
            int curbounce = 0;
            if(isFbo)curpoint= ofVec2f(attr->at(0).x*w,(1-attr->at(0).y)*h);
            else curpoint= ofVec2f(attr->at(0).x*w,attr->at(0).y*h);
    traj.clear();
    if(nattr>1){
        if(isFbo){
            curpoint = (curpoint+ofVec2f(attr->at(1).x*w,(1-attr->at(1).y)*h))/2.0;
            curdir = (1-2*dir)*(curpoint - ofVec2f(attr->at(1).x*w,(1-attr->at(1).y)*h)).getNormalized();
        }        
        else{
            curpoint = (curpoint+ofVec2f(attr->at(1).x*w,attr->at(1).y*h))/2.0;
            curdir = (1-2*dir)*(curpoint - ofVec2f(attr->at(1).x*w,attr->at(1).y*h)).getNormalized();            
            }        
        }


            int dev=0;
        for(int l = 0 ; l<2.0*w/res;l++){
            
        if((curpoint.x>0&&curpoint.x<w)||!bounce&&(curpoint.y>border&&curpoint.y<h-border)){
            
            if(env>-1&&l<envlop.size()){
                if(mode==0){
                    traj.push_back(curpoint+ envlop[l]*curamp*ofRandom(-1,1)*curdir.getRotated(90)) ;}
                if(mode==1){
                  dev+=curamp*ofRandom(-1,1) ;
                        traj.push_back(curpoint + MIN(h/10,l*l*1.0/latt)*dev*envlop[0]*curdir.getRotated(90));
                    
                    
                }
                
            }
            else{
            traj.push_back(curpoint+ MIN(h/10,curamp*l*l*1.0/latt)*(1+sin(2.0*PI*(l/5.0-ofGetElapsedTimef()*2)))*ofRandom(-1,1)*curdir.getRotated(90));
            }
            if(curbounce<bounce&&(curpoint.y<border||curpoint.y>h-border)){
                curbounce++;
                curdir.y*=-1;
            }
            curpoint += res*curdir ;
        }
        else{
            break;
        }
   
    }

            if(isFbo)ofSetColor(0);
            else ofSetColor(255,255,255,ofRandom(0.5,1)*255);
    ofSetLineWidth(curthickness);
    ofPolyline poly;
    for(int k = 0 ; k< traj.size();k++){
        poly.lineTo(traj[k]);
//        if(k>1&&ofRandom(3)>2){
//            ofLine(traj[k], 2*traj[k]-traj[k-1]);
//        }
    }
    poly.draw();
        }
    
    //curdir*=-1;
}    

    
    
    ofPopMatrix();
    ofPopStyle();
        
    }
}






MagicRuban::MagicRuban(){
    gravity=0.000014f;
}

MagicRuban::MagicRuban(vector<ofPoint>* attrin,vector<int>* famillyin){
    
    rub1 = new ofPoint[100];
    rub2 = new ofPoint[100];
    
    attr = attrin;
    familly=famillyin;
    
    segLength = 7;
    for(int i=0; i<100; i++) {
        rub1[i] = ofPoint(0,0);
        rub2[i] = ofPoint(0,0);
        rubBis1.addVertex(ofPoint(0,0));
        rubBis2.addVertex(ofPoint(0,0));
        
    }
    ofEnableAlphaBlending();
    ofSetLineWidth(10.0f);
    
    
}

void MagicRuban::dragSegment(int i, ofPoint point1, ofPoint point2) {
    
    // Calculating rub1
    
    ofPoint nextPoint = rub1[i];
    ofPoint pointBis;
    float dx = point1.x - nextPoint.x;
    float dy = point1.y - nextPoint.y;
    float angle = atan2(dy, dx);
    nextPoint.x = (point1.x - cos(angle) * segLength + i*i*i*gravity);
    nextPoint.y =  (point1.y - sin(angle) * segLength + i*i*i*gravity );
    rub1[i]= nextPoint;
    
    float angleBis = angle*2.0 + cos(i*2.0*PI/10.0 + ofGetElapsedTimef()*8.0);
    
    pointBis.x = (point1.x - cos(angleBis) * (segLength+ 25) );
    pointBis.y =  (point1.y - sin(angleBis) * (segLength + 25) + i*i*i*gravity );
    
    rubBis1[i] = pointBis;
    
    //Calculating rub2
    
    nextPoint = rub2[i];
    dx = point2.x - nextPoint.x;
    dy = point2.y - nextPoint.y;
    angle = atan2(dy, dx);
    nextPoint.x = (point2.x - cos(angle) * segLength - i*i*i*gravity);
    nextPoint.y =  (point2.y - sin(angle) * segLength + i*i*i*gravity );
    rub2[i]= nextPoint;
    
    angleBis = angle*2.0 + cos(i*2.0*PI/10.0 + ofGetElapsedTimef()*8.0);
    
    pointBis.x = (point2.x - cos(angleBis) * (segLength+ 25));
    pointBis.y =  (point2.y - sin(angleBis) * (segLength + 25) + i*i*i*gravity );
    
    rubBis2[i] = pointBis;
    
    
}





void MagicRuban::draw(){
    
    
    //Updating postion
    int nattr = attr->size();
    for(int i = 0 ; i< nattr; i++){
        if(familly->at(i)==0){
        pos1=ofPoint(attr->at(i).x*ofGetWidth(),attr->at(i).y*ofGetHeight());
        }
        else if(familly->at(i)==1){
        pos2=ofPoint(attr->at(i).x*ofGetWidth(),attr->at(i).y*ofGetHeight());
        }
       
    }

    
    this->dragSegment(0, pos1, pos2);
    float grad;
    int gradColor;
    ofPoint  currPoint1;
    ofPoint currPoint2;
    
    for(int i=0; i<99; i++) {
        currPoint1 = rub1[i];
        currPoint2 = rub2[i];
        dragSegment(i+1, currPoint1, currPoint2);
        grad = 255.0f - (i*255.0f/(100*1.0f));
        gradColor =(int)( 255-(i*0.95f));
        ofSetColor(gradColor, gradColor,255 , (int)grad);
        ofCircle(currPoint1, 20-(i*0.1));
        ofCircle(currPoint2, 20-(i*0.1));
        
        
    }
    
    rubBis1 = rubBis1.getSmoothed(20);
    rubBis2 = rubBis2.getSmoothed(20);
    rubBis1[0]=pos1;
    rubBis2[0]=pos2;
    ofSetColor(255,154,0, 128);
    rubBis1.draw();
    rubBis2.draw();
    
    
}

MagicRuban::~MagicRuban(){
    
    //delete [] rub1;
    //delete [] rub2;
    
}



Spider::Spider(){
    
}
Spider::~Spider(){
    
}
Spider::Spider(vector<ofPoint>* attrin,vector<int>* famillyin){
    attr=attrin;
    familly = famillyin;
    sub = 10;

    count = -0.5;

}

void Spider::draw(float audioenv,int inw,int inh){
    ofPushMatrix();
    ofPushStyle();
    if(audioenv>-1)count+=velocity*audioenv;
    else count+=velocity;
    if(count>0.5){
        count=-0.5;
    }


    
    ofSetColor(255);
    ofSetLineWidth(1);
    for(int i=0;i<attr->size();i++){
        if(familly->at(i)<2){
            ofPoint p = attr->at(i)*ofVec2f(inw,inh);
            bool lr=p.x>(inw)/2;
            if(sub>0){
                for(int j=0;j<2*(sub+1);j++){
                    ofLine(ofVec2f((j%(sub+1)+(j<(sub+1)?count:-count))*(inw)/sub,j<(sub+1)?0:(inh)),p);
                }
                for(int j=0;j<2*(sub+1);j++){
                    ofLine(ofVec2f(j<(sub+1)?0:(inw),(j%(sub+1)+(j<(sub+1)?-count:+count))*(inh)/sub),p);
                }
            }

               
                
            
        }
    }    
    ofPopMatrix();
    ofPopStyle();
}


 
//--------------------------------------------------------------
MagicPlanet::MagicPlanet(){
    
}


//--------------------------------------------------------------

MagicPlanet::MagicPlanet(vector<ofPoint>* attrin, vector<int>* famillyin){
    
    nbPlanet = 7;
    radiusMax = 380;
    radiusMin = 20;
    speed = 20;
    sizePlanet = 0.07;
    centroid = ofPoint(ofGetWidth()/2,ofGetHeight()/2);
    isBeat = false;
    
	attr = attrin;
	familly = famillyin;
    
    float angle=0.0f;
    
    for(int i=0; i<nbPlanet; i++)
    {
        
        anglePlanete.push_back(angle);
        
    }
    alphangle = 0.1f;
    ofSetCircleResolution(40);
 
    
}


//--------------------------------------------------------------
void MagicPlanet::draw(){
    



    if(attr->size()>1){
        
        
        float Xpos = (( attr->at(0).x+attr->at(1).x)/2.0f)*ofGetWidth() ;
        float Ypos = ((attr->at(0).y+attr->at(1).y)/2.0f)*ofGetHeight() ;
        
        ofVec2f baton = ofVec2f((attr->at(0).x - attr->at(1).x),(attr->at(0).y - attr->at(1).y));
        
        ofPoint centreBaton = ofPoint(Xpos, Ypos );
        
        NewAngle = baton.angle(ofVec2f(1.0f,0));
        
        float alpha = 0.2f;
        
        centroid.x = centroid.x*(1-alpha) + centreBaton.x*alpha;
        //centroid.y = centroid.x*(1-alpha) + centreBaton.x*alpha;
        
        
    }
    
    
    // Update angle
    
    
    anglePlanete.at(0) =  -NewAngle ;
    
    for(int i=0; i<(nbPlanet-1); i++){
        
        float actual = anglePlanete.at(i);
        float next = anglePlanete.at(i+1);
        
        next = next*(1.0f - alphangle ) + actual*alphangle;
        
        anglePlanete.at(i+1)=next;
        
        
    }
    
    
    
    
    float angle = ofGetElapsedTimef()*0.6f;
    ofPoint posPlanet;
    float radius;
    ofPolyline actualCircle;
    
    ofTranslate(centroid);
    
    ofPushMatrix();
    ofPushStyle();
    ofSetLineWidth(2);
    
    ofRotateX(80.0f);
    
    
    for(int i=0; i<nbPlanet; i++)
    {
        
        radius = radiusMax - (radiusMax-radiusMin)*i*1.0f/(nbPlanet*1.0f);
        angle *= 1.0f + i*0.05f;
        
        if((i+1)%2==0)angle *= -1.0f;
        
        posPlanet =ofPoint(radius*cosf(angle), radius*sinf(angle));
        ofSetColor(255,255,255);
        
        
        ofFill();
        
        ofRotateY(anglePlanete.at(i));
        
        //Draw planet
        
        float finalRadius = radius*sizePlanet;
        if(isBeat){
            finalRadius *=1.4;
            ofSetColor(ofRandom(100, 255),ofRandom(100, 255), 255 );
        }
        
        ofTranslate(posPlanet);
        ofRotateX(-80);
        ofCircle(ofPoint(0,0), finalRadius);
        ofNoFill();
        ofRotateX(80);
        ofTranslate(-posPlanet);
        
        //Draw trajectory
        ofSetColor(255);
        ofCircle(0,0, radius);
        ofRotateY(-anglePlanete.at(i));
        
        
        
    }
    
    ofPopStyle();
    ofPopMatrix();
    
}
