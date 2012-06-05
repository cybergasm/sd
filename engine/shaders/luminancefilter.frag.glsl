//Image to extract from
uniform sampler textureImg;

varying vec2 texcoord;

uniform float illuminanceThresh = .5f;
void main() {
	vec4 pixelVal = texture2D(textureImg, texcoord);
	float illuminance = .2126*pixelVal.r + .7152*pixelVal.g + .0733*pixelVal.b;
	
	if (illuminance > illuminanceThresh) {
		gl_FragColor = pixelVal;
	} else {
		gl_FragColor = vec4(0, 0, 0, 1);
	}
}
