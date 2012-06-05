/*
 * LuminanceFilterEffect.cpp
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#include "LuminanceFilterEffect.h"
#include "PostprocessUtils.h"
#include <iostream>
#include <cstdlib>
using namespace std;
LuminanceFilterEffect::LuminanceFilterEffect() : shader("shaders/luminancefilter"){
  PostprocessUtils::initColorTexture(outputTex);
  if (!shader.loaded()) {
    cerr<<shader.errors()<<endl;
    exit(-1);
  }
}

LuminanceFilterEffect::~LuminanceFilterEffect() {
  // TODO Auto-generated destructor stub
}

GLuint LuminanceFilterEffect::getResultTextureHandle() const {
  return outputTex;
}

void LuminanceFilterEffect::processEffect(GLuint initTexture, GLuint initDepthTexture, GLuint prevTexture) {
  PostprocessUtils::displayTexture(initTexture, &shader);
}
