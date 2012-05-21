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
  genExportedVars(headerWriter, parsedShader);
  genHeaderConclusion(headerWriter);
}

void ShaderClassGenerator::generateMethodDeclarations(ofstream& headerFile,
    const ShaderParser* parsedShader) const {
  const vector<ShaderVariable>& uniformVars = parsedShader->getUniformVars();
  const vector<ShaderVariable>& attributeVars = parsedShader->getAttrVars();

  headerFile << endl << endl;

  for (vector<ShaderVariable>::const_iterator iter = attributeVars.begin(); iter
      != attributeVars.end(); ++iter) {
    genSemanticDeclaration(headerFile, *iter);
    genAttributeDeclaration(headerFile, *iter);
  }

  for (vector<ShaderVariable>::const_iterator iter = uniformVars.begin(); iter
      != uniformVars.end(); ++iter) {
    genSemanticDeclaration(headerFile, *iter);
    genUniformDeclaration(headerFile, *iter);
  }
}

void ShaderClassGenerator::genExportedVars(ofstream& headerWriter,
    const ShaderParser* parsedShader) const {
  const vector<ShaderVariable>& uniformVars = parsedShader->getUniformVars();
  const vector<ShaderVariable>& attributeVars = parsedShader->getAttrVars();

  //If we have one written out so that we can add ','
  int count = 0;
  for (vector<ShaderVariable>::const_iterator iter = attributeVars.begin(); iter
      != attributeVars.end(); ++iter) {
    if (iter->getSemanticType() != ShaderVariable::NoInfo) {
      count++;
    }
  }

  for (vector<ShaderVariable>::const_iterator iter = uniformVars.begin(); iter
      != uniformVars.end(); ++iter) {
    if (iter->getSemanticType() != ShaderVariable::NoInfo) {
      count++;
    }
  }

  headerWriter << "  private:" << endl;
  headerWriter << "    KnownVars exportedVars[" << count << "];" << endl;
}
void ShaderClassGenerator::genSemanticDeclaration(ofstream& headerFile,
    const ShaderVariable& var) const {
  if (var.getSemanticType() == ShaderVariable::NoInfo) {
    return;
  }

  //add spacing so it aligns well
  headerFile << "    void " << getSemanticMethod(var.getSemanticType()) << ";"
      << endl;
}

void ShaderClassGenerator::genUniformDeclaration(ofstream& headerFile,
    const ShaderVariable& var) const {
  headerFile << "    void setUniform" << getCamelCase(var.getName()) << "(";
  headerFile << genInputVars(var);
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
  genConstructorDef(classWriter, fileName, parsedShader);
  genMethodDef(classWriter, fileName, parsedShader);
}

void ShaderClassGenerator::genConstructorDef(ofstream& classWriter,
    const string& fileName, const ShaderParser* parsedShader) const {
  classWriter << fileName << "::" << fileName
      << "(const std::string& location) : Shader(location) {" << endl;

  genExportedVarArrayInit(classWriter, parsedShader);

  classWriter << "}" << endl << endl;
}

void ShaderClassGenerator::genExportedVarArrayInit(ofstream& classWriter,
    const ShaderParser* parsedShader) const {
  const vector<ShaderVariable>& uniformVars = parsedShader->getUniformVars();
  const vector<ShaderVariable>& attributeVars = parsedShader->getAttrVars();

  //Array index
  int count = 0;
  for (vector<ShaderVariable>::const_iterator iter = attributeVars.begin(); iter
      != attributeVars.end(); ++iter) {
    if (iter->getSemanticType() != ShaderVariable::NoInfo) {
      classWriter << "  exportedVars[" << count << "] = " << translateSemanticType(
          iter->getSemanticType()) << ";" << endl;
      count++;
    }
  }

  for (vector<ShaderVariable>::const_iterator iter = uniformVars.begin(); iter
      != uniformVars.end(); ++iter) {
    if (iter->getSemanticType() != ShaderVariable::NoInfo) {
      classWriter << "  exportedVars[" << count << "] = " << translateSemanticType(
          iter->getSemanticType()) << ";" << endl;
      count++;
    }
  }
}
void ShaderClassGenerator::genMethodDef(ofstream& classWriter,
    const string& fileName, const ShaderParser* parsedShader) const {
  vector<ShaderVariable> uniformVars = parsedShader->getUniformVars();
  vector<ShaderVariable> attributeVars = parsedShader->getAttrVars();

  for (vector<ShaderVariable>::iterator iter = attributeVars.begin(); iter
      != attributeVars.end(); ++iter) {
    genAttributeDef(classWriter, fileName, *iter);
    genAttributeSemanticDef(classWriter, fileName, *iter);
  }

  for (vector<ShaderVariable>::iterator iter = uniformVars.begin(); iter
      != uniformVars.end(); ++iter) {
    genUniformDef(classWriter, fileName, *iter);
    genUniformSemanticDef(classWriter, fileName, *iter);
  }
}

void ShaderClassGenerator::genUniformSemanticDef(ofstream& classWriter,
    const string& fileName, const ShaderVariable& var) const {
  if (var.getSemanticType() == ShaderVariable::NoInfo) {
    return;
  }
  classWriter << "void " << fileName << "::" << getSemanticMethod(
      var.getSemanticType()) << "{" << endl;
  classWriter << "  setUniform" << getCamelCase(var.getName()) << "("
      << getUntypedSemanticData(var.getSemanticType()) << ");" << endl;
  classWriter << "}" << endl << endl;
}

void ShaderClassGenerator::genUniformDef(ofstream& classWriter,
    const string& fileName, const ShaderVariable & var) const {
  classWriter << "void " << fileName << "::setUniform" << getCamelCase(
      var.getName()) << "(";
  classWriter << genInputVars(var);
  classWriter << "){" << endl;
  genUniformBody(classWriter, var);
  classWriter << "}" << endl;
}

void ShaderClassGenerator::genAttributeSemanticDef(ofstream& classWriter,
    const string& fileName, const ShaderVariable& var) const {
  if (var.getSemanticType() == ShaderVariable::NoInfo) {
    return;
  }

  classWriter << "void " << fileName << "::" << getSemanticMethod(
      var.getSemanticType()) << "{" << endl;
  classWriter << "  setAttribute" << getCamelCase(var.getName()) << "("
      << getUntypedSemanticData(var.getSemanticType()) << ");" << endl;
  classWriter << "}" << endl << endl;
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
      classWriter << "  setUniform4f(\"" << var.getName()
          << "\", in1, in2, in3, in4);" << endl;
      break;
    case ShaderVariable::Vec3:
      classWriter << "  setUniform3f(\"" << var.getName()
          << "\", in1, in2, in3);" << endl;
      break;
    case ShaderVariable::Vec2:
      classWriter << "  setUniform2f(\"" << var.getName() << "\", in1, in2);"
          << endl;
      break;
    case ShaderVariable::Float:
      classWriter << "  setUniform1f(\"" << var.getName() << "\", in1);"
          << endl;
      break;
    case ShaderVariable::Int:
      classWriter << "  setUniform1i(\"" << var.getName() << "\", in1);"
          << endl;
      break;
    case ShaderVariable::Sampler:
      classWriter << "  setUniform1i(\"" << var.getName() << "\", in1);"
          << endl;
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

string ShaderClassGenerator::genInputVars(const ShaderVariable& var) const {
  switch (var.getType()) {
    case ShaderVariable::Vec4:
      return "float in1, float in2, float in3, float in4";
    case ShaderVariable::Vec3:
      return "float in1, float in2, float in3";
    case ShaderVariable::Vec2:
      return "float in1, float in2";
    case ShaderVariable::Float:
      return "float in1";
    case ShaderVariable::Int:
      return "int in1";
    case ShaderVariable::Sampler:
      return "int in1";
    default:
      return "UNKNOWN TYPE";
  }
}

string ShaderClassGenerator::getSemanticMethod(
    ShaderVariable::SemanticType type) const {
  switch (type) {
    case ShaderVariable::Tangent:
      return "setTangent(bool normalized, GLsizei stride, GLvoid* data)";
    case ShaderVariable::Bitangent:
      return "setBitangent(bool normalized, GLsizei stride, GLvoid* data)";
    case ShaderVariable::Normal:
      return "setNormal(bool normalized, GLsizei stride, GLvoid* data)";
    case ShaderVariable::Position:
      return "setPosition(bool normalized, GLsizei stride, GLvoid* data)";
    case ShaderVariable::TextureCoord:
      return "setTextureCoords(bool normalized, GLsizei stride, GLvoid* data)";
    case ShaderVariable::Time:
      return "setTime(float in1)";
    case ShaderVariable::Ka:
      return "setKa(float in1, float in2, float in3)";
    case ShaderVariable::Ks:
      return "setKs(float in1, float in2, float in3)";
    case ShaderVariable::Kd:
      return "setKd(float in1, float in2, float in3)";
    case ShaderVariable::Shininess:
      return "setShininess(float in1)";
    case ShaderVariable::NormalMap:
      return "setNormalMap(int in1)";
    case ShaderVariable::HeightMap:
      return "setHeightMap(int in1)";
    case ShaderVariable::DiffuseMap:
      return "setDiffuseMap(int in1)";
    case ShaderVariable::SpecularMap:
      return "setSpecularMap(int in1)";
    default:
      return "";
      break;
  }
}

string ShaderClassGenerator::getUntypedSemanticData(
    ShaderVariable::SemanticType type) const {
  switch (type) {
    case ShaderVariable::Tangent:
      return "normalized, stride, data";
    case ShaderVariable::Bitangent:
      return "normalized, stride, data";
    case ShaderVariable::Normal:
      return "normalized, stride,data";
    case ShaderVariable::Position:
      return "normalized, stride, data";
    case ShaderVariable::TextureCoord:
      return "normalized, stride, data";
    case ShaderVariable::Time:
      return "in1";
    case ShaderVariable::Ka:
      return "in1, in2, in3";
    case ShaderVariable::Ks:
      return "in1, in2, in3";
    case ShaderVariable::Kd:
      return "in1, in2, in3";
    case ShaderVariable::Shininess:
      return "in1";
    case ShaderVariable::NormalMap:
      return "in1";
    case ShaderVariable::HeightMap:
      return "in1";
    case ShaderVariable::DiffuseMap:
      return "in1";
    case ShaderVariable::SpecularMap:
      return "in1";
    default:
      return "";
      break;
  }
}

string ShaderClassGenerator::translateSemanticType(
    ShaderVariable::SemanticType type) const {
  switch (type) {
    case ShaderVariable::Tangent:
      return "Tangent";
    case ShaderVariable::Bitangent:
      return "Bitangent";
    case ShaderVariable::Normal:
      return "Normal";
    case ShaderVariable::Position:
      return "Position";
    case ShaderVariable::TextureCoord:
      return "TextureCoord";
    case ShaderVariable::Time:
      return "Time";
    case ShaderVariable::Ka:
      return "Ka";
    case ShaderVariable::Ks:
      return "Ks";
    case ShaderVariable::Kd:
      return "Kd";
    case ShaderVariable::Shininess:
      return "Shininess";
    case ShaderVariable::NormalMap:
      return "NormalMap";
    case ShaderVariable::HeightMap:
      return "HeightMap";
    case ShaderVariable::DiffuseMap:
      return "DiffuseMap";
    case ShaderVariable::SpecularMap:
      return "SpecularMap";
    default:
      return "";
      break;
  }
}
