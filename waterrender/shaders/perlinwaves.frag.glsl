//@HeightMap
uniform sampler2D heightMap;

//@DiffuseMap
uniform sampler2D diffuseMap;

//texcoord to derive normal
varying vec2 texcoord;

varying vec3 eyePosition;

uniform vec3 Ks = vec3(0, .1, .4);
uniform vec3 Ka = vec3(.35, .55, .46);
uniform vec3 Kd = vec3(0, .2, .8);
uniform float alpha = 1.5;

uniform mat3 sobelX = mat3(
	-1.0, 0.0, 1.0,
	-2.0, 0.0, 2.0,
	-1.0, 0.0, 1.0);

uniform mat3 sobelY = mat3(
	-1.0, -2.0, -1.0,
	 0.0,  0.0,  0.0,
	 1.0,  2.0,  1.0);

vec3 genN() {
  float gX = 0.0;
  float gY = 0.0;
  float dX = dFdx(texcoord.s);
  float dY = dFdx(texcoord.t);
  for (int x=-1; x<2; x++){
    for (int y=-1; y<2; y++){
       //the '+1' takes it from [-1,1] -> [0,2] the proper indices
       gX += sobelX[y+1][x+1] * (texture2D(heightMap, vec2(texcoord.s+dX*x, texcoord.t)).r);
       gY += sobelY[y+1][x+1] * (texture2D(heightMap, vec2(texcoord.s, texcoord.t+dY*y)).r);
    }
  }
  return vec3(gX, gY, sqrt(1-gX*gX-gY*gY));
}

void main() {
  vec3 N = normalize(genN());
  N = gl_NormalMatrix*N;
  //Basis of Phong as in assignment 3/2
  vec3 V = normalize(-eyePosition);

  vec4 finalColor;
  
  for (int lightIndex = 0; lightIndex < 1; lightIndex++) {
  	vec3 L = normalize(gl_LightSource[lightIndex].position.xyz);
  
  	//Diffuse
  	float Rd = max(0.0, dot(L, N));
  	vec3 Td = texture2D(diffuseMap, texcoord);
  	vec3 diffuse = Rd * Kd * Td * gl_LightSource[lightIndex].diffuse.rgb;
    
    //Specular
  	vec3 R = reflect(-L, N);
  	float Rs = pow(max(0.0, dot(V, R)), alpha);
  	vec3 Ts = vec3(.1, .2, .3);
  	vec3 specular = Rs * Ks * Ts * gl_LightSource[lightIndex].specular.rgb;

  	//Ambient
  	vec3 ambient = Ka * gl_LightSource[lightIndex].ambient.rgb;
  	finalColor += vec4(diffuse + specular + ambient, 1.0);
  }
  gl_FragColor = finalColor;
}