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

#include "Shader.h"

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

    /*
     * Method for actually rendering the vertices and texture coords of a full
     * screen textured quad. Assumes the appropriate textures have been set
     * on shader and shader has been called as active program.
     */
    static void setupQuadAndRenderTexture(Shader* shader);

    /*
     * Given texture and shader passes in texture as textureImg
     */
    static void displayTexture(GLuint texture, Shader* shader);
};

#endif /* POSTPROCESSUTILS_H_ */
