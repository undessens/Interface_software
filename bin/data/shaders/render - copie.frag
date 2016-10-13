#version 120
#extension GL_ARB_texture_rectangle : enable


// This fill the billboard made on the Geometry Shader with a texture


uniform float texw;

uniform float alpha;


void main() {
    vec2 st = 2*gl_PointCoord.st-vec2(1,1);
 
    
    float curalpha = alpha*max(0.3,1-length(st));//max(0.f,1.f-texture2DRect(Tex,vec2(l,1)).x);
    



    gl_FragColor = vec4(gl_Color.xyz,curalpha*curalpha);
    


}