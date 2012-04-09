/*
 * main.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */
#include <iostream>

#include "Character.h"

#include "Framework.h"

//sfml window settings
sf::WindowSettings settings(24, 8, 2);
sf::Window window(sf::VideoMode(800, 600), "SD", sf::Style::Close, settings);

Character* mainCharacter;

using namespace std;

float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 1.0f;

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
}
void handleInput() {
  sf::Event evt;
  while (window.GetEvent(evt)) {
    switch (evt.Type) {
      case sf::Event::Closed:
        // Close the window.  This will cause the game loop to exit,
        // because the IsOpened() function will no longer return true.
        window.Close();
        break;
      case sf::Event::KeyPressed:
        if (evt.Key.Code == sf::Key::W) {
          cameraZ -= .1f;
        } else if (evt.Key.Code == sf::Key::S) {
          cameraZ += .1f;
        } else if (evt.Key.Code == sf::Key::A) {
          cameraX -= .1f;
        } else if (evt.Key.Code == sf::Key::D) {
          cameraX += .1f;
        }
        break;
    }
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

int main() {
  glInit();
  mainCharacter = new Character();
  while (window.IsOpened()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleInput();
    createView();
    mainCharacter->render();
    window.Display();
  }
}
