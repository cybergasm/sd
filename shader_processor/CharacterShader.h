#ifndef __CharacterShader__h__
#define __CharacterShader__h__
#include "Shader.h"

class CharacterShader : public Shader {
  public: 
    CharacterShader(const std::string& location);
    virtual ~CharacterShader();


    void setAttributeColorIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setNormal(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setKa(float in1, float in2, float in3) const;
    void setUniformKa(float in1, float in2, float in3) const;


    void setKd(float in1, float in2, float in3) const;
    void setUniformKd(float in1, float in2, float in3) const;


    void setKs(float in1, float in2, float in3) const;
    void setUniformKs(float in1, float in2, float in3) const;


    void setShininess(float in1) const;
    void setUniformAlpha(float in1) const;


    void setTime(float in1) const;
    void setUniformT(float in1) const;


    void setDiffuseMap(int in1) const;
    void setUniformTextureImg(int in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[9];
};

#endif
