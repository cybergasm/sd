/*
 * PerlinNoiseGenerator.h
 *
 * Generates 1024x1024 Perlin noise
 *
 *  Created on: May 24, 2012
 *      Author: emint
 */

#ifndef PERLINNOISEGENERATOR_H_
#define PERLINNOISEGENERATOR_H_

// SFML automatically includes SDL headers
#include "engine/Texture.h"

#include <vector>
using namespace std;

class PerlinNoiseGenerator {
  public:
    PerlinNoiseGenerator();
    virtual ~PerlinNoiseGenerator();

    //Generates 'slices' number of Perlin noise textures
    void generateNoise(int slices);

    //Returns slice
    Texture* getSlice(int slice) const;
  private:
    //Width and height of the Perlin textures
    int width;
    int height;

    //Random seed to differentiate runs
    int seed;
    //The textures across the third dimension
    vector<Texture*> noiseSeries;

    //Generates a single slice and adds it to the vector of slices
    void generateSlice(int slice, int numSlices);

    //Returns pseudo-random number as per
    //http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
    //Returns [0,-1]
    float getPseudoRandom(int x, int y, int z) const;

    //Returns interpolation values based on 5th degree polynomial. Implementation
    //taken from http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
    float interpVal(int t) const;

    //Performs linear interpolation
    float lerp(float a, float b, float t) const;

    //Samples point at different octaves and returns sum. Based on
    //http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
    float samplePoint(float x, float y, float slice, int numSlices, int octaves, float persistence) const;

    //Returns perlin noise at point x,y and slice. Based on mix of implementation from here
    //http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf and here
    //http://devmag.org.za/2009/04/25/perlin-noise/
    float noise (int x, int y, int slice, int period, float frequency, int numSlices) const;

    //Returns the amplitude across all octaves we consider
    float getTotAmp(int octaves, float persistence) const;
};

#endif /* PERLINNOISEGENERATOR_H_ */
