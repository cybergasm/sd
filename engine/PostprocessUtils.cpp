/*
 * PostprocessUtils.cpp
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#include "PostprocessUtils.h"
#include <stdio.h>
#include <iostream>

using namespace std;

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

PostprocessUtils::PostprocessUtils() {
}

PostprocessUtils::~PostprocessUtils() {
}

void PostprocessUtils::initColorTexture(GLuint& texture) {
  GL_CHECK(glGenTextures(1, &texture));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));

  GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK( glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_LINEAR));
  GL_CHECK( glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK( glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK( glGenerateMipmapEXT(GL_TEXTURE_2D));

  GL_CHECK(
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA,
          GL_UNSIGNED_BYTE, 0));
}

void PostprocessUtils::initDepthTexture(GLuint& depthTexture) {
  GL_CHECK(glGenTextures(1, &depthTexture));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthTexture));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 1024 ,
          1024, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0));
}

void PostprocessUtils::bindTexturesToBuffer(GLuint colorTex, GLuint depthTex,
    GLuint fbo) {
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo));

  GL_CHECK(glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, colorTex, 0));
  GL_CHECK(glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTex, 0));

  if (GL_FRAMEBUFFER_COMPLETE
      != glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT)) {
    cout << "FBO fail" << endl;
  }
}

void PostprocessUtils::initFBOAndTexture(GLuint& fbo, GLuint& texture,
    GLuint& depthTexture) {
  initColorTexture(texture);
  initDepthTexture(depthTexture);

  GL_CHECK(glGenFramebuffersEXT(1, &fbo));

  bindTexturesToBuffer(texture, depthTexture, fbo);

  //reset the buffer
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
}
