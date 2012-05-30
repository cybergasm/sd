#ifndef __ParallaxShader__h__
#define __ParallaxShader__h__
#include "Shader.h"

class ParallaxShader : public Shader {
  public: 
    ParallaxShader(const std::string& location);
    virtual ~ParallaxShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setDiffuseMap(int in1) const;
    void setUniformDiffuseTex(int in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[2];
};

#endif
