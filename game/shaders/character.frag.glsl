//for opacity mapping
uniform sampler textureImg;

varying vec3 normal;
varying vec3 eyePosition;
varying vec4 color;
varying vec2 texcoord;

//Won't waste time passing stuff in as it is the same for
//most tiles  
uniform vec3 Ks = vec3(.3, .4, 0.34);
uniform vec3 Ka = vec3(.35, .55, .46);
uniform vec3 Kd = vec3(.2, .1, .4);
uniform float alpha = .8;
uniform float t = 0;

void main() {
  vec2 tcoord = texcoord + cos(.1*t)/2.0f;
  vec4 texColor = texture2D(textureImg, tcoord);

  //Basis of Phong as in assignment 3/2
  vec3 N = normalize(normal);
  vec3 V = normalize(-eyePosition);

  vec4 finalColor;
  
  for (int lightIndex = 0; lightIndex < 1; lightIndex++) {
  	vec3 L = normalize(gl_LightSource[lightIndex].position.xyz - eyePosition);
  
  	//Diffuse
  	float Rd = max(0.0, dot(L, N));
  
  	vec3 Td = texColor.rgb;
  	vec3 diffuse = Rd * Kd * Td * gl_LightSource[lightIndex].diffuse.rgb;
    
    //Specular
  	vec3 R = reflect(-L, N);
  	float Rs = pow(max(0.0, dot(V, R)), alpha);

  
  	vec3 Ts = texColor.rgb;
  	vec3 specular = Rs * Ks * Ts * gl_LightSource[lightIndex].specular.rgb;

  	//Ambient
  	vec3 ambient = Ka * gl_LightSource[lightIndex].ambient.rgb;
  	finalColor += vec4(diffuse + specular + ambient, 1.0f);
  }
  
  gl_FragColor = finalColor;
}