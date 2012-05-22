//vertex position
//@Position
attribute vec3 positionIn;

//normals
//@Normal
attribute vec3 normalIn;

//texture coordinate
//@TextureCoordinates
attribute vec2 texCoordIn;

varying vec3 normal;
varying vec3 eyePosition;
varying vec2 texcoord;

void main() {
  vec4 eyeT = gl_ModelViewMatrix * vec4(positionIn, 1);
  eyePosition = eyeT.xyz;
  
  normal = gl_NormalMatrix * normalIn;
  
  gl_Position = (gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(positionIn, 1));
  texcoord = texCoordIn;
}