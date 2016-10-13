#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
    
uniform sampler2DRect tex0;


uniform float thresh;
void main()
{

    vec4 col=texture2DRect(tex0, gl_TexCoord[0].st);
//    float intensity = dot(col, vec4(0.299, 0.587, 0.114,0));


    if(col.w>thresh)gl_FragColor = col;
    else gl_FragColor = vec4(0,0,0,0);
    

}