/*
 * main.cpp
 *
 *  Created on: May 23, 2012
 *      Author: emint
 */
#include <iostream>

// GLEW must be included first, if we need it.
#define FRAMEWORK_USE_GLEW
#include <GL/glew.h>

#include "engine/RenderingWindow.h"
#include "engine/InputProcessor.h"
#include "engine/ResourceManager.h"
#include "engine/MeshRenderer.h"
#include "engine/Camera.h"

#include "CloseWindowEvent.h"
#include "WavesShader.h"

using namespace std;

RenderingWindow window("Water", 1024, 1024);
InputProcessor inputProcessor(&window);
Camera* camera;

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

  //lighting
  //Enable lighting and set some color
  GLfloat lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  GLfloat lightSpecular[] = { 0.10f, 0.10f, 0.10f, 1.0f };
  GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
  glEnable(GL_LIGHTING);

  //Enable the following so we can still use glColor for triangles
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
}

void configureInput() {
  //Wire up the event to close window
  CloseWindowEvent* cWindow = new CloseWindowEvent(&window);
  inputProcessor.bind(KeySequence(InputEvent::WinClosed), cWindow);
}

void getInput() {
  inputProcessor.getEvents();
}

void init() {
  // Set up the projection and model-view matrices
  GLfloat nearClip = 0.1f;
  GLfloat farClip = 500.0f;
  GLfloat fieldOfView = 45.0f; // Degrees

  camera = new Camera(nearClip, farClip, fieldOfView, window.getHeight(),
      window.getWidth());
}

int main() {
  glInit();
  init();
  configureInput();
  ResourceManager::init();
  MeshRenderer renderer;
  WavesShader* waves = new WavesShader("shaders/waves");
  while (window.isOpened()) {
    getInput();
    camera->posCameraSetupView();
    window.display();
    renderer.renderMesh((ResourceManager::get())->getMesh("tile-hr"), waves);
  }
}
