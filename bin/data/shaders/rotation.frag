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

uniform float speed;
uniform float r;
uniform int type;
uniform vec3 orientation;



    
void main(void){
    
    vec3 vel = texture2DRect(tex0, gl_TexCoord[0].xy).xyz;
    vec3 pos = texture2DRect( posData, gl_TexCoord[0].xy).xyz;
    
    
    vec3 distbuf = (attr-pos);
    float normbuf = length(distbuf);
    vec3 orientationnorm = normalize(orientation);
    

    if(normbuf<r){
    if(type>0){
        vel+= cross(distbuf/normbuf,orientationnorm)*speed;
    }
        else{
    
        vel.x+=distbuf.y*distbuf.z/normbuf*speed;
        vel.y+=distbuf.x*distbuf.z/normbuf*speed;
        vel.z+=-2*distbuf.y*distbuf.x/normbuf*speed;
    }

    }
    
    gl_FragColor.xyz = vel;

}