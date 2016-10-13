#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
    
uniform sampler2DRect tex0;

uniform float contrast;
uniform float saturation;
uniform float brightness;


    
    void main()
    {
            // coeefficients to convert to greyscale; coeeficients taken from OpenCV, which
            // were derived from 'Adrian Ford, Alan Roberts. Colour Space Conversions.', which
            // can be found here: http://www.poynton.com/PDFs/coloureq.pdf
            //
        vec3 rgb2greyCoeff = vec3(0.299, 0.587, 0.114);
        // color for 0% contrast (mean color intensity)
        vec3 meanLuminosity = vec3(0.5, 0.5, 0.5);
            
            // enbrighten color
            vec3 brightened = texture2DRect(tex0, gl_TexCoord[0].st).xyz * brightness;
            
            // approximate color intensity by transforming rgb to grey
            float intensity = dot(brightened, rgb2greyCoeff);		
            
            // saturate (brightended) color
            vec3 saturated = mix(vec3(intensity, intensity, intensity), brightened, saturation);
            
            // apply contrast to saturated color
            vec3 contrasted = mix(meanLuminosity, saturated, contrast);
        

    
            gl_FragColor.xyz = contrasted;

}