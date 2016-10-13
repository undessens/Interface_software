#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
//#define GL_FRAGMENT_PRECISION_HIGH 1

uniform sampler2DRect tex0;  // recive the previus position texture
uniform sampler2DRect velData;      // recive the velocity texture


uniform float timestep;
uniform int resolution;



void main(void){
    
    
    
    vec2 st = gl_TexCoord[0].st;  
    
    
    vec3 pos = texture2DRect(tex0,st).xyz; // ... in order to look at a particulary place on it
    vec3 vel = texture2DRect( velData, st ).xyz;     // Fetch both the pos and vel.
    //vel.x*=1.7;
    pos += vel*timestep ; // Updates the position
    //if(borders.x==1){
//        if ( pos.x < 0.0)
//        {pos.x=0;}
//        
//        else if ( pos.x > 1.0)
//        {pos.x=1.0;}
//        
//        if (pos.y < 0.0)
//        {pos.y=0;}
//        
//        else if ( pos.y > 1.0)
//        {pos.y=1.0;}
//    
//    if (pos.z < 0.0)
//    {pos.z=0;}
//    
//    else if ( pos.z > 1.0)
//    {pos.z=1.0;}
    
    //}
    gl_FragColor.xyz = pos;  // And finaly it store it on the position FBO
//}
}