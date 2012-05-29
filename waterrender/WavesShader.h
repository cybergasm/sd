#ifndef __WavesShader__h__
#define __WavesShader__h__
#include "Shader.h"

class WavesShader : public Shader {
  public: 
    WavesShader(const std::string& location);
    virtual ~WavesShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setTime(float in1) const;
    void setUniformT(float in1) const;


    void setUniformPI(float in1) const;


    void setUniformKs(float in1, float in2, float in3) const;


    void setUniformKa(float in1, float in2, float in3) const;


    void setUniformKd(float in1, float in2, float in3) const;


    void setUniformAlpha(float in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[2];
};

#endif
