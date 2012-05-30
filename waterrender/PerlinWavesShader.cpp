#include "PerlinWavesShader.h"

PerlinWavesShader::PerlinWavesShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Normal;
  exportedVars[1] = Position;
  exportedVars[2] = TextureCoord;
  exportedVars[3] = DiffuseMap;
  exportedVars[4] = HeightMap;
}

PerlinWavesShader::~PerlinWavesShader() {
}
void PerlinWavesShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void PerlinWavesShader::setNormal(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeNormalIn(normalized, stride,data);
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

void PerlinWavesShader::setUniformKa(float in1, float in2, float in3) const{
  setUniform3f("Ka", in1, in2, in3);
}
void PerlinWavesShader::setUniformKd(float in1, float in2, float in3) const{
  setUniform3f("Kd", in1, in2, in3);
}
void PerlinWavesShader::setUniformKs(float in1, float in2, float in3) const{
  setUniform3f("Ks", in1, in2, in3);
}
void PerlinWavesShader::setUniformAlpha(float in1) const{
  setUniform1f("alpha", in1);
}
void PerlinWavesShader::setUniformDiffuseMap(int in1) const{
  setUniform1i("diffuseMap", in1);
}
void PerlinWavesShader::setDiffuseMap(int in1) const{
  setUniformDiffuseMap(in1);
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
  return 5;
}