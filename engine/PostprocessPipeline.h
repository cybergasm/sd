/*
 * PostprocessPipeline.h
 *
 *  Class which manages a series of effects to be applied linearly.
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#ifndef POSTPROCESSPIPELINE_H_
#define POSTPROCESSPIPELINE_H_

#include <vector>
#include <GL/glew.h>

#include "PostprocessEffect.h"

using namespace std;

class PostprocessPipeline {
  public:
    PostprocessPipeline();
    virtual ~PostprocessPipeline();

    /**
     * Adds effect into the chain
     */
    void addEffect(PostprocessEffect* effect);

    /**
     * Sets up the appropriate buffer to render into
     * to capture upcoming render calls as the image to
     * process
     */
    void captureBuffer() const;

    /**
     * Sets the current draw buffer to the default
     */
    void releaseBuffer() const;

    /**
     * Applies set effects in order
     */
    GLuint applyEffects();
  private:
    //The user specified effects to apply.
    vector<PostprocessEffect*> effects;

    //The texture handles to color and depth buffers of
    //the intial rendering of the scene to postprocess
    GLuint initRenderColor;
    GLuint initRenderDepth;

    //The Framebuffer object to use
    GLuint effectsFBO;

    //A throw-away depth texture to set to the FBO
    //between calls so as not to use the initial render
    //depth texture and intermediate steps shouldn't need
    //a unique depth buffer anyway
    GLuint effectsDepth;

};

#endif /* POSTPROCESSPIPELINE_H_ */
