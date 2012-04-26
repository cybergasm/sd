/*
 * main.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */

#include <iostream>
#include <stdio.h>

#include "Character.h"
#include "InputResponder.h"
#include "Camera.h"
#include "Tile.h"

#include "Framework.h"

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}
//sfml window settings
sf::WindowSettings settings(24, 8, 2);
sf::Window window(sf::VideoMode(1024, 1024), "SD", sf::Style::Close, settings);

//The user's avatar
Character* mainCharacter;

//Input handling
InputResponder input;

//Camera controls
Camera* camera;

//Shader to texture quad
Shader* textureShader;

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
  static GLfloat lightPosition[] = { 13.4, 5, -15.6 };
  while (window.GetEvent(evt)) {
    input.inputIs(evt);
    //hack to let me test lighting quickly
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

  textureShader = new Shader("shaders/simpletexture");

  if (!textureShader->loaded()) {
    cerr << textureShader->errors() << endl;
    exit(-1);
  }
}

/**
 * Initialization routine for setting up a texture, mipmapping it and then
 * allocating a FBO and binding the texture to it. This leaves the buffer as
 * it was when entered, just allocating the buffer and texture and wiring it
 * all up.
 */
void initFBOAndTexture(GLuint& fbo, GLuint& texture, GLuint& depthTexture) {
  GL_CHECK(glGenTextures(1, &texture));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024,
          1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0));

  GL_CHECK(glGenTextures(1, &depthTexture));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, depthTexture));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 1024 ,
          1024, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0));

  GL_CHECK(glGenFramebuffersEXT(1, &fbo));
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo));

  GL_CHECK(glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, texture, 0));
  GL_CHECK(glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTexture, 0));

  if (GL_FRAMEBUFFER_COMPLETE
      != glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT)) {
    cout << "FBO fail on shadow" << endl;
  }

  //reset the buffer
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
}

void writeTextureToImage() {
  GLubyte* data = new GLubyte[1024 * 1024 * 4];
  sf::Image img(1024, 1024, sf::Color::White);
  glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  if (!img.LoadFromPixels(1024, 1024, data)) {
    cerr << "Error writing texture to file";
  }
  img.SaveToFile("Frame.jpg");
  delete[] data;
}

void displayTexture(GLuint texture) {
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

  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(textureShader->programID()));

  glActiveTexture(GL_TEXTURE0);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, texture));

  textureShader->setVertexAttribArray("positionIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &vertices[0]);
  textureShader->setVertexAttribArray("texCoordIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &texCoords[0]);

  GLint textureId = glGetUniformLocation(textureShader->programID(),
      "textureImg");
  if (textureId == -1) {
    cerr << "Error getting texture handle for instructions." << endl;
  }
  GL_CHECK(glUniform1i(textureId,0));

  GL_CHECK(
      glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,
          &vertexIndex[0]));

  GL_CHECK(glUseProgram(oldId));
}

int main() {
  glInit();
  init();

  Tile* cobbleTile = new Tile("cobble");
  Tile* brickTile = new Tile("brick");

  GLuint renderFbo = 0;
  GLuint initialRenderTexture = 0;
  GLuint renderDepthTexture = 0;

  initFBOAndTexture(renderFbo, initialRenderTexture, renderDepthTexture);

  while (window.IsOpened()) {
    GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, renderFbo));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleInput();

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
    GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
    displayTexture(initialRenderTexture);
    writeTextureToImage();

    window.Display();
  }
}
