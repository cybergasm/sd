//for opacity mapping
uniform sampler diffuseTex;

varying vec2 texCoord;

void main() {
	vec4 texColor = texture2D(diffuseTex, texCoord);
	gl_FragColor = vec4(texColor.r - .2, texColor.g - .2, texColor.b - .2, texColor.a);
}