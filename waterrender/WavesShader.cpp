#include "WavesShader.h"

WavesShader::WavesShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = Time;
}

WavesShader::~WavesShader() {
}
void WavesShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void WavesShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void WavesShader::setUniformKa(float in1, float in2, float in3) const{
  setUniform3f("Ka", in1, in2, in3);
}
void WavesShader::setUniformKd(float in1, float in2, float in3) const{
  setUniform3f("Kd", in1, in2, in3);
}
void WavesShader::setUniformKs(float in1, float in2, float in3) const{
  setUniform3f("Ks", in1, in2, in3);
}
void WavesShader::setUniformPI(float in1) const{
  setUniform1f("PI", in1);
}
void WavesShader::setUniformAlpha(float in1) const{
  setUniform1f("alpha", in1);
}
void WavesShader::setUniformT(float in1) const{
  setUniform1f("t", in1);
}
void WavesShader::setTime(float in1) const{
  setUniformT(in1);
}

const Shader::KnownVars* WavesShader::getExpectedVars() const {
  return exportedVars;
}
int WavesShader::getExpectedVarsCount() const {
  return 2;
}