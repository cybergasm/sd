#include "CharacterShader.h"

CharacterShader::CharacterShader(const std::string& location) : Shader(location) {
}

void CharacterShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setAttributeColorIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("colorIn", 3, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void CharacterShader::setUniformTextureImg(int in1){
  setUniform1i("textureImg", in1);
}
void CharacterShader::setUniformKs(float in1, float in2, float in3){
  setUniform3f("Ks", in1, in2, in3);
}
void CharacterShader::setUniformKa(float in1, float in2, float in3){
  setUniform3f("Ka", in1, in2, in3);
}
void CharacterShader::setUniformKd(float in1, float in2, float in3){
  setUniform3f("Kd", in1, in2, in3);
}
void CharacterShader::setUniformAlpha(float in1){
  setUniform1f("alpha", in1);
}
void CharacterShader::setUniformT(float in1){
  setUniform1f("t", in1);
}
