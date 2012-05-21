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

void CharacterShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setPosition(bool normalized, GLsizei stride, GLvoid* data){
  setAttributePositionIn(normalized, stride, data);
}

void CharacterShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setNormal(bool normalized, GLsizei stride, GLvoid* data){
  setAttributeNormalIn(normalized, stride,data);
}

void CharacterShader::setAttributeColorIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("colorIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setTextureCoords(bool normalized, GLsizei stride, GLvoid* data){
  setAttributeTexCoordIn(normalized, stride, data);
}

void CharacterShader::setUniformTextureImg(int in1){
  setUniform1i("textureImg", in1);
}
void CharacterShader::setDiffuseMap(int in1){
  setUniformTextureImg(in1);
}

void CharacterShader::setUniformKs(float in1, float in2, float in3){
  setUniform3f("Ks", in1, in2, in3);
}
void CharacterShader::setKs(float in1, float in2, float in3){
  setUniformKs(in1, in2, in3);
}

void CharacterShader::setUniformKa(float in1, float in2, float in3){
  setUniform3f("Ka", in1, in2, in3);
}
void CharacterShader::setKa(float in1, float in2, float in3){
  setUniformKa(in1, in2, in3);
}

void CharacterShader::setUniformKd(float in1, float in2, float in3){
  setUniform3f("Kd", in1, in2, in3);
}
void CharacterShader::setKd(float in1, float in2, float in3){
  setUniformKd(in1, in2, in3);
}

void CharacterShader::setUniformAlpha(float in1){
  setUniform1f("alpha", in1);
}
void CharacterShader::setShininess(float in1){
  setUniformAlpha(in1);
}

void CharacterShader::setUniformT(float in1){
  setUniform1f("t", in1);
}
void CharacterShader::setTime(float in1){
  setUniformT(in1);
}

