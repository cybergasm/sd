#ifndef __CharacterShader__h__
#define __CharacterShader__h__
#include "Shader.h"

class CharacterShader : public Shader {
  public: 
    CharacterShader(const std::string& location);
    ~CharacterShader();


    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data);


    void setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data);


    void setAttributeColorIn(bool normalized, GLsizei stride, GLvoid* data);


    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data);


    void setUniformTextureImg(int in1);


    void setUniformKs(float in1, float in2, float in3);


    void setUniformKa(float in1, float in2, float in3);


    void setUniformKd(float in1, float in2, float in3);


    void setUniformAlpha(float in1);


    void setUniformT(float in1);


};

#endif
