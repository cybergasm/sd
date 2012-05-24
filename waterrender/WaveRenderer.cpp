/*
 * WaveRenderer.cpp
 *
 *  Created on: May 23, 2012
 *      Author: emint
 */

#include "WaveRenderer.h"
#include <iostream>
using namespace std;

WaveRenderer::WaveRenderer() : time(0.0f) {
  waveShader = new WavesShader("shaders/waves");

  if (!waveShader->loaded()) {
    cerr << waveShader->errors() << endl;
    exit(-1);
  }
}

WaveRenderer::~WaveRenderer() {
  // TODO Auto-generated destructor stub
}

void WaveRenderer::render(float framerate) {
  time += framerate * 6.0f;

  renderMesh((ResourceManager::get())->getMesh("tile-hr"), waveShader);
}

float WaveRenderer::getTime() const {
  return time;
}
