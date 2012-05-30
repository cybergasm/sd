#include "CharacterShader.h"

CharacterShader::CharacterShader(const std::string& location) : Shader(location) {
  exportedVars[0] = Normal;
  exportedVars[1] = Position;
  exportedVars[2] = TextureCoord;
  exportedVars[3] = Ka;
  exportedVars[4] = Kd;
  exportedVars[5] = Ks;
  exportedVars[6] = Shininess;
  exportedVars[7] = Time;
  exportedVars[8] = DiffuseMap;
}

CharacterShader::~CharacterShader() {
}
void CharacterShader::setAttributeColorIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("colorIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setNormal(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeNormalIn(normalized, stride,data);
}

void CharacterShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setPosition(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributePositionIn(normalized, stride, data);
}

void CharacterShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const{
  setAttributeTexCoordIn(normalized, stride, data);
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

void CharacterShader::setUniformKs(float in1, float in2, float in3) const{
  setUniform3f("Ks", in1, in2, in3);
}
void CharacterShader::setKs(float in1, float in2, float in3) const{
  setUniformKs(in1, in2, in3);
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
  return 9;
}