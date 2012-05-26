/*
 * PerlinNoiseGenerator.cpp
 *
 *  Created on: May 24, 2012
 *      Author: emint
 */

#include "PerlinNoiseGenerator.h"

#include <iostream>
#include <sstream>

PerlinNoiseGenerator::PerlinNoiseGenerator() :
  width(256), height(256) {
}

PerlinNoiseGenerator::~PerlinNoiseGenerator() {
}

void PerlinNoiseGenerator::generateNoise(int slices) {
  for (int i = 0; i < slices; i++) {
    generateSlice(i, slices);
  }
}

void PerlinNoiseGenerator::generateSlice(int slice, int numSlices) {
  float vals[width][height];
  int oCount = 5;
  float persistence = .6;
  float totAmp = getTotAmp(oCount, persistence);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      float sample = samplePoint(x, y, slice, numSlices, oCount, persistence);
      vals[x][y] = sample;
    }
  }
  //Normalize so all are between 0,1
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      vals[x][y] /= totAmp;
    }
  }
  //Save this in the time series
  sf::Image* img = new sf::Image(width, height);
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      img->SetPixel(
          x,
          y,
          sf::Color(vals[x][y] * 255.0f, vals[x][y] * 255.0f,
              vals[x][y] * 255.0f));
    }
  }

  noiseSeries.push_back(img);
}

float PerlinNoiseGenerator::getTotAmp(int octaves, float persistence) const {
  float tot = 0;
  for (int octave = octaves; octave >= 0; octave--) {
    tot += pow(persistence, octave);
  }
  return tot;
}

float PerlinNoiseGenerator::samplePoint(float x, float y, float slice,
    int numSlices, int octaveCnt, float persistence) const {
  float total = 0;
  //this avoids us having to keep an intermediate smooth noise array
  for (int octave = octaveCnt; octave >= 0; octave--) {
    int period = pow(2, octave);
    float freq = 1.0f / period;
    //we take the power going in the opposite direction
    float amplitude = pow(persistence, octaveCnt - octave);
    float n = noise(x, y, slice, period, freq, numSlices);
    total += n * amplitude;
  }
  return total;
}

float PerlinNoiseGenerator::noise(int x, int y, int slice, int period,
    float frequency, int numSlices) const {
  //Division to truncate. We are looking for the points
  //around x,y,slice
  int x0 = (x / period) * period;
  int x1 = (x0 + (int) period) % width;

  int y0 = (y / period) * period;
  int y1 = (y0 + (int) period) % height;

  int slice0 = (slice / period) * period;
  int slice1 = (slice0 + (int) period) % numSlices;

  //interpolation factors
  float u = (x - x0) * frequency;
  float v = (y - y0) * frequency;
  float w = (slice - slice0) * frequency;

  //We interpolate across the x-axis
  float top0 = lerp(getPseudoRandom(x0, y0, slice0),
      getPseudoRandom(x1, y0, slice0), u);
  float bot0 = lerp(getPseudoRandom(x0, y1, slice0),
      getPseudoRandom(x1, y1, slice0), u);
  float top1 = lerp(getPseudoRandom(x0, y0, slice1),
      getPseudoRandom(x1, y0, slice1), u);
  float bot1 = lerp(getPseudoRandom(x0, y1, slice1),
      getPseudoRandom(x1, y1, slice1), u);
  //y-axis
  float mid0 = lerp(top0, bot0, v);
  float mid1 = lerp(top1, bot1, v);
  //z-axis
  return lerp(mid0, mid1, w);
}

float PerlinNoiseGenerator::lerp(float a, float b, float t) const{
  return (1 - t) * a + t * b;
}

float PerlinNoiseGenerator::interpVal(int t) const {
  return t * t * t * (t * (t * 6 - 15) + 10);
}

float PerlinNoiseGenerator::getPseudoRandom(int x, int y, int z) const {
  int num = x + y * 57 + z * 809;
  num = (num << 13) ^ num;
  float multiplier = (1.0f - ((num * (num * num * 15731 + 789221) + 1376312589)
      & 0x7fffffff) / 1073741824.0);
  //move out of negative range
  multiplier += 1.0f;
  multiplier /= 2.0f;
  return multiplier;
}

sf::Image* PerlinNoiseGenerator::getSlice(int slice) const {
  return noiseSeries.at(slice);
}
