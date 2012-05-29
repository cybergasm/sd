varying vec3 N;
varying vec3 eyePosition;

uniform vec3 Ks = vec3(1, 1, 1);
uniform vec3 Ka = vec3(.35, .55, .46);
uniform vec3 Kd = vec3(0, .2, .8);
uniform float alpha = .8;

void main() {
  //Basis of Phong as in assignment 3/2
  N = normalize(N);
  vec3 V = normalize(-eyePosition);

  vec4 finalColor;
  
  for (int lightIndex = 0; lightIndex < 1; lightIndex++) {
  	vec3 L = normalize(gl_LightSource[lightIndex].position.xyz - eyePosition);
  
  	//Diffuse
  	float Rd = max(0.0, dot(L, N));
  
  	vec3 Td = vec3(0, .2, .7);
  	vec3 diffuse = Rd * Kd * Td * gl_LightSource[lightIndex].diffuse.rgb;
    
    //Specular
  	vec3 R = reflect(-L, N);
  	float Rs = pow(max(0.0, dot(V, R)), alpha);

  
  	vec3 Ts = vec3(1, 1, 1);
  	vec3 specular = Rs * Ks * Ts * gl_LightSource[lightIndex].specular.rgb;

  	//Ambient
  	vec3 ambient = Ka * gl_LightSource[lightIndex].ambient.rgb;
  	finalColor += vec4(diffuse + specular + ambient, 1.0f);
  }
  
  gl_FragColor = finalColor;
  
}