/*
 * main.cpp
 *
 *  Created on: May 12, 2012
 *      Author: emint
 */

#include <iostream>
#include "ShaderParser.h"
#include "ShaderClassGenerator.h"

using namespace std;

int main() {
  cout << "Hello world." << endl;
  ShaderParser parser("shaders/parallax");
  ShaderClassGenerator generator;
  generator.generateClass("ParallaxShader", &parser);
  return 1;
}
