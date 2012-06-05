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
Shader* illuminanceFilter;
Shader* blurFilter;
Shader* bloomEffect;

//Pipeline to apply postprocess
PostprocessPipeline* pipeline;

//Tiles
MeshRenderer cobbleTile;
MeshRenderer brickTile;
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

  pipeline = new PostprocessPipeline();

  textureShader = (ResourceManager::get())->getShader("simpletex");
  illuminanceFilter = (ResourceManager::get())->getShader("luminance");
  blurFilter = (ResourceManager::get())->getShader("blur");
  bloomEffect = (ResourceManager::get())->getShader("bloom");

}
/*
 * Method for actually rendering the vertices and texture coords. Assumes
 * the appropriate textures have been set on shader and shader has been called
 * as active program.
 */
void setupQuadAndRenderTexture(Shader* shader) {
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

  shader->setVertexAttribArray("positionIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &vertices[0]);
  shader->setVertexAttribArray("texCoordIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), &texCoords[0]);

  GL_CHECK(
      glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT,
          &vertexIndex[0]));
}

void bloomTexture(GLuint baseTexture, GLuint lightTexture, Shader* shader) {

  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader->programID()));

  glActiveTexture(GL_TEXTURE0);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, baseTexture));

  glActiveTexture(GL_TEXTURE1);
  GL_CHECK(glBindTextureEXT(GL_TEXTURE_2D, lightTexture));

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

  PostprocessUtils::setupQuadAndRenderTexture(shader);

  GL_CHECK(glUseProgram(oldId));
}

void renderScene() {
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
  LuminanceFilterEffect* luminance = new LuminanceFilterEffect();
  BlurFilterEffect* blur = new BlurFilterEffect();
  BloomFilterEffect* bloom = new BloomFilterEffect();

  pipeline->addEffect(luminance);
  pipeline->addEffect(blur);
  pipeline->addEffect(bloom);
}

int main() {
  glInit();
  init();
  initScenery();
  initPostprocess();
  //TODO: Remove once pipeline is up and running
  /*GLuint renderFbo = 0;
  GLuint initialRenderTexture = 0;
  GLuint luminanceTexture = 0;
  GLuint bluredTexture = 0;
  GLuint renderDepthTexture = 0;
  GLuint effectDepthTexture = 0;

  PostprocessUtils::initFBOAndTexture(renderFbo, initialRenderTexture,
      renderDepthTexture);
  PostprocessUtils::initDepthTexture(effectDepthTexture);
  PostprocessUtils::initColorTexture(luminanceTexture);
  PostprocessUtils::initColorTexture(bluredTexture);
*/
  while (window.isOpened()) {
    //GL_CHECK(glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, renderFbo));
    pipeline->captureBuffer();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    handleInput();
    camera->posCameraSetupView();

    renderScene();

    //TODO:Will remove once the effects pipeline is up
    /*//bind the luminance texture so that we render to it
     PostprocessUtils::bindTexturesToBuffer(luminanceTexture,
     effectDepthTexture, renderFbo);
     //render to texture
     PostprocessUtils::displayTexture(initialRenderTexture, illuminanceFilter);
     //bind the blur texture so that we render to it
     PostprocessUtils::bindTexturesToBuffer(bluredTexture, effectDepthTexture,
     renderFbo);
     //blur the current luminance storing it to the bound blured texture
     PostprocessUtils::displayTexture(luminanceTexture, blurFilter);
     //PostprocessUtils::displayTexture(luminanceTexture, textureShader);
     bloomTexture(initialRenderTexture, bluredTexture, bloomEffect);*/

    GLuint texture = pipeline->applyEffects();
    pipeline->releaseBuffer();
    PostprocessUtils::displayTexture(texture, textureShader);
    window.display();

    //PostprocessUtils::bindTexturesToBuffer(initialRenderTexture,
    //renderDepthTexture, renderFbo);
  }
}
