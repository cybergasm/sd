/*
 * ShaderParser.cpp
 *
 *  Created on: May 12, 2012
 *      Author: emint
 */

#include "ShaderParser.h"

#include <fstream>
#include <iostream>

ShaderParser::ShaderParser(string location) {
  string vertShader = location + ".vert.glsl";
  string fragShader = location + ".frag.glsl";
  parseFile(vertShader);
  parseFile(fragShader);
}

ShaderParser::~ShaderParser() {
  // TODO Auto-generated destructor stub
}

void ShaderParser::parseFile(string fileName) {
  cout << "Parsing: " << fileName << endl;
  ifstream shaderFile(fileName.c_str(), ios::in);
  string sourceLine;

  if (shaderFile.is_open()) {
    while (shaderFile.good()) {
      getline(shaderFile, sourceLine);
      parseLine(sourceLine);
    }
  } else {
    cout << "Error opening shader location: " << fileName << endl;
  }
}

void ShaderParser::parseLine(string line) {
  //Take the line and split on white spaces, looking
  //for a declaration keyword
  istringstream parser(line);
  string substring;

  ShaderVariable::ScopeTypes typeFound = ShaderVariable::None;
  string name = "";
  while (parser >> substring) {
    if (typeFound == ShaderVariable::Uniform) {
      //this time around the type is the substring if this is a valid declaration, so
      //instead of undoing the stream we pass in this token (substring) as the type
      ShaderVariable var = parseDeclaration(parser, substring,
          ShaderVariable::Uniform);
      cout << var.toString() << endl;
      uniformVars.push_back(var);
      return;
    } else if (typeFound == ShaderVariable::Attribute) {
      ShaderVariable var = parseDeclaration(parser, substring,
          ShaderVariable::Attribute);
      cout << var.toString() << endl;
      attrVars.push_back(var);
      return;
    } else {
      //if this is a variable declaration than the first
      //keyword will be scope
      if (substring == "attribute") {
        typeFound = ShaderVariable::Attribute;
      } else if (substring == "uniform") {
        typeFound = ShaderVariable::Uniform;
      } else {
        //if it is neither then this is not a declaration
        return;
      }
    }
  }
}

ShaderVariable ShaderParser::parseDeclaration(istringstream& parser,
    string type, ShaderVariable::ScopeTypes scope) {
  //we have found out whether or not is uniform or attribute
  //so now we need the variable type (e.g. int, vector, etc...)
  string name;

  if (!(parser >> name)) {
    //could not parse name
    return ShaderVariable();
  }
  name = sanitizeName(name);

  ShaderVariable::VarTypes varType = getType(type);

  return ShaderVariable(name, scope, varType);
}

string ShaderParser::sanitizeName(string name) {
  if (name.at(name.length() - 1) == ';') {
    return name.substr(0, name.length() - 1);
  }
  return name;
}

ShaderVariable::VarTypes ShaderParser::getType(string type) {
  if (type == "vec2") {
    return ShaderVariable::Vec2;
  } else if (type == "vec3") {
    return ShaderVariable::Vec3;
  } else if (type == "sampler") {
    return ShaderVariable::Sampler;
  } else if (type == "float") {
    return ShaderVariable::Float;
  } else if (type == "int") {
    return ShaderVariable::Int;
  } else {
    return ShaderVariable::Unknown;
  }
}

const vector<ShaderVariable>& ShaderParser::getUniformVars() const {
  return uniformVars;
}

const vector<ShaderVariable>& ShaderParser::getAttrVars() const {
  return attrVars;
}
