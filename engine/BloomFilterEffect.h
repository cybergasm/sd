/*
 * BloomFilterEffect.h
 *
 *  Created on: Jun 5, 2012
 *      Author: emint
 */

#ifndef BLOOMFILTEREFFECT_H_
#define BLOOMFILTEREFFECT_H_

#include "BloomFilterShader.h"
#include "PostprocessEffect.h"

class BloomFilterEffect: public PostprocessEffect {
  public:
    BloomFilterEffect();
    virtual ~BloomFilterEffect();

    //Return handle to filtered texture
    GLuint getResultTextureHandle() const;

    //Applies filtering to prev texture and init texture
    void processEffect(GLuint initTexture, GLuint initDepthTexture,
        GLuint prevTexture);
  private:
    GLuint outputTex;

    //Shader that applies bloom
    BloomFilterShader shader;
};

#endif /* BLOOMFILTEREFFECT_H_ */
