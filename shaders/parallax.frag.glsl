//for diffuse values
uniform sampler diffuseTex;
uniform sampler heightMap;
uniform sampler normalMap;

varying vec2 texCoord;
varying vec3 eyePosition;
varying vec3 eye;
varying vec3 tangent;
varying vec3 bitangent;
varying vec3 normal;

//Won't waste time passing stuff in as it is the same for
//most tiles  
uniform vec3 Ks = vec3(1, 1, 1);
uniform vec3 Ka = vec3(.3, .1, .1);
uniform vec3 Kd = vec3(1, 1, 1);
uniform float alpha = .8;

void main() {
	float height = texture2D(heightMap, texCoord).r;
	
	//scale and bias to try and represent physical property of
	//surface better.
	float scale = .08;
	float bias = .05;
	
	float newHeight = scale*height - bias;
	
	vec3 eyeVec = normalize(eyePosition);
	
	//move the original texture coordinates
	vec2 texCoordsToUse = texCoord + (eyeVec.xy * newHeight);
	
	//sample diffuse as usual
	vec4 diffuseColor = texture2D(diffuseTex, texCoordsToUse);
	
	//get the normal from texture
    vec3 sampledNormal = texture2D(normalMap, texCoordsToUse).xyz;
    //expand it
    sampledNormal = (sampledNormal - .5) * 2.0;
    //create our tbn
    mat3 tbn = mat3(normalize(tangent), normalize(bitangent), normalize(normal));

    //multiply and normalize
    vec3 N = gl_NormalMatrix * tbn * sampledNormal;

    vec3 L = normalize(gl_LightSource[0].position.xyz);
    vec3 V = normalize(-eye);
	
	// Calculate the diffuse color coefficient, and sample the diffuse texture
	float Rd = max(0.0, dot(L, N));
	vec3 Td = diffuseColor.rgb;
   	vec3 diffuse = Rd * Kd * Td * gl_LightSource[0].diffuse.rgb;
   	
   	// Calculate the specular coefficient
  	vec3 R = reflect(-L, N);
  	float Rs = pow(max(0.0, dot(V, R)), alpha);
  	vec3 Ts = diffuseColor.brg;
  	vec3 specular = Rs * Ks * Ts * gl_LightSource[0].specular.rgb;
  	
  	// Ambient
    vec3 ambient = Ka * gl_LightSource[0].ambient.rgb;

	gl_FragColor = vec4(diffuse + specular + ambient, 1);
}