/*
 * LuminanceFilterEffect.h
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#ifndef LUMINANCEFILTEREFFECT_H_
#define LUMINANCEFILTEREFFECT_H_
#include <GL/glew.h>

#include "PostprocessEffect.h"
#include "LuminanceFilterShader.h"

class LuminanceFilterEffect : public PostprocessEffect{
  public:
    LuminanceFilterEffect();
    virtual ~LuminanceFilterEffect();

    //Return handle to filtered texture
    GLuint getResultTextureHandle() const;

    //Applies filtering to initTexture. prev is not used
    void processEffect(GLuint initTexture, GLuint initDepthTexture,
            GLuint prevTexture);

    //Set/get the threshold
    void setLumThresh(float thresh);
    float getLumThresh() const;

  private:
    GLuint outputTex;

    //The shader for the filter
    LuminanceFilterShader shader;

    //Illuminance filter threshold
    float lumThresh;
};

#endif /* LUMINANCEFILTEREFFECT_H_ */
