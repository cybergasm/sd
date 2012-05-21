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

    //Generates definition for exported getter
    void genExportedGetterDef(ofstream& headerFile) const;

    //Generates the array declaration storing exported vars
    void
    genExportedVars(ofstream& headerWriter,
        const ShaderParser* var) const;

    //Generates the overwrite declaration of setters for semantic values
    void
        genSemanticDeclaration(ofstream& headerFile, const ShaderVariable& var) const;

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
    //to the Shader constructor along with an initialization of the
    //exported variable array
    void
    genConstructorDef(ofstream& classWriter, const string& fileName, const ShaderParser* parsedShader) const;

    //Generates the initialization code for the exported variable array. Have to
    //go through each individually.
    void genExportedVarArrayInit(ofstream& classWriter, const ShaderParser* parsedShader) const;

    //Generates definitions for setter methods
    void genMethodDef(ofstream& classWriter, const string& fileName,
        const ShaderParser* parsedShader) const;

    //Generates the getter for exported variables method
    void genExportedVarGetter(ofstream& classWriter, const string& fileName) const;

    //Generates definition for attribute setter
    void genAttributeDef(ofstream& classWriter, const string& fileName,
        const ShaderVariable& var) const;

    //Generates a semantic variable setter definition for attribute variable
    void genAttributeSemanticDef(ofstream& classWriter, const string& fileName,
        const ShaderVariable& var) const;

    //Generates method body by making a call to one of the appropriate
    //setter methods. Note that this does assume use of the vertexAttribPointer
    //to set attribute values
    void
    genAttributeBody(ofstream& classWriter, const ShaderVariable& var) const;

    //Generates uniform definition
    void genUniformDef(ofstream& classWriter, const string& fileName,
        const ShaderVariable& var) const;

    //Generates a semantic variable setter definition for uniform variable
    void genUniformSemanticDef(ofstream& classWriter, const string& fileName,
        const ShaderVariable& var) const;

    //Generates method body by making call to one of the setUniform
    //functions
    void genUniformBody(ofstream& classWriter, const ShaderVariable& var) const;

    /**
     * Utilities shared by both class and headers
     */
    //Returns camel-case version of name. Assumes names are
    //camel-case by default so this just capitalizes the first letter
    string getCamelCase(string name) const;

    //returns a variable's input variables
    string genInputVars(const ShaderVariable& var) const;

    //Given a semantic value, returns its method name and inputs
    string getSemanticMethod(ShaderVariable::SemanticType type) const;

    //Given a semantic value returns the data that is passed in without type
    //info
    string getUntypedSemanticData(ShaderVariable::SemanticType type) const;

    //Given a ShaderVariable semantic type, converts it to Shader one
    string translateSemanticType(ShaderVariable::SemanticType type) const;

    //Returns number of semantically significant vars
    int getNumberSemanticVars(const ShaderParser* parsedShader) const;

};

#endif /* SHADERCLASSGENERATOR_H_ */
