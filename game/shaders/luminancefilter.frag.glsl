//for opacity mapping
uniform sampler textureImg;

varying vec2 texcoord;

void main() {
	vec4 pixelVal = texture2D(textureImg, texcoord);
	float illuminance = .2126*pixelVal.r + .7152*pixelVal.g + .0733*pixelVal.b;
	
	if (illuminance > .5f) {
		gl_FragColor = pixelVal;
	} else {
		gl_FragColor = vec4(0, 0, 0, 1);
	}
}
