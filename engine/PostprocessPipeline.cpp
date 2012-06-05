/*
 * PostprocessPipeline.cpp
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#include "PostprocessPipeline.h"
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

PostprocessPipeline::PostprocessPipeline() {
  PostprocessUtils::initFBOAndTexture(effectsFBO, initRenderColor,
      initRenderDepth);
  PostprocessUtils::initDepthTexture(effectsDepth);
}

PostprocessPipeline::~PostprocessPipeline() {
}

void PostprocessPipeline::addEffect(PostprocessEffect* effect) {
  effects.push_back(effect);
}

void PostprocessPipeline::captureBuffer() const {
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, effectsFBO));
  PostprocessUtils::bindTexturesToBuffer(initRenderColor,
      initRenderDepth, effectsFBO);
}

void PostprocessPipeline::releaseBuffer() const {
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
}

GLuint PostprocessPipeline::applyEffects() {
  GLuint prev = initRenderColor;
  for (vector<PostprocessEffect*>::iterator iter = effects.begin(); iter
      != effects.end(); ++iter) {
    PostprocessUtils::bindTexturesToBuffer((*iter)->getResultTextureHandle(),
        effectsDepth, effectsFBO);
    (*iter)->processEffect(initRenderColor, initRenderDepth, prev);
    prev = (*iter)->getResultTextureHandle();
  }
  return prev;
}
