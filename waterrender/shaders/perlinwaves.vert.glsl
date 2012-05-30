//@Position
attribute vec3 positionIn;

//@TextureCoordinates
attribute vec2 texCoordsIn;

//@Normal
attribute vec3 normalIn;

//@HeightMap
uniform sampler2D heightMap;

//passing in texcoord to derive normal in frag
varying vec2 texcoord;

varying vec3 eyePosition;

void main () {
	float sampledHeight = texture2D(heightMap, texCoordsIn).r;
	vec3 position = normalIn*(sampledHeight/7.0) + positionIn;
	
	texcoord = texCoordsIn;
    
    //generate eye position vector
	vec4 eyeT = gl_ModelViewMatrix * vec4(positionIn, 1);
  	eyePosition = eyeT.xyz;
  	
	gl_Position = (gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(position, 1));
}