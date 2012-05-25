/*
 * main.cpp
 *
 *  Created on: May 24, 2012
 *      Author: emint
 */
#include <iostream>

#include "engine/MeshRenderer.h"
#include "engine/InputProcessor.h"
#include "engine/RenderingWindow.h"

#include "PerlinNoiseGenerator.h"

using namespace std;

int main() {
  PerlinNoiseGenerator gen;
  gen.generateNoise(2);
}
