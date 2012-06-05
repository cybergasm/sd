/*
 * PostprocessUtils.h
 *
 *  Utility class of methods for allocating buffers and setting up
 *  rendering targets
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#ifndef POSTPROCESSUTILS_H_
#define POSTPROCESSUTILS_H_
#include <GL/glew.h>

class PostprocessUtils {
  public:
    PostprocessUtils();
    virtual ~PostprocessUtils();

    /**
     * Initializes a texture to be bound to the color attachment of a framebuffer
     */
    static void initColorTexture(GLuint& texture);

    /**
     * Initializes a texture to be bound to the depth attachment of a framebuffer
     */
    static void initDepthTexture(GLuint& depthTexture);

    /**
     * Binds color and depth textures to buffer which is bound to the frame buffer
     */
    static void bindTexturesToBuffer(GLuint colorTex, GLuint depthTex, GLuint fbo);

    /**
     * Initialization routine for setting up a texture, mipmapping it and then
     * allocating a FBO and binding the texture to it. This leaves the buffer as
     * it was when entered, just allocating the buffer and texture and wiring it
     * all up.
     */
    static void initFBOAndTexture(GLuint& fbo, GLuint& texture, GLuint& depthTexture);


};

#endif /* POSTPROCESSUTILS_H_ */
