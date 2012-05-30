#ifndef __CharacterShader__h__
#define __CharacterShader__h__
#include "Shader.h"

class CharacterShader : public Shader {
  public: 
    CharacterShader(const std::string& location);
    virtual ~CharacterShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setDiffuseMap(int in1) const;
    void setUniformTextureImg(int in1) const;


    const Shader::KnownVars* getExpectedVars() const;
    int getExpectedVarsCount() const;
  private:
    KnownVars exportedVars[2];
};

#endif
