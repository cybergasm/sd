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
#include "engine/Camera.h"

#include "engine/PerlinNoiseGenerator.h"

#include "CloseWindowEvent.h"
#include "KeyMovement.h"
#include "MouseLookEvent.h"
#include "LightMovementEvent.h"
#include "WavesShader.h"
#include "WaveRenderer.h"
#include "PerlinWavesRenderer.h"
using namespace std;

RenderingWindow window("Water", 1024, 1024);
InputProcessor inputProcessor(&window);
Camera* camera;
GLfloat lightPosition[] = { 0, 2, 0 };

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

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

  //Wire up the event to move the Camera along the axis
  KeyMovement* movement = new KeyMovement(camera);
  KeySequence movementKeys;
  movementKeys.add(InputEvent::KeyW);
  movementKeys.add(InputEvent::KeyA);
  movementKeys.add(InputEvent::KeyS);
  movementKeys.add(InputEvent::KeyD);
  movementKeys.add(InputEvent::KeyV);
  movementKeys.add(InputEvent::Space);
  inputProcessor.bind(movementKeys, movement);

  //Wire up keys to move light around
  LightMovementEvent* lMove = new LightMovementEvent(lightPosition);
  KeySequence lMovementKeys;
  lMovementKeys.add(InputEvent::KeyI);
  lMovementKeys.add(InputEvent::KeyJ);
  lMovementKeys.add(InputEvent::KeyK);
  lMovementKeys.add(InputEvent::KeyL);
  inputProcessor.bind(lMovementKeys, lMove);

  //Wire up the mouse to rotate view
  MouseLookEvent* mouseLook = new MouseLookEvent(&window, camera);
  inputProcessor.bind(KeySequence(InputEvent::MouseMove), mouseLook);
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
  camera->setMovementRate(.05);
  window.showMouseCursor(false);
}

int main(int argc, char* argv[]) {
  glInit();
  init();
  configureInput();
  string mode;
  ResourceManager::init();
  //WaveRenderer renderer;
  PerlinWavesRenderer renderer;

  while (window.isOpened()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    getInput();
    camera->posCameraSetupView();
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    renderer.render(window.getFramerate());
    window.display();
  }
}
