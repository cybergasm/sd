#ifndef __ParallaxShader__h__
#define __ParallaxShader__h__
#include "Shader.h"

class ParallaxShader : Shader {
  public: 
    ParallaxShader(const std::string& location);
    ~ParallaxShader();


    void setAttributePositionIn(bool normalized, GLsizei stride, GLvoid* data);


    void setAttributeTexCoordIn(bool normalized, GLsizei stride, GLvoid* data);


    void setAttributeNormalIn(bool normalized, GLsizei stride, GLvoid* data);


    void setAttributeTangentIn(bool normalized, GLsizei stride, GLvoid* data);


    void setAttributeBitangentIn(bool normalized, GLsizei stride, GLvoid* data);


    void setUniformDiffuseTex(int in1);


    void setUniformHeightMap(int in1);


    void setUniformNormalMap(int in1);


    void setUniformKs(float in1, float in2, float in3);


    void setUniformKa(float in1, float in2, float in3);


    void setUniformKd(float in1, float in2, float in3);


    void setUniformAlpha(float in1);


};

#endif
