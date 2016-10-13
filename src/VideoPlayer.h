//
//  VideoPlayer.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 04/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#pragma once
#include "ofMain.h"
#include "VisuHandler.h"




class VideoPlayer:public VisuClass{
public:
    
    VideoPlayer(VisuHandler * v);
    ~VideoPlayer(){};
    
    ofParameter<int> playPauseStop;
    ofParameter<int> num;
    ofParameter<ofVec3f> color;
    ofParameter<int> alpha;
    
    void draw(int w, int h);
    void update(int w, int h);
    void setupData();
    void ppp(int & s);
    int lasts;
    ofVideoPlayer player;
    unsigned int framenum;
    
};




