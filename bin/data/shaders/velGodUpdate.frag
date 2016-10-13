#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#define GL_FRAGMENT_PRECISION_HIGH 1

//uniform sampler2DRect backbuffer;  // recive the previus position texture
//uniform sampler2DRect pos;      // recive the velocity texture




uniform float timestep;
uniform int resolution;
uniform int newnum;


uniform float newvel[120]; 
uniform float newidx[80];


void main(void){
    
    
    
    vec2 st = gl_TexCoord[0].st;  // gets the position of the pixel that it´s dealing with...
    int isNew=-1;

   // vec4 stnorm = gl_TexCoord[0];
    if(newnum>0){
        for(int k = 0 ; k<newnum;k++){
            if(abs(st.s-.5-newidx[2*k])<.25&&abs(st.t-.5-newidx[2*k+1])<.25){
                isNew=k;
                break;
            }
        }
    }


if(isNew>-1){
            gl_FragColor.rgba = vec4(newvel[isNew*3],newvel[isNew*3+1],newvel[isNew*3+2],1.0);    
                
            }
     
    


}