#include "TextureShader.h"

TextureShader::TextureShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = TextureCoord;
  exportedVars[2] = DiffuseMap;
}

TextureShader::~TextureShader() {
}
void TextureShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void TextureShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void TextureShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void TextureShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTexCoordIn(normalized, stride, data);
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
  return 3;
}