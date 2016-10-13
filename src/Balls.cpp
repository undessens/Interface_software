//
//  Balls.cpp
//  Balls_and_links
//
//  Created by Conil Aurélien on 03/02/2014.
//
//

#include "Balls.h"

BouncingBall::BouncingBall(){}

BouncingBall::BouncingBall( ofPoint posin, ofVec2f speedin ){
    
    pos = posin;
    speed = speedin;
    
    size = 10;
    
    thresh = 0.00001;
    
    bounce = false;
    
    
}

BouncingBall::BouncingBall( ofPoint posin, ofVec2f speedin , float sizein, ofColor colin, ofImage* imgin,bool* useGridin,
                           int* numColin, int* numRowin, bool* useBorderin, bool* useTorin,ofParameter<float>* gridForcein,
                           ofParameter<float>* userForcein,ofParameter<float>* gridOpenin, bool* insideModein , int* dieModein, int lifeTimein,
                           ofPoint* centroidPolyin, ofVec2f* speedCentroidin, ofVec2f* gravityin){
    
    
    pos = posin;
    speed = speedin;
    size = sizein;
    imgPart = imgin;
    
    origin = posin;
    
    isVisible = true;
    dieAfterBounce = false;
    
    color = colin;
    numRow = numRowin;
    useGrid = useGridin;
    useBorder = useBorderin;
    useTor = useTorin;
    gridForce = gridForcein;
    userForce = userForcein;
    gridOpen = gridOpenin;
    insideMode = insideModein;
    dieMode = dieModein;
    lifeTime = lifeTimein;
    
    centroid = centroidPolyin;
    centroidSpeed = speedCentroidin;
    
    gravity = gravityin;
    
}

int BouncingBall::update(ofPolyline poly, int w, int h){
    
    
    float t = 4.0f/(ofGetFrameRate());
    
    // Timelife
    int isDying = 1;
    
    if(*dieMode == 2){
        lifeTime--;
    }
    if(lifeTime == 0){
        return 0;
    }
    
    
    
    //--- is Boucing ? ----
    
    bool isInside = (poly.inside(pos) && !*useGrid);
    
    if(isInside != *(insideMode))
    {
        
        if(*dieMode == 3){
            return 0;
        }
        
        //---find closest index;
        float minLenght = 1000;
        int finalindex;
        
        for(int i=0 ; i<poly.size() ; i++){
            
            float length = ( pos.x - poly[i].x)*( pos.x - poly[i].x) + ( pos.y - poly[i].y)*( pos.y - poly[i].y);
            
            if(length<minLenght){
                
                minLenght= length;
                finalindex = i;
            }
            
        }
        
        bounce = true;
        speed = speed * 0.85;
        
        normal = poly.getNormalAtIndex(finalindex);
        normal.normalize();
        
        if(!*insideMode){
            speed = speed.length()*normal*(-1.0f);
        }
        else{
            speed = speed.length()*normal*(1.0f);
        }
        
        speed = speed + *(centroidSpeed);
        
        pos = pos +  speed*t + *(gravity);
        
        
        
    }
    else
    {
        bounce = false;
        float damping = 0.95;
        float mass = 10;
        
        
        
        
        //origin and grid moved from user
        if(*useGrid)
        {
            
            bool isBlob = poly.size()>2;

            ofPoint centroidBlob = poly.getCentroid2D();
            float alpha;
            float indexRow = origin.x /(1.0f) - 0.5f;
            float indexCol = origin.y/(1.0f) - 0.5f;
            
            alpha = indexRow*indexRow + indexCol*indexCol;
            alpha = alpha + 0.5;
            alpha = pow(alpha, *gridOpen);

            
            ofPoint finalPos;
            if(isBlob)
            finalPos= centroidBlob*(1 -alpha) + origin*(alpha);
            else finalPos = origin;
            
            ofPoint force = ( finalPos - pos) * (*gridForce);

            speed = damping * ( speed + force/mass);
        }
        
        //Limit speed
        //        if(speed.length() > 1.5){
        //            speed *= 0.95;
        //        }
        
        
        //gravity
        speed += *gravity;
        pos = pos +  speed*t ;
        
        
        
        
        // Die mode 1 : die out of the border OR if the speed is null
        
        if(*dieMode == 1 && ( pos.x > 1.0 || pos.y > 1.0 || pos.x < 0.0 || pos.y < 0.0)){
            isDying = 0;
        }
        if(*dieMode== 1 && speed.length()<0.0001){
            isDying = 0;
        }
        
        // Is boucing over the edges ?
        
        bool isUsedTor = *(useTor);
        if( isUsedTor)
        {
            
            if(pos.x < 0.0 ){
                pos.x = 1.0;}
            if( pos.x > 1.0){
                pos.x = 0.0;
            }
            if(pos.y < 0.0 ){
                pos.y = 1.0;}
            if( pos.y > 1.0){
                pos.y = 0.0;
            }
            
            
        }
        if( *(useBorder))
        {
            
            if(pos.x < 0.0 ){
                speed.x *= -0.99f;}
            if( pos.x > 1.0){
                speed.x *= -0.99f;
            }
            if(pos.y < 0.0 ){
                speed.y *= -0.90f;
                speed.x += 0.002*ofRandomf();
            }
            if( pos.y > 1.0){
                speed.y *= -0.90f;
                speed.x += 0.002*ofRandomf();
            }
            
        }
        
    }
    
    return isDying;
    
    
    
}

void BouncingBall::draw(int w,int h){
    
    
    ofPushMatrix();
    int alpha = 255;
    
    if(*dieMode==2 && lifeTime<25){
        
        alpha = (int) lifeTime*10;
        
    }
    
    ofSetColor(color.r, color.g, color.b, alpha);
    ofFill();
    
    if(bounce){
        
        imgPart->draw(pos.x*w - size/2.0f, pos.y*h - size/2.0f, size, size );
        //        ofSetColor(color.r, color.g, color.b, 100);
        //        ofCircle(pos.x*w, pos.y*h, size);
        //        ofSetColor(color.r, color.g, color.b, 200);
        
    }
    else{
        //        ofSetColor(color.r, color.g, color.b, 50);
        //        ofCircle(pos.x*w, pos.y*h, size);
        //        ofSetColor(color.r, color.g, color.b, 100);
        //        ofCircle(pos.x*w, pos.y*h, 5);
        imgPart->draw(pos.x*w - size/2.0f, pos.y*h - size/2.0f, size, size );
        // ofCircle(origin.x*w, origin.y*h, 2);
        
    }
    
    
    ofPopMatrix();
    
    
}





