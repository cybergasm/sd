/*
 * BlurFilterEffect.h
 *
 *  Gaussian Blur filter
 *  Created on: Jun 5, 2012
 *      Author: emint
 */

#ifndef BLURFILTEREFFECT_H_
#define BLURFILTEREFFECT_H_

#include "PostprocessEffect.h"
#include "BlurFilterShader.h"
class BlurFilterEffect: public PostprocessEffect {
  public:
    BlurFilterEffect();
    virtual ~BlurFilterEffect();

    //Return handle to filtered texture
    GLuint getResultTextureHandle() const;

    //Applies filtering to prev texture. Others not used.
    void processEffect(GLuint initTexture, GLuint initDepthTexture,
        GLuint prevTexture);
  private:
    GLuint outputTex;

    //Shader performing blur
    BlurFilterShader shader;

};

#endif /* BLURFILTEREFFECT_H_ */
