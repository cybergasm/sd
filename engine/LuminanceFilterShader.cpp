#include "LuminanceFilterShader.h"

LuminanceFilterShader::LuminanceFilterShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = TextureCoord;
}

LuminanceFilterShader::~LuminanceFilterShader() {
}
void LuminanceFilterShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void LuminanceFilterShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void LuminanceFilterShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void LuminanceFilterShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTexCoordIn(normalized, stride, data);
}

void LuminanceFilterShader::setUniformIlluminanceThresh(float in1) const{
  setUniform1f("illuminanceThresh", in1);
}
void LuminanceFilterShader::setUniformTextureImg(int in1) const{
  setUniform1i("textureImg", in1);
}
const Shader::KnownVars* LuminanceFilterShader::getExpectedVars() const {
  return exportedVars;
}
int LuminanceFilterShader::getExpectedVarsCount() const {
  return 2;
}