//
//  old.h
//  MurMur d'Ombre
//
//  Created by Tinmar on 05/02/14.
//  Copyright (c) 2014 __MyCompanyName__. All rights reserved.
//




////UPdate
/*

 
 
 
 #ifndef PVISU
 float mult = width;
 
 ofVec3f mousevec  ;
 mousevec.x=mouseX;
 mousevec.y=mouseY;
 mousevec.z=f.mousez;
 
 velPingPong.dst->begin();
 //ofClear(0);
 updateVel.begin();
 updateVel.setUniformTexture("backbuffer", velPingPong.src->getTextureReference(), 0);   // passing the previus velocity information
 updateVel.setUniformTexture("posData", posPingPong.src->getTextureReference(), 1);
 updateVel.setUniformTexture("originData", origins.getTextureReference(), 2); // passing the position information
 #ifdef blobosc
 
 updateVel.setUniformTexture("blob", polyBlob.src->getTextureReference(), 3);
 updateVel.setUniform4f("blobf",(float)f.blobin,(float)f.blobforce,(float)f.blobz,(float)f.bloboutvel);
 #endif
 
 #ifdef localcamera 
 updateVel.setUniformTexture("blob", colorImg.getTextureReference(), 3);
 updateVel.setUniform4f("blobf",(float)f.blobin,(float)f.blobforce,(float)f.blobz,(float)f.bloboutvel);
 #endif
 #ifdef testvid 
 
 updateVel.setUniformTexture("blob", colorImg.getTextureReference(), 3);
 updateVel.setUniform4f("blobf",(float)f.blobin,(float)f.blobforce,(float)f.blobz,(float)f.bloboutvel);
 #endif
 #ifdef syphon
 updateVel.setUniformTexture("blob", blobClient.getTexture(), 3);
 updateVel.setUniform4f("blobf",(float)f.blobin,(float)f.blobforce,(float)f.blobz,(float)f.bloboutvel);
 #endif
 
 updateVel.setUniform1i("resolution", (int)textureRes); 
 
 updateVel.setUniform2f("screen", (float)width, (float)height);
 updateVel.setUniform3f("mousein",(float)(mousevec.x*1.0f/width),(float)(mousevec.y*1.0f/height),(float)0.5+mousevec.z*1.0/zdepth);
 updateVel.setUniform1i("Click",ofGetMousePressed()?1:0);
 updateVel.setUniform1f("timestep", (float)timeStep);
 updateVel.setUniform1f("seed",(float)ofRandomuf());
 
 updateVel.setUniform2f("insize",inw,inh);
 //forces
 updateVel.setUniform4f("friction",(float)f.fr,(float)f.minv,(float)f.maxv,(float)f.frmin);
 updateVel.setUniform4f("origin",(float)f.origin,(float)f.korigin,(float)f.zorigin,(float)f.forceorigin);
 updateVel.setUniform1i("netshot",f.netshot?1:0);
 updateVel.setUniform4f("netw",(float)f.netw,(float)mult*f.lnetw,(float)f.knetw,(float)f.znetw);
 updateVel.setUniform4f("neth",(float)f.neth,(float)mult*f.lneth,(float)f.kneth,(float)f.zneth);
 updateVel.setUniform3f("mouserotation",(float)f.mouserotation,(float)f.rmrotation,(float)f.smrotation);
 updateVel.setUniform2f("borders",(float)f.border,(float)f.zborder);
 updateVel.setUniform4f("mousespring",(float)f.mousespring,(float)f.rmspring,(float)f.kmspring,(float)f.zmspring);
 updateVel.setUniform3f("mousedamp",(float)f.mousedamp,(float)f.rmdamp,(float)f.dmdamp);
 updateVel.setUniform4f("mousepicker",(float)f.mousepicker,(float)f.rmpicker,(float)f.kmpicker,(float)f.zmpicker);
 updateVel.setUniform3f("gravitouse",(float)f.Gx,(float)f.Gy,(float)f.Gz);
 updateVel.setUniform4f("mousegravity",(float)f.mousegravity,(float)f.mmgravity,(float)f.rinmgravity,(float)f.minmgravity);
 updateVel.setUniform2f("lorenz",(float)f.lorenz,(float)f.lorenzatt);
 updateVel.setUniform4f("xspring",(float)f.xspring,(float)mult*f.xori,(float)f.kxspring,(float)f.zxspring);
 updateVel.setUniform4f("yspring",(float)f.yspring,(float)scrh*f.yori,(float)f.kyspring,(float)f.zyspring);
 updateVel.setUniform4f("zspring",(float)f.zspring,(float)mult*f.zori,(float)f.kzspring,(float)f.zzspring);
 updateVel.setUniform1fv("attractors",attrctl.attr,5*MAXATTRACTORS);
 updateVel.setUniform1i("numattractors",f.isAtt?attrctl.numattr:0);
 
 updateVel.setUniform3f("attrrotation0",(float)f.attrrotation0,(float)f.rarotation0,(float)f.sarotation0);
 updateVel.setUniform3f("attrrotation1",(float)f.attrrotation1,(float)f.rarotation1,(float)f.sarotation1);
 updateVel.setUniform3f("attrrotation2",(float)f.attrrotation2,(float)f.rarotation2,(float)f.sarotation2);
 
 updateVel.setUniform4f("attrspring0",(float)f.attrspring0,(float)f.raspring0,(float)f.kaspring0,(float)f.zaspring0);
 updateVel.setUniform4f("attrspring1",(float)f.attrspring1,(float)f.raspring1,(float)f.kaspring1,(float)f.zaspring1);
 updateVel.setUniform4f("attrspring2",(float)f.attrspring2,(float)f.raspring2,(float)f.kaspring2,(float)f.zaspring2);
 
 updateVel.setUniform4f("attrgravity0",(float)f.attrgravity0,(float)f.magravity0,(float)f.rinagravity0,(float)f.minagravity0);
 updateVel.setUniform4f("attrgravity1",(float)f.attrgravity1,(float)f.magravity1,(float)f.rinagravity1,(float)f.minagravity1);
 updateVel.setUniform4f("attrgravity2",(float)f.attrgravity2,(float)f.magravity2,(float)f.rinagravity2,(float)f.minagravity2);
 
 updateVel.setUniform3f("attrdamp0",(float)f.attrdamp0,(float)f.radamp0,(float)f.cadamp0);
 updateVel.setUniform3f("attrdamp1",(float)f.attrdamp1,(float)f.radamp1,(float)f.cadamp1);
 updateVel.setUniform3f("attrdamp2",(float)f.attrdamp2,(float)f.radamp2,(float)f.cadamp2);
 
 updateVel.setUniform3f("plan",f.plan.getNormalized().x,f.plan.getNormalized().y,f.plan.getNormalized().z);
 updateVel.setUniform4f("planforce",f.planforce,f.dplanforce,f.kplanforce,f.zplanforce);
 updateVel.setUniform1i("random",f.random>0?ofRandom(f.random)-f.random/4.0:0);
 
 
 
 
 ///Just a frame to put pixels on
 ofSetColor(255,255,255,255);
 glBegin(GL_QUADS);
 glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
 glTexCoord2f(textureRes, 0); glVertex3f(textureRes, 0, 0);
 glTexCoord2f(textureRes, textureRes); glVertex3f( textureRes, textureRes, 0);
 glTexCoord2f(0, textureRes);  glVertex3f(0, textureRes, 0);
 glEnd();
 
 updateVel.end();
 velPingPong.dst->end();
 // camera.end();
 velPingPong.swap();
 
 
 // Positions PingPong
 //
 // With the velocity calculated updates the position
 //
 glFinish();
 
 posPingPong.dst->begin();
 //ofClear(0);
 updatePos.begin();
 updatePos.setUniformTexture("prevPosData", posPingPong.src->getTextureReference(), 0);  // Previus position
 updatePos.setUniformTexture("velData", velPingPong.src->getTextureReference(), 1);      // Velocity
 updatePos.setUniform1f("timestep",(float) timeStep );
 updatePos.setUniform1i("resolution",(int) textureRes);
 
 
 
 
 
 // Just a frame to put pixels on
 ofSetColor(255,255,255,255);
 glBegin(GL_QUADS);
 glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
 glTexCoord2f(textureRes, 0); glVertex3f(textureRes, 0, 0);
 glTexCoord2f(textureRes, textureRes); glVertex3f( textureRes, textureRes, 0);
 glTexCoord2f(0, textureRes);  glVertex3f(0, textureRes, 0);
 glEnd();
 
 updatePos.end();
 posPingPong.dst->end();
 
 posPingPong.swap();
 
 
 //camera.begin();   
 glFinish();
 #endif
 
 
 
*/




///////DRAW



/*
 
 // 1st POSTION for DRAW VISU
 //    visuHandler.draw();
 
 #ifndef PVISU
 updateRender.begin();
 updateRender.setUniformTexture("posTex", posPingPong.src->getTextureReference(), 0);
 
 if(f.gradtype==2){
 updateRender.setUniformTexture("velTex",velPingPong.src->getTextureReference(),1);
 }
 if(f.gradtype>0){
 updateRender.setUniformTexture("gradient",gradient.getTextureReference(),2);
 
 }
 
 
 
 #ifdef CAMCOLOR
 updateRender.setUniformTexture("camin", backImage.getTextureReference(), 4);
 updateRender.setUniform1i("iscam",iscam);
 updateRender.setUniform2f("insize",backImage.getWidth(),backImage.getHeight());
 #endif
 
 
 updateRender.setUniform1f("texw",33);
 updateRender.setUniform1i("resolution", (int)textureRes); 
 updateRender.setUniform3f("screen", (float)width, (float)height,(float)zdepth);
 
 
 
 updateRender.setUniform4f("colorpart",(float)f.gradtype,(float)rpart,(float)gpart,(float)bpart);
 updateRender.setUniform2f("gradbounds",(float)f.mingrad,(float)f.maxgrad);
 updateRender.setUniform2f("gradbounds2",(float)f.mingrad2,(float)f.maxgrad2);
 
 updateRender.setUniform3f("mouse",(float)(mouseX),(float)(height-mouseY),(float)zdepth/2 + f.mousez);
 
 
 updateRender.setUniform1f("alpha",alphaparticle);
 
 
 
 glPointSize(particleSize);
 glBegin( GL_POINTS ); 
 for(int x = 0; x < textureRes; x++){
 for(int y = 0; y < textureRes; y++){
 
 glVertex3d(x,y,0);
 
 }
 }
 
 glEnd();
 
 updateRender.end();
 #endif

 
 */



/////OSC




/*
 
 #ifndef PVISU
 else if(m.getAddress() == "/Gx"){
 f.Gx=m.getArgAsFloat(0)/100.0;            
 }
 else if(m.getAddress() == "/Gy"){
 f.Gy=m.getArgAsFloat(0)/100.0;            
 }
 else if(m.getAddress() == "/Gz"){
 f.Gz=m.getArgAsFloat(0)/100.0;            
 }
 
 else if (m.getAddress()=="/zmouse"){
 f.mousez=m.getArgAsFloat(0);
 
 
 }
 
 else if(m.getAddress()=="/random"){
 f.random=m.getArgAsFloat(0);
 }
 
 
 
 else if(m.getAddress() == "/fr"){
 f.fr=(1-m.getArgAsFloat(0)/5000.0);
 }
 else if(m.getAddress() == "/frmin"){
 f.frmin=(1-m.getArgAsFloat(0)/5000.0);
 }
 else if(m.getAddress() == "/minv"){
 f.minv=m.getArgAsFloat(0)/10.0;
 }
 else if(m.getAddress() == "/maxv"){
 f.maxv=m.getArgAsFloat(0)/10.0;
 }
 
 else if(m.getAddress() == "/origin"){
 f.origin=m.getArgAsFloat(0)==1;            
 }
 else if(m.getAddress() == "/forceorigin"){
 f.forceorigin=m.getArgAsFloat(0)==1;            
 }
 else if(m.getAddress() == "/zorigin"){
 f.zorigin=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress() == "/korigin"){
 f.korigin=m.getArgAsFloat(0)/1000.0;
 }
 else if(m.getAddress() == "/origintype"){
 
 changeOrigin(m.getArgAsFloat(0));
 }
 
 
 else if(m.getAddress() == "/mousespring"){            
 f.mousespring=m.getArgAsFloat(0);
 }
 else if(m.getAddress() == "/rmspring"){ 
 f.rmspring=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/kmspring"){ 
 f.kmspring=m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress() == "/zmspring"){ 
 f.zmspring=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress() == "/nkmspring"){ 
 f.nkmspring=m.getArgAsFloat(0);
 }
 else if(m.getAddress() == "/knmspring"){ 
 f.knmspring=m.getArgAsFloat(0)/(10000.0*powf(300,f.nkmspring));
 }
 
 
 else if(m.getAddress() == "/mouserotation"){
 f.mouserotation=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/rmrotation"){
 f.rmrotation=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/smrotation"){
 f.smrotation=m.getArgAsFloat(0)/100.0;
 } 
 
 
 else if(m.getAddress() == "/mousepicker"){
 f.mousepicker=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/rmpicker"){
 f.rmpicker=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/kmpicker"){
 f.kmpicker=m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress()=="/zmpicker"){
 f.zmpicker=m.getArgAsFloat(0)/10000.0;
 
 }
 
 else if(m.getAddress() == "/mousedamp"){
 f.mousedamp=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/rmdamp"){
 f.rmdamp=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/dmdamp"){
 f.dmdamp=1.0-m.getArgAsFloat(0)/100.0;
 }
 
 else if(m.getAddress() == "/mousegravity"){
 f.mousegravity=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/mmgravity"){
 f.mmgravity=m.getArgAsFloat(0)*1000.0;
 }
 else if(m.getAddress() == "/rinmgravity"){
 f.rinmgravity=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/minmgravity"){
 f.minmgravity=m.getArgAsFloat(0)*1000.0;            
 }
 
 else if(m.getAddress()=="/xspring"){
 f.xspring=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/kxspring"){
 f.kxspring=m.getArgAsFloat(0)/1000.0;
 }
 else if(m.getAddress()=="/zxspring"){
 f.zxspring=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress()=="/xori"){
 f.xori=m.getArgAsFloat(0)/(100.0);
 }
 else if(m.getAddress()=="/yspring"){
 f.yspring=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/kyspring"){
 f.kyspring=m.getArgAsFloat(0)/1000.0;
 }
 else if(m.getAddress()=="/zyspring"){
 f.zyspring=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress()=="/yori"){
 f.yori=m.getArgAsFloat(0)/100.0;
 }
 
 else if(m.getAddress()=="/zspring"){
 f.zspring=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/kzspring"){
 f.kzspring=m.getArgAsFloat(0)/1000.0;
 }
 else if(m.getAddress()=="/zzspring"){
 f.zzspring=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress()=="/zori"){
 f.zori=m.getArgAsFloat(0)/100.0+0.5;
 }
 
 else if(m.getAddress()=="/lorenz"){
 f.lorenz=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/lorenzatt"){
 f.lorenzatt=m.getArgAsFloat(0)/100000.0;
 }
 
 else if(m.getAddress() == "/border"){
 f.border=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/rborder"){
 f.rborder=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/kborder"){
 f.kborder=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress()=="/zborder"){
 f.zborder=1-m.getArgAsFloat(0)/100.0;
 
 }
 
 else if (m.getAddress()=="/zminborder"){
 f.zminborder=m.getArgAsFloat(0);
 }
 else if (m.getAddress()=="/zmaxborder"){
 f.zmaxborder=m.getArgAsFloat(0);
 }
 
 else if(m.getAddress()=="/neth"){
 f.neth=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/kneth"){
 f.kneth=m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress()=="/zneth"){
 f.zneth=m.getArgAsFloat(0)/1000000.0;
 
 }
 else if(m.getAddress()=="/lneth"){
 f.lneth=m.getArgAsFloat(0)/(1000.0*textureRes);
 
 }
 
 else if(m.getAddress()=="/netw"){
 f.netw=m.getArgAsFloat(0)==1;
 }
 
 else if(m.getAddress()=="/knetw"){
 f.knetw=m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress()=="/znetw"){
 f.znetw=m.getArgAsFloat(0)/1000000.0;
 
 }
 else if(m.getAddress()=="/lnetw"){
 f.lnetw=m.getArgAsFloat(0)/(1000.0*textureRes) ;
 
 }
 else if(m.getAddress()=="/netshot"){
 f.netshot=m.getArgAsFloat(0)==1 ;
 
 }
 
 //Plan
 
 else if(m.getAddress()=="/planx"){
 f.plan.x=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/plany"){
 f.plan.y=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/planz"){
 f.plan.z=m.getArgAsFloat(0);
 
 }
 
 
 else if(m.getAddress()=="/planforce"){
 f.planforce=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/dplanforce"){
 f.dplanforce=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/kplanforce"){
 f.kplanforce=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress()=="/zplanforce"){
 f.zplanforce=m.getArgAsFloat(0)/1000.0;
 }
 
 //blob
 else if(m.getAddress()=="/blobin"){
 f.blobin=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/blobforce"){
 f.blobforce=m.getArgAsFloat(0)/100.0;
 }
 
 else if(m.getAddress()=="/blobz"){
 f.blobz=1-m.getArgAsFloat(0)/1000.0;
 }
 else if(m.getAddress()=="/bloboutvel"){
 f.bloboutvel=m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress()=="/blobblur"){
 f.blobblur=m.getArgAsFloat(0)/100.;//+(m.getArgAsFloat(0)%2-1);
 }
 
 else if(m.getAddress()=="/blobxinvert"){
 f.blobxinvert=m.getArgAsFloat(0)==1;
 }
 
 else if(m.getAddress()=="/blobyinvert"){
 f.blobyinvert=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/blobmirrorx"){
 f.blobmirrorx=m.getArgAsFloat(0)==1;
 }
 
 else if(m.getAddress()=="/blobmirrory"){
 f.blobmirrory=m.getArgAsFloat(0)==1;
 }
 // Points
 
 else if(m.getAddress()=="/isAttractors"){
 f.isAtt=m.getArgAsFloat(0)==1;
 }
 
 else if(m.getAddress() == "/attrrotate"){
 attrctl.attrotate=m.getArgAsFloat(0)/100.0;
 }
 
 
 else if(m.getAddress() == "/attrgravity0"){
 f.attrgravity0=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/attrgravity1"){
 f.attrgravity1=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/attrgravity2"){
 f.attrgravity2=m.getArgAsFloat(0)==1;
 }
 
 else if(m.getAddress() == "/magravity0"){
 f.magravity0=m.getArgAsFloat(0)*1000.0;
 }
 else if(m.getAddress() == "/magravity1"){
 f.magravity1=m.getArgAsFloat(0)*1000.0;
 }
 else if(m.getAddress() == "/magravity2"){
 f.magravity2=m.getArgAsFloat(0)*1000.0;
 }
 
 else if(m.getAddress() == "/rinagravity0"){
 f.rinagravity0=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/rinagravity1"){
 f.rinagravity1=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/rinagravity2"){
 f.rinagravity2=m.getArgAsFloat(0)*1.0;
 }
 
 
 else if(m.getAddress() == "/minagravity0"){
 f.minagravity0=m.getArgAsFloat(0)*1000.0;            
 }
 else if(m.getAddress() == "/minagravity1"){
 f.minagravity1=m.getArgAsFloat(0)*1000.0;            
 }
 else if(m.getAddress() == "/minagravity2"){
 f.minagravity2=m.getArgAsFloat(0)*1000.0;            
 }
 
 
 else if(m.getAddress() == "/attrrotation0"){
 f.attrrotation0=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/attrrotation1"){
 f.attrrotation1=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/attrrotation2"){
 f.attrrotation2=m.getArgAsFloat(0)==1;
 }
 
 
 else if(m.getAddress() == "/rarotation0"){
 f.rarotation0=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/rarotation1"){
 f.rarotation1=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/rarotation2"){
 f.rarotation2=m.getArgAsFloat(0)*1.0;
 }
 
 
 else if(m.getAddress() == "/sarotation0"){
 f.sarotation0=m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress() == "/sarotation1"){
 f.sarotation1=m.getArgAsFloat(0)/100.0;
 } 
 else if(m.getAddress() == "/sarotation2"){
 f.sarotation2=m.getArgAsFloat(0)/100.0;
 } 
 
 else if(m.getAddress() == "/attrspring0"){            
 f.attrspring0=m.getArgAsFloat(0);
 }
 else if(m.getAddress() == "/attrspring1"){            
 f.attrspring1=m.getArgAsFloat(0);
 }
 else if(m.getAddress() == "/attrspring2"){            
 f.attrspring2=m.getArgAsFloat(0);
 }
 
 
 else if(m.getAddress() == "/raspring0"){ 
 f.raspring0=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/raspring1"){ 
 f.raspring1=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/raspring2"){ 
 f.raspring2=m.getArgAsFloat(0)*1.0;
 }
 
 
 else if(m.getAddress() == "/kaspring0"){ 
 f.kaspring0=m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress() == "/kaspring1"){ 
 f.kaspring1=m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress() == "/kaspring2"){ 
 f.kaspring2=m.getArgAsFloat(0)/100.0;
 }
 
 
 else if(m.getAddress() == "/zaspring0"){ 
 f.zaspring0=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress() == "/zaspring1"){ 
 f.zaspring1=m.getArgAsFloat(0)/10000.0;
 }
 else if(m.getAddress() == "/zaspring2"){ 
 f.zaspring2=m.getArgAsFloat(0)/10000.0;
 }
 
 
 else if(m.getAddress() == "/attrdamp0"){            
 f.attrdamp0=m.getArgAsFloat(0);
 }
 else if(m.getAddress() == "/attrdamp1"){            
 f.attrdamp1=m.getArgAsFloat(0);
 }
 else if(m.getAddress() == "/attrdamp2"){            
 f.attrdamp2=m.getArgAsFloat(0);
 }
 
 
 
 else if(m.getAddress() == "/radamp0"){ 
 f.radamp0=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/radamp1"){ 
 f.radamp1=m.getArgAsFloat(0)*1.0;
 }
 else if(m.getAddress() == "/radamp2"){ 
 f.radamp2=m.getArgAsFloat(0)*1.0;
 }
 
 
 else if(m.getAddress() == "/cadamp0"){ 
 f.cadamp0=1-m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress() == "/cadamp1"){ 
 f.cadamp1=1-m.getArgAsFloat(0)/100.0;
 }
 else if(m.getAddress() == "/cadamp2"){ 
 f.cadamp2=1-m.getArgAsFloat(0)/100.0;
 }
 
 else if(m.getAddress() == "/attrmirrorx0"){ 
 attrctl.attrmirorx[0]=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/attrmirrory0"){ 
 attrctl.attrmirory[0]=m.getArgAsFloat(0)==1;
 }
 
 else if(m.getAddress() == "/attrmirrorx1"){ 
 attrctl.attrmirorx[1]=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/attrmirrory1"){ 
 attrctl.attrmirory[1]=m.getArgAsFloat(0)==1;
 }
 
 else if(m.getAddress() == "/attrmirrorx2"){ 
 attrctl.attrmirorx[2]=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress() == "/attrmirrory2"){ 
 attrctl.attrmirory[2]=m.getArgAsFloat(0)==1;
 }
 
 
 
 
 ////////////////////
 
 
 else if(m.getAddress() == "/camctlnum"){ 
 camctl=m.getArgAsFloat(0);
 // if(camctl==1)f.split=false;
 }
 
 
 
 else if(m.getAddress() == "/split"){ 
 f.split=m.getArgAsFloat(0)==1;
 }
 
 //        //EMITTERS
 //        else if(m.getAddress()=="/emitpart"){
 //            isAdding=m.getArgAsFloat(0)==1;
 //        }
 //        else if(m.getAddress()=="/emitcircle"){
 //            emitcircle=m.getArgAsInt32(0)==1;
 //        }
 //        else if(m.getAddress()=="/emitangle"){
 //            emitangle=m.getArgAsInt32(0);
 //        }
 //        else if(m.getAddress()=="/emitvel"){
 //            emitvel=m.getArgAsInt32(0)/100.0;
 //        }
 //        else if(m.getAddress()=="/emitlocx"){
 //            emitloc.x=m.getArgAsInt32(0)/100.0;
 //        }
 //        else if(m.getAddress()=="/emitlocy"){
 //            emitloc.y=m.getArgAsInt32(0)/100.0;
 //        }
 //        else if(m.getAddress()=="/emitlocz"){
 //            emitloc.z=(m.getArgAsInt32(0)/200.0+0.5);
 //        }
 //        else if(m.getAddress()=="/emitrate"){
 //            emitrate=(int)ofClamp(m.getArgAsInt32(0),0,MAXNEWPART);
 //        }
 //        else if(m.getAddress()=="/emitautostop"){
 //            emitautostop=m.getArgAsInt32(0)==1;
 //        }
 //        
 
 //Colors
 
 else if(m.getAddress()=="/splitgrad"){
 f.splitgradient=m.getArgAsFloat(0)==1;
 }
 else if(m.getAddress()=="/mingrad"){
 f.mingrad=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/maxgrad"){
 f.maxgrad=m.getArgAsFloat(0);
 
 }
 
 else if(m.getAddress()=="/mingrad2"){
 f.mingrad2=m.getArgAsFloat(0);
 }
 else if(m.getAddress()=="/maxgrad2"){
 f.maxgrad2=m.getArgAsFloat(0);
 
 }
 
 else if(m.getAddress()=="/foregroundtype"){
 foregroundtype=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/backgroundtype"){
 backgroundtype=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/rback"){
 rback=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/gback"){
 gback=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/bback"){
 bback=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/rblob"){
 rblob=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/gblob"){
 gblob=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/bblob"){
 bblob=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/ablob"){
 ablob=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/alphablur"){
 alphablur=m.getArgAsFloat(0);
 
 }

 else if(m.getAddress()=="/brightness2"){
 brightness2=m.getArgAsFloat(0)/100.0;
 
 }
 else if(m.getAddress()=="/contrast2"){
 contrast2=m.getArgAsFloat(0)/100.0;
 
 }
 else if(m.getAddress()=="/saturation2"){
 saturation2=m.getArgAsFloat(0)/100.0;
 
 }
 
 
 else if(m.getAddress()=="/gradienttype"){
 f.gradtype=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/camin"){
 iscam=m.getArgAsFloat(0)==1;
 }
 #ifdef CAMCOLOR        
 else if(m.getAddress()=="/photoname"){
 string path=m.getArgAsString(0);
 backImage.loadImage("photos/"+path+".jpg");
 backImage.mirror(true,false);
 }
 #endif
 else if(m.getAddress()=="/gradname"){
 string path=m.getArgAsString(0);
 gradient.loadImage("gradients/"+path+".tiff");
 }
 
 
 
 
 else if(m.getAddress()=="/rpart"){
 rpart=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/gpart"){
 gpart=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/bpart"){
 bpart=m.getArgAsFloat(0);
 
 }
 else if(m.getAddress()=="/partsize"){
 particleSize=m.getArgAsFloat(0)/100.0+1;
 
 }
 else if(m.getAddress()=="/alphaparticle"){
 alphaparticle=m.getArgAsFloat(0)/100.0;
 
 }
 
 
 
 
 else if(m.getAddress()=="/reset"){
 reset();
 }
 else if(m.getAddress() == "/timestep"){
 timeStep = m.getArgAsFloat(0)/(100.0*FPS);
 }
 
 
 #endif

 
 
 */


/*
 
 #ifndef PVISU
 // Loading the Shaders
 updatePos.load("","shaders/posUpdate.frag");// shader for updating the texture that store the particles position on RG channels
 updateVel.load("","shaders/velUpdate.frag");// shader for updating the texture that store the particles velocity on RG channels
 
 
 updateRender.load("shaders/render.vert","shaders/render.frag");
 
 
 
 // Seting the textures where the information ( position and velocity ) will be
 textureRes = (int)sqrt((float)numParticles);
 numParticles = textureRes * textureRes;
 
 // 1. Making arrays of float pixels with position information
 float * pos = new float[numParticles*3];
 for (int x = 0; x < textureRes; x++){
 for (int y = 0; y < textureRes; y++){
 int i = textureRes * y + x;
 
 pos[i*3 + 0] = x*1.0/textureRes;
 pos[i*3 + 1] = y*1.0/textureRes;
 pos[i*3 + 2] = 0.5;
 }
 }
 
 // Load this information in to the FBO´s texture
 posPingPong.allocate(textureRes, textureRes,GL_RGB32F);
 posPingPong.src->getTextureReference().loadData(pos, textureRes, textureRes, GL_RGB);
 posPingPong.dst->getTextureReference().loadData(pos, textureRes, textureRes, GL_RGB);
 origins.allocate(textureRes, textureRes,GL_RGB32F);
 origins.getTextureReference().loadData(pos, textureRes, textureRes, GL_RGB);
 
 delete [] pos;    // Delete the array
 
 
 
 // 2. Making arrays of float pixels with velocity information and the load it to a texture
 float * vel = new float[numParticles*3];
 for (int i = 0; i < numParticles; i++){
 vel[i*3 + 0] = 0.;//+ofRandom(-.1,.1);vu
 vel[i*3 + 1] = 0.;//+ofRandom(-.1,.1);
 vel[i*3 + 2] = 0.;
 }
 // Load this information in to the FBO´s texture
 velPingPong.allocate(textureRes, textureRes,GL_RGB32F);
 velPingPong.src->getTextureReference().loadData(vel, textureRes, textureRes, GL_RGB);
 velPingPong.dst->getTextureReference().loadData(vel, textureRes, textureRes, GL_RGB);
 delete [] vel; // Delete the array
 
 
 
 
 
 rpart=gpart=bpart=0;
 
 
 
 gradient.loadImage("gradients/rasta.tiff");
 
 
 
 
 isGradient=true;
 #endif
*/


/*
 
 #ifndef PVISU
 //init
 
 f.isAtt=true;
 f.netshot=false;
 f.mousespring=1;
 f.mousez = 0;
 f.kmspring=0.31;
 f.zmspring=0.1;
 f.rmspring=50;
 f.origin=true;
 f.korigin=0.03;
 f.zorigin=0.00181;
 f.blobblur=9;
 f.attrrotation0=f.attrgravity0=f.attrrotation1=f.attrgravity1=f.attrrotation2=f.attrgravity2=false;
 f.attrspring0=f.attrspring1=f.attrspring2=0;
 f.attrdamp0=f.attrdamp1=f.attrdamp2=0;
 f.blobforce=0;
 f.bloboutvel=0;
 f.blobz=0;
 
 f.forceorigin=false;
 f.mingrad=0;
 f.maxgrad=100;
 f.gradtype=2;
 f.border=true;
 f.zborder=0.8;
 f.netw=f.neth=false;
 f.Gx=f.Gy=f.Gz=0;
 
 f.mouserotation=false;
 f.mousegravity=false;
 
 f.fr=1.0;
 f.frmin=1.0;
 f.minv=0;
 f.maxv=1000;
 
 
 f.splitgradient=false;
 
 f.planforce=0;
 
 f.gradtype = 0;
 
 
 isAdding=false;
 emitangle=0;
 emitrate=0;
 emitcircle=false;
 emitvel=0;
 emitloc=ofPoint(0,0,0.5);
 emitautostop=true;
 #endif 
 
 */



/*
 #if defined CAMCOLOR & not defined PVISU
 backImage.loadImage("photos/noms.png");
 #endif
 */


/*
 
 #ifndef PVISU    
 particleSize = 3.0f;
 alphaparticle=0.5f;
 timeStep = 1.f;
 timeStep*=timeStep/(FPS);
 numParticles = 100000;
 
 curNumParticles = 50000;
 curNumParticles = numParticles;
 #endif
 */



/*
 
 #ifdef blobosc 
 #ifndef PVISU
 oscBlobUpdate();
 #endif
 #endif
 */
/*
 #ifndef PVISU
 
 void oscBlobUpdate();
 
 
 ofShader    updatePos;
 ofShader    updateVel;
 ofShader    updateRender;
 
 
 ofFbo   origins;
 ofFbo   colors;
 // ofFbo  visuFbo;
 pingPongBuffer posPingPong;
 pingPongBuffer velPingPong;
 
 // void godUpdate();
 void addParticles(ofPoint loc,int rate,float vel,float angle,bool circle);
 void findExtrem(ofxCvBlob blob, float simpl);
 void changeOrigin(int type);
 void reset();
 
 float   timeStep;
 float   particleSize;
 float alphaparticle;
 
 
 int     numParticles;
 
 int curNumParticles;
 int     textureRes;
 
 forces f;
 ofImage gradient;
 Boolean isGradient;
 Boolean isVelColors;
 int rpart,gpart,bpart;
 
 ofImage backImage;
 
 //emetters
 int newnum;
 bool isAdding;
 ofPoint emitloc;
 float emitangle;
 int emitrate;
 bool emitcircle;
 float emitvel;
 bool emitautostop;
 //ReadObj
 
 void readObj(const char * path);
 
 
 
 #else
*/


/*
 
 
 struct forces{
 
 float mousex;
 float mousey;
 float mousez;
 bool isClicked;
 float screenw;
 float screenh;
 int lin;
 int col;
 float timestep;
 
 float Gx;
 float Gy;
 float Gz;
 
 float random;
 
 
 
 //Friction
 bool friction;
 float fr;
 float frmin;
 float minv;
 float maxv;
 
 
 //Origin
 bool origin;
 bool circle;
 bool forceorigin;
 float korigin;
 float zorigin;
 
 //Border
 bool border;
 float kborder;
 float zborder;
 float rborder;
 float zminborder;
 float zmaxborder;
 
 //Net
 bool neth;
 float kneth;
 float zneth;
 float lneth;
 bool netshot;
 
 bool netw;
 float knetw;
 float znetw;
 float lnetw;
 
 //MouseSpring
 int mousespring;
 float kmspring;
 float knmspring;
 int nkmspring;
 float zmspring;
 float rmspring;
 
 
 //MouseRotation
 bool mouserotation;
 
 float rmrotation;
 float smrotation;
 
 //Mousepick
 bool mousepick;
 float rmpick;
 float kmpick;
 float zmpick;
 
 int mousepicker;
 float rmpicker;
 float kmpicker;
 float zmpicker;
 
 int mousedamp;
 float rmdamp;
 float dmdamp;
 
 //CONTOURSPRING
 bool contourspring;
 float kctrspring;
 float zctrspring;
 float rctrspring;
 
 //MOUSEGRAVITY
 bool mousegravity;
 float mmgravity;
 float rinmgravity;
 float minmgravity;
 
 
 // XSPRING   
 bool xspring;
 float kxspring;
 float zxspring;
 float xori;
 
 
 //YSPRING
 bool yspring;
 float kyspring;
 float zyspring;
 float yori;
 
 
 
 
 //ZSPRING
 bool zspring;
 float kzspring;
 float zzspring;
 float zori;
 
 
 
 
 
 //
 bool lorenz;
 float lorenzatt;
 
 // PLAN FORCE
 ofVec3f plan;
 
 
 int planforce;
 float dplanforce;
 float kplanforce;
 float zplanforce;
 
 
 
 
 // ATTRACTORS
 
 bool split;
 
 bool isAtt;
 
 
 int attrspring0;
 int attrspring1;
 int attrspring2;
 
 
 float raspring0;
 float raspring1;
 float raspring2;
 
 float kaspring0;
 float kaspring1;
 float kaspring2;
 
 float zaspring0;
 float zaspring1;
 float zaspring2;
 
 
 Boolean attrgravity0;
 Boolean attrgravity1;
 Boolean attrgravity2;
 
 float rinagravity0;
 float rinagravity1;
 float rinagravity2;
 
 float minagravity0;
 float minagravity1;
 float minagravity2;
 
 float magravity0;
 float magravity1;
 float magravity2;
 
 
 Boolean attrrotation0;
 Boolean attrrotation1;
 Boolean attrrotation2;
 
 float sarotation0;
 float sarotation1;
 float sarotation2;
 
 float rarotation0;
 float rarotation1;
 float rarotation2;
 
 int attrdamp0;
 int attrdamp1;
 int attrdamp2;
 
 float radamp0;
 float radamp1;
 float radamp2;
 
 float cadamp0;
 float cadamp1;
 float cadamp2;
 
 
 
 
 
 
 
 
 //gradient
 bool splitgradient;
 int gradtype;
 int gradsize;
 float mingrad;
 float maxgrad;
 float mingrad2;
 float maxgrad2;
 
 
 //blob
 Boolean blobin;
 float blobforce;
 float blobz;
 float bloboutvel;
 bool blobxinvert;
 bool    blobyinvert;
 bool    blobmirrory;
 bool    blobmirrorx;
 float blobblur;
 
 };
 
*/
