#include "CharacterShader.h"

CharacterShader::CharacterShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Position;
  exportedVars[1] = Normal;
  exportedVars[2] = TextureCoord;
  exportedVars[3] = DiffuseMap;
  exportedVars[4] = Ks;
  exportedVars[5] = Ka;
  exportedVars[6] = Kd;
  exportedVars[7] = Shininess;
  exportedVars[8] = Time;
}

CharacterShader::~CharacterShader() {
}
void CharacterShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void CharacterShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setNormal(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeNormalIn(normalized, stride,data);
}

void CharacterShader::setAttributeColorIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("colorIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTexCoordIn(normalized, stride, data);
}

void CharacterShader::setUniformTextureImg(int in1) const{
  setUniform1i("textureImg", in1);
}
void CharacterShader::setDiffuseMap(int in1) const{
  setUniformTextureImg(in1);
}

void CharacterShader::setUniformKs(float in1, float in2, float in3) const{
  setUniform3f("Ks", in1, in2, in3);
}
void CharacterShader::setKs(float in1, float in2, float in3) const{
  setUniformKs(in1, in2, in3);
}

void CharacterShader::setUniformKa(float in1, float in2, float in3) const{
  setUniform3f("Ka", in1, in2, in3);
}
void CharacterShader::setKa(float in1, float in2, float in3) const{
  setUniformKa(in1, in2, in3);
}

void CharacterShader::setUniformKd(float in1, float in2, float in3) const{
  setUniform3f("Kd", in1, in2, in3);
}
void CharacterShader::setKd(float in1, float in2, float in3) const{
  setUniformKd(in1, in2, in3);
}

void CharacterShader::setUniformAlpha(float in1) const{
  setUniform1f("alpha", in1);
}
void CharacterShader::setShininess(float in1) const{
  setUniformAlpha(in1);
}

void CharacterShader::setUniformT(float in1) const{
  setUniform1f("t", in1);
}
void CharacterShader::setTime(float in1) const{
  setUniformT(in1);
}

const Shader::KnownVars* CharacterShader::getExpectedVars() const {
  return exportedVars;
}
int CharacterShader::getExpectedVarsCount() const {
  return 9;
}