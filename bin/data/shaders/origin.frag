#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#define GL_FRAGMENT_PRECISION_HIGH 1





uniform sampler2DRect tex0;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture
uniform sampler2DRect originData;      // recive the origin

uniform int resolution;
uniform vec2  screen;



// forces

uniform float k;
uniform float z;
uniform float freeze;
uniform float freezemin;
uniform float damp;


    
void main(void){

    vec3 vel = texture2DRect(tex0, gl_TexCoord[0].xy).xyz;
    
    vec3 ori =  texture2DRect( originData, gl_TexCoord[0].xy).xyz;
    vec3 pos = texture2DRect( posData, gl_TexCoord[0].xy).xyz;
    
    
    vec3 velbuf = (ori-pos)*k;
    
    if( velbuf.x * velbuf.x * velbuf.y * velbuf.y > 0 ){
    
    vel+=velbuf-normalize(velbuf)*dot(vel,normalize(velbuf))*z;
        
    }
    
    if(freeze>0&&length(ori-pos)<freeze &&length(ori-pos)>freezemin ){
        vel*=damp;
    
    }
     

    //vel.x+= 0.1;
    //	if(vel.x>1.0){    
    //		 vel.x=0;   
    //	}
  
    

    
    gl_FragColor.xyz = vel;

}