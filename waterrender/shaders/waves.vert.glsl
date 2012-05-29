//@Position
attribute vec3 positionIn;


//Time
//@Time
uniform float t;

//Pi constant
uniform 	float PI = 3.1415926535897932384626433832795028841971693993751058209;

//This returns a vec3 containing (dx, dy, height). Since we have to do
//many redundant calculations for each, we do them all in one pass
vec3 getWaveHeight(vec2 xyPos,  vec2 dir, float amplitude, 
	float wavelength, float speed) {
	float freq = 2.0*PI/wavelength;
	float phase = speed*freq;
	float cosSinTerm = dot(xyPos, dir)*freq + t*phase;
	float dx = freq*dir.x*amplitude*cos(cosSinTerm);
	float dy = freq*dir.y*amplitude*cos(cosSinTerm);
	return vec3(dx, dy, amplitude*sin(cosSinTerm));
}

//Derived normal value
varying vec3 N;
varying vec3 eyePosition;

void main() {
	N = vec3(0,0,1);
	positionIn.z = 0;
		
	//Generate information about the wave by summing over the different waves
	vec3 waveInfo = getWaveHeight(positionIn.xy, vec2(1,0), .01, 1.0, .01);
	positionIn.z += waveInfo.z;
	N.x += waveInfo.x;
	N.y += waveInfo.y;
	waveInfo = getWaveHeight(positionIn.xy, vec2(1,1), .01, 1.0, .06);
	positionIn.z += waveInfo.z;
	N.x += waveInfo.x;
	N.y += waveInfo.y;
	waveInfo = getWaveHeight(positionIn.xy, vec2(0,1), .01, .5, .01);
	positionIn.z += waveInfo.z;
	N.x += waveInfo.x;
	N.y += waveInfo.y;
	
	//transform normal
	N = gl_NormalMatrix * N;
	
	//generate eye position vector
	vec4 eyeT = gl_ModelViewMatrix * vec4(positionIn, 1);
  	eyePosition = eyeT.xyz;
  	
	gl_Position = (gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(positionIn, 1));
}