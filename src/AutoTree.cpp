 //
//  AutoTree.cpp
//  MursMurentDombres
//
//  Created by Aurélien Conil on 16/08/13.
//
//

#include "AutoTree.h"

AutoTree::AutoTree(){
    
}

AutoTree::AutoTree(VisuHandler * v):VisuClass(v){
    
   
    
    list.clear();

    myfbo = ofFbo();
    
    count = 0;
    introPhase = 0;
    
    settings.setName("AutoTree");
    
    MYPARAM(pointToBegin,ofVec2f(0.5),ofVec2f(0),ofVec2f(1));
    
    
    MYPARAM(initTrig,false,false,true);
    //initTrig.addListener(this, &AutoTree::startStop);
    MYPARAM(addPoint,false,false,true);
    
    MYPARAM(debugMode,false,false,true);
    MYPARAM(reset,false,false,true);

    MYPARAM(insideMode, false, false, true);

    
//    
//    MYPARAM(addTrig,false,false,true);
//    addTrig.addListener(this,&AutoTree::reset);
}

void AutoTree::setupData(){
        init();
    imagePart.loadImage("images/part.png");
    imagePart.setAnchorPercent(0.5, 0.5);
    addPoint.addListener(this, &AutoTree::addNewPoint);
        reset.addListener(this, &AutoTree::resetAll);
        insideMode.addListener(this, &AutoTree::switchMode);
}


void AutoTree::init(){

    width = ofGetWidth();
    height = ofGetHeight();
    //    ofPoint center = ofPoint(width/2.0f, height-10);
    //    Branche b = Branche( center,1.57f, 200, true);
    //    b.angle = 1.57f;
    //    b.lifeTime = 200;
    //    b.finalLength = 200;
    //    list.push_back(b);
    // myfbo = ofFbo();
    
    myfbo.allocate(width,height, GL_RGBA);
    
    myfbo.begin();
    ofClear(0, 0, 0, 255);
    myfbo.end();
    list.clear();
    
    
}

//--------------------------------------------------------------
void AutoTree::clear(){
 introPhase = 0;
    list.clear();
    
    if(myfbo.isAllocated()){
        myfbo.allocate(1,1,GL_RGBA);
      //  myfbo = ofFbo();
      // myfbo.~ofFbo();
    }
    
}


//--------------------------------------------------------------
void AutoTree::startStop(bool & start){
    
    
    if(start)
    {
        
        clear();
        init();
        bool isReset = true;
        resetAll(isReset);
        
    }
    else
    {
        
        clear();
        
    }
    
    
    
}

//--------------------------------------------------------------
void AutoTree::update(int w, int h){
    width = w;
    height = h;
}

//--------------------------------------------------------------
void AutoTree::draw(int width, int height)
{
    
    ofPushMatrix();
//    if (ofGetMousePressed())
//    {
//        reset(ofPoint(ofGetMouseX(), ofGetMouseY()));
//    }
    
    std::vector<Branche>::iterator it;
    vector<Branche> newBranche;
    ofPoint newBrancheP ;
    float newBrancheA;
    int newBrancheL;
    bool endOfBranche = false;
    
    ofPolyline blob;
    blob.clear();
    ofPolyline bigBlob;
    bigBlob.clear();
    
    if(dad->bH->getBlobs().size()>0 && insideMode){
        bigBlob = dad->bH->getBlobs(width,height).front();
        
    }
    bigBlob.close();
    
    
    
    //INtro
    if(initTrig )
    {
        int duree = 600; // 600
        float finalSize = 22.0f;
        introPhase++;
        
        if(introPhase< duree)
        {
        
            //--INTRO
            
            float size = (finalSize/(duree*1.0f))*(introPhase*1.0f);
            
            myfbo.begin();
            //ofClear(0, 0, 0, 255);
            ofSetColor(255, 255, 255, 5);

            imagePart.draw(pointToBegin.get()*ofVec2f(width,height) , size, size);
            myfbo.end();
        }
        else{
            
            
            //-- REAL TREE
            ofSetColor(255);
            myfbo.begin();
            
            //Update branches
            for (it = list.begin() ; it != list.end();  )
            {
                
                ofPoint pos = it->end;
                pos = pos/ofPoint(width, height);
                pos = pos*ofPoint(320,240);
                
                it->update(bigBlob, insideMode);
                
                // Branche is over
                if(it->lifeTime < 1 && !(it->isChildCreated)  )
                {
                    
                    if(it->totalLength < 400 && it->length> 10)
                    {
                        
                        newBranche.push_back(*it);
                        
                    }
                    
                    
                    list.erase(it);
                    
                    
                }
                // Branche is growing
                else
                {
                    ofEnableAlphaBlending();
                    it->draw();
                    ++it;
                    
                }
                
            }
            
            
            
            myfbo.end();
            
            
            //Create new branche
            if(newBranche.size()>0)
            {
                
                for (it = newBranche.begin() ; it != newBranche.end(); ++it  )
                {
                    
                    createBranche(it->end, it->angle, it->length, it->totalLength,  true);
                    
                }
                
            }
            
            
            
            
            
        }
        
    }
    

   // myfbo.updateTexture();
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    ofSetColor(255);
    myfbo.draw(0, 0,width,height);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
    if(debugMode){
    ofSetColor(255, 255, 100);
    ofNoFill();
    ofSetLineWidth(4);
    ofCircle(pointToBegin->x*width, pointToBegin->y*height,30);
        
        ofSetColor(255, 100, 255);
        bigBlob.draw();
    }
    
    ofPopMatrix();
}

//--------------------------------------
void AutoTree::switchMode(bool &isInside){
    
}

//--------------------------------------------------------------
void AutoTree::createBranche(ofPoint p, float a, int l,int tot,  bool isEnd){
    
    
    int nb;
    Branche b;
    bool isClockWise ;
    
    //if(l > 45){
    if(0){
    nb = (int)  2;
    }
    else
    {
        nb = (int) (ofRandomuf()*1.9+ 1.0);
    }
    
    
    for(int i=0; i<nb; i++)
    {
        isClockWise = false;
        float angle = ofRandom(0.0, 0.75);
        if((i+1)%2 == 0 ){
            angle = -angle;
            isClockWise = true;
        }
        angle = angle+a;
        
        b = Branche(p, angle, l,tot, isClockWise, &imagePart);
        list.push_back(b);
        
    }
    
    
    
}

//--------------------------------------------------------------
void AutoTree::resetAll(bool &isReset){
    
    
    list.clear();
    myfbo.allocate(width,height, GL_RGBA);
    
    myfbo.begin();
    ofClear(0, 0, 0, 255);
    myfbo.end();
    list.clear();
    
    initTrig = false;
    introPhase = 0;
    
}

//--------------------------------------------------------------
void AutoTree::addNewPoint(bool &newPoint){
    
    if(newPoint){
    
        if(list.size()==0 && !initTrig)
        {
            initTrig = true;
            introPhase = 0;
        }
        
        float n = 3.0f;
        float angle = 2*PI/n;
        float curAngle = ofRandomuf()*3.14;
        
    //    if(pointToBegin->x * pointToBegin->y == 0 )
    //    if(dad->attr->getType(0).size()>0)
    //        pointToBegin = dad->attr->getType(0)[0]*ofVec2f(width,height);
        
        
        for(int i=0; i<n; i++){
            
            float finalAngle = curAngle ;
            Branche b = Branche( pointToBegin.get()*ofVec2f(width,height),finalAngle,0, 200, false, &imagePart);
            b.lifeTime = 13 + ofRandomuf()*30.0f;
            b.finalLength = b.lifeTime;
            if((i+1)%2 == 0 ){
                //b.angle *= -1.0f;
                b.clockWise = true;
            }
            list.push_back(b);
            
            
            curAngle +=angle;
            
            
        }
        
        
    }
    
    
    
    //    Branche b = Branche( p,1.47f, 50, false, &imageLeaf);
    //
    //    b.lifeTime = 50;
    //    b.finalLength = 50;
    //    list.push_back(b);
    //
    //
    //
    //    b = Branche( p,0.8, 150, true, &imageLeaf);
    //        b.lifeTime = 40;
    //    b.finalLength =40;
    //    list.push_back(b);
    //
    //
    //
    //    b = Branche( p , 2.2f, 150, false, &imageLeaf);
    //
    //    b.lifeTime = 45;
    //    b.finalLength = 45;
    //    list.push_back(b);
    

    
    
}


//--------------------------------------- BRANCHE --------------

Branche::Branche(){
    
    
}

Branche::Branche( ofPoint b, float a, int actualL,int totalL, bool isClockWise, ofImage* img){
    
    begin =b;
    end =b;
    
    isGrowing = true;
    isChildCreated = false;
    lifeTime = (int) ofRandom(actualL/1.5f, actualL/0.6f);
    finalLength = (float)lifeTime;
    totalLength = totalL + finalLength;
    
    clockWise=isClockWise;

    angle = a;
    length = 0.0f;
    
    leaf = img;
    
    lastTimeBouncing = 0;
        
}



void Branche::update(ofPolyline poly, bool insideMode){
    
    int maxLife = 200;
    
    float speed = 0.06f; //0.2f
    
    if(insideMode && !poly.inside(end) ){
        isGrowing = false;
    }
    if(insideMode && poly.inside(end)){
        isGrowing = true;
    }
    
    if(isGrowing)
    {

        
        lifeTime -= speed;
        length += speed;
        
//        float curve = (200/finalLength)*0.0007;
//        if (clockWise) curve *= -1.0f;
        float curve = (cos(length*0.05)*0.003);
        if (clockWise) curve *= -1.0f;
        
        angle +=  curve;
        
        
        
    }
    if (lifeTime<0 ){
        
        isGrowing = false;
        isChildCreated = true;
    }
    
    if(isGrowing)
    {
        end = ofPoint( begin.x + length*cos(-angle), begin.y + length*sin(-angle));
    
    }
    
    
}

void Branche::draw(){
    
    
    
   // float radius = 4.0 + finalLength/60.0f;
    float radius = 1.0 ;
    if(radius<1.0f) radius = 1.0f;
    ofSetColor(255,255,255,85);
    
    if(isGrowing){
        
        ofPushMatrix();
        ofCircle(end, radius);
        
//        if(ofRandomf()>0.90 && finalLength < 56)
//        {
//            
//            ofTranslate(end);
//            ofRotateZ(RAD_TO_DEG*angle);
//            leaf->draw(0, 0);
//            
//        }
        ofPopMatrix();
        
    }
    
    
}
