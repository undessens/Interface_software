//
//  Photo.h
//  MurMur d'Ombre
//
//  Created by Conil Aurélien on 07/03/2014.
//
//

#ifndef __MurMur_d_Ombre__Photo__
#define __MurMur_d_Ombre__Photo__

#include "ofMain.h"
#include "VisuHandler.h"
#include <iostream>


class Photo : public VisuClass{
public:
    Photo();
    Photo(VisuHandler * v);
    
    void update(int w, int h);
    void draw(int w, int h);
    void setupData();
    void changeImage(int &num);
    void changeResize(bool& resize);
    void changeMirror(bool& ismir);
    
    ofParameter<int> numPhoto;
    ofParameter<bool> isResize;
    ofParameter<bool> isMirror;
    ofParameter<ofVec3f> color;
    
    vector<ofImage> listOfImage;
    
    ofImage imgToDraw;
    bool isSet;
    
    
};

#endif /* defined(__MurMur_d_Ombre__Photo__) */
