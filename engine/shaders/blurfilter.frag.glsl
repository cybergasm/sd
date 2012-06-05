//What we're blurring
uniform sampler textureImg;

varying vec2 texcoord;


void main() {
  float x;
  float y;
  vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);
  vec4 coef = vec4(0.0, 0.0, 0.0, 0.0);
  //Applying gaussian filter. 
  for (y=0.0; y<4.0; y+=.5){
    for (x=0.0; x<4.0; x+=.5){
      vec2 offset = vec2((-1.0+x)*.005, (-1.0+y)*.005);
      vec2 newTex = texcoord.xy + offset; 
      vec4 neighbor = texture2D(textureImg, newTex);
      //tried using discretized version but could not get
      //it to stop making the image darker
      float gaus = exp(-1.0*(length(offset)*length(offset)));
      //weighted average
      sum += gaus*neighbor;
      coef += vec4(1.0); 
    }
  }
  //get the filtered coefficient
  gl_FragColor = sum/coef;
}
