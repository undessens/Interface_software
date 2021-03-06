#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#define GL_FRAGMENT_PRECISION_HIGH 1





uniform sampler2DRect tex0;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture

uniform int resolution;
uniform vec2  screen;



// forces
uniform vec3 attr;
uniform float mass;
uniform float massin;
uniform float r;
uniform float rin;
uniform float damp;



    
void main(void){
    
    vec3 vel = texture2DRect(tex0, gl_TexCoord[0].xy).xyz;
    vec3 pos = texture2DRect( posData, gl_TexCoord[0].xy).xyz;
    
    
    vec3 distbuf = (attr-pos);
    float normbuf = length(distbuf);//dist.x*dist.x+dist.y*dist.y+dist.z*dist.z;
    
//    float normxy = sqrt(distbuf.x*distbuf.x+distbuf.y*distbuf.y);
    
    if(normbuf>=r){
        vel+=distbuf*mass/(normbuf*normbuf*normbuf);
    }
    else if(normbuf<=rin){
        vel+=distbuf*massin/(normbuf*normbuf*normbuf);
    }
    else{
        
         vel *=damp;   
        }


    
    gl_FragColor.xyz = vel;

}