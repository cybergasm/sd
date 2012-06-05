#ifndef __LuminanceFilterShader__h__
#define __LuminanceFilterShader__h__
#include "Shader.h"

class LuminanceFilterShader : public Shader {
  public: 
    LuminanceFilterShader(const std::string& location);
    virtual ~LuminanceFilterShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setUniformIlluminanceThresh(float in1) const;


    void setUniformTextureImg(int in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[2];
};

#endif
