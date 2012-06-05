//original rendering
uniform sampler textureImg;
//light to add
uniform sampler lightImg;

varying vec2 texcoord;

uniform float bloomFactor = .8;

void main() {
  vec4 origColor = texture2D(textureImg, texcoord);
  vec4 lightColor = texture2D(lightImg, texcoord);
  gl_FragColor = bloomFactor*lightColor + origColor;
}
