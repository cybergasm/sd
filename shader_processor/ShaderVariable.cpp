/*
 * ShaderVariable.cpp
 *
 *  Created on: May 12, 2012
 *      Author: emint
 */

#include "ShaderVariable.h"

ShaderVariable::ShaderVariable(string name_, ScopeTypes scope_, VarTypes type_,
    SemanticType semType_) :
  name(name_), scope(scope_), type(type_), semType(semType_) {
  // TODO Auto-generated constructor stub

}

ShaderVariable::ShaderVariable() :
  type(Unknown) {

}

ShaderVariable::~ShaderVariable() {
  // TODO Auto-generated destructor stub
}

string ShaderVariable::toString() const {
  return getScopeAsString() + " " + getTypeAsString() + " "
      + getSemanticAsString() + " " + name;
}

string ShaderVariable::getName() const {
  return name;
}

ShaderVariable::ScopeTypes ShaderVariable::getScope() const {
  return scope;
}

ShaderVariable::VarTypes ShaderVariable::getType() const {
  return type;
}

string ShaderVariable::getScopeAsString() const {
  if (scope == Uniform) {
    return "uniform";
  } else if (scope == Attribute) {
    return "attribute";
  } else {
    return "unknown";
  }
}

string ShaderVariable::getTypeAsString() const {
  if (type == Vec2) {
    return "vec2";
  } else if (type == Vec3) {
    return "vec3";
  } else if (type == Sampler) {
    return "sampler";
  } else if (type == Float) {
    return "float";
  } else if (type == Int) {
    return "int";
  } else {
    return "unknown";
  }
}

string ShaderVariable::getSemanticAsString() const {
  if (semType == Tangent) {
    return "Tangent";
  } else if (semType == Bitangent) {
    return "Bitangent";
  } else if (semType == Normal) {
    return "Normal";
  } else if (semType == Position) {
    return "Normal";
  } else if (semType == TextureCoord) {
    return "TextureCoords";
  } else if (semType == Time) {
    return "Time";
  } else if (semType == Ka) {
    return "Ka";
  } else if (semType == Ks) {
    return "Ks";
  } else if (semType == Kd) {
    return "Kd";
  } else if (semType == NormalMap) {
    return "NormalMap";
  } else if (semType == HeightMap) {
    return "HeightMap";
  } else if (semType == DiffuseMap) {
    return "DiffuseMap";
  } else if (semType == SpecularMap) {
    return "SpecularMap";
  } else {
    return "No semantic info.";
  }
}
