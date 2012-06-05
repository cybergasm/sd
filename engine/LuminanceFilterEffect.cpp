/*
 * LuminanceFilterEffect.cpp
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#include <iostream>
#include <cstdlib>
#include <stdio.h>

#include "LuminanceFilterEffect.h"
#include "PostprocessUtils.h"


#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}


using namespace std;
LuminanceFilterEffect::LuminanceFilterEffect() :
  shader("shaders/luminancefilter"), lumThresh(.5f) {
  PostprocessUtils::initColorTexture(outputTex);
  if (!shader.loaded()) {
    cerr << shader.errors() << endl;
    exit(-1);
  }
}

LuminanceFilterEffect::~LuminanceFilterEffect() {
  // TODO Auto-generated destructor stub
}

GLuint LuminanceFilterEffect::getResultTextureHandle() const {
  return outputTex;
}

void LuminanceFilterEffect::processEffect(GLuint initTexture,
    GLuint initDepthTexture, GLuint prevTexture) {
  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader.programID()));

  glActiveTexture(GL_TEXTURE0);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, initTexture));


  shader.setUniformTextureImg(0);
  shader.setUniformIlluminanceThresh(lumThresh);

  PostprocessUtils::setupQuadAndRenderTexture(&shader);

  GL_CHECK(glUseProgram(oldId));
}
