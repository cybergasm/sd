#include "BlurFilterShader.h"

BlurFilterShader::BlurFilterShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = TextureCoord;
}

BlurFilterShader::~BlurFilterShader() {
}
void BlurFilterShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void BlurFilterShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void BlurFilterShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void BlurFilterShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTexCoordIn(normalized, stride, data);
}

void BlurFilterShader::setUniformTextureImg(int in1) const{
  setUniform1i("textureImg", in1);
}
const Shader::KnownVars* BlurFilterShader::getExpectedVars() const {
  return exportedVars;
}
int BlurFilterShader::getExpectedVarsCount() const {
  return 2;
}