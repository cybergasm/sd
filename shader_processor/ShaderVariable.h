/*
 * ShaderVariable.h
 *
 *  Created on: May 12, 2012
 *      Author: emint
 */

#ifndef SHADERVARIABLE_H_
#define SHADERVARIABLE_H_

#include <string>

using namespace std;

class ShaderVariable {
  public:
    enum ScopeTypes {
      Uniform, Attribute, None
    };

    enum VarTypes {
      Vec4, Vec2, Vec3, Sampler, Float, Int, Unknown
    };

    enum SemanticType {
      Tangent,
      Bitangent,
      Normal,
      Position,
      TextureCoord,
      Time,
      Ka,
      Ks,
      Kd,
      NormalMap,
      HeightMap,
      DiffuseMap,
      SpecularMap,
      NoInfo
    };

    ShaderVariable(string name, ScopeTypes scope, VarTypes type, SemanticType semType);
    ShaderVariable();
    virtual ~ShaderVariable();

    //Returns a string representation of this variable
    string toString() const;

    //getters
    string getName() const;
    ScopeTypes getScope() const;
    VarTypes getType() const;
  private:
    string name;
    ScopeTypes scope;
    VarTypes type;
    SemanticType semType;

    //String conversions
    string getTypeAsString() const;
    string getScopeAsString() const;
    string getSemanticAsString() const;
};

#endif /* SHADERVARIABLE_H_ */
