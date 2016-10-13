#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
    
uniform sampler2DRect tex0;

uniform int size;

    
    void main()
    {

        vec2 st = gl_TexCoord[0].st;
        vec4 sum = vec4(0);
        
        int j,i;
        for( i= -size ;i < size; i++){
            for (j = -size+1; j < size-1; j++){
                sum += texture2DRect(tex0, st + vec2(j, i)*0.004) * 0.25;
            }
        }
        
        if (texture2DRect(tex0, st).r < 0.3){
            gl_FragColor = sum * sum * 0.012 + texture2DRect(tex0, st);
        } else {
            if (texture2DRect(tex0, st).r < 0.5){
                gl_FragColor = sum * sum * 0.009 + texture2DRect(tex0, st);
            } else {
                gl_FragColor = sum * sum * 0.0075 + texture2DRect(tex0, st);
            }
        }

}