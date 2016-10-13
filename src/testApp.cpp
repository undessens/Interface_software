#include "testApp.h"



//--------------------------------------------------------------
void testApp::setup(){
    //    ofSetDataPathRoot("../Resources/data/");
    
#ifndef GUIMODE
    
    
    isFPS = false;
    
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    isFullScreen=false;
    
    
    
    ofBackground(0);
    glDisable(GL_DEPTH_TEST);
    ofEnableAlphaBlending();
    glBlendEquation(GL_FUNC_ADD_EXT);
    glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    ofSetBackgroundAuto(false);
    ofEnableArbTex();
    glEnable(GL_POINT_SPRITE);
    glPointParameteri(	GL_POINT_SPRITE_COORD_ORIGIN,GL_UPPER_LEFT);
    
    ofSetVerticalSync(false);
    ofSetFrameRate(FPS);
    
    width = ofGetWindowWidth();
    height = ofGetWindowHeight();
    
    inw=320;
    inh=240;

    
    //Zdepth
    zdepth=1000;    
    
    
#ifdef testvid
    vidplay.loadMovie("bien.mov");
    vidplay.play();
    threshold=55;
#endif
    
    
    
    receiver.setup(12345);
    
    blurX.load("","shaders/blurX.frag");
    blurY.load("","shaders/blurY.frag");
    colorMod.load("","shaders/colorMod.frag");
    bloom.load("","shaders/bloom.frag");
    gloom.load("","shaders/gloom.frag");
    
    finalRender.allocate(scrw,scrh,GL_RGB);
    
    
#if defined  localcamera || defined testvid || defined blobcomp
    
    colorImg.allocate(inw,inh);
    grayImage.allocate(inw,inh);
    grayDiff.allocate(inw,inh);
    
    bLearnBakground=true;
    
#endif  
    
    
    
    finalblur=0;
    
    
    
    attrctl = AttrCtl();  

    
#endif  
    sH.setup(&scrw,&scrh,zdepth);
    bH.setup(inw,inh,&sH);
    visuHandler.setup(&attrctl,&bH,inw,inh,zdepth,&scrw,&scrh,&sH);
    
#ifndef GUIMODE 
    

    
#ifdef blobosc
    drawBlob = false;
#endif

    
#endif
    camera2.setup(&scrw,&scrh, &zdepth);
    
    
    globalParam.setName("OF");
    settings.setName("global");
    MYPARAM(loadName, "", "", "");
    loadName.setSerializable(false);
    MYPARAM(saveName, "", "", "");
    saveName.setSerializable(false);
    saveName.addListener(this, &testApp::saveState);
    loadName.addListener(this, &testApp::loadState);
    
    MYPARAM(finalblur, 0.f, 0.f, 10.f);
    MYPARAM(saturation, 1.f, 0.f, 2.f);
    MYPARAM(contrast, 1.f, 0.f, 2.f);
    MYPARAM(brightness, 1.f, 0.f, 2.f);
    MYPARAM(brightnessM,100.f,0.f,100.f);
    brightnessM.setSerializable(false);
    MYPARAM(rback, 0, 0, 255);
    MYPARAM(gback, 0, 0, 255);
    MYPARAM(bback, 0, 0, 255);
    MYPARAM(alphablur, 255, 0, 255);
    MYPARAM(bloomsize,0,0,10);
    MYPARAM(isGloom,false,false,true);
    MYPARAM(isPipe,false,false,true);
    MYPARAM(pipeblur, 0.f,0.f,25.f);
    MYPARAM(pipeAlphablur, 255,0,255);
    MYPARAM(hidePipe,false,false,true);
    MYPARAM(pipeMask,false,false,true);
    MYPARAM(cropScreen,ofVec4f(0,0,0,0),ofVec4f(0),ofVec4f(0.6))
    cropScreen.setSerializable(false);
    
    
    settings.add(camera2.settings);
    
    
    //    settings.add(finalblur);
    
    visuHandler.addVisu(new background(&visuHandler));
    
    visuHandler.addVisu(new Particles(&visuHandler));
    visuHandler.addVisu(new metaBalls(&visuHandler));
    visuHandler.addVisu(new AutoTree(&visuHandler));
    
    visuHandler.addVisu(new BallManager(&visuHandler));
    visuHandler.addVisu(new drawBlob(&visuHandler));
    
    visuHandler.addVisu(new VideoPlayer(&visuHandler));
    visuHandler.addVisu(new boule2gomme(&visuHandler));
    visuHandler.addVisu(new Photo(&visuHandler));
    visuHandler.addVisu(new ColorRuban(&visuHandler));
    visuHandler.addVisu(new Liner(&visuHandler));
    
    
    
    visuHandler.registerParams();
    sH.registerParams();
    
    
    
    globalParam.add(settings);
    
    globalParam.add(bH.settings);
    globalParam.add(attrctl.settings);
    globalParam.add(sH.screensCtl);
    globalParam.add(sH.screensParam);
    globalParam.add(visuHandler.allParams);
//    ofParameterGroup pg;
//    screensParam.add(sH.screensParam);
//    screensParam.setName("screensG");
//    ofParameterGroup pg = screensParam.getGroup("screens");
    
    
#ifdef GUIMODE
    paramSync.setup(globalParam,VISU_OSC_IN,VISU_OSC_IP_OUT,VISU_OSC_OUT);

#else
    visuHandler.setupData();
    bH.setupData(&blurX,&blurY);
    sH.setupData();
    paramSync.setup(globalParam,VISU_OSC_OUT,"localhost",VISU_OSC_IN);
    
#endif
    
#ifdef GUIMODE
    ofSetFrameRate(12);

    gui.load(globalParam);
    
    
#endif
    
}




//--------------------------------------------------------------

///// UPDATE

//---------------------------------------------------------------



void testApp::update(){
    
    paramSync.update();
    
#ifndef GUIMODE
    bH.update();
    
    
    //    attrctl.clearPoints();
    
    attrctl.addPoints(bH.centroids, 1);
    attrctl.addPoints(bH.arms, 2);
    
    attrctl.update();
    
    
    visuHandler.update();
    
    
    
    for (int ncom = 0 ; ncom< computeRatio;ncom++){
        visuHandler.updateHighFPS();
    }
    
    
    
    oscUpdate();
    
    
    
    
#endif 
    
    
} 


//--------------------------------------------------------------
//     
//     DRAW
//
//--------------------------------------------------------------




void testApp::draw(){
    
#ifdef GUIMODE
    ofSetBackgroundAuto(true);
    gui.draw();
    
#else
    
    
    if(isPipe){
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        ofPushMatrix();
        ofPushView();
        
        
        visuHandler.pipePP.src->begin();

                ofSetColor(0,0,0,pipeAlphablur);
                ofRect(0,0,inw,inh);


                ofEnableAlphaBlending();
                ofSetColor(255,255,255,255);  
            
        //    glBlendEquation(GL_FUNC_ADD);            
        //    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
            
            
                //Draw only for pipe
                
                visuHandler.draw(1);

            

        
        visuHandler.pipePP.src->end();

        ofPopMatrix();
        ofPopView();
        
        //PIPE Blur
        glBlendEquation(GL_FUNC_ADD_EXT);
        glBlendFunc(GL_ONE,GL_ZERO);
        ofSetColor(255);
        
        visuHandler.pipePP.dst->begin();
        blurX.begin();
        blurX.setUniform1f("blurAmnt", pipeblur);
        visuHandler.pipePP.src->draw(0,0);
        blurX.end();        
        visuHandler.pipePP.dst->end();
        ofSetColor(255);  
        visuHandler.pipePP.swap();
        
        visuHandler.pipePP.dst->begin();
        blurY.begin();
        blurY.setUniform1f("blurAmnt", pipeblur);
        
        visuHandler.pipePP.src->draw(0,0);
        
        blurY.end();        
        visuHandler.pipePP.dst->end();
        visuHandler.pipePP.swap();
        
        
//        glBlendEquation(GL_FUNC_ADD);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    
    
    
    //Direct Render
    
//glBlendEquation(GL_FUNC_ADD);            
   glBlendFunc(GL_DST_ALPHA, GL_DST_ALPHA);
    ofEnableAlphaBlending();
        finalRender.src->begin();
//        if(hidePipe) {
            ofSetColor(rback,gback,bback,alphablur);
//            if(!isPipe)ofRect(0,0,scrw,scrh);
//            ofSetColor(0,0,0,255);
            ofRect(0,0,scrw,scrh);
            ofSetColor(255);
//        }
        
        
        
        ofPushMatrix();
        ofPushView();
        ofEnableAlphaBlending();
        camera2.begin();
        //draw reciever of pipe
        visuHandler.draw(0);
        
        camera2.end();
        ofPopMatrix();
        ofPopView();
        
        finalRender.src->end();
        
        
    
    
    
    //FinalTOUCH
    glBlendEquation(GL_FUNC_ADD_EXT);
    glBlendFunc(GL_ONE,GL_ZERO);
//
    
    finalRender.dst->begin();
    blurX.begin();
    blurX.setUniform1f("blurAmnt",finalblur);
    finalRender.src->draw(0,0); 
    blurX.end();
    finalRender.dst->end();
    
    finalRender.swap();
    
    finalRender.dst->begin();
    blurY.begin();
    blurY.setUniform1f("blurAmnt",finalblur);            
    finalRender.src->draw(0,0);
    blurY.end();        
    finalRender.dst->end();
    
    finalRender.swap();
    
    finalRender.dst->begin();
    colorMod.begin();
    colorMod.setUniform1f("contrast",contrast); 
    colorMod.setUniform1f("saturation",saturation); 
    colorMod.setUniform1f("brightness",brightness*brightnessM/100.); 
    finalRender.src->draw(0,0);
    //    ofRect(0,0,ofGetHeight()/2,300);
    colorMod.end();
    finalRender.dst->end();
    
    finalRender.swap();
    
    if(bloomsize>0){
        finalRender.dst->begin();
        bloom.begin();
        bloom.setUniform1i("size", bloomsize);
        finalRender.src->draw(0,0);
        bloom.end();
        finalRender.dst->end();
        
        finalRender.swap();
    }
    if(isGloom){
        finalRender.dst->begin();
        gloom.begin();
        finalRender.src->draw(0,0);
        gloom.end();
        finalRender.dst->end();
        
        finalRender.swap();
        
    }
    
    
    
    ofSetColor(255);
    
    bool oneMask = false;
    for (int i = 0 ; i<visuHandler.visuList.size();i++){
        if(visuHandler.visuList[i]->isMasking && visuHandler.visuList[i]->isActive){
            oneMask=true;
            break;
        }
    }
    if(!oneMask){
        for(int i = 0 ; i< sH.screenL.size();i++){
            if(sH.screensCtl.getBool("mask"+ofToString(i))){
                oneMask=true;
                break;
                
            }
        }
    }
    if(!oneMask){
        oneMask = pipeMask;
        
    }
    glBlendEquation(GL_FUNC_ADD);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA);
    if(oneMask){
  
        if(!sH.invertMask)ofSetColor(0);
        else ofSetColor(255);
        ofRect(0, 0, scrw, scrh);
        if(!sH.invertMask)ofSetColor(255);
        else ofSetColor(0);

        if(pipeMask)visuHandler.pipePP.src->draw(0,0,scrw,scrh);
        visuHandler.draw(2);  
        
        sH.drawMask();
    }
    else{
        ofSetColor(255);
        ofRect(0, 0, scrw, scrh);
    }
    glBlendEquation(GL_ADD);
    glBlendFunc(GL_DST_COLOR,GL_ZERO);
    
    
    ofSetColor(255);
    finalRender.src->draw(0,0,scrw,scrh);
    ofSetColor(0);
    ofRect(0,0,cropScreen->x*scrw,scrh);
    ofRect(0,0,scrw,cropScreen->y*scrh);
    ofRect(scrw*(1-cropScreen->z),0,scrw*cropScreen->z,scrh);
    ofRect(0,scrh*(1-cropScreen->w),scrw,scrh*cropScreen->w);
    
    
    if(isFPS){
        ofSetColor(0,0,0,!isFPS?0:255);
        ofRect(0, 0, 300, 25);
        ofSetColor(255, 255, 255,!isFPS?0:255);
        ofDrawBitmapString("Fps: " + ofToString( ofGetFrameRate()) , 15,15);
    }
    else{
        //        ofSetColor(0,0,0);
        //        ofRect(0, 00, 1000, 25);
        //        ofSetColor(255, 255, 255);
        //        ofDrawBitmapString("Un Des Sens : www.undessens.org",50,40);
        //        ofDrawBitmapString(" www.facebook.com/AssoUnDesSens",500,40);
    }
    //    cout << ofGetFrameNum()<< endl;
    
#endif
    
    
}
#ifdef GUIMODE
void testApp::keyPressed(int key){
    switch (key){
        case 's':
        {ofFileDialogResult filep = ofSystemSaveDialog("preset","save preset file");
            saveName = filep.getPath();}
            break;
        case 'l':
        {ofFileDialogResult filep = ofSystemLoadDialog("load preset");
            loadName = filep.getPath();}
            break;
            
        case'v':
            gui.visuSettings++;
            gui.visuSettings %=3 ;
            break;
            
    }
}
#endif


#ifndef GUIMODE
//--------------------------------------------------------------
void testApp::keyPressed(int key){
    int k = 0;
    
    switch (key){
            
            
#ifdef blobcomp
        case 'b':
            bLearnBakground=true;
            break;
#endif
            
        case 's':
            isFullScreen=!isFullScreen;
            ofSetFullscreen(isFullScreen);
            break;
            
            
            
            
        case 356:
            camera2.ypr+=ofVec2f(5,0);
            break;
            
        case 357:
            camera2.ypr=ofVec2f(camera2.ypr.get().x,ofClamp(camera2.ypr.get().y+5,-90,90));
            break;
            
        case 358:
            camera2.ypr-=ofVec2f(5,0);
            break;
            
        case 359:
            camera2.ypr=ofVec2f(camera2.ypr.get().x,ofClamp(camera2.ypr.get().y-5,-90,90));
            break;
            
        case ' ':
#if defined testvid || defined localcamera
            vidplay.setPaused(!vidplay.isPaused());
#endif
            break;
            
            
        case 'f':
            isFPS=!isFPS ;
            break;
        case 'x':
            if( visuHandler.get("particles")){
                Particles * ptmp =(Particles *)visuHandler.get("particles") ;
                ptmp->initFbo();
            };
            
        default :
            break;
    }
    
    
    
}



//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
#ifndef syphonout
    scrw=width=w;
    scrh=height=h;
    
    
    
    visuHandler.updateScreenSize();
    finalRender.allocate(width,height,GL_RGB);
    camera2.updateScreenSize(w, h);
#endif
}



void testApp::oscUpdate(){
    ofxOscMessage m;
    while(receiver.getNextMessage(&m)){

        

    }
    
}





void testApp::exit(){
    

    
}










void testApp::mouseDragged(int x, int y, int button){
    vector<ofPoint> points;
    
    points.push_back(ofPoint(x*1.0/scrw,y*1.0/scrh,0));
    //    points.push_back(ofPoint(0.2,0.2,0));
    
    if(points.size()>0)attrctl.addPoints(points,0);
    
}
void testApp::mouseReleased(int x, int y, int button){
    vector<ofPoint> points;
    
    points.clear();
    
    attrctl.addPoints(points,0);
    
}

#endif




void testApp::saveState(string & s){
#ifdef GUIMODE
    if(s!=""){
        string abspath = ofToDataPath("presets/filage/"+ofToString(loadName));
        if(s.find("/")!=string::npos) {abspath = s;}
        else{ofLogWarning("saving to local : " + abspath);}
        cout<<"saving to " + abspath<<endl;
        ofXml xml;
        sH.screensParam.setSerializable(false);
        xml.serialize(globalParam);
        sH.screensParam.setSerializable(true);
        cout<<xml.save(abspath)<<endl;
    }
    else{
        ofLogWarning("no argument for save state");
    }
#endif
}





void testApp::loadState(string & s){
//#if defined GUIMODE || defined STANDALONEMODE
    string abspath = "";
#ifdef GUIMODE  
    if(s.find("/")!=string::npos){abspath = s;}
#else
    if(s.find("/")==string::npos){ abspath = ofToDataPath("presets/filage/"+ofToString(s));}
     else ofLogWarning("wrong preset name");
#endif
    
    if(abspath!=""){
 
        ofXml xml;
        
        xml.load(abspath);
        
        sH.screensParam.setSerializable(false);
        xml.deserialize(globalParam);
        sH.screensParam.setSerializable(true);
    }
    else{
        ofLogWarning("no argument for load state");
    }
//#endif  
}

