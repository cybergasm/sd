/*
 * BlurFilterEffect.cpp
 *
 *  Created on: Jun 5, 2012
 *      Author: emint
 */
#include <cstdlib>
#include <iostream>

#include "BlurFilterEffect.h"
#include "PostprocessUtils.h"

using namespace std;

BlurFilterEffect::BlurFilterEffect() :
  shader("shaders/blurfilter") {
  PostprocessUtils::initColorTexture(outputTex);
  if (!shader.loaded()) {
    cerr << shader.errors() << endl;
    exit(-1);
  }
}

BlurFilterEffect::~BlurFilterEffect() {
  // TODO Auto-generated destructor stub
}

GLuint BlurFilterEffect::getResultTextureHandle() const {
  return outputTex;
}

void BlurFilterEffect::processEffect(GLuint initTexture,
    GLuint initDeptTexture, GLuint prevTexture) {
  PostprocessUtils::displayTexture(prevTexture, &shader);
}
