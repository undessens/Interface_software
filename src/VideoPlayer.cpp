//
//  VideoPlayer.cpp
//  MurMur d'Ombre
//
//  Created by Tinmar on 04/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//

#include "VideoPlayer.h"



VideoPlayer::VideoPlayer(VisuHandler * v):VisuClass(v){
    MYPARAM(playPauseStop,0,0,3);
    MYPARAM(num,1,1,4);
    MYPARAM(color,ofVec3f(255),ofVec3f(0),ofVec3f(255));
    MYPARAM(alpha,255,0,255);

    playPauseStop.setSerializable(false);
    settings.setName("VideoPlayer");
    lasts=playPauseStop;
    framenum = 0;
}

void VideoPlayer::setupData(){
        playPauseStop.addListener(this, &VideoPlayer::ppp);
        
}

void VideoPlayer::update(int w, int h){

    player.update();
}




void VideoPlayer::ppp(int & s){
#ifndef GUIMODE
    if(s!=lasts){
    switch(s){
        case 1:{
            
            player.setPaused(true);
            lasts=s;
            break;
        }
        case 2:{
            if(lasts==1&&player.isLoaded()){
                
                player.setPaused(false);
            }
            else{
            
            player.loadMovie("Video/"+ofToString(num)+".mp4");
            player.play();
            }
            lasts=s;
            break;
        }
        case 0:{
            player.stop();
            player.close();
            lasts=s;
            framenum =0;
            break;
        }
    }
    }
#endif
}
void VideoPlayer::draw(int w, int h){
    if(playPauseStop == 2 && player.isLoaded() && player.isPlaying()){
    
            int numFram = player.getCurrentFrame();

            if(framenum>3){
            ofSetColor(color->x,color->y,color->z,alpha);
            player.draw(0,0,w,h);
            }
        
        framenum++;
        
        
    }
   }
