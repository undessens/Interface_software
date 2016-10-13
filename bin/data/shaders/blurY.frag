#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable


uniform sampler2DRect tex0;
uniform float blurAmnt;

void main()
{
    gl_FragColor =  .06 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, -blurAmnt * 1.0))
                    +.09 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, -blurAmnt * .75))
                    +.12 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, -blurAmnt * .5))
                    +.15 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, -blurAmnt * .25))
    
                    +.16 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0,blurAmnt))
    
                    +.15 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, blurAmnt * .25))
                    +.12 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, blurAmnt * .50))
                    +.09 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, blurAmnt * .75))
                    +.06 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(0.0, blurAmnt * 1.0));
    
    
    

    
    
}