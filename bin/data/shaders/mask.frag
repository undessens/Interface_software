#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
    
uniform sampler2DRect tex0;
uniform sampler2DRect mask;
    
void main()
{
    vec4 col;
    col.xyz = texture2DRect(tex0, gl_TexCoord[0].st).xyz * texture2DRect(mask, gl_TexCoord[0].st).y;
    col.w= texture2DRect(mask, gl_TexCoord[0].st).y ;
        gl_FragColor = col;

}