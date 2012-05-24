#include "WavesShader.h"

WavesShader::WavesShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
}

void WavesShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void WavesShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

const Shader::KnownVars* WavesShader::getExpectedVars() const {
  return exportedVars;
}
int WavesShader::getExpectedVarsCount() const {
  return 1;
}