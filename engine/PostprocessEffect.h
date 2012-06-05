/*
 * PostprocessEffect.h
 *
 *  Base class for postprocessing effects handeled by the PostprocessPipeline.
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#ifndef POSTPROCESSEFFECT_H_
#define POSTPROCESSEFFECT_H_

#include <GL/glew.h>

class PostprocessEffect {
  public:
    PostprocessEffect();
    virtual ~PostprocessEffect();

    virtual GLuint getResultTextureHandle() const = 0;
    virtual void processEffect(GLuint initTexture, GLuint initDepthTexture,
        GLuint prevTexture) = 0;
};

#endif /* POSTPROCESSEFFECT_H_ */
