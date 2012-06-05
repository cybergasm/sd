#include "BloomFilterShader.h"

BloomFilterShader::BloomFilterShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = TextureCoord;
}

BloomFilterShader::~BloomFilterShader() {
}
void BloomFilterShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void BloomFilterShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void BloomFilterShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void BloomFilterShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTexCoordIn(normalized, stride, data);
}

void BloomFilterShader::setUniformBloomFactor(float in1) const{
  setUniform1f("bloomFactor", in1);
}
void BloomFilterShader::setUniformLightImg(int in1) const{
  setUniform1i("lightImg", in1);
}
void BloomFilterShader::setUniformTextureImg(int in1) const{
  setUniform1i("textureImg", in1);
}
const Shader::KnownVars* BloomFilterShader::getExpectedVars() const {
  return exportedVars;
}
int BloomFilterShader::getExpectedVarsCount() const {
  return 2;
}