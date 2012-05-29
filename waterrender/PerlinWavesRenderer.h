/*
 * PerlinWavesRenderer.h
 *
 *  Created on: May 29, 2012
 *      Author: emint
 */

#ifndef PERLINWAVESRENDERER_H_
#define PERLINWAVESRENDERER_H_

#include "engine/MeshRenderer.h"

#include "PerlinWavesShader.h"
#include "perlin-noise/PerlinNoiseGenerator.h"

class PerlinWavesRenderer : public MeshRenderer {
  public:
    PerlinWavesRenderer();
    virtual ~PerlinWavesRenderer();

    void render(float time);

  private:
    //Current frame of waves
    int curFrame;

    //Time counter
    float timeCntr;

    //Keeps track of if we are going forward or backwards
    int modifier;

    //How many frames to generate
    int numFrames;

    //The perlin noise data
    PerlinNoiseGenerator* pNoise;

    //The shader
    PerlinWavesShader shader;
};

#endif /* PERLINWAVESRENDERER_H_ */
