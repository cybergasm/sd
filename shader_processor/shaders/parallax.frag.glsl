//for diffuse values
//@DiffuseMap
uniform sampler diffuseTex;
//@HeightMap
uniform sampler heightMap;
//@NormalMap
uniform sampler normalMap;

varying vec2 texCoord;
varying vec3 eyePosition;
varying vec3 eye;
varying vec3 tangent;
varying vec3 bitangent;
varying vec3 normal;

//Won't waste time passing stuff in as it is the same for
//most tiles
//@Ks  
uniform vec3 Ks = vec3(.14, .14, .1);
//@Ka
uniform vec3 Ka = vec3(.01, .01, .01);
//@Kd
uniform vec3 Kd = vec3(1, 1, 1);
//@Shininess
uniform float alpha = .3;

void main() {
	float height = texture2D(heightMap, texCoord).r;
	
	//scale and bias to try and represent physical property of
	//surface better.
	float scale = .8;
	float bias = .4;
	
	float newHeight = scale*height - bias;
	
	vec3 eyeVec = normalize(eyePosition);
	
	//move the original texture coordinates
	vec2 texCoordsToUse = texCoord + (eyeVec.xy * newHeight);
	
	//sample diffuse as usual
	vec4 diffuseColor = texture2D(diffuseTex, texCoordsToUse);
	
	//get the normal from texture
    vec3 sampledNormal = texture2D(normalMap, texCoord).xyz;
    //expand it
    sampledNormal = (sampledNormal - .5) * 2.0;
    //create our tbn
    mat3 tbn = mat3(normalize(tangent), normalize(bitangent), normalize(normal));

    //multiply and normalize
    vec3 N = gl_NormalMatrix * tbn * sampledNormal;
    N = normalize(N);
    vec3 V = normalize(-eye);

	vec4 finalColor;
	
	for (int lightIndex = 0; lightIndex < 1; lightIndex++) {
    	vec3 L = normalize(gl_LightSource[lightIndex].position.xyz);
	
		// Calculate the diffuse color coefficient, and sample the diffuse texture
		float Rd = max(0.0, dot(L, N));
		vec3 Td = diffuseColor.rgb;
   		vec3 diffuse = Rd * Kd * Td * gl_LightSource[lightIndex].diffuse.rgb;
   	
   		// Calculate the specular coefficient
  		vec3 R = reflect(-L, N);
  		float Rs = pow(max(0.0, dot(V, R)), alpha);
  		vec3 Ts = vec3(.1);
  		vec3 specular = Rs * Ks * Ts * gl_LightSource[lightIndex].specular.rgb;
  	
  		// Ambient
    	vec3 ambient = Ka * gl_LightSource[lightIndex].ambient.rgb;
    	finalColor += vec4(diffuse + specular + ambient, 1);
	}
	gl_FragColor = finalColor;
}