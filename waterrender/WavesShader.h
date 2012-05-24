#ifndef __WavesShader__h__
#define __WavesShader__h__
#include "Shader.h"

class WavesShader : public Shader {
  public: 
    WavesShader(const std::string& location);
    ~WavesShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[1];
};

#endif
