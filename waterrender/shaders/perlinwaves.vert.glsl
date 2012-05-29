//@Position
attribute vec3 positionIn;

//@TextureCoordinates
attribute vec2 texCoordsIn;

//@Normal
attribute vec3 normalIn;

//@HeightMap
uniform sampler2D heightMap;

void main () {
	float sampledHeight = texture2D(heightMap, texCoordsIn).r;
	vec3 position = normalIn*(sampledHeight/5) + positionIn;
	gl_Position = (gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(position, 1));
}