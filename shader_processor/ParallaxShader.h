#ifndef __ParallaxShader__h__
#define __ParallaxShader__h__
#include "Shader.h"

class ParallaxShader : public Shader {
  public: 
    ParallaxShader(const std::string& location);
    ~ParallaxShader();


    void setPosition(bool normalized, GLsizei stride, GLvoid* data);
    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data);


    void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data);
    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data);


    void setNormal(bool normalized, GLsizei stride, GLvoid* data);
    void setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data);


    void setTangent(bool normalized, GLsizei stride, GLvoid* data);
    void setAttributeTangentIn(bool normalized, GLsizei stride, GLvoid* data);


    void setBitangent(bool normalized, GLsizei stride, GLvoid* data);
    void setAttributeBitangentIn(bool normalized, GLsizei stride, GLvoid* data);


    void setDiffuseMap(int in1);
    void setUniformDiffuseTex(int in1);


    void setHeightMap(int in1);
    void setUniformHeightMap(int in1);


    void setNormalMap(int in1);
    void setUniformNormalMap(int in1);


    void setKs(float in1, float in2, float in3);
    void setUniformKs(float in1, float in2, float in3);


    void setKa(float in1, float in2, float in3);
    void setUniformKa(float in1, float in2, float in3);


    void setKd(float in1, float in2, float in3);
    void setUniformKd(float in1, float in2, float in3);


    void setShininess(float in1);
    void setUniformAlpha(float in1);


};

#endif
