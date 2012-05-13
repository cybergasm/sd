/*
 * ShaderVariable.cpp
 *
 *  Created on: May 12, 2012
 *      Author: emint
 */

#include "ShaderVariable.h"

ShaderVariable::ShaderVariable(string name_, ScopeTypes scope_, VarTypes type_) :
  name(name_), scope(scope_), type(type_) {
  // TODO Auto-generated constructor stub

}

ShaderVariable::ShaderVariable() :
  type(Unknown) {

}

ShaderVariable::~ShaderVariable() {
  // TODO Auto-generated destructor stub
}

string ShaderVariable::toString() const {
  return getScopeAsString() + " " + getTypeAsString() + " " + name;
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

string ShaderVariable::getScopeAsString() const{
  if (scope == Uniform) {
    return "uniform";
  } else if (scope == Attribute) {
    return "attribute";
  } else {
    return "unknown";
  }
}

string ShaderVariable::getTypeAsString() const{
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
