#ifndef __TextureShader__h__
#define __TextureShader__h__
#include "Shader.h"

class TextureShader : public Shader {
  public: 
    TextureShader(const std::string& location);
    ~TextureShader();


    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setDiffuseMap(int in1) const;
    void setUniformTextureImg(int in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[1];
};

#endif
