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
Shader* illuminanceFilter;
Shader* blurFilter;
Shader* bloomEffect;

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

  ResourceManager::init();

  mainCharacter = new Character();

  input = new InputResponder(&window, mainCharacter, camera);

  window.showMouseCursor(false);

  camera->setAnchor(mainCharacter->getPos());

  textureShader = (ResourceManager::get())->getShader("simpletex");
  illuminanceFilter = (ResourceManager::get())->getShader("luminance");
  blurFilter = (ResourceManager::get())->getShader("blur");
  bloomEffect = (ResourceManager::get())->getShader("bloom");

}

/**
 * Initializes a texture to be bound to the color attachment of a framebuffer
 */
void initColorTexture(GLuint& texture) {
  GL_CHECK(glGenTextures(1, &texture));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture));

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024,
          1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0));
}

/**
 * Initializes a texture to be bound to the depth attachment of a framebuffer
 */
void initDepthTexture(GLuint& depthTexture) {
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

/**
 * Binds color and depth textures to buffer which is bound to the frame buffer
 */
void bindTexturesToBuffer(GLuint colorTex, GLuint depthTex, GLuint fbo) {
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo));

  GL_CHECK(glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, colorTex, 0));
  GL_CHECK(glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, depthTex, 0));

  if (GL_FRAMEBUFFER_COMPLETE
      != glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT)) {
    cout << "FBO fail" << endl;
  }
}

/**
 * Initialization routine for setting up a texture, mipmapping it and then
 * allocating a FBO and binding the texture to it. This leaves the buffer as
 * it was when entered, just allocating the buffer and texture and wiring it
 * all up.
 */
void initFBOAndTexture(GLuint& fbo, GLuint& texture, GLuint& depthTexture) {
  initColorTexture(texture);
  initDepthTexture(depthTexture);

  GL_CHECK(glGenFramebuffersEXT(1, &fbo));

  bindTexturesToBuffer(texture, depthTexture, fbo);

  //reset the buffer
  GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
}

void displayTexture(GLuint texture, Shader* shader) {
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
  GL_CHECK(glUseProgram(shader->programID()));

  glActiveTexture(GL_TEXTURE0);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, texture));

  shader->setVertexAttribArray("positionIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &vertices[0]);
  shader->setVertexAttribArray("texCoordIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &texCoords[0]);

  GLint textureId = glGetUniformLocation(shader->programID(), "textureImg");
  if (textureId == -1) {
    cerr << "Error getting texture handle for texture." << endl;
  }
  GL_CHECK(glUniform1i(textureId,0));

  GL_CHECK(
      glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,
          &vertexIndex[0]));

  GL_CHECK(glUseProgram(oldId));
}

void bloomTexture(GLuint baseTexture, GLuint lightTexture, Shader* shader) {
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
  GL_CHECK(glUseProgram(shader->programID()));

  glActiveTexture(GL_TEXTURE0);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, baseTexture));

  glActiveTexture(GL_TEXTURE1);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, lightTexture));

  shader->setVertexAttribArray("positionIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &vertices[0]);
  shader->setVertexAttribArray("texCoordIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &texCoords[0]);

  GLint textureId = glGetUniformLocation(shader->programID(), "textureImg");
  GLint lightId = glGetUniformLocation(shader->programID(), "lightImg");

  if (textureId == -1) {
    cerr << "Error getting texture handle for base texture." << endl;
  }

  if (lightId == -1) {
    cerr << "Error getting texture handle for light texture." << endl;
  }

  GL_CHECK(glUniform1i(textureId,0));
  GL_CHECK(glUniform1i(lightId,1));
  GL_CHECK(
      glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,
          &vertexIndex[0]));

  GL_CHECK(glUseProgram(oldId));
}
int main() {
  glInit();
  init();

  MeshRenderer cobbleTile;
  cobbleTile.setDiffuseTex("cobble_diffuse");
  cobbleTile.setNormTex("cobble_normal");
  cobbleTile.setHeightTex("cobble_height");
  MeshRenderer brickTile;
  brickTile.setDiffuseTex("brick_diffuse");
  brickTile.setNormTex("brick_normal");
  brickTile.setHeightTex("brick_height");

  GLuint renderFbo = 0;
  GLuint initialRenderTexture = 0;
  GLuint luminanceTexture = 0;
  GLuint bluredTexture = 0;
  GLuint renderDepthTexture = 0;
  GLuint effectDepthTexture = 0;

  initFBOAndTexture(renderFbo, initialRenderTexture, renderDepthTexture);
  initDepthTexture(effectDepthTexture);
  initColorTexture(luminanceTexture);
  initColorTexture(bluredTexture);
  while (window.isOpened()) {
    GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, renderFbo));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleInput();
    camera->posCameraSetupView();

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
    //bind the luminance texture so that we render to it
    bindTexturesToBuffer(luminanceTexture, effectDepthTexture, renderFbo);
    //render to texture
    displayTexture(initialRenderTexture, illuminanceFilter);
    //bind the blur texture so that we render to it
    bindTexturesToBuffer(bluredTexture, effectDepthTexture, renderFbo);
    //blur the current luminance storing it to the bound blured texture
    displayTexture(luminanceTexture, blurFilter);
    GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0));
    displayTexture(luminanceTexture, textureShader);
    bloomTexture(initialRenderTexture, bluredTexture, bloomEffect);
    window.display();

    bindTexturesToBuffer(initialRenderTexture, renderDepthTexture, renderFbo);
  }
}
