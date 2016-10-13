#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
//#define KERNEL_SIZE 9
#define GL_FRAGMENT_PRECISION_HIGH 1
//#define Debugmode




uniform sampler2DRect backbuffer;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture
uniform sampler2DRect originData;      // recive the position texture
uniform sampler2DRect blob;

uniform int resolution;
uniform vec2  screen;
uniform vec3 mousein;
uniform int Click;
uniform vec2 insize;

uniform float timestep;


// forces

uniform int random;
uniform vec4 origin;
uniform vec4 netw;
uniform vec4 neth;
uniform int netshot;
uniform vec2 borders;
uniform vec3 mouserotation;
uniform vec4 mousespring;
uniform vec3 mousedamp;
uniform vec3 gravitouse;
uniform vec4 mousegravity;
uniform vec4 mousepicker;
uniform vec2 lorenz;


uniform vec4 xspring;
uniform vec4 yspring;
uniform vec4 zspring;

uniform float attractors[80];
uniform vec3 attrrotation0;
uniform vec3 attrrotation1;
uniform vec3 attrrotation2;
uniform vec4 attrspring0;
uniform vec4 attrspring1;
uniform vec4 attrspring2;
uniform vec4 attrgravity0;
uniform vec4 attrgravity1;
uniform vec4 attrgravity2;
uniform vec3 attrdamp0;
uniform vec3 attrdamp1;
uniform vec3 attrdamp2;
uniform int numattractors;

uniform vec4 friction;



uniform vec4 blobf;
uniform float seed;

uniform int split;


uniform vec3 plan;
uniform vec4 planforce;






//Updates
// uniform float newvel[30];
//uniform int newnum;
//
//uniform float newidx[20];

    
void main(void){
    float mult=screen.x;
    float screenratio=screen.y/screen.x;
    vec2 st = gl_TexCoord[0].xy;    // gets the position of the pixel that it´s dealing with...

//    int isNew=-1;
//    int newnumcpy = newnum;
//    if(newnum>0){
//        for(int k = 0 ; k<newnumcpy;k++){
//            if(abs(st.s-.5-newidx[2*k])<.25&&abs(st.t-.5-newidx[2*k+1])<.25){
//                isNew=k;
//                break;
//            }
//        }
//    }
//  
//    
//    if(isNew>-1){
//        gl_FragColor.rgba = vec4(newvel[isNew*3],newvel[isNew*3+1]/screenratio,newvel[isNew*3+2],1.0);    
//        
//    }
//    else{
    
    
 
    vec3 pos = texture2DRect( posData, st).xyz;
    
   
    
    pos.y*=screenratio;
    pos*=mult;
    // ... for gettinh the position data 
    vec3 vel = texture2DRect( backbuffer, st ).xyz;
    vel.y*=screenratio;
    vel*=mult;
    vec3 ori =  texture2DRect( originData, st).xyz;
    ori.y*=screenratio;
    ori*=mult;
    ori-=pos;    
    vec3 prevvel = vel;
    vec3 velbuf;
    vec3 distbuf;
    float normbuf;


    
    
    vec3 mouse=mousein;
    mouse.x*= mult;
    mouse.y*=screenratio*mult;
    mouse.z*=mult;
 
    float netmax=mult*50.0/resolution;
    
    if(origin.x>0){
        if(origin.w>0&&length(ori)<10){
                vel*=0.5;

        }
    velbuf = ori*origin.y;
    // TODO check the BMF bug.
    vel+=velbuf-normalize(velbuf)*dot(prevvel,normalize(velbuf))*origin.z;
    //vel+=ori*origin.y*(1+origin.z)-origin.z*prevvel;        
    }
    
  
    vel.x+=gravitouse.x;
        vel.y+=gravitouse.y;
    vel.z+=gravitouse.z;
    
        
    if(xspring.x>0){
           // if(abs(xspring.y-pos.x)>0.1){
            
            vel.x+=(xspring.y-pos.x)*xspring.z-prevvel.x*xspring.w;
           // }
        }
    if(yspring.x>0){
        //if(abs(yspring.y-pos.y)>0.1){
            
            vel.y+=(yspring.y-pos.y)*yspring.z-prevvel.y*yspring.w;
        //}
    }
    if(zspring.x>0){
        //if(abs(zspring.y-pos.z)>0.1){
            
            vel.z+=(zspring.y-pos.z)*zspring.z-prevvel.z*zspring.w;
        //}
    }
    
    if(planforce.x>0){
        distbuf=pos;
        distbuf-=mult/2.0*vec3(1,screenratio,1);
        velbuf= (planforce.y-dot(plan,distbuf))*planforce.z*plan;
        vel+=velbuf-normalize(velbuf)*(dot(normalize(velbuf),prevvel))*planforce.w;
    }
   
    
    //Mouse
    if(Click>0){ 
     
        distbuf = (mouse-pos);
        vec3 distnormed = normalize(distbuf);
        normbuf = length(distbuf);//dist.x*dist.x+dist.y*dist.y+dist.z*dist.z;
        float normxy = sqrt(distbuf.x*distbuf.x+distbuf.y*distbuf.y);
        
        if(mousespring.x>0){
            if(mousespring.x<2&&normbuf<mousespring.y||mousespring.x>1){
            velbuf=distnormed*(normbuf-mousespring.y)*mousespring.z;
                vel+=velbuf;//-normalize(velbuf)*(dot(normalize(velbuf),prevvel))*mousespring.w;
//    vel+=distnormed*(norm-mousespring.y)*mousespring.z*(1+mousespring.w)-prevvel*mousespring.w;
            }
        }
        if(mouserotation.x>0&&normxy<mouserotation.y){
            vel.x+=distbuf.y*distbuf.z/normbuf*mouserotation.z;
            vel.y+=distbuf.x*distbuf.z/normbuf*mouserotation.z;
            vel.z+=-2*distbuf.y*distbuf.x/normbuf*mouserotation.z;
        }
        
        if(mousegravity.x>0&&normbuf>1){
          vel+=normbuf<=mousegravity.z?distbuf*mousegravity.w/(normbuf*normbuf*normbuf) : distbuf*mousegravity.y/(normbuf*normbuf*normbuf);
        }
     
        if(lorenz.x>0){
        
            vel.x+=lorenz.y*10.0*(distbuf.y-distbuf.x);
            vel.y+=lorenz.y*(28.0*distbuf.x-distbuf.y-distbuf.x*distbuf.z);
            vel.z+=lorenz.y*(-8.0/3.0*distbuf.z+distbuf.x*distbuf.y);
        }  
        
        if(mousepicker.x>0){

            vec2 coordtmp;
            coordtmp.x=resolution/2;
            coordtmp.y=resolution/2;
            if(mousepicker.x==2&&st.x<mousepicker.y||mousepicker.x==1&&length(st-coordtmp)<mousepicker.y){
           
            velbuf=distbuf*mousepicker.z;
                vel+=velbuf-normalize(velbuf)*(dot(normalize(velbuf),prevvel))*mousepicker.w;
            }
            
        }
        
        if(mousedamp.x>0){
            if(normbuf<mousedamp.y){
                vel*=1.0*mousedamp.z;
            }
        }
       
        
        

      
    }
    
    //Attractors

        for(int k=0;k< numattractors;k++){
            float attrclass = attractors[k*5];
            //if(attractors[k*4]>0){
            distbuf = mult*vec3(attractors[k*5+1],attractors[k*5+2]*screenratio,mousein.z)-pos;
            normbuf = length(distbuf);
            float attrnormxy = length(distbuf.xy);
            if(attrclass==0){
                if(attrspring0.x>0){
                    if(attrspring0.x<2&&normbuf<attrspring0.y||attrspring0.x>1){
                        velbuf = normalize(distbuf)*(normbuf-attrspring0.y)*attrspring0.z;
                        vel+=velbuf-normalize(velbuf)*dot(prevvel,normalize(velbuf))*attrspring0.w;
                    }
                }
                
                if(attrgravity0.x>0&&normbuf>1){
                    
                    vel+=normbuf<attrgravity0.z?distbuf*attrgravity0.w/(normbuf*normbuf*normbuf):distbuf*attrgravity0.y/(normbuf*normbuf*normbuf);
                    
                }
                
                if(attrrotation0.x>0&&normbuf<attrrotation0.y){
                    vel.x+=distbuf.y*distbuf.z/normbuf*attrrotation0.z;
                    vel.y+=distbuf.x*distbuf.z/normbuf*attrrotation0.z;
                    vel.z+=-2*distbuf.y*distbuf.x/normbuf*attrrotation0.z;
                }
                if(attrdamp0.x>0){
                    if(normbuf<attrdamp0.y){
                        vel*=1.0*attrdamp0.z;
                    }
                }
                
                // vel+=3*mult/attrnorm*vec3(attractors[nattr*4+2],attractors[nattr*4+3],0);
            }
        
    else if(attrclass==1){
        if(attrspring1.x>0){
            if(attrspring1.x<2&&normbuf<attrspring1.y||attrspring1.x>1){
                velbuf = normalize(distbuf)*(normbuf-attrspring1.y)*attrspring1.z;
                vel+=velbuf-normalize(velbuf)*dot(prevvel,normalize(velbuf))*attrspring1.w;
            }
        }
        
        if(attrgravity1.x>0&&normbuf>1){
            
            vel+=normbuf<attrgravity1.z?distbuf*attrgravity1.w/(normbuf*normbuf*normbuf):distbuf*attrgravity1.y/(normbuf*normbuf*normbuf);
            
        }
        
        if(attrrotation1.x>0&&normbuf<attrrotation1.y){
            vel.x+=distbuf.y*distbuf.z/normbuf*attrrotation1.z;
            vel.y+=distbuf.x*distbuf.z/normbuf*attrrotation1.z;
            vel.z+=-2*distbuf.y*distbuf.x/normbuf*attrrotation1.z;
        }
        if(attrdamp1.x>0){
            if(normbuf<attrdamp1.y){
                vel*=1.0*attrdamp1.z;
            }
        }
        
        // vel+=3*mult/attrnorm*vec3(attractors[nattr*4+2],attractors[nattr*4+3],0);
    
}
else if(attrclass==2){
    if(attrspring2.x>0){
        if(attrspring2.x<2&&normbuf<attrspring2.y||attrspring2.x>1){
            velbuf = normalize(distbuf)*(normbuf-attrspring2.y)*attrspring2.z;
            vel+=velbuf-normalize(velbuf)*dot(prevvel,normalize(velbuf))*attrspring2.w;
        }
    }
    
    if(attrgravity2.x>0&&normbuf>1){
        
        vel+=normbuf<attrgravity2.z?distbuf*attrgravity2.w/(normbuf*normbuf*normbuf):distbuf*attrgravity2.y/(normbuf*normbuf*normbuf);
        
    }
    
    if(attrrotation2.x>0&&normbuf<attrrotation2.y){
        vel.x+=distbuf.y*distbuf.z/normbuf*attrrotation2.z;
        vel.y+=distbuf.x*distbuf.z/normbuf*attrrotation2.z;
        vel.z+=-2*distbuf.y*distbuf.x/normbuf*attrrotation2.z;
    }
    if(attrdamp2.x>0){
        if(normbuf<attrdamp2.y){
            vel*=1.0*attrdamp2.z;
        }
    }
    
    // vel+=3*mult/attrnorm*vec3(attractors[nattr*4+2],attractors[nattr*4+3],0);
}
}



    if((netshot>0&&Click>0)||netshot==0){  
       // float plast = 1.0;
    vec3 linbuf;
    if(netw.x>0){
        
        
        linbuf.x=netmax+1;
        
    if(st.x<resolution-1){
        distbuf= texture2DRect( posData, st+vec2(1,0)).xyz;
        distbuf.y*=screenratio;
        distbuf*=mult;
        distbuf-=pos;
        linbuf=distbuf;
        normbuf = length(distbuf);
//        
//      if(normbuf>netmax){
//          plast= 0;//= 1/(normbuf-netmax);
//      }
            vel+=normalize(distbuf)*(normbuf-netw.y)*netw.z;//velbuf-normalize(velbuf)*dot(prevvel,normalize(velbuf))*netw.w;
               
    }
   
    
    if(st.x>1){
        
        //plast=1.0;
        distbuf= texture2DRect( posData, st-vec2(1,0)).xyz;
        distbuf.y*=screenratio;
        distbuf*=mult;
        distbuf-=pos;
        normbuf = length(distbuf);
        if(normbuf<netmax){
            if(length(linbuf)<netmax){
                vel+=mult*netw.w*(distbuf+linbuf);
            }
           //1/(normbuf-netmax);
        }
        
            vel+=normalize(distbuf)*(normbuf-netw.y)*netw.z;//velbuf-normalize(velbuf)*dot(prevvel,normalize(velbuf))*netw.w;
        
        
    }
    
    }
    
    if(neth.x>0){
        
  
    if(st.y<resolution-1){
        distbuf= texture2DRect( posData, st+vec2(0,1)).xyz;
        distbuf.y*=screenratio;
        distbuf*=mult;
        distbuf-=pos;
        linbuf=distbuf;
        normbuf = length(distbuf);
        if(normbuf<netmax){
            vel += normalize(distbuf)*(normbuf-neth.y)*neth.z;
            //vel+=velbuf-normalize(velbuf)*dot(prevvel,normalize(velbuf))*neth.w;
        }
        
    }
    if(st.y>1){
        distbuf= texture2DRect( posData, st-vec2(0,1)).xyz;
        distbuf.y*=screenratio;
        distbuf*=mult;
        distbuf-=pos;
        normbuf = length(distbuf);
        if(normbuf<netmax){
            if(length(linbuf)<netmax){
                vel+=mult*netw.w*(distbuf+linbuf);
            }
            //velbuf = 
            vel+=normalize(distbuf)*(normbuf-neth.y)*neth.z;//velbuf//-normalize(velbuf)*dot(prevvel,normalize(velbuf))*neth.w;
        }
        
    }
    }
    
    }
        
        
    velbuf.x=length(vel);
        
        
        
        
        if(velbuf.x>friction.z){
            vel=normalize(vel)*friction.z;
        }
        else if(velbuf.x>friction.y){   
            vel*=friction.x;
        }
        else{
            vel*=friction.w;
        }

    //float normori= ori.x*ori.x+ori.y*ori.y+ori.z*ori.z;
        //Blob
        if(blobf.y!=0){
        distbuf=pos/mult;
#ifdef Debugmode
        distbuf.x=insize.x*(1-distbuf.x);
#else
        distbuf.x*=insize.x;
#endif
        distbuf.y=insize.y*(distbuf.y/(screenratio));
            if(distbuf.y<insize.y-2&&distbuf.y>2&&distbuf.x>2&&distbuf.x<insize.x-2){
        vec3 blobforce;
        //if(texture2DRect( blob, distbuf.xy).x<0.9){
            
        normbuf = texture2DRect( blob, distbuf.xy).y;
            
        if(normbuf>0.9){//0.8){
                    if(blobf.w!=0){vel+= mult*vec3(0,0,blobf.w);}       
        }
        
        else if(normbuf>0.1){
           
#ifdef Debugmode
            velbuf.x=-(texture2DRect( blob, distbuf.xy+vec2(1,0)).x-normbuf);//texture2DRect( blob, distbuf.xy-vec2(1,0) ).x);
#else
            velbuf.x=(texture2DRect( blob, distbuf.xy+vec2(1,0)).x-normbuf);//texture2DRect( blob, distbuf.xy-vec2(1,0) ).x);
#endif
            
                      
                      
            velbuf.y =-(texture2DRect( blob, distbuf.xy+vec2(0,1) ).x-normbuf);//texture2DRect( blob, distbuf.xy-vec2(0,1) ).x);
            velbuf.z =0;//blobf*normbuf;//blobf* texture2DRect( blob, distbuf.xy).x;
            //}
            velbuf = normalize(velbuf);
            blobforce=blobf.y*velbuf;
            if(blobf.x==0){
                blobforce*=-1;
            }
            if(dot(vel,blobforce)<0){
            //vel*=blobf.z;
            vel=blobforce*mult;
            }
        }

        }
        }
    
    if(random>0||random<0){
    vel*=1+random/100.0*st.x/resolution;//*st.y/resolution;
    }
    
    //vel*=vec3(.9,.9,.9);
    // Calculates what´s going to be the next position without updating it.
    // Just to see if it collide with the borders of the FBO texture
    //
   // pos.x*=screenratio;
    
    
    //distbufition
    distbuf = pos/mult;
    vel/=mult;
    vel.y/=screenratio;
    

    
  //  float lala =vel.x*vel.x+vel.y*vel.y+vel.z*vel.z;
//    vel*=min(0.8/lala,1.0);
    distbuf += vel * timestep;
   
        
    // If it´s going to collide change the velocity course
    //
    if(borders.x>0){
    if ( distbuf.x < 0.0)
    {vel.x = borders.y * abs(vel.x)+0.001;}
        
    else if ( distbuf.x > 1.0)
   {vel.x = -borders.y * abs(vel.x)-0.001;}
        
    if (distbuf.y < 0.0)
    {vel.y = borders.y * abs(vel.y)+0.001;}
    
   else if ( distbuf.y/screenratio > 1.0)
    {vel.y = -borders.y * abs(vel.y)-0.001;}
    
    if (distbuf.z < 0.0)
    {vel.z = borders.y * abs(vel.z)+0.001;}
    
   else if ( distbuf.z > 1.0)
    {vel.z = -borders.y * abs(vel.z)-0.001;}
    
 }
    

    
    gl_FragColor = vec4(vel.x,vel.y,vel.z,1.0);
        
        // Then save the vel data into the velocity FBO
        
        
    
    
   // } 
}