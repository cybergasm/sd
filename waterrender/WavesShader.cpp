#include "WavesShader.h"

WavesShader::WavesShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = Time;
}

void WavesShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void WavesShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
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