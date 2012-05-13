/*
 *  Shader.cpp
 *  CS248-Final-Project
 *  Created by Matthew Fichman on 1/25/11.
 *
 *  Edited by Emin Topalovic to add support for easier information passing
 *  to shader
 *  NOTE: Students should not need to modify this file.
 *  
 */
/**
 * Stealing the assignment three shader class for fun and profit.
 */
#include "Shader.h"
#include <fstream>

#include <iostream>

using namespace std;

#define ERROR_BUFSIZE 1024

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

Shader::Shader(const std::string& path) :
	path_(path),
	vertexShaderID_(0),
	fragmentShaderID_(0),
	programID_(0),
	loaded_(false) {

	const GLchar* source[1];
    int length = 0;
	
	// Load the fragment shader and compile
	std::vector<char> fragmentSource = readSource(path + ".frag.glsl");
	source[0] = &fragmentSource.front();
    length = fragmentSource.size()-1;
	fragmentShaderID_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderID_, 1, source, &length);
    glCompileShader(fragmentShaderID_);
		
	// Load the vertex shader and compile
	std::vector<char> vertexSource = readSource(path + ".vert.glsl");
	source[0] = &vertexSource.front();
    length = vertexSource.size()-1;
	vertexShaderID_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderID_, 1, source, &length);
    glCompileShader(vertexShaderID_);
	
	// Create the vertex program
	programID_ = glCreateProgram();
	glAttachShader(programID_, fragmentShaderID_);
	glAttachShader(programID_, vertexShaderID_);
	glLinkProgram(programID_);
	
	// Error checking
	glGetProgramiv(programID_, GL_LINK_STATUS, (GLint*)&loaded_);
    //glGetShaderiv(vertexShaderID_, GL_COMPILE_STATUS, (GLint*)&loaded_);
	if (!loaded_) {
        GLchar tempErrorLog[ERROR_BUFSIZE];
		GLsizei length;
		glGetShaderInfoLog(fragmentShaderID_, ERROR_BUFSIZE, &length, tempErrorLog);
        errors_ += "Fragment shader errors:\n";
		errors_ += std::string(tempErrorLog, length) + "\n";
		glGetShaderInfoLog(vertexShaderID_, ERROR_BUFSIZE, &length, tempErrorLog);
        errors_ += "Vertex shader errors:\n";
		errors_ += std::string(tempErrorLog, length) + "\n";
		glGetProgramInfoLog(programID_, ERROR_BUFSIZE, &length, tempErrorLog);
        errors_ += "Linker errors:\n";
		errors_ += std::string(tempErrorLog, length) + "\n";
    }
}

Shader::~Shader() {
	glDeleteShader(vertexShaderID_);
	glDeleteShader(fragmentShaderID_);
	glDeleteProgram(programID_);
}

std::vector<char> Shader::readSource(const std::string& path) {

	// Open the file
	std::vector<char> source;
	std::ifstream in(path.c_str());
	if (in.fail()) {
		source.push_back(0);
		return source;
	}
	
	// Seek to the end of the file to get the size
	in.seekg(0, std::ios::end);
	source.reserve((unsigned)(1 + in.tellg()));
	source.resize((unsigned)in.tellg());
	in.seekg(0, std::ios::beg);
	if (source.empty()) {
		source.push_back(0);
		return source;
	}
	
	// Now read the whole buffer in one call, and don't 
	// forget to null-terminate the vector with a zero
	in.read(&source.front(), source.size());
	source.push_back(0);
	
	return source;
}

const std::string& Shader::path() const {
	return path_;
}

GLuint Shader::programID() const {
	return programID_;
}

const std::string& Shader::errors() const {
	return errors_;
}

bool Shader::loaded() const {
	return loaded_;
}

void Shader::setVertexAttribArray(std::string idName, GLint size, GLint type,
    bool normalized, GLsizei stride, GLvoid* data) const {
  GLint id = glGetAttribLocation(programID_, idName.c_str());

  if (id == -1) {
    cerr << "Location for id "<<idName<<" could not be found."<<endl;
  }
  GL_CHECK(glEnableVertexAttribArray(id));
  GL_CHECK(glVertexAttribPointer(id, size, type, normalized, stride, data));
}

void Shader::setUniform1f(std::string idName, float value) const {
  GLint id = glGetUniformLocation(programID_, idName.c_str());

  if (id == -1) {
    cerr << "Location for id "<<idName<<" could not be found."<<endl;
  }

  GL_CHECK(glUniform1f(id, value));
}

void Shader::setUniform3f(std::string idName, float value1, float value2, float value3) const {
  GLint id = glGetUniformLocation(programID_, idName.c_str());

  if (id == -1) {
    cerr << "Location for id "<<idName<<" could not be found."<<endl;
  }

  GL_CHECK(glUniform3f(id, value1, value2, value3));
}
