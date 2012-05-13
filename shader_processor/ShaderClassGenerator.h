/*
 * ShaderClassGenerator.h
 *
 *  Created on: May 13, 2012
 *      Author: emint
 */

#ifndef SHADERCLASSGENERATOR_H_
#define SHADERCLASSGENERATOR_H_

#include "ShaderParser.h"
#include <string>
#include <fstream>

using namespace std;

class ShaderClassGenerator {
  public:
    ShaderClassGenerator();
    virtual ~ShaderClassGenerator();

    /**
     * Generates headers and source
     */
    void
        generateClass(const string& className, const ShaderParser* parsedShader) const;
  private:
    //The parsed variables
    ShaderParser* parsedShader;

    /**
     * Header file generation methods
     */
    //Generates the header file
    void
    genHeader(const string& fileName, const ShaderParser* parsedShader) const;

    //Generates the header preamble. This is the standard stuff
    //like the necessary inclusions and class declaration.
    void genHeaderPreamble(ofstream& headerFile, const string& fileName) const;

    //Generates the method declarations. The names are
    // set[Uniform|Attribute]<Name>([float|int]...)
    void generateMethodDeclarations(ofstream& headerFile,
        const ShaderParser* parsedShader) const;

    //Generates a uniform declaration
    void
    genUniformDeclaration(ofstream& headerFile, const ShaderVariable& var) const;

    //Generates an attribute declaration
    void genAttributeDeclaration(ofstream& headerFile,
        const ShaderVariable& var) const;

    //Generates the closing part of the header
    void genHeaderConclusion(ofstream& headerFile) const;

    //Returns the header name for the ifndef
    string genHeaderDefName(const string& fileName) const;

    /**
     * Class file generation methods
     */

    //Generates the class file
    void
    genClassFile(const string& fileName, const ShaderParser* parsedShader) const;

    //Generates the constructor definition which is basically just a call
    //to the Shader constructor
    void
    genConstructorDef(ofstream& classWriter, const string& fileName) const;

    //Generates definitions for setter methods
    void genMethodDef(ofstream& classWriter, const string& fileName,
        const ShaderParser* parsedShader) const;

    //Generates definition for attribute setter
    void genAttributeDef(ofstream& classWriter, const string& fileName,
        const ShaderVariable& var) const;

    //Generates method body by making a call to one of the appropriate
    //setter methods
    void genAttributeBody(ofstream& classWriter, const ShaderVariable& var) const;

    /**
     * Utilities shared by both class and headers
     */
    //Returns camel-case version of name. Assumes names are
    //camel-case by default so this just capitalizes the first letter
    string getCamelCase(string name) const;

    //Generates a variable's input variables
    void genInputVars(ofstream& headerFile, const ShaderVariable& var) const;
};

#endif /* SHADERCLASSGENERATOR_H_ */
