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
#include "Tile.h"

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

void handleInput() {
  sf::Event evt;
  static GLfloat lightPosition[] = {13.4, 5, -15.6};
  while (window.GetEvent(evt)) {
    input.inputIs(evt);

    if (evt.Key.Code == sf::Key::J) {
      lightPosition[0] -= .1;
      cout << lightPosition[0] << " " << lightPosition[1] << " "
          << lightPosition[2] << endl;
    } else if (evt.Key.Code == sf::Key::K) {
      lightPosition[2] -= .1;
      cout << lightPosition[0] << " " << lightPosition[1] << " "
          << lightPosition[2] << endl;
    } else if (evt.Key.Code == sf::Key::L) {
      lightPosition[0] += .1;
      cout << lightPosition[0] << " " << lightPosition[1] << " "
          << lightPosition[2] << endl;
    } else if (evt.Key.Code == sf::Key::I) {
      lightPosition[2] += .1;
      cout << lightPosition[0] << " " << lightPosition[1] << " "
          << lightPosition[2] << endl;
    }
  }
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void init() {
  // Set up the projection and model-view matrices
  GLfloat nearClip = 0.1f;
  GLfloat farClip = 500.0f;
  GLfloat fieldOfView = 45.0f; // Degrees

  camera = new Camera(nearClip, farClip, fieldOfView, window.GetHeight(),
      window.GetWidth());

  mainCharacter = new Character();

  window.ShowMouseCursor(false);

  camera->setAnchor(mainCharacter->getPos());
  input.characterIs(mainCharacter);
  input.cameraIs(camera);
  input.windowIs(&window);
}

void setLightPositions() {
}

int main() {
  glInit();
  init();

  Tile* cobbleTile = new Tile("cobble");
  Tile* brickTile = new Tile("brick");

  while (window.IsOpened()) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleInput();

    setLightPositions();

    camera->posCameraSetupView();

    glPushMatrix();
    glTranslatef(0, 6, 6);
    glRotatef(90, 1, 0, 0);
    for (int j = 0; j < 5; j++) {
      glPushMatrix();
      glTranslatef(-1.6 * j, 0, 0);
      for (int i = 0; i < 5; i++) {
        brickTile->render();
        glTranslatef(0, 0, 1.6);
      }
      glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    //glTranslatef(0, 0, 5);
    //glRotatef(90, 1, 0, 0);
    for (int j = 0; j < 5; j++) {
      glPushMatrix();
      glTranslatef(-1.6 * j, 0, 0);
      for (int i = 0; i < 5; i++) {
        cobbleTile->render();
        glTranslatef(0, 0, 1.6);
      }
      glPopMatrix();
    }
    glPopMatrix();

    mainCharacter->render(window.GetFrameTime());

    window.Display();
  }
}
