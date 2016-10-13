
#include "Warp.h"
#include "homography.h"

Warp::Warp(){
    glMat = (float *) malloc (sizeof(float)*16);
    //we set it to the default - 0 translation
	//and 1.0 scale for x y z and w
	for(int i = 0; i < 16; i++){
		if(i % 5 != 0) glMat[i] = 0.0;
		else glMat[i] = 1.0;
	}
    ctlRadius = 20;


}

Warp::~Warp(){
//    free (glMat);
}

void Warp::setup(){
       
    srcPoint[0].x = 0;
    srcPoint[0].y = 0;
    srcPoint[1].x = 1.;
    srcPoint[1].y = 0;
    srcPoint[2].x = 1.;
    srcPoint[2].x = 1.;
    srcPoint[3].x = 0;
    srcPoint[3].x = 1.;
    
//    (dstPoint.get())[0].x = 0;
////    =ofPoint(0,0);
//    dstPoint.get()[1]=ofPoint(1,0);
//    dstPoint[2]=ofPoint(1,1);
//    dstPoint[3]=ofPoint(0,1);
    

    
    updateMatrix();
}

void Warp::setSrc(ofPoint p0,ofPoint p1,ofPoint p2,ofPoint p3){
    srcPoint[0] = p0;
    srcPoint[1] = p1;
    srcPoint[2] = p2;
    srcPoint[3] = p3;
    
//    updateMatrix();
}

void Warp::setDst(ofPoint p0,ofPoint p1,ofPoint p2,ofPoint p3){
    dstPoint[0] = p0;
    dstPoint[1] = p1;
    dstPoint[2] = p2;
    dstPoint[3] = p3;
    
    
//    updateMatrix();
}

int Warp::isOverCtl(ofPoint p){
    for (int i =0; i< 4; i++) {
        if(dstPoint[i].distance(p)< ctlRadius){
            return i;
        }
    }
    return -1;
}


void Warp::loadFile(string name){
    
}

void Warp::loadMat(){
    glPushMatrix();
    glMultMatrixf(glMat);
}

void Warp::unloadMat(){
    glPopMatrix();
}

void Warp::updateMatrix(){
//    ofPoint tmpdstPoint[4];
//    for(int i = 0 ; i<4;i++){
//    tmpdstPoint[i] = dstPoint[i].get();
//    }
    findHomography(srcPoint, dstPoint,glMat);
    
/*    homoMat = findHomography (srcPoint, dstPoint);
    
    //we need to copy these values
	//from the 3x3 2D openCV matrix which is row ordered
	//
	// ie:   [0][1][2][ ] x
	//       [3][4][5][ ] y
	//       [6][7][8][ ] w
	//       [ ][ ][ ][ ]
    
	//to openGL's 4x4 3D column ordered matrix
	//        x  y  z  w   
	// ie:   [0][3][ ][6]
	//       [1][4][ ][7]
	//		 [ ][ ][ ][ ]
	//       [2][5][ ][9]

    glMat[0] = homoMat(0, 0);
    glMat[4] = homoMat(0, 1);
    glMat[12] = homoMat(0, 2);
    glMat[1] = homoMat(1, 0);
    glMat[5] = homoMat(1, 1);
    glMat[13] = homoMat(1, 2);
    glMat[3] = homoMat(2, 0);
    glMat[7] = homoMat(2, 1);
    glMat[15] = homoMat(2, 2);
*/
}



void Warp::drawControlPoints(){
    ofSetColor(255, 0, 0);
    ofNoFill();
    ofCircle(dstPoint[0], ctlRadius);
    ofCircle(dstPoint[1], ctlRadius);
    ofCircle(dstPoint[2], ctlRadius);
    ofCircle(dstPoint[3], ctlRadius);
    ofSetColor(255, 255, 255);
}
