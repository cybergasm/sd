#ifndef __CharacterShader__h__
#define __CharacterShader__h__
#include "Shader.h"

class CharacterShader : public Shader {
  public: 
    CharacterShader(const std::string& location);
    ~CharacterShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data);
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data);


    void setNormal(bool normalized, GLsizei stride, GLvoid* data);
    void setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data);


    void setAttributeColorIn(bool normalized, GLsizei stride, GLvoid* data);


    void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data);
    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data);


    void setDiffuseMap(int in1);
    void setUniformTextureImg(int in1);


    void setKs(float in1, float in2, float in3);
    void setUniformKs(float in1, float in2, float in3);


    void setKa(float in1, float in2, float in3);
    void setUniformKa(float in1, float in2, float in3);


    void setKd(float in1, float in2, float in3);
    void setUniformKd(float in1, float in2, float in3);


    void setShininess(float in1);
    void setUniformAlpha(float in1);


    void setTime(float in1);
    void setUniformT(float in1);


  private:
    KnownVars exportedVars[9];
};

#endif
