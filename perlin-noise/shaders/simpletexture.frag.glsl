//for diffuse mapping
//@DiffuseMap
uniform sampler textureImg;

varying vec2 texcoord;

void main() {
	gl_FragColor = texture2D(textureImg, texcoord);
}
