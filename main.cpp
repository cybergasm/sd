/*
 * main.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */
#include <iostream>

#include "Character.h"
#include "InputResponder.h"
#include "Camera.h"

#include "Framework.h"

//sfml window settings
sf::WindowSettings settings(24, 8, 2);
sf::Window window(sf::VideoMode(800, 600), "SD", sf::Style::Close, settings);

//The user's avatar
Character* mainCharacter;

//Input handling
InputResponder input;

//Camera controls
Camera* camera;

using namespace std;

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
  glViewport(0, 0, window.GetWidth(), window.GetHeight());

  glClearDepth(1.f);
  glClearColor(0.0f, 0.0f, 0.0f, 0.f);

  glEnable(GL_DEPTH_TEST);
  glDepthMask(GL_TRUE);

  //lighting
  //Enable lighting and set some color
  GLfloat lightDiffuse[] = { 0.34f, .04f, .86f, 1.0f };
  GLfloat lightSpecular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
  glEnable(GL_LIGHTING);

  //Enable the following so we can still use glColor for triangles
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

  GLfloat lightPosition[] = { 0, .15, 5, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void handleInput() {
  sf::Event evt;
  while (window.GetEvent(evt)) {
    input.inputIs(evt);
  }
}

void init() {
  // Set up the projection and model-view matrices
  GLfloat nearClip = .1f;
  GLfloat farClip = 500.0f;
  GLfloat fieldOfView = 45.0f; // Degrees

  mainCharacter = new Character();
  camera = new Camera(nearClip, farClip, fieldOfView, window.GetHeight(),
      window.GetWidth());

  window.ShowMouseCursor(false);

  camera->setAnchor(mainCharacter->getPos());
  input.characterIs(mainCharacter);
  input.cameraIs(camera);
  input.windowIs(&window);
}

int main() {
  glInit();
  init();
  while (window.IsOpened()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleInput();
    camera->posCameraSetupView();
    glBegin(GL_TRIANGLES);
    glColor3f(.34f, 0, 0);
    glVertex3f(0, 2, 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();

    glBegin(GL_QUADS);
    for (int i = 0; i < 5; i++) {
      glColor3f(.34f, .34f, .34f);
      glVertex3f(.5, 0, 0);
      glVertex3f(-.5, 0, 0);
      glVertex3f(-.5, 0, 2 * i);
      glVertex3f(.5, 0, 2 * i);
    }
    glEnd();
    glBegin(GL_TRIANGLES);
    glColor3f(.0f, .0f, .34f);
    glVertex3f(0, 0, -2);
    glVertex3f(-1, 0, 0);
    glVertex3f(1, 0, 0);

    glEnd();
    mainCharacter->render(window.GetFrameTime());

    window.Display();
  }
}
