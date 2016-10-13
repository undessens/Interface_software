#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#define GL_FRAGMENT_PRECISION_HIGH 1





uniform sampler2DRect tex0;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture

uniform int resolution;
uniform vec2  screen;



// forces
uniform float f;
uniform float fmin;
uniform float vmax;
uniform float vmin;




    
void main(void){
    
    vec3 vel = texture2DRect(tex0, gl_TexCoord[0].xy).xyz;
    
    
    vel*=f;
    float velnorm = length(vel);
    if(velnorm>vmax){
        vel = normalize(vel)*vmax;
    }
    else if (velnorm>vmin){
        vel*=f;
    }
    else {
        vel*=fmin;
    }


    
    gl_FragColor.xyz = vel;

}