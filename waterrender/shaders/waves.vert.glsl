//@Position
attribute vec3 positionIn;


//Time
//@Time
uniform float t;

float getWaveHeight(vec2 xyPos,  vec2 dir, float amplitude, 
	float wavelength, float speed) {
	float PI = 3.1415926535897932384626433832795028841971693993751058209;
	float freq = 2.0*PI/wavelength;
	float phase = speed*freq;
	return amplitude*sin(dot(xyPos, dir)*freq + t*phase);
}

void main() {
	positionIn.z = 0;
	positionIn.z += getWaveHeight(positionIn.xy, vec2(1,0), .01, 1.0, .01);
	positionIn.z += getWaveHeight(positionIn.xy, vec2(1,1), .01, 1.0, .06);
	positionIn.z += getWaveHeight(positionIn.xy, vec2(0,1), .01, .5, .01);
	gl_Position = (gl_ProjectionMatrix * gl_ModelViewMatrix * vec4(positionIn, 1));
}