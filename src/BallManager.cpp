//
//  BallManager.cpp
//  Balls_and_links
//
//  Created by Conil Aurélien on 03/02/2014.
//
//

#include "BallManager.h"

BallManager::BallManager(VisuHandler * v):VisuClass(v){
    settings.setName("BallManager");
    int num = 25;
    imgPart.loadImage("images/ballPart.png");
    
    centroidPoly = ofPoint( 0.5, 0,5);
    centroidSpeed = ofVec2f( 0.0, 0.0);
    
    MYPARAM(usePointEmitter,true,false,true);
    MYPARAM(noiseF,ofVec2f(0),ofVec2f(0),ofVec2f(1));
    MYPARAM(emitter,ofVec2f(0),ofVec2f(0),ofVec2f(1));
    MYPARAM(emission,0.0,0.0f,1.0f);
    MYPARAM(mode,0,0,10);
    MYPARAM(lifeTime,100,0,2000);
    MYPARAM(gridForce, 0.0f, 0.0f, 1.0f);
    MYPARAM(userForce, 1.0f, 0.0f, 1.0f);
    MYPARAM(gridOpen, 1.0f, 0.1f, 2.0f);
    
    
    mode.addListener(this,&BallManager::changeMode);
    int m = 0;
    changeMode(m);
}


//-------------------------------------------------------------
void BallManager::update(int w,int h){

    globalWidth = w;
    globalHeight = h;
    
    bool isblob = false;
    bool is2blob = false;

    
    sizedPolyline.clear();
    ofPolyline middlePolyline;
    ofPolyline secMiddlePolyline;
    ofPolyline smallPolyline;
    smallPolyline.clear();
    ofPolyline secSmallPolyline;
    secSmallPolyline.clear();
    
    if(dad->bH->getBlobs().size()>0)
    {
      
        middlePolyline = dad->bH->getBlobs(w,h).front();
        //middlePolyline.simplify(7.0f);
        for(int i=0; i<middlePolyline.size(); i++)
        {
            
            ofPoint p = middlePolyline[i]/ofPoint(w,h);
            smallPolyline.lineTo(p);
            
        }
        smallPolyline.close();
        isblob = true;
        
        if(dad->bH->getBlobs().size()>1)
        {
            
            secMiddlePolyline = dad->bH->getBlobs(w,h).at(1);
            for(int i=0; i<secMiddlePolyline.size(); i++)
            {
                
                ofPoint p = secMiddlePolyline[i]/ofPoint(w, h);
                secSmallPolyline.lineTo(p);
                
            }
            secSmallPolyline.close();
            is2blob = true;
            
        }
        
        
        
    }
    

    
    
    if(isblob && !usePointEmitter &&!useGrid)
    {
        

        
        float t = 1.0f/(ofGetFrameRate()/4.0f);
        ofPoint newcentroid = smallPolyline.getCentroid2D();
        centroidSpeed = ((newcentroid - centroidPoly)/t )* 0.65f;
        
        if(ofRandomuf()<emission )
        {
            ofPoint finalEmitter = newcentroid;
            ofPoint speed = centroidSpeed;
            
            speed.normalize();
            
            speed = speed * 0.1;
            
            ofPoint pos = finalEmitter + ofPoint( 0.04*ofRandomf(), 0.04*ofRandomf());
            ofColor color ;
            color.setHsb(ofRandom(255), 10, 255);
            
            
            addBall(pos, speed, color, 10 + ofRandom(20));
        }

         centroidPoly = newcentroid;
    }
    
    if(ofRandomuf()<emission  && usePointEmitter &&!useGrid)
    {
        
        
        ofPoint noise = noiseF.get()*ofVec2f(ofRandomf());
        ofPoint speed = ofPoint(0, 0.01);
        speed +=noise;
        speed *= 0.6f;
        
        ofPoint finalEmitter = emitter.get();

        ofPoint pos = finalEmitter + ofPoint( 0.04*ofRandomf(), 0.04*ofRandomf());
        ofColor color ;
        color.setHsb(ofRandom(255), 10, 255);
        
        
        addBall(pos, speed, color, 4 + ofRandom(8));
        
    }
    
    
    for( vector<BouncingBall>::iterator it = listOfBalls.begin(); it < listOfBalls.end() ; )
    {
        
        int res = 1;
        
        // ONE BLOB
        if(!is2blob){
        
        res = it->update(smallPolyline, w, h);
            
        }
        // TWO BLOB
        else if(useGrid){
            
            ofPoint c1 = smallPolyline.getCentroid2D();
            ofPoint c2 = secSmallPolyline.getCentroid2D();
            ofPoint ori = it->origin;
            
            if( c1.distance(ori) < c2.distance(ori) ){
                
                res =it->update(smallPolyline, w, h);
                
            }
            else{
                
               res = it->update(secSmallPolyline, w, h);
            }
            
            
        }
        
        
        if(res == 0)
        {
            listOfBalls.erase(it);
        }
        else
        {
            it++;
        }
    }
    
    
   
    

}

//-------------------------------------------------------------
void BallManager::draw(int w, int h){
    
    ofEnableAlphaBlending();
    
    if(drawPart)
    {
        
        for(int i=0; i<listOfBalls.size(); i++)
        {
            (listOfBalls.at(i)).draw(w, h);
        }
        
    }
    
    ofSetColor(255);
    ofSetLineWidth(2.0f);
    //sizedPolyline.draw();
    

    
    if(drawGrid)
    {
        ofSetColor(255);
        ofSetLineWidth(2.0f);
        for (int i=0; i<numRow; i++)
        {
            
            for(int j=0; j<numCol; j++)
            {
                
                int index = numCol*i + j;
                
                if(index<listOfBalls.size() && useGrid)
                {
                    
                    if(j>0)
                    {
                        ofLine(listOfBalls.at(index).pos*ofPoint(w, h),listOfBalls.at(numCol*i + (j-1)).pos*ofPoint(w,h));

       
                    }
                    if(i>0)
                    {
                        ofLine(listOfBalls.at(index).pos*ofPoint(w, h),listOfBalls.at(numCol*(i-1) + j).pos*ofPoint(w,h));
                    }
                    
                
                }
                
            }
            
        }
        
    }
    
    

    
    
}

//-------------------------------------------------------------
void BallManager::addBall(ofPoint posin, ofPoint speedin, ofColor colin, float sizein){
    
    int life = (int) lifeTime + ofRandom(100);
    
    BouncingBall ball = BouncingBall(posin, speedin,sizein,colin , &imgPart,&useGrid,&numCol,&numRow,&useBorder, &useTor
                                     ,&gridForce,&userForce,&gridOpen, &insideMode , &dieMode, lifeTime, &centroidPoly, &centroidSpeed, &gravity);
    listOfBalls.push_back(ball);
    
    
}

//-------------------------------------------------------------
void BallManager::calcGrid(int w , int h){
    
    int num = listOfBalls.size();
    float ratio = w*1.0f / h*1.0f ;
    
    numRow = sqrt(num*1.0f/ratio);
    numCol = numRow*ratio;
    
    num = numRow * numCol;
    
    for(vector<BouncingBall>::iterator it = (listOfBalls.begin()+num); it<listOfBalls.end() ;){
        
        listOfBalls.erase(it);
        
    }
    
    float spaceW = 1.0 / numCol;
    float spaceH = 1.0 / numRow;
    
    for (int i=0; i<numRow; i++)
    {
        
        for(int j=0; j<numCol; j++)
        {
          
            int index = numCol*i + j;
            ofPoint pos = ofPoint(spaceW/2.0f + j*spaceW, spaceH/2.0f + i*spaceH );
            
            if(index<listOfBalls.size())
            {
            listOfBalls.at(index).origin = pos;
            }
            
        }
        
    }
    
    
}

//-------------------------------------------------------------
void BallManager::explosion( int mode){
    
    switch (mode) {
        case 0:            
            for(vector<BouncingBall>::iterator it = listOfBalls.begin(); it<listOfBalls.end() ;it++)
            {
                it->pos = ofPoint(ofRandomuf(), 1.0f);
                it->speed = ofVec2f(ofRandom(-0.1, 0.1), -1.1f -0.8*ofRandomuf());
                
            }
            break;
        case 1:
            for(vector<BouncingBall>::iterator it = listOfBalls.begin(); it<listOfBalls.end() ;it++)
            {
                it->pos = ofPoint( 0.0f, ofRandomuf());
                it->speed = ofVec2f( +0.3f +0.4*ofRandomuf(), ofRandom(-0.1, 0.1));
                
            }
            break;
        case 2:
            for(vector<BouncingBall>::iterator it = listOfBalls.begin(); it<(listOfBalls.end()-listOfBalls.size()/2.0f) ;it++)
            {
                it->pos = ofPoint( 0.0f, ofRandomuf());
                it->speed = ofVec2f( +0.3f +0.4*ofRandomuf(), ofRandom(-0.1, 0.1));
                
            }
            for(vector<BouncingBall>::iterator it = (listOfBalls.end()-listOfBalls.size()/2.0f); it<listOfBalls.end() ;it++)
            {
                it->pos = ofPoint( 1.0f, ofRandomuf());
                it->speed = ofVec2f( -0.3f -0.4*ofRandomuf(), ofRandom(-0.1, 0.1));
                
            }
            
            break;
            
            
        default:
            break;
    }
    

    
}

//-------------------------------------------------------------
void BallManager::changeMode(int & m){
    
    
    //Die mode ------- 0 : rien || 1 : bordures || 2 : temps
    
    
    
    switch (m) {
            case 0:
                //TOr
                setNum(0);
                drawGrid = false;
                drawPart = false;
                useGrid =true;
                gridForce = 0.0;
                useBorder = false;
                useTor = true;
                insideMode = false;
                dieMode = 0;
                emission = 0.0;
                usePointEmitter = false;
                gravity = ofVec2f(0.0, 0.0);
            break;
            case 1:{
                //TOr
                setNum(1);
                setNum(30);
                calcGrid(globalWidth, globalHeight);
                drawGrid = true;
                drawPart = true;
                useGrid =true;
                gridForce = 0.0;
                useBorder = false;
                useTor = true;
                insideMode = false;
                dieMode = 0;
                emission = 0.0;
                usePointEmitter = false;
                gravity = ofVec2f(-0.01, 0.02);
                break;}
            case 2:{
                //border
                setNum(30);
                drawGrid = false;
                drawPart = true;
                useGrid = false;
                useBorder = true;
                useTor = false;
                gridForce = 0.0;
                insideMode = false;
                dieMode = 0;
                emission = 0.0;
                usePointEmitter = false;
                gravity = ofVec2f(0, 0);
            }
            break;
            case 3 : {
                setNum(0);
                drawPart = true;
                drawGrid = false;
                useGrid = false;
                useBorder = true;
                useTor = false;
                gridForce = 0.2;
                insideMode = false;
                dieMode = 2;
                emission = 0.0;
                usePointEmitter = true;
                gravity = ofVec2f(0, 0.0003);
                }
            break;
            case 4 : {
                // Tor with time
                drawPart = true;
                drawGrid = false;
                useGrid = false;
                useBorder = false;
                useTor = false;
                gridForce = 0.2;
                insideMode = false;
                dieMode = 1;
                emission = 0.9;
                usePointEmitter = false;
                gridForce = 0.1;
                gravity = ofVec2f(0, 0.0);
                }
            break;
            case 5 : {
                // Grid
                setNum(0);
                setNum(25);
                calcGrid(globalWidth, globalHeight);
                drawPart = false;
                drawGrid = true;
                useGrid = true;
                useBorder = false;
                useTor = false;
                //gridForce = 0.9;
                insideMode = false;
                dieMode = 0;
                emission = 0.0;
                usePointEmitter = false;
                gravity = ofVec2f(0, 0);
            }
                break;
            case 6 : {
                // Grid dying if it is inside
                setNum(0);
                setNum(25);
                calcGrid(globalWidth, globalHeight);
                drawPart = false;
                drawGrid = true;
                useGrid = true;
                 useBorder = false;
                useTor = false;
                //gridForce = 0.7;
                insideMode = false;
                dieMode = 0;
                emission = 0.0;
                usePointEmitter = false;
                gravity = ofVec2f(0, 0);
            }
                break;
        case 7 : {
            // Grid dying if it is inside
            setNum(0);
            setNum(40);
            calcGrid(globalWidth, globalHeight);
            drawPart = false;
            drawGrid = true;
            useGrid = true;
            useBorder = true;
            useTor = false;
            gridForce = 0.4;
            insideMode = false;
            dieMode = 0;
            emission = 0.0;
            usePointEmitter = false;
            gravity = ofVec2f(0, 0);
        }
            break;
        case 8 : {
            // Grid dying if it is inside
            setNum(0);
            setNum(50);
            calcGrid(globalWidth, globalHeight);
            drawPart = false;
            drawGrid = true;
            useGrid = true;
            useBorder = false;
            useTor = false;
            gridForce = 0.2;
            insideMode = false;
            dieMode = 0;
            emission = 0.0;
            usePointEmitter = false;
            gravity = ofVec2f(0, 0);
        }
            break;
            
            
            
        default:
            break;
        }
            
            
        
    
}

//-------------------------------------------------------------
void BallManager::setNum(int num){
    

        
    int numToCreate = num - listOfBalls.size();
    if(numToCreate>0){
    
        for(int i=0; i< numToCreate; i++)
        {
            
            ofColor color ;
            color.setHsb(ofRandom(255), 10, 255);
            
            ofPoint pos = ofPoint(ofRandomuf(), ofRandomuf());
            ofVec2f speed = ofVec2f(0, 0);
            addBall( pos, speed, color, 15 + ofRandom(10));
            
        }
    
    
    }
    else{
     
        for(vector<BouncingBall>::iterator it = (listOfBalls.begin()+num); it<listOfBalls.end() ;){
            
            listOfBalls.erase(it);
            
        }
        
        
    }
    
    
    
}