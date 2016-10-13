#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable

uniform sampler2DRect texture;
uniform float offset;
uniform float direction_x;
uniform float contrast;
uniform float saturation;
uniform float brightness;

void main()
{
    vec2 off;
    
    if(direction_x == 1.0)
        off = vec2(offset, 0.0);
    else
        off = vec2(0.0, offset);
    
    
    
    vec4 colorblur = gl_Color * (texture2DRect(texture, gl_TexCoord[0].xy + off * 1.0)	* 0.06 + 
                                 texture2DRect(texture, gl_TexCoord[0].xy + off * 0.75)	* 0.09 +
                                 texture2DRect(texture, gl_TexCoord[0].xy + off * 0.5)	* 0.12 +
                                 texture2DRect(texture, gl_TexCoord[0].xy + off * 0.25)	* 0.15 +
                                 
                                 texture2DRect(texture, gl_TexCoord[0].xy)	* 0.16 + //16
                                 
                                 texture2DRect(texture, gl_TexCoord[0].xy - off * 1.0) 	* 0.06 +
                                 texture2DRect(texture, gl_TexCoord[0].xy - off * 0.75)	* 0.09 +
                                 texture2DRect(texture, gl_TexCoord[0].xy - off * 0.5)	* 0.12 +
                                 texture2DRect(texture, gl_TexCoord[0].xy - off * 0.25)	* 0.15 );
    if(direction_x == 1.0)
        gl_FragColor = colorblur;
    else
    {
        
        // color for 0% contrast (mean color intensity)
        vec3 meanLuminosity = vec3(0.5, 0.5, 0.5);
        
        // coeefficients to convert to greyscale; coeeficients taken from OpenCV, which
        // were derived from 'Adrian Ford, Alan Roberts. Colour Space Conversions.', which
        // can be found here: http://www.poynton.com/PDFs/coloureq.pdf
        //
        vec3 rgb2greyCoeff = vec3(0.299, 0.587, 0.114);
        
        // enbrighten color
        vec3 brightened = colorblur.xyz * brightness;
        
        // approximate color intensity by transforming rgb to grey
        float intensity = dot(brightened, rgb2greyCoeff);		
        
       
        // saturate (brightended) color
        vec3 saturated = mix(vec3(intensity, intensity, intensity), brightened, saturation);
        
        // apply contrast to saturated color
        vec3 contrasted = mix(meanLuminosity, saturated, contrast);
        
        
        gl_FragColor.xyz=contrasted;
       // gl_FragColor.w=intensity;
       
    }
    
}