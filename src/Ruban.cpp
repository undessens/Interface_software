//
//  Ruban.cpp
//  MursMurentDombres
//
//  Created by Aurélien Conil on 16/08/13.
//
//

#include "Ruban.h"

Spring::Spring(){
    
}

Spring::Spring(float xpos, float ypos, float m, float g, float i, float s) {
    x = xpos;
    y = ypos;
    mass = m;
    gravity = g;
    initialSize = i;
    stiffness = s;
    radius = 5;

 damping = 0.6;
}

void Spring::update(ofPoint target) {
    
    ofPoint sp = ofPoint(x,y);
    
    if((target-sp).length()> initialSize){
    
    float forceX = (target.x - x) * stiffness;
    float ax = forceX / mass;
    vx = damping * (vx + ax);
    
    float forceY = (target.y - y) * stiffness;
    forceY += gravity;
    float ay = forceY / mass;
    vy = damping * (vy + ay);
    }
    
    x += vx;
    y += vy;
}


void Spring::draw(ofPoint p) {
    
    ofCircle(x, y, 20);
    
}


//-----------------------------------------------------------------------------

ruban::ruban(){
    
    
}

ruban::ruban(ofPoint pos, float stiffness, int length ){
    
    
    nbSpring = 20;
    float gravity = 0.3;
    float mass = 2.2;
    float spSize = 3.0;
    //stiffness = 0.55;
    
    for( int i=0;i<nbSpring; i++){
        
        Spring sp1 = Spring(0, 0, (mass + i*0.02), gravity, spSize, (stiffness - i*0.001));
        
        rub1.push_back(sp1);
        rub2.push_back(sp1);
        
    }
    mypath.clear();
    mypath.setFilled(TRUE);
    mypath.setFillColor(ofColor(0,0,255));
    
    pointCol = ofColor(0,120,210);
    stillMoving = false;
    
}

int ruban::update(ofPoint externControl, int channel, float argument,ofVec3f vout){
    
    Spring actual1, prev1, actual2, prev2;
    float sizex, sizey;
    actual1 = rub1.at(0);
    sizex = abs(actual1.vy)* 0.3  + 2 ;
    sizey = abs(actual1.vx)* 0.45  + 2;
    
    int note = 0; // 0 = nothing ; 1 = note ON ; 2 = note off;
    
    //Speed stuff
    speedDiff =  sqrt(actual1.vy*actual1.vy + actual1.vx*actual1.vx );
    if(speedDiff > 50) strong = true;
    else strong = false;
    if( speedDiff < 6 && stillMoving)
    {
        stillMoving = false;
        note = 2;
    }
    if( !stillMoving && speedDiff > 20 ){
        
        stillMoving = true;
        
        mypath.setFillColor(pointCol);
        note = 1;
    }
    
    mypath.clear();
    mypath.curveTo(pos1.x-sizex, pos1.y-sizey);
    
    if(externControl.x * externControl.y > 0)
    pos1 = externControl;
    
    
    
    for(int i=0; i<nbSpring; i++){
        
    rub1.at(i).x+=vout.x;
    rub1.at(i).y+=vout.y;    
    rub2.at(i).x+=vout.x;
    rub2.at(i).y+=vout.y;
        
        
        actual1 = rub1.at(i);
        actual2 = rub2.at(i);
        if(i==0){
            rub1.at(i).update(ofPoint(pos1.x -sizex, pos1.y-sizey));
            //actual1.draw(ofPoint(ofGetMouseX(), ofGetMouseY()-5));
            rub2.at(i).update(ofPoint(pos1.x +sizex, pos1.y+sizey));
            //actual2.draw(ofPoint(ofGetMouseX(), ofGetMouseY()+5));
        }
        else{
            prev1 = rub1.at(i-1);
            prev2=  rub2.at(i-1);
            rub1.at(i).update(ofPoint(prev1.x , prev1.y));
            //actual1.draw(ofPoint(prev1.x,prev1.y));
            rub2.at(i).update(ofPoint(prev2.x , prev2.y));
            //actual2.draw(ofPoint(prev2.x,prev2.y));
            
        }
        
        mypath.curveTo(actual1.x - sizex, actual1.y);
        
        
    }
    
    for(int i=(nbSpring-1); i>=0; i--){
        
        actual1 = rub2.at(i);
        mypath.curveTo(actual1.x, actual1.y);
        
    }
    
    mypath.curveTo(pos1.x + sizex, pos1.y+sizey);

    return note;
    
    
}

void ruban::draw(ofColor color)
{
    ofPushMatrix();
    
    ofFill();
    ofSetColor(255);
    if(mypath.getFillColor() != color){
        mypath.setFillColor(color);
    }
    mypath.draw();
    
    
//------------Debug music sending-------
//    if( stillMoving){
//        ofSetColor(pointCol);
//        
//        if(strong)
//        ofCircle(300, 300, 80);
//        else
//        ofCircle(300, 300, 40);
//    }
   
    
    ofPopMatrix();
}

void ruban::changeStiffness(float stif){
    
    if(rub1.size()==rub2.size())
    {
        
        for(int i=0; i<rub1.size(); i++)
        {
            float finalStiff = (stif - i*0.001);
            rub1.at(i).stiffness = finalStiff;
            rub2.at(i).stiffness = finalStiff;
        }
            
    }
    
}

void ruban::changeLength(float length){
    
    if(rub1.size()==rub2.size())
    {
        
        for(int i=0; i<rub1.size(); i++)
        {
            rub1.at(i).initialSize = length;
            rub2.at(i).initialSize = length;
        }
        
    }
    
}






//------------------------------------------------------------------------------



ColorRuban::ColorRuban(VisuHandler *v):VisuClass(v){
    
    ofPoint pos = ofPoint( 0, 0);
    ofPoint angle = ofPoint();
    MYPARAM(onPause,false,false,true);
    MYPARAM(stiffness,0.55f,0.f,2.0f);
    MYPARAM(timestep,0.02f,0.f,0.1f);
    MYPARAM(color,ofVec3f(255),ofVec3f(0),ofVec3f(255));
    MYPARAM(vout, ofVec3f(0),ofVec3f(-50),ofVec3f(50));
    MYPARAM(alpha,255,0,255);
    MYPARAM(length, 3.0, 0.1f, 10.0f);
    MYPARAM(curFamilly, 1, 0, 2);
    MYPARAM(isHidden, true, false, true);
    stiffness.addListener(this, &ColorRuban::changeStiffness);
    length.addListener(this, &ColorRuban::changeLength);
    init(pos, angle);
    
#ifdef OSCSEND
    setupb = false;
#endif
    settings.setName("ColorRuban");
    
}


void ColorRuban::init(ofPoint pos, ofPoint angle){
    
    int length = (int) ofRandom(8.0f, 18.0f);
//    float stiff = ofRandom(0.06f, 0.16);
    
//    stiff = 0.02;
        
    ruban1 = ruban(pos, stiffness, length);
    
    onPause = false;

    
}

int ColorRuban::update( int channel, float argument, int w , int h){
    
    
#ifdef OSCSEND
    if(!setupb)
    {
        
        setupb = true;
        musicSender.setup("localhost", 12351);
    }
#endif
    std::vector<ruban>::iterator it;

    int num=0;
    ofPoint control;
    int note=0;
    vector<ofPoint> attr = dad->attr->getType(curFamilly,w,h);
    
    if(!onPause){
        
        if( attr.size()>0 )
        {
        
            for( int i=0;i<attr.size();i++){
                
                 
                note = ruban1.update(attr[i], channel, argument,vout);
                
            }
                    
            
        
        }
        else
        {
            ruban1.update(ofPoint(0,0), channel, argument,vout);
        }
    }
    
#ifdef OSCSEND
    
    if(note>0){
    
        int value ;
        if ( note ==1) value = 1;
        if (note ==2) value = 0;
        
    ofxOscMessage msg =  ofxOscMessage();
    msg.setAddress("flute");
    msg.addIntArg(value);
        
        musicSender.sendMessage(msg);
        
    }
    
#endif

    return 1;
    
}

void ColorRuban::draw(int w, int h){
    
    //update(0, 0, w, h);
    
    if(!isHidden){
    ofColor col = ofColor(color->x, color->y, color->z);
    ruban1.draw(col);
    }
}

void ColorRuban::changeStiffness(float &f){
    ruban1.changeStiffness(f);
}

void ColorRuban::changeLength(float &f){
    ruban1.changeLength(f);
}


