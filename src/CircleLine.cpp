//
//  CircleLine.cpp
//  MurMurDombre
//
//  Created by Conil Aurélien on 25/02/2014.
//
//

//TODO: make it a visuClass

#include "CircleLine.h"


CircleLine::CircleLine(){}

CircleLine::CircleLine(vector<ofPoint>* attrin,vector<int>* famillyin, int w, int h){
    
    attr = attrin;
    familly = famillyin;
    isLine = false;
    isCircle = false;
    listOfCentroid.clear();
    pointToCircle.clear();
    
    myfbo.allocate(w,h, GL_RGBA);
    
    myfbo.begin();
    ofClear(0, 0, 0, 255);
    myfbo.end();
    
    
    
}

void CircleLine::update(int w , int h){
    
    listOfCentroid.clear();
    pointToCircle.clear();
    listOfTop.clear();
    
    if(attr->size() == familly->size() ){
    
        for(int i=0; i<attr->size(); i++)
        {
          
            if(familly->at(i) == 0)listOfCentroid.push_back(attr->at(i));
            //if(familly->at(i) == 3)listOfTop.push_back(attr->at(i));
            //if(familly->at(i) == 4)pointToCircle.push_back(attr->at(i));
            
        }
        
    }

    isCircle = false;
    
    // Check is line
    if(listOfCentroid.size() > 0)
    {
        
        isLine = true;
//        linePos = (listOfCentroid.at(0) + listOfCentroid.at(1) )/ 2.0f;
//        linePos *= ofPoint(w, h);
        
//        ofVec2f blob1 =  listOfCentroid.at(0) - listOfTop.at(0);
//        ofVec2f blob2 =  listOfCentroid.at(1) - listOfTop.at(1);
//        
//        float angle1 = blob1.angle(ofVec2f(1.0, 0.0))*DEG_TO_RAD;
//        float angle2 = blob2.angle(ofVec2f(1.0,0.0))*DEG_TO_RAD;
//        
//        float moy = (angle1+angle2)/2.0f;
//        
//        riverOfLine.addLine(linePos, -1.57);
//        if(ofRandomuf()>0.5)
//        riverOfLine.addLine(listOfCentroid.at(0),angle1);
//        if(ofRandomuf()>0.5)
//        riverOfLine.addLine(listOfCentroid.at(1), angle2);
        

        
    }
    else
    {
        isLine = false;
    }
    
    
//    if(ofGetMousePressed()){
//        
//        ofPoint mouse = ofPoint(ofGetMouseX(), ofGetMouseY());
//        float angle = 1.57f;
//        isLine = true;
//        
//        
//        
//        riverOfLine.addLine(mouse, angle);
//        
//    }
    
//    if(isLine){
//        riverOfLine.update(0, 0);
//    }
//    else{
//        riverOfLine.obj.clear();
//    }
    
    
    
}

void CircleLine::draw(int w, int h){
    
    myfbo.begin();
    ofClear(0, 0, 0, 255);
    myfbo.end();

    if(isLine){
    //riverOfLine.draw();
        ofSetLineWidth(8.0f);
        
        if( listOfCentroid.size()>=2){
            
            ofPoint left, right;
            
            if(listOfCentroid.at(0).x < listOfCentroid.at(1).x){
                
                left = listOfCentroid.at(0)* ofPoint(w,h);
                right = listOfCentroid.at(1)*ofPoint(w,h);
                
            }
            else
            {
                left = listOfCentroid.at(1)* ofPoint(w,h);
                right = listOfCentroid.at(0)*ofPoint(w,h);
            }
            
            myfbo.begin();
            
            ofSetColor(255);
            ofLine(ofPoint(0,0), left);
            ofLine(ofPoint(0,h), left);
            
            ofLine(ofPoint(w,0), right);
            ofLine(ofPoint(w,h), right);
            
            myfbo.end();
            
            
            
        }
            
            
            
        
        
    }
    
    if(isCircle)
    {
      
        std::vector<ofPoint>::iterator it;
        for(it = pointToCircle.begin(); it<pointToCircle.end(); it++)
        {
            ofSetColor(255);
            ofNoFill();
            ofCircle(*it *ofPoint(w,h), 90);
            
        }
        
    }
    
    
    ofEnableBlendMode(OF_BLENDMODE_MULTIPLY);
    ofSetColor(255);
    myfbo.draw(0, 0);
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    
}






//------------------------------- River of Line ---------------------------------------
lotOfLine::lotOfLine(ofPoint pos, float angle){
    
   // init( pos,  angle);
    obj.clear();
    
    
}

lotOfLine::lotOfLine(){
    
}

void lotOfLine::addLine( ofPoint pos, float angle){
    
    //int nbLigne = (int) ofRandom(2.0f);
    int nbLigne = 1;
    
    float a = 30.0;
    float b = 10.0;

    
    for(int i=0;i<nbLigne; i++ )
    {
        
        ofPoint linePos = ofPoint(pos.x + ofRandom(-a, a), pos.y + ofRandom(-b, b));
        float thickness = ofRandom(1.0, 5.0);
        float length = (int) (thickness*10 + 200 +ofRandomuf()*400);
        
        if(ofRandomuf()>0.5) angle = -angle;
        
        movingline myLine = movingline(linePos, angle, thickness, length);
        obj.push_back(myLine);
        
    }
    
    
}

int lotOfLine::update( int channel, float argument){
    
    std::vector<movingline>::iterator it;
    int totalOfLife = 0;
    ofPoint control = ofPoint();
    for (it = obj.begin() ; it != obj.end(); )
    {
        int res =  (it)->update();
        totalOfLife += res;
        
        if(res==0){
            obj.erase(it);
        }
        else{
            ++it;
        }
    }
    
    
    if (totalOfLife == 0)
        return 0;
    else return 1;
    
    
}

void lotOfLine::draw(){
    
    std::vector<movingline>::iterator it;
    for (it = obj.begin() ; it != obj.end(); ++it)
    {
        (it)->draw();
    }
    
    
}


//--------------------------------Line----------------------------------------------------

movingline::movingline(){}

movingline::movingline(ofPoint pos, float a, float t, float l){
    
    
    begin = pos;
    end = pos;
    angle = a;
    thickness = t;
    length = 0.0f;
    maxLength = l;
    length =  0;
    
    life = 0;
    lifeTime =(int) 2* l;
    
    isBlack = false;
    
}

int movingline::update(){
    
    
    //Update length and position
    int speed = 10;
    
    
    // if the line is growing
    if ( life < lifeTime / 2)
    {
        length += speed;
        end = ofPoint ( begin.x + length*cos(angle), begin.y +length*sin(angle));
        
    }
    else
    {
        
        length -=speed;
        begin = ofPoint (end.x - length*cos(angle),end.y - length*sin(angle));
        
    }
    
    life +=speed;
    if(life>lifeTime) return 0;
    else return 1;
    
}

void movingline::draw(){
    
    ofSetLineWidth(thickness);
    if(isBlack)
        ofSetColor(0);
    else
        ofSetColor(255);
    ofLine(begin, end);
    
    
}