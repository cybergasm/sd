/*
 * ShaderClassGenerator.cpp
 *
 *  Created on: May 13, 2012
 *      Author: emint
 */

#include "ShaderClassGenerator.h"

#include <vector>
#include <iostream>

ShaderClassGenerator::ShaderClassGenerator() {

}

ShaderClassGenerator::~ShaderClassGenerator() {
  // TODO Auto-generated destructor stub
}

void ShaderClassGenerator::generateClass(const string& className,
    const ShaderParser* parsedShader) const {
  genHeader(className, parsedShader);
  genClassFile(className, parsedShader);
}

void ShaderClassGenerator::genHeader(const string& fileName,
    const ShaderParser* parsedShader) const {
  ofstream headerWriter;
  string fileHeaderName = fileName + ".h";
  headerWriter.open(fileHeaderName.c_str());
  genHeaderPreamble(headerWriter, fileName);
  generateMethodDeclarations(headerWriter, parsedShader);
  genHeaderConclusion(headerWriter);
}

void ShaderClassGenerator::generateMethodDeclarations(ofstream& headerFile,
    const ShaderParser* parsedShader) const {
  vector<ShaderVariable> uniformVars = parsedShader->getUniformVars();
  vector<ShaderVariable> attributeVars = parsedShader->getAttrVars();

  headerFile << endl << endl;

  for (vector<ShaderVariable>::iterator iter = attributeVars.begin(); iter
      != attributeVars.end(); ++iter) {
    genAttributeDeclaration(headerFile, *iter);
  }

  for (vector<ShaderVariable>::iterator iter = uniformVars.begin(); iter
      != uniformVars.end(); ++iter) {
    genUniformDeclaration(headerFile, *iter);
  }
}

void ShaderClassGenerator::genUniformDeclaration(ofstream& headerFile,
    const ShaderVariable& var) const {
  headerFile << "    void setUniform" << getCamelCase(var.getName()) << "(";
  genInputVars(headerFile, var);
  headerFile << ");" << endl << endl << endl;
}

void ShaderClassGenerator::genAttributeDeclaration(ofstream& headerFile,
    const ShaderVariable& var) const {
  headerFile << "    void setAttribute" << getCamelCase(var.getName())
      << "(bool normalized, GLsizei stride, GLvoid* data);";
  headerFile << endl << endl << endl;
}

void ShaderClassGenerator::genHeaderPreamble(ofstream& headerFile,
    const string& fileName) const {
  headerFile << "#ifndef " << genHeaderDefName(fileName) << endl;
  headerFile << "#define " << genHeaderDefName(fileName) << endl;
  headerFile << "#include \"Shader.h\"" << endl;
  headerFile << endl;
  headerFile << "class " << fileName << " : public Shader {" << endl;
  headerFile << "  public: " << endl;
  headerFile << "    " << fileName << "(const std::string& location);" << endl;
  headerFile << "    ~" << fileName << "();" << endl;

}

void ShaderClassGenerator::genHeaderConclusion(ofstream& headerFile) const {
  headerFile << "};" << endl;
  headerFile << endl;
  headerFile << "#endif" << endl;
}

string ShaderClassGenerator::genHeaderDefName(const string& fileName) const {
  return "__" + fileName + "__h__";
}

void ShaderClassGenerator::genClassFile(const string& fileName,
    const ShaderParser* parsedShader) const {
  ofstream classWriter;
  string classFileName = fileName + ".cpp";
  classWriter.open(classFileName.c_str());
  classWriter << "#include \"" << fileName << ".h\"" << endl << endl;
  genConstructorDef(classWriter, fileName);
  genMethodDef(classWriter, fileName, parsedShader);
}

void ShaderClassGenerator::genConstructorDef(ofstream& classWriter,
    const string& fileName) const {
  classWriter << fileName << "::" << fileName
      << "(const std::string& location) : Shader(location) {" << endl;
  classWriter << "}" << endl << endl;
  ;
}

void ShaderClassGenerator::genMethodDef(ofstream& classWriter,
    const string& fileName, const ShaderParser* parsedShader) const {
  vector<ShaderVariable> uniformVars = parsedShader->getUniformVars();
  vector<ShaderVariable> attributeVars = parsedShader->getAttrVars();

  for (vector<ShaderVariable>::iterator iter = attributeVars.begin(); iter
      != attributeVars.end(); ++iter) {
    genAttributeDef(classWriter, fileName, *iter);
  }

  for (vector<ShaderVariable>::iterator iter = uniformVars.begin(); iter
      != uniformVars.end(); ++iter) {
    genUniformDef(classWriter, fileName, *iter);
  }
}

void ShaderClassGenerator::genUniformDef(ofstream& classWriter,
    const string& fileName, const ShaderVariable & var) const {
  classWriter << "void " << fileName << "::setUniform" << getCamelCase(
      var.getName()) << "(";
  genInputVars(classWriter, var);
  classWriter << "){" << endl;
  genUniformBody(classWriter, var);
  classWriter << "}" << endl;
}

void ShaderClassGenerator::genAttributeDef(ofstream& classWriter,
    const string& fileName, const ShaderVariable& var) const {
  classWriter << "void " << fileName << "::setAttribute" << getCamelCase(
      var.getName()) << "(bool normalized, GLsizei stride, GLvoid* data) {"
      << endl;
  genAttributeBody(classWriter, var);
  classWriter << "}" << endl;
}

void ShaderClassGenerator::genUniformBody(ofstream& classWriter,
    const ShaderVariable& var) const {
  switch (var.getType()) {
    case ShaderVariable::Vec4:
      classWriter << "  setUniform4f(\"" << var.getName() << "\", in1, in2, in3, in4);"
          << endl;
      break;
    case ShaderVariable::Vec3:
      classWriter << "  setUniform3f(\"" << var.getName() << "\", in1, in2, in3);"
          << endl;
      break;
    case ShaderVariable::Vec2:
      classWriter << "  setUniform2f(\"" << var.getName() << "\", in1, in2);" << endl;
      break;
    case ShaderVariable::Float:
      classWriter << "  setUniform1f(\"" << var.getName() << "\", in1);" << endl;
      break;
    case ShaderVariable::Int:
      classWriter << "  setUniform1i(\"" << var.getName() << "\", in1);" << endl;
      break;
    case ShaderVariable::Sampler:
      classWriter << "  setUniform1i(\"" << var.getName() << "\", in1);" << endl;
      break;
    default:
      classWriter << "UNKNOWN" << endl;
      break;
  }
}

void ShaderClassGenerator::genAttributeBody(ofstream& classWriter,
    const ShaderVariable& var) const {
  switch (var.getType()) {
    case ShaderVariable::Vec4:
      classWriter << "  setVertexAttribArray(\"" << var.getName()
          << "\", 4, GL_FLOAT, normalized, stride, data);" << endl;
      break;
    case ShaderVariable::Vec3:
      classWriter << "  setVertexAttribArray(\"" << var.getName()
          << "\", 3, GL_FLOAT, normalized, stride, data);" << endl;
      break;
    case ShaderVariable::Vec2:
      classWriter << "  setVertexAttribArray(\"" << var.getName()
          << "\", 2, GL_FLOAT, normalized, stride, data);" << endl;
      break;
    case ShaderVariable::Float:
      classWriter << "  setVertexAttribArray(\"" << var.getName()
          << "\", 1, GL_FLOAT, normalized, stride, data);" << endl;
      break;
    case ShaderVariable::Int:
      classWriter << "  setVertexAttribArray(\"" << var.getName()
          << "\", 1, GL_INT, normalized, stride, data);" << endl;
      break;
    default:
      break;
  }
}

string ShaderClassGenerator::getCamelCase(string name) const {
  char first = toupper(name[0]);
  string camelStr = first + name.substr(1, name.length() - 1);
  return camelStr;
}

void ShaderClassGenerator::genInputVars(ofstream& file,
    const ShaderVariable& var) const {
  switch (var.getType()) {
    case ShaderVariable::Vec4:
      file << "float in1, float in2, float in3, float in4";
      break;
    case ShaderVariable::Vec3:
      file << "float in1, float in2, float in3";
      break;
    case ShaderVariable::Vec2:
      file << "float in1, float in2";
      break;
    case ShaderVariable::Float:
      file << "float in1";
      break;
    case ShaderVariable::Int:
      file << "int in1";
      break;
    case ShaderVariable::Sampler:
      file << "int in1";
      break;
    default:
      file << "UNKNOWN TYPE" << endl;
      break;

  }
}
