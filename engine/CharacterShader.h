#ifndef __CharacterShader__h__
#define __CharacterShader__h__
#include "Shader.h"

class CharacterShader : public Shader {
  public: 
    CharacterShader(const std::string& location);
    ~CharacterShader();


    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setAttributeColorIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data) const;


    void setUniformTextureImg(int in1) const;


    void setUniformKs(float in1, float in2, float in3) const;


    void setUniformKa(float in1, float in2, float in3) const;


    void setUniformKd(float in1, float in2, float in3) const;


    void setUniformAlpha(float in1) const;


    void setUniformT(float in1) const;


};

#endif
