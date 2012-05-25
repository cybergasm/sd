#include "TextureShader.h"

TextureShader::TextureShader(const std::string& location) : Shader(location) {
  exportedVars[0] = DiffuseMap;
}

void TextureShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void TextureShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void TextureShader::setUniformTextureImg(int in1) const{
  setUniform1i("textureImg", in1);
}
void TextureShader::setDiffuseMap(int in1) const{
  setUniformTextureImg(in1);
}

const Shader::KnownVars* TextureShader::getExpectedVars() const {
  return exportedVars;
}
int TextureShader::getExpectedVarsCount() const {
  return 1;
}