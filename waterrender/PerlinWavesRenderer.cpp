/*
 * PerlinWavesRenderer.cpp
 *
 *  Created on: May 29, 2012
 *      Author: emint
 */

#include "PerlinWavesRenderer.h"

#include <iostream>
using namespace std;

PerlinWavesRenderer::PerlinWavesRenderer() : curFrame(0), timeCntr(0), modifier(1), numFrames(1), shader("shaders/perlinwaves") {
  if (!shader.loaded()) {
    cerr<<shader.errors()<<endl;
    exit(-1);
  }
  cout<<"Generating perlin noise...";
  pNoise = new PerlinNoiseGenerator();
  pNoise->generateNoise(numFrames);
  cout<<"done."<<endl;
}

PerlinWavesRenderer::~PerlinWavesRenderer() {
  // TODO Auto-generated destructor stub
}

void PerlinWavesRenderer::render(float time) {
  timeCntr += time;
  if (timeCntr > .1) {
    timeCntr = 0;
    curFrame += modifier;
    if (curFrame >= numFrames || curFrame < 0) {
      modifier *= -1;
      curFrame += modifier;
    }
  }

  setHeightTex(pNoise->getSlice(curFrame));

  renderMesh((ResourceManager::get())->getMesh("tile-hr"), &shader);
}
