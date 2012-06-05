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

    //Sets/Gets bloom factor
    void setBloomFactor(float bloomF);
    float getBloomFactor() const;
  private:
    GLuint outputTex;

    //Shader that applies bloom
    BloomFilterShader shader;

    //Level of bloom to preserve
    float bloomFactor;
};

#endif /* BLOOMFILTEREFFECT_H_ */
