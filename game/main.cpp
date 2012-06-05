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
#include "engine/Camera.h"
#include "Tile.h"
#include "engine/ResourceManager.h"
#include "engine/InputProcessor.h"
#include "engine/RenderingWindow.h"
#include "engine/MeshRenderer.h"
#include "engine/PostprocessUtils.h"
#include "engine/PostprocessPipeline.h"
#include "engine/PostprocessEffect.h"
#include "engine/BloomFilterEffect.h"
#include "engine/BlurFilterEffect.h"
#include "engine/LuminanceFilterEffect.h"

#include "Framework.h"

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}
//sfml window settings
RenderingWindow window("SD", 1024, 1024);

//The user's avatar
Character* mainCharacter;

//Input handling
InputResponder* input;

//Camera controls
Camera* camera;

//Shader to texture quad
Shader* textureShader;

//Pipeline to apply postprocess
PostprocessPipeline* pipeline;

//Tiles
MeshRenderer cobbleTile;
MeshRenderer brickTile;

//Filters
LuminanceFilterEffect* luminance;
BlurFilterEffect* blur;
BloomFilterEffect* bloom;

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

void handleInput() {
  input->processEvents();
}

void lightingPosition() {
  static GLfloat lightPosition[] = { 13.4, 5, -15.6 };
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void init() {
  // Set up the projection and model-view matrices
  GLfloat nearClip = 0.1f;
  GLfloat farClip = 500.0f;
  GLfloat fieldOfView = 45.0f; // Degrees

  camera = new Camera(nearClip, farClip, fieldOfView, window.getHeight(),
      window.getWidth());

  //Initialize resource manager to find all resources
  ResourceManager::init();

  //Initialize main character
  mainCharacter = new Character();

  //Set initial anchor around character
  camera->setAnchor(mainCharacter->getPos());

  //Initilize Input handler
  input = new InputResponder(&window, mainCharacter, camera);

  //Configure window
  window.showMouseCursor(false);

  //Initialize postprocessing pipeline
  pipeline = new PostprocessPipeline();

  //Initialize shader to output postprocessing
  textureShader = (ResourceManager::get())->getShader("simpletex");

  //Postprocessing effects init
  luminance = new LuminanceFilterEffect();
  blur = new BlurFilterEffect();
  bloom = new BloomFilterEffect();
}

void renderScene() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //This is a little weird, but here is what happens. The light
  //position needs to get multiplied by the MV matrix, which is set
  //to identity by the display call below. This is an oops, since the loop
  //back around, the MV is still identity when lighting is set in handleInput.
  //We can not just switch these two calls as camera->pos...() depends on
  //having the most up to date position, so we have a circular dependency.
  //This pulls out the lighting position (which is temporary anyway),
  lightingPosition();

  glPushMatrix();
  glTranslatef(0, 0, 6);
  glRotatef(-90, 1, 0, 0);
  for (int j = 0; j < 5; j++) {
    glPushMatrix();
    glTranslatef(-1.6 * j, 0, 0);
    for (int i = 0; i < 5; i++) {
      brickTile.renderMesh((ResourceManager::get())->getMesh("tile"),
          (ResourceManager::get())->getParallaxShader());
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
      cobbleTile.renderMesh((ResourceManager::get())->getMesh("tile"),
          (ResourceManager::get())->getParallaxShader());
      glTranslatef(0, 0, 1.6);
    }
    glPopMatrix();
  }
  glPopMatrix();

  mainCharacter->render(window.getFramerate());
}

void initScenery() {
  cobbleTile.setDiffuseTex("cobble_diffuse");
  cobbleTile.setNormTex("cobble_normal");
  cobbleTile.setHeightTex("cobble_height");
  brickTile.setDiffuseTex("brick_diffuse");
  brickTile.setNormTex("brick_normal");
  brickTile.setHeightTex("brick_height");
}

void initPostprocess() {
  pipeline->addEffect(luminance);
  pipeline->addEffect(blur);
  pipeline->addEffect(bloom);
}

int main() {
  glInit();
  init();
  initScenery();
  initPostprocess();

  while (window.isOpened()) {
    pipeline->captureBuffer();

    handleInput();

    camera->posCameraSetupView();

    renderScene();

    GLuint texture = pipeline->applyEffects();
    pipeline->releaseBuffer();

    PostprocessUtils::displayTexture(texture, textureShader);
    window.display();
  }
}
