#include "CharacterShader.h"

CharacterShader::CharacterShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = DiffuseMap;
}

CharacterShader::~CharacterShader() {
}
void CharacterShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void CharacterShader::setUniformTextureImg(int in1) const{
  setUniform1i("textureImg", in1);
}
void CharacterShader::setDiffuseMap(int in1) const{
  setUniformTextureImg(in1);
}

const Shader::KnownVars* CharacterShader::getExpectedVars() const {
  return exportedVars;
}
int CharacterShader::getExpectedVarsCount() const {
  return 2;
}