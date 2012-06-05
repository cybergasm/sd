#ifndef __BloomFilterShader__h__
#define __BloomFilterShader__h__
#include "Shader.h"

class BloomFilterShader : public Shader {
  public: 
    BloomFilterShader(const std::string& location);
    virtual ~BloomFilterShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setUniformBloomFactor(float in1) const;


    void setUniformLightImg(int in1) const;


    void setUniformTextureImg(int in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[2];
};

#endif
