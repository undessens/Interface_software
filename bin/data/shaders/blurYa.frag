#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable


uniform sampler2DRect tex0;
uniform float blurAmnt;

void main()
{
 
    
    gl_FragColor.z =  .06 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, -blurAmnt * 1.0)).z
                    +.09 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, -blurAmnt * .75)).z
                    +.12 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, -blurAmnt * .5)).z
                    +.15 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, -blurAmnt * .25)).z
    
                    +.16 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0,blurAmnt)).z
    
                    +.15 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, blurAmnt * .25)).z
                    +.12 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, blurAmnt * .50)).z
                    +.09 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, blurAmnt * .75)).z
                    +.06 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, blurAmnt * 1.0)).z;
    
    
    

    
    
}