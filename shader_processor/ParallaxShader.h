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



    void setUniformDiffuseTex(int n1);


    void setUniformHeightMap(int n1);


    void setUniformNormalMap(int n1);


    void setUniformKs(float in1, float in2, float in3);


    void setUniformKa(float in1, float in2, float in3);


    void setUniformKd(float in1, float in2, float in3);


    void setUniformAlpha(float n1);


};

#endif
