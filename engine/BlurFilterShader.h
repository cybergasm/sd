#ifndef __BlurFilterShader__h__
#define __BlurFilterShader__h__
#include "Shader.h"

class BlurFilterShader : public Shader {
  public: 
    BlurFilterShader(const std::string& location);
    virtual ~BlurFilterShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setUniformTextureImg(int in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[2];
};

#endif
