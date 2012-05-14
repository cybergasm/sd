/*
 * main.cpp
 *
 *  Created on: May 12, 2012
 *      Author: emint
 */

#include <iostream>
#include <cstdlib>
#include "ShaderParser.h"
#include "ShaderClassGenerator.h"

using namespace std;

int main(int argc, char* argv[]) {

  if (argc < 3) {
    cout<<"Please input the location and desired class name of a shader."<<endl;
    exit(1);
  }

  string location (argv[1]);
  string name(argv[2]);
  ShaderParser parser(location);
  ShaderClassGenerator generator;
  generator.generateClass(name, &parser);
  return 0;
}
