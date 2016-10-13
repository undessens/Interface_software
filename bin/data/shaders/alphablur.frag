#version 120
uniform float amount;
uniform sampler2D tex0;


void main() {
	vec4 col = texture2D(tex0, gl_TexCoord[0].xy);

	float destalpha = col.w-amount;

        gl_FragColor =vec4(col.xyz, max(0,destalpha));

}
