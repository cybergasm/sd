/*
 * PostprocessUtils.cpp
 *
 *  Created on: Jun 4, 2012
 *      Author: emint
 */

#include "PostprocessUtils.h"
#include <stdio.h>
#include <iostream>

// Open Asset Import Library
#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

using namespace std;

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

PostprocessUtils::PostprocessUtils() {
}

PostprocessUtils::~PostprocessUtils() {
}

void PostprocessUtils::initColorTexture(GLuint& texture) {
  GL_CHECK(glGenTextures(1, &texture));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));

  GL_CHECK( glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK( glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_LINEAR));
  GL_CHECK( glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK( glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK( glGenerateMipmapEXT(GL_TEXTURE_2D));

  GL_CHECK(
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA,
          GL_UNSIGNED_BYTE, 0));
}

void PostprocessUtils::initDepthTexture(GLuint& depthTexture) {
  GL_CHECK(glGenTextures(1, &depthTexture));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthTexture));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 1024 ,
          1024, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0));
}

void PostprocessUtils::bindTexturesToBuffer(GLuint colorTex, GLuint depthTex,
    GLuint fbo) {
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo));

  GL_CHECK(glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, colorTex, 0));
  GL_CHECK(glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTex, 0));

  if (GL_FRAMEBUFFER_COMPLETE
      != glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT)) {
    cout << "FBO fail" << endl;
  }
}

void PostprocessUtils::initFBOAndTexture(GLuint& fbo, GLuint& texture,
    GLuint& depthTexture) {
  initColorTexture(texture);
  initDepthTexture(depthTexture);

  GL_CHECK(glGenFramebuffersEXT(1, &fbo));

  bindTexturesToBuffer(texture, depthTexture, fbo);

  //reset the buffer
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
}

void PostprocessUtils::setupQuadAndRenderTexture(Shader* shader) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //frame-buffer origin is bottom left (-1,-1) which corresponds to the origin
  //of the texture at (0,0)
  aiVector3D vertices[4] = { aiVector3D(-1, -1, -1), aiVector3D(1, -1, -1),
      aiVector3D(1, 1, 1), aiVector3D(-1, 1, -1) };
  aiVector3D texCoords[4] = { aiVector3D(0, 0, 0), aiVector3D(1, 0, 0),
      aiVector3D(1, 1, 0), aiVector3D(0, 1, 0) };
  unsigned int vertexIndex[4] = { 0, 1, 2, 3 };

  shader->setVertexAttribArray("positionIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &vertices[0]);
  shader->setVertexAttribArray("texCoordIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &texCoords[0]);

  GL_CHECK(
      glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,
          &vertexIndex[0]));
}

void PostprocessUtils::displayTexture(GLuint texture, Shader* shader) {
  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader->programID()));

  glActiveTexture(GL_TEXTURE0);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, texture));

  shader->setUniform1i("textureImg", 0);

  setupQuadAndRenderTexture(shader);

  GL_CHECK(glUseProgram(oldId));
}
