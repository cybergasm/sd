/*
 * main.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */
#include <iostream>

#include "Character.h"
#include "InputResponder.h"

#include "Framework.h"

//sfml window settings
sf::WindowSettings settings(24, 8, 2);
sf::Window window(sf::VideoMode(800, 600), "SD", sf::Style::Close, settings);

//The user's avatar
Character* mainCharacter;

//Input handling
InputResponder input;

using namespace std;

float cameraX = 0.0f, cameraY = 3.0f, cameraZ = 4.0f;

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
  glClearColor(0.0f, 0.0f, .0f, 0.f);

  //lighting
  //Enable lighting and set some color
  GLfloat lightDiffuse[] = { 0.34f, .04f, .86f, 1.0f };
  GLfloat lightSpecular[] = { 0.8f, 0.8f, 0.8f, 1.0f };
  GLfloat lightAmbient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

  GLfloat lightPosition[] = { 0, 1, 1, 0.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void handleInput() {
  sf::Event evt;
  while (window.GetEvent(evt)) {
    input.inputIs(evt);
  }
}

void createView() {
  // Set up the projection and model-view matrices
  GLfloat aspectRatio = (GLfloat) window.GetWidth() / window.GetHeight();
  GLfloat nearClip = 0.1f;
  GLfloat farClip = 500.0f;
  GLfloat fieldOfView = 45.0f; // Degrees

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fieldOfView, aspectRatio, nearClip, farClip);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

}

void init() {
  mainCharacter = new Character();
  input.characterIs(mainCharacter);
  input.windowIs(&window);
}

int main() {
  glInit();
  init();
  while (window.IsOpened()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleInput();
    createView();
    mainCharacter->render(window.GetFrameTime());
    window.Display();
  }
}
