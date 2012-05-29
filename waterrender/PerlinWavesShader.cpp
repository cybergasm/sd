#include "PerlinWavesShader.h"

PerlinWavesShader::PerlinWavesShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = TextureCoord;
  exportedVars[2] = Normal;
  exportedVars[3] = HeightMap;
}

PerlinWavesShader::~PerlinWavesShader() {
}
void PerlinWavesShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void PerlinWavesShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void PerlinWavesShader::setAttributeTexCoordsIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordsIn", 2, GL_FLOAT, normalized, stride, data);
}
void PerlinWavesShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTexCoordsIn(normalized, stride, data);
}

void PerlinWavesShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void PerlinWavesShader::setNormal(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeNormalIn(normalized, stride,data);
}

void PerlinWavesShader::setUniformHeightMap(int in1) const{
  setUniform1i("heightMap", in1);
}
void PerlinWavesShader::setHeightMap(int in1) const{
  setUniformHeightMap(in1);
}

const Shader::KnownVars* PerlinWavesShader::getExpectedVars() const {
  return exportedVars;
}
int PerlinWavesShader::getExpectedVarsCount() const {
  return 4;
}