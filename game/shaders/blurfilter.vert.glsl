//vertex color
attribute vec3 positionIn;

//texture coordinate
attribute vec2 texCoordIn;

varying vec2 texcoord;

void main() {
  gl_Position = (gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(positionIn, 1));
  texcoord = texCoordIn;
}

