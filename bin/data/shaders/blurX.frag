#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
    

uniform sampler2DRect tex0;
uniform float blurAmnt;

void main()
{
    gl_FragColor =   .06 * texture2DRect(tex0, gl_TexCoord[0].st + vec2( -blurAmnt * 1.0, 0.0))
                    +.09 * texture2DRect(tex0, gl_TexCoord[0].st + vec2( -blurAmnt * .75, 0.0))
                    +.12 * texture2DRect(tex0, gl_TexCoord[0].st + vec2( -blurAmnt * .50, 0.0))
                    +.15 * texture2DRect(tex0, gl_TexCoord[0].st + vec2( -blurAmnt * .25, 0.0))
                    
                    +.16 * texture2DRect(tex0, gl_TexCoord[0].st + vec2(blurAmnt, 0.0))
                    
                    +.15 * texture2DRect(tex0, gl_TexCoord[0].st + vec2( blurAmnt * .25, 0.0))
                    +.12 * texture2DRect(tex0, gl_TexCoord[0].st + vec2( blurAmnt * .50, 0.0))
                    +.09 * texture2DRect(tex0, gl_TexCoord[0].st + vec2( blurAmnt * .75, 0.0))
                    +.06 * texture2DRect(tex0, gl_TexCoord[0].st + vec2( blurAmnt * 1.0, 0.0));
}