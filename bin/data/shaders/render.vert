#version 120 
#extension GL_EXT_gpu_shader4 : enable
#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect posTex;
uniform sampler2DRect velTex;
uniform sampler2DRect gradient;

uniform sampler2DRect img;




uniform vec4 colorpart;
uniform vec3 screen;
uniform int resolution;

uniform int curnum;
uniform int iscam;
uniform vec2 gradbounds;
uniform vec2 gradbounds2;
uniform vec3 mouse;
uniform vec2 insize;
uniform vec2 imgRes;



void main() {
    // Takes the position of a vertex that was send on porpuse to the same  
    // position on the texture were it´s the information stored on the Red Green channels
    //
    vec2 verPos = gl_Vertex.xy;
   
    
    vec4 pixPos = texture2DRect( posTex, verPos );
    
    // Maps the position from the texture (from 0.0 to 1.0) to
    // the screen position (0 - screenWidth/screenHeight)
   
    // gl_PointSize  = pixPos.z;
    
    
    if(colorpart.x==0){
        
        gl_FrontColor = vec4(colorpart.y/255.0,colorpart.z/255.0,colorpart.w/255.0,1.);
    }
    else if(colorpart.x==1){
        
        gl_FrontColor = texture2DRect(gradient,vec2(100.0*(pixPos.z-1/2.0-gradbounds.x)/(gradbounds.y-gradbounds.x),1));
    }
    
    
    else if(colorpart.x==2){
        
        
        gl_FrontColor = texture2DRect(gradient,vec2(100.0*(100.0*length(texture2DRect(velTex, verPos ).xyz)-gradbounds.x)/(gradbounds.y-gradbounds.x),0));
        
        
    }
    
    else if(colorpart.x == 3){
         gl_FrontColor = texture2DRect(img,verPos*imgRes/vec2(resolution,resolution));
    }
    

    
    pixPos.x =pixPos.x*screen.x;
    pixPos.y =pixPos.y*screen.y;
    pixPos.z =(pixPos.z-0.5)*screen.z;
    
    gl_Position = gl_ModelViewProjectionMatrix*pixPos;
    



 
//    if(iscam>0){
//        vec2 camPos=verPos.xy;
//        camPos.x*=insize.x/resolution;
//        camPos.y=insize.y*(1-camPos.y/resolution);
//    gl_FrontColor =texture2DRect( camin, camPos.xy );//vec4(0.0,0.8,0.1,1.);//gl_Color;//
//    }
//    else{


      
//    }
    
    

}