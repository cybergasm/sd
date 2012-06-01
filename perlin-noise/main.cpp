/*
 * main.cpp
 *
 *  Created on: May 24, 2012
 *      Author: emint
 */

// GLEW must be included first, if we need it.
#define FRAMEWORK_USE_GLEW
#include <GL/glew.h>

#include <iostream>

#include "engine/MeshRenderer.h"
#include "engine/InputProcessor.h"
#include "engine/RenderingWindow.h"
#include "engine/ResourceManager.h"

#include "PerlinNoiseGenerator.h"
#include "CloseWindowEvent.h"
#include "TextureShader.h"

#include <sys/time.h>
using namespace std;

RenderingWindow window("noise", 1024, 1024);
InputProcessor inputProcessor(&window);
TextureShader* texShader = NULL;

void glInit() {
#ifdef FRAMEWORK_USE_GLEW
  GLint error = glewInit();
  if (GLEW_OK != error) {
    std::cerr << glewGetErrorString(error) << std::endl;
    exit(-1);
  }
  if (!GLEW_VERSION_2_0 || !GL_EXT_framebuffer_object) {
    std::cerr << "This program requires OpenGL 2.0 and FBOs" << std::endl;
    exit(-1);
  }
#endif
  glViewport(0, 0, window.getWidth(), window.getHeight());

  glClearDepth(1.f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.f);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);
}

void inputInit() {
  //Wire up the event to close window
  CloseWindowEvent* cWindow = new CloseWindowEvent(&window);
  inputProcessor.bind(KeySequence(InputEvent::WinClosed), cWindow);
}

void render(const PerlinNoiseGenerator& gen,
    int curFrame) {
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glUseProgram(texShader->programID());
  glActiveTexture(GL_TEXTURE0);
  texShader->setDiffuseMap(0);
  gen.getSlice(curFrame)->bind();
  unsigned int vertices[4] = { 0, 1, 2, 3 };
  aiVector3D positions[4] = { aiVector3D(-1, -1, -1), aiVector3D(1, -1, -1),
      aiVector3D(1, 1, -1), aiVector3D(-1, 1, -1) };
  aiVector3D texCoords[4] = { aiVector3D(0, 0, 0), aiVector3D(0, 1, 0),
      aiVector3D(1, 1, -1), aiVector3D(1, 0, -1) };

  texShader->setPosition(false, sizeof(aiVector3D), positions);
  texShader->setTextureCoords(false, sizeof(aiVector3D), texCoords);

  glDrawElements(
                GL_QUADS,
                4,
                GL_UNSIGNED_INT, &vertices[0]);
  glUseProgram(0);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
}

long getMs(timeval t){
  return t.tv_sec*1000+t.tv_usec/1000;
}
int main() {
  glInit();
  inputInit();
  texShader = new TextureShader("shaders/simpletexture");
  PerlinNoiseGenerator gen;
  int numFrames = 10;
  gen.generateNoise(numFrames);
  int curFrame = 0;
  time_t lastTime = 0;
  timeval curTimeV;
  long modifier = 1;
  while (window.isOpened()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    inputProcessor.getEvents();
    render(gen, curFrame);
    window.display();
    gettimeofday(&curTimeV, NULL);
    long curTime = getMs(curTimeV);
    if ((curTime - lastTime) > 100) {
      lastTime = curTime;
      curFrame += modifier;
    }
    if (curFrame >= numFrames || curFrame < 0) {
      modifier *= -1;
      curFrame += modifier;
    }
  }
}
