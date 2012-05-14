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
void ParallaxShader::setUniformDiffuseTex(int n1){
  setUniform1i(diffuseTex, n1);
}
void ParallaxShader::setUniformHeightMap(int n1){
  setUniform1i(heightMap, n1);
}
void ParallaxShader::setUniformNormalMap(int n1){
  setUniform1i(normalMap, n1);
}
void ParallaxShader::setUniformKs(float in1, float in2, float in3){
  setUniform3f(Ks, n1, n2, n3);
}
void ParallaxShader::setUniformKa(float in1, float in2, float in3){
  setUniform3f(Ka, n1, n2, n3);
}
void ParallaxShader::setUniformKd(float in1, float in2, float in3){
  setUniform3f(Kd, n1, n2, n3);
}
void ParallaxShader::setUniformAlpha(float n1){
  setUniform1f(alpha, n1);
}
