#include "ParallaxShader.h"

ParallaxShader::ParallaxShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = DiffuseMap;
}

ParallaxShader::~ParallaxShader() {
}
void ParallaxShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void ParallaxShader::setUniformDiffuseTex(int in1) const{
  setUniform1i("diffuseTex", in1);
}
void ParallaxShader::setDiffuseMap(int in1) const{
  setUniformDiffuseTex(in1);
}

const Shader::KnownVars* ParallaxShader::getExpectedVars() const {
  return exportedVars;
}
int ParallaxShader::getExpectedVarsCount() const {
  return 2;
}