//vertex position
//@Position
attribute vec3 positionIn;

//texture coordinate
//@TextureCoordinates
attribute vec2 texCoordIn;

//normal vector
//@Normal
attribute vec3 normalIn;

//tangent bitangent vector
//@Tangent
attribute vec3 tangentIn;
//@Bitangent
attribute vec3 bitangentIn;

varying vec2 texCoord;
varying vec3 tangent;
varying vec3 bitangent;
varying vec3 normal;

//we need the eye vector to do calculations
//in frag shader
varying vec3 eyePosition;

//The eye position 
varying vec3 eye;

void main() {
	texCoord = texCoordIn;
	tangent = tangentIn;
	bitangent = bitangentIn;
	normal = normalIn;
		
	//form the TBN matrix to get the position in tangent space where
	//our height is
	mat3 tangentBitangentNormal = mat3(normalize(tangent), normalize(bitangent), normalize(normal));  
    vec4 eyeTemp = gl_ModelViewMatrix * vec4(positionIn, 1);
    eyePosition = eyeTemp.xyz;
	eyePosition *= tangentBitangentNormal;	
	eye = eyeTemp.xyz;
	
	gl_Position = (gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(positionIn, 1));

}