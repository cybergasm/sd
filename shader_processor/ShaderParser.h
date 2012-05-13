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
#include <vector>

#include "ShaderVariable.h"

using namespace std;

class ShaderParser {
  public:
    ShaderParser(string location);
    virtual ~ShaderParser();

    //getters for found variables
    const vector<ShaderVariable>& getUniformVars() const;
    const vector<ShaderVariable>& getAttrVars() const;
  private:
    //Given a fragment or vertex shader, this parses it looking
    //for uniform or attribute files
    void parseFile(string fileName);

    //Given a specific line this sees if it is a variable declaration
    void parseLine(string line);

    //Once a variable declaration has been found, parse it into an object
    ShaderVariable parseDeclaration(istringstream& parseStream, string type,
        ShaderVariable::ScopeTypes scope);

    //Removes trailing ';' from name if it exists
    string sanitizeName(string name);

    //Returns the type given parsed type
    ShaderVariable::VarTypes getType(string type);

    //Stores the found variables
    vector<ShaderVariable> uniformVars;
    vector<ShaderVariable> attrVars;
};

#endif /* SHADERPARSER_H_ */
