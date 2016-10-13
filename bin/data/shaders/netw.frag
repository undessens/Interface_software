#version 120
#extension GL_ARB_texture_rectangle : enable
#extension GL_EXT_gpu_shader4 : enable
#define GL_FRAGMENT_PRECISION_HIGH 1





uniform sampler2DRect tex0;   // recive the previus velocity texture
uniform sampler2DRect posData;      // recive the position texture

uniform int resolution;
uniform vec2  screen;



// forces

uniform float k;
uniform float l0;
uniform float z;
uniform int size;


    
void main(void){
    vec2 st=gl_TexCoord[0].xy;
    vec3 vel = texture2DRect(tex0, st).xyz;
    vec3 pos = texture2DRect( posData, st).xyz;
    
        for(int i = 1 ; i<=size;i++){
    
    
    
    
    
    vec3 distbuf;
    float l0norm = l0/resolution;

    float netmax = 100*l0norm;
            
    float normbuf;
    vec3 linbuf;
    linbuf.x=netmax+1;
        
    if(st.x<resolution-i-1){
            distbuf=pos- texture2DRect( posData , st+vec2(i,0)).xyz;
            linbuf=distbuf;
            normbuf = length(distbuf);
            if(normbuf<netmax){
            vel-=normalize(distbuf)*(normbuf-i*l0norm)*k;
            }
        }
    if(st.x>i+1){
        distbuf=pos-texture2DRect( posData , st+vec2(-i,0)).xyz;
        normbuf = length(distbuf);
        
        if(normbuf<netmax){
            vel-=normalize(distbuf)*(normbuf-i*l0norm)*k;
//            if(st.y<resolution-i){
//               if(length(distbuf)<netmax){
//                vel-=z*(distbuf+linbuf);
//            }
//            }
        }
        
        if(length(linbuf)<netmax){
            vel-=z*(distbuf+linbuf);
        }
        
    }
    
    


    
        }
    

    
    gl_FragColor.xyz = vel;

}