#ifndef __ParallaxShader__h__
#define __ParallaxShader__h__
#include "Shader.h"

class ParallaxShader : public Shader {
  public: 
    ParallaxShader(const std::string& location);
    ~ParallaxShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setNormal(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setTangent(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeTangentIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setBitangent(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeBitangentIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setDiffuseMap(int in1) const;
    void setUniformDiffuseTex(int in1) const;


    void setHeightMap(int in1) const;
    void setUniformHeightMap(int in1) const;


    void setNormalMap(int in1) const;
    void setUniformNormalMap(int in1) const;


    void setKs(float in1, float in2, float in3) const;
    void setUniformKs(float in1, float in2, float in3) const;


    void setKa(float in1, float in2, float in3) const;
    void setUniformKa(float in1, float in2, float in3) const;


    void setKd(float in1, float in2, float in3) const;
    void setUniformKd(float in1, float in2, float in3) const;


    void setShininess(float in1) const;
    void setUniformAlpha(float in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[12];
};

#endif
