#include "ParallaxShader.h"

ParallaxShader::ParallaxShader(const std::string& location) : Shader(location) {
}

void ParallaxShader::setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("positionIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("texCoordIn", 2, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("normalIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setAttributeTangentIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("tangentIn", 3, GL_FLOAT, normalized, stride, data);
}
void ParallaxShader::setAttributeBitangentIn(bool normalized, GLsizei stride, GLvoid* data) {
  setVertexAttribArray("bitangentIn", 3, GL_FLOAT, normalized, stride, data);
}
