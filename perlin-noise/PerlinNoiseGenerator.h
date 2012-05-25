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
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <vector>
using namespace std;

class PerlinNoiseGenerator {
  public:
    PerlinNoiseGenerator();
    virtual ~PerlinNoiseGenerator();

    //Generates 'slices' number of Perlin noise textures
    void generateNoise(int slices);

  private:
    //Width and height of the Perlin textures
    int width;
    int height;

    //The textures across the third dimension
    vector<sf::Image*> noiseSeries;

    //Generates a single slice and adds it to the vector of slices
    void generateSlice(int slice, int numSlices);

    //Returns pseudo-random number as per
    //http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
    //Returns [0,-1]
    float getPseudoRandom(int x, int y, int z);

    //Returns interpolation values based on 5th degree polynomial. Implementation
    //taken from http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf
    float interpVal(int t);

    //Performs linear interpolation
    float lerp(float a, float b, float t);

    //Samples point at different octaves and returns sum. Based on
    //http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
    float samplePoint(float x, float y, float slice, int numSlices, int octaves, float persistence);

    //Returns perlin noise at point x,y and slice. Based on mix of implementation from here
    //http://staffwww.itn.liu.se/~stegu/simplexnoise/simplexnoise.pdf and here
    //http://devmag.org.za/2009/04/25/perlin-noise/
    float noise (int x, int y, int slice, int period, float frequency, int numSlices);

    //Returns the amplitude across all octaves we consider
    float getTotAmp(int octaves, float persistence);
};

#endif /* PERLINNOISEGENERATOR_H_ */
