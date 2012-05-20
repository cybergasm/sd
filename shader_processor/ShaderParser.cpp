/*
 * ShaderParser.cpp
 *
 *  Created on: May 12, 2012
 *      Author: emint
 */

#include "ShaderParser.h"

#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace boost;

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
      ShaderVariable::SemanticType lastSemanticType;
      parseLine(sourceLine, lastSemanticType);
    }
  } else {
    cout << "Error opening shader location: " << fileName << endl;
  }
}

void ShaderParser::parseLine(string line,
    ShaderVariable::SemanticType& lastSemanticType) {
  //Gets rid of whitespace around the line to account for strange
  //formatting
  trim(line);

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
          ShaderVariable::Uniform, lastSemanticType);
      cout << var.toString() << endl;
      uniformVars.push_back(var);
      //reset the annotation
      lastSemanticType = ShaderVariable::NoInfo;
      return;
    } else if (typeFound == ShaderVariable::Attribute) {
      ShaderVariable var = parseDeclaration(parser, substring,
          ShaderVariable::Attribute, lastSemanticType);
      cout << var.toString() << endl;
      attrVars.push_back(var);
      //reset the annotation
      lastSemanticType = ShaderVariable::NoInfo;
      return;
    } else {
      //if this is a variable declaration than the first
      //keyword will be scope
      if (substring == "attribute") {
        typeFound = ShaderVariable::Attribute;
      } else if (substring == "uniform") {
        typeFound = ShaderVariable::Uniform;
      } else {
        //if it is neither then this is not a declaration, so we
        //check if it is an annotation. Note that actually this whole
        //loop is fairly order dependent. Since we assume that annotations
        //occur the line right before the variable they relate to, this
        //sets the loop-global semantic type variable which then holds for
        //the next line which could be a variable. If the next line is not
        //a variable then it will also execute this code resetting the
        //type to none.
        lastSemanticType = parseAnnotation(line);
        return;
      }
    }
  }
}

ShaderVariable::SemanticType ShaderParser::parseAnnotation(string line) {
  if (line.length() < 4) {
    return ShaderVariable::NoInfo;
  }

  string begin = line.substr(0, 3);

  if (begin != "//@") {
    return ShaderVariable::NoInfo;
  }

  string attribute = line.substr(3);

  if (attribute == "Tangent") {
    return ShaderVariable::Tangent;
  } else if (attribute == "Bitangent") {
    return ShaderVariable::Bitangent;
  } else if (attribute == "Normal") {
    return ShaderVariable::Normal;
  } else if (attribute == "Position") {
    return ShaderVariable::Position;
  } else if (attribute == "TextureCoordinates") {
    return ShaderVariable::TextureCoord;
  } else if (attribute == "Time") {
    return ShaderVariable::Time;
  } else if (attribute == "Ka") {
    return ShaderVariable::Ka;
  } else if (attribute == "Ks") {
    return ShaderVariable::Ks;
  } else if (attribute == "Kd") {
    return ShaderVariable::Kd;
  } else if (attribute == "Shininess") {
    return ShaderVariable::Shininess;
  } else if (attribute == "NormalMap") {
    return ShaderVariable::NormalMap;
  } else if (attribute == "HeightMap") {
    return ShaderVariable::HeightMap;
  } else if (attribute == "DiffuseMap") {
    return ShaderVariable::DiffuseMap;
  } else if (attribute == "SpecularMap") {
    return ShaderVariable::SpecularMap;
  } else {
    cerr << "Semantic Type: " << attribute << " of " << line << " unknown."
        << endl;
    return ShaderVariable::NoInfo;
  }
}

ShaderVariable ShaderParser::parseDeclaration(istringstream& parser,
    string type, ShaderVariable::ScopeTypes scope,
    ShaderVariable::SemanticType semType) {
  //we have found out whether or not is uniform or attribute
  //so now we need the variable type (e.g. int, vector, etc...)
  string name;

  if (!(parser >> name)) {
    //could not parse name
    return ShaderVariable();
  }
  name = sanitizeName(name);

  ShaderVariable::VarTypes varType = getType(type);

  return ShaderVariable(name, scope, varType, semType);
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
  } else if (type == "vec4") {
    return ShaderVariable::Vec4;
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
