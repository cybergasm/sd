/*
 * BloomFilterEffect.cpp
 *
 *  Created on: Jun 5, 2012
 *      Author: emint
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>

#include "BloomFilterEffect.h"
#include "PostprocessEffect.h"
#include "PostprocessUtils.h"


#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

using namespace std;
BloomFilterEffect::BloomFilterEffect() :
  shader("shaders/bloomfilter"), bloomFactor(.8f) {

  PostprocessUtils::initColorTexture(outputTex);
  if (!shader.loaded()) {
    cerr << shader.errors() << endl;
    exit(-1);
  }
}

BloomFilterEffect::~BloomFilterEffect() {
  // TODO Auto-generated destructor stub
}

GLuint BloomFilterEffect::getResultTextureHandle() const {
  return outputTex;
}

void BloomFilterEffect::setBloomFactor(float bloomF) {
  bloomFactor = bloomF;
}

void BloomFilterEffect::processEffect(GLuint initTexture,
    GLuint initDepthTexture, GLuint prevTexture) {
  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader.programID()));

  glActiveTexture(GL_TEXTURE0);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, initTexture));

  glActiveTexture(GL_TEXTURE1);
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, prevTexture));

  shader.setUniformTextureImg(0);
  shader.setUniformLightImg(1);
  shader.setUniformBloomFactor(bloomFactor);
  PostprocessUtils::setupQuadAndRenderTexture(&shader);

  GL_CHECK(glUseProgram(oldId));
}
