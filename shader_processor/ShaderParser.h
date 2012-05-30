/*
 * ShaderParser.h
 *
 *  Created on: May 12, 2012
 *      Author: emint
 */

#ifndef SHADERPARSER_H_
#define SHADERPARSER_H_

#include <string>
#include <sstream>
#include <set>

#include "ShaderVariable.h"

using namespace std;

class ShaderParser {
  public:
    ShaderParser(string location);
    virtual ~ShaderParser();

    //getters for found variables
    const set<ShaderVariable>& getUniformVars() const;
    const set<ShaderVariable>& getAttrVars() const;
  private:
    //Given a fragment or vertex shader, this parses it looking
    //for uniform or attribute files
    void parseFile(string fileName);

    //Given a specific line this sees if it is a variable declaration or
    //possibly an annotation. If it is an annotation it stores it into the
    //lastType seen. The lastType is expected to be passed in as the annotation
    //defined by the line before the one being parsed (if no attribute then
    //NoInfo should be passed). If line is not attribute, NoInfo is set. If
    //a variable is found it is given the semantic type of the type passed in.
    void parseLine(string line, ShaderVariable::SemanticType& lastType);

    //Once a variable declaration has been found, parse it into an object
    ShaderVariable parseDeclaration(istringstream& parseStream, string type,
        ShaderVariable::ScopeTypes scope, ShaderVariable::SemanticType semType);

    //Tries to parse line as an annotation
    ShaderVariable::SemanticType parseAnnotation(string line);

    //Removes trailing ';' from name if it exists
    string sanitizeName(string name);

    //Returns the type given parsed type
    ShaderVariable::VarTypes getType(string type);

    //Stores the found variables
    set<ShaderVariable> uniformVars;
    set<ShaderVariable> attrVars;
};

#endif /* SHADERPARSER_H_ */
