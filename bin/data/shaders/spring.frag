#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#define GL_FRAGMENT_PRECISION_HIGH 1





uniform sampler2DRect tex0;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture

uniform int resolution;
uniform vec2  screen;

uniform vec3 attr;

// forces

uniform float k;
uniform float l0;
uniform float z;
uniform int mode;


    
void main(void){
    vec2 st=gl_TexCoord[0].xy;
    vec3 vel = texture2DRect(tex0, st).xyz;
    vec3 pos = texture2DRect( posData, st).xyz;   
    
    


    vec3 distbuf = (attr-pos);
    vec3 distnormed = normalize(distbuf);
    float normbuf = length(distbuf);
    
    //    float normxy = sqrt(distbuf.x*distbuf.x+distbuf.y*distbuf.y);
    if(mode==0){
        vel+=distnormed*((normbuf-l0)*k - dot(vel,distnormed)*z);

    }
    else if (normbuf<l0){
     vel+=distnormed*((normbuf-l0)*k - dot(vel,distnormed)*z);
    }
    
    


    
    
    

    
    gl_FragColor.xyz = vel;

}