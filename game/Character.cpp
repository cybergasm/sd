/*
 * Character.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

#include "Character.h"

#include <stdio.h>

#include "engine/ResourceManager.h"

Character::Character() :
  movementRate(.05), cameraRotation(0), cyclicAniTime(0), straightAniTime(0),
      aniTimeRate(1), xPos(0), yPos(.25), zPos(0) {
  //set our diffuse texture
  setDiffuseTex("main_char_tex1");
}

Character::~Character() {
}

void Character::move(aiVector3D translation) {
  xPos += movementRate * translation.x;
  yPos += movementRate * translation.y;
  zPos += movementRate * translation.z;
}

aiVector3D Character::getPos() {
  return aiVector3D(xPos, yPos, zPos);
}

void Character::updateTime(float framerate) {
  cyclicAniTime += aniTimeRate * framerate * 6.0f;
  straightAniTime += framerate * 6.0f;

  if (cyclicAniTime > 10) {
    aniTimeRate = -1;
  } else if (cyclicAniTime < 0) {
    aniTimeRate = 1;
  }
}

void Character::setCameraRotation(float cameraRot) {
  cameraRotation = cameraRot;
}

void Character::setWholeMeshTransform() const {
  //Move it to position
  glTranslatef(xPos, yPos, zPos);
  //Make it smaller so it fits better
  glScalef(.25, .25, .25);
  //Rotate it so its back is to the camera
  glRotatef(cameraRotation, 0, 1, 0);
}

void Character::render(float framerate) {
  //move internal animation timer forward
  updateTime(framerate);

  renderMesh((ResourceManager::get())->getMesh("spirit"),
      (ResourceManager::get())->getCharacterShader());
}

void Character::setCustomTransformation(string meshName) const {
  if (meshName == "0" || meshName == "1") {
    glRotatef(cyclicAniTime, 1, 1, 0);
  } else if (meshName == "2") {
    glScalef(1, 1 - cyclicAniTime * .09, 1);
  }
}

float Character::getTime() const {
  return straightAniTime;
}
