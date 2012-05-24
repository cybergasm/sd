/*
 * WaveRenderer.h
 *
 *  Created on: May 23, 2012
 *      Author: emint
 */

#ifndef WAVERENDERER_H_
#define WAVERENDERER_H_

#include "engine/MeshRenderer.h"
#include "WavesShader.h"

class WaveRenderer : public MeshRenderer {
  public:
    WaveRenderer();
    virtual ~WaveRenderer();

    //Renders wave using framerate to update time
    void render(float framerate);

    //Returns the time
    float getTime() const;
  private:
    //WaveShader
    WavesShader* waveShader;

    //current animation time
    float time;


};

#endif /* WAVERENDERER_H_ */
