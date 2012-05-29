#include "ParallaxShader.h"

ParallaxShader::ParallaxShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = TextureCoord;
  exportedVars[2] = Normal;
  exportedVars[3] = Tangent;
  exportedVars[4] = Bitangent;
  exportedVars[5] = DiffuseMap;
  exportedVars[6] = HeightMap;
  exportedVars[7] = NormalMap;
}

ParallaxShader::~ParallaxShader() {
}
void ParallaxShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void ParallaxShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTexCoordIn(normalized, stride, data);
}

void ParallaxShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setNormal(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeNormalIn(normalized, stride,data);
}

void ParallaxShader::setAttributeTangentIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("tangentIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setTangent(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTangentIn(normalized, stride, data);
}

void ParallaxShader::setAttributeBitangentIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("bitangentIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setBitangent(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeBitangentIn(normalized, stride, data);
}

void ParallaxShader::setUniformDiffuseTex(int in1) const{
  setUniform1i("diffuseTex", in1);
}
void ParallaxShader::setDiffuseMap(int in1) const{
  setUniformDiffuseTex(in1);
}

void ParallaxShader::setUniformHeightMap(int in1) const{
  setUniform1i("heightMap", in1);
}
void ParallaxShader::setHeightMap(int in1) const{
  setUniformHeightMap(in1);
}

void ParallaxShader::setUniformNormalMap(int in1) const{
  setUniform1i("normalMap", in1);
}
void ParallaxShader::setNormalMap(int in1) const{
  setUniformNormalMap(in1);
}

void ParallaxShader::setUniformKs(float in1, float in2, float in3) const{
  setUniform3f("Ks", in1, in2, in3);
}
void ParallaxShader::setUniformKa(float in1, float in2, float in3) const{
  setUniform3f("Ka", in1, in2, in3);
}
void ParallaxShader::setUniformKd(float in1, float in2, float in3) const{
  setUniform3f("Kd", in1, in2, in3);
}
void ParallaxShader::setUniformAlpha(float in1) const{
  setUniform1f("alpha", in1);
}
const Shader::KnownVars* ParallaxShader::getExpectedVars() const {
  return exportedVars;
}
int ParallaxShader::getExpectedVarsCount() const {
  return 8;
}