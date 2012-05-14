#include "ParallaxShader.h"

ParallaxShader::ParallaxShader(const std::string& location) : Shader(location) {
}

void ParallaxShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setAttributeTangentIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("tangentIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setAttributeBitangentIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("bitangentIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setUniformDiffuseTex(int in1){
  setUniform1i("diffuseTex", in1);
}
void ParallaxShader::setUniformHeightMap(int in1){
  setUniform1i("heightMap", in1);
}
void ParallaxShader::setUniformNormalMap(int in1){
  setUniform1i("normalMap", in1);
}
void ParallaxShader::setUniformKs(float in1, float in2, float in3){
  setUniform3f("Ks", in1, in2, in3);
}
void ParallaxShader::setUniformKa(float in1, float in2, float in3){
  setUniform3f("Ka", in1, in2, in3);
}
void ParallaxShader::setUniformKd(float in1, float in2, float in3){
  setUniform3f("Kd", in1, in2, in3);
}
void ParallaxShader::setUniformAlpha(float in1){
  setUniform1f("alpha", in1);
}
