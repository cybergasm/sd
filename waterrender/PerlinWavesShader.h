#ifndef __PerlinWavesShader__h__
#define __PerlinWavesShader__h__
#include "Shader.h"

class PerlinWavesShader : public Shader {
  public: 
    PerlinWavesShader(const std::string& location);
    virtual ~PerlinWavesShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeTexCoordsIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setNormal(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setHeightMap(int in1) const;
    void setUniformHeightMap(int in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[4];
};

#endif
