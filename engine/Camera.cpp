/*
 * Camera.cpp
 *
 *  Created on: Mar 5, 2012
 *      Author: emint
 */
#include "Camera.h"

#include <math.h>
#include <GL/glu.h>

#include "assimp/aiTypes.h"

Camera::Camera(float nClip, float fClip, float fov_, int wH, int wW) :
  zOffset(-2), yOffset(.1), nearClip(nClip), farClip(fClip), fov(fov_),
      winHeight(wH), winWidth(wW), yAxisMax(.95), rateOfMovement(.1),
      totYAngle(0.0f), totXAngle(0.0f), sensitivity(1) {
  lookAt.x = 0.0f;
  lookAt.y = 0.0f;
  lookAt.z = -1.0f;
  lookAt.Normalize();

  upVec.x = 0.0f;
  upVec.y = 1.0f;
  upVec.z = 0.0f;

  //Shift our camera so it is 15 degrees at an angle looking at the back
  //of our character
  float degreesToRadians = M_PI / 180;
  rotateAroundAngle(-1 * M_PI, -15 * degreesToRadians);
}

Camera::~Camera() {
}

/**
 * Simply returns the cross product to get the orthogonal vector
 */
aiVector3D Camera::sideDirection() const {
  aiVector3D result;
  result.x = lookAt.y * upVec.z - upVec.y * lookAt.z;
  result.y = lookAt.z * upVec.x - upVec.z * lookAt.x;
  result.z = lookAt.x * upVec.y - upVec.x * lookAt.y;
  return result;
}

void Camera::wHeightIs(int height) {
  winHeight = height;
}

void Camera::wWidthIs(int width) {
  winWidth = width;
}

void Camera::rotateIncrementally(int dX_, int dY_) {
  float dX = (float) dX_ / sensitivity;
  float dY = (float) dY_ / sensitivity;

  float degreesToRadians = M_PI / 180;

  //grab the angles looking up and down
  float upDownAngle = -2 * fov * degreesToRadians * dY / winHeight;
  float leftRightAngle = -2 * fov * degreesToRadians * dX / winWidth;

  rotateAroundAngle(leftRightAngle, upDownAngle);
}

void Camera::rotateAroundAngle(float angleX, float angleY) {
  //Accumulate a total rotation lr
  totXAngle += angleX;

  //Now we have to rotate up-down around whatever the side-axis is
  aiVector3D tempRot;
  aiVector3D side = sideDirection();
  aiMatrix4x4 rotateAroundSide = aiMatrix4x4::Rotation(angleY, side,
      rotateAroundSide);

  //Attempt to rotate around side axis (e.g. up and down)
  aiVector3D newLook = rotateAroundSide * lookAt;

  //Can we not look farther up?
  if (fabs(newLook.y) < yAxisMax) {
    //if we can, make this the new view and add to the accumulation
    totYAngle += angleY;
    lookAt = newLook;
  }

  //Look left and right
  aiMatrix4x4 rotateAroundY = aiMatrix4x4::RotationY(angleX, rotateAroundY);
  lookAt *= rotateAroundY;

  lookAt.Normalize();
}

void Camera::posCameraSetupView() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov, (float) winHeight / (float) winWidth, nearClip, farClip);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  float dist = sqrt(zOffset * zOffset + yOffset * yOffset);
  position = aiVector3D(anchor.x - dist * lookAt.x, anchor.y - dist * lookAt.y,
      anchor.z - dist * lookAt.z);
  gluLookAt(anchor.x - dist * lookAt.x, anchor.y - dist * lookAt.y,
      anchor.z - dist * lookAt.z, anchor.x, anchor.y, anchor.z, upVec.x,
      upVec.y, upVec.z);
}

void Camera::setAnchor(aiVector3D anchor_) {
  anchor = anchor_;
}

void Camera::setMovementRate(float rate) {
  rateOfMovement = rate;
}
/**
 * Movement for a camera done by moving the point around which it is
 * anchored
 */
void Camera::moveBackwards() {
  anchor -= rateOfMovement * lookAt;
}

void Camera::moveForward() {
  anchor += rateOfMovement * lookAt;
}

void Camera::moveUp() {
  anchor += upVec * rateOfMovement;
}

void Camera::moveDown() {
  anchor -= upVec * rateOfMovement;
}

void Camera::moveLeft() {
  anchor -= sideDirection() * rateOfMovement;
}

void Camera::moveRight() {
  anchor += sideDirection() * rateOfMovement;
}

/**
 * Getters
 */

float Camera::getX() const {
  return position.x;
}

float Camera::getY() const {
  return position.y;
}

float Camera::getZ() const {
  return position.z;
}

float Camera::anchorX() const {
  return anchor.x;
}

float Camera::anchorY() const {
  return anchor.y;
}

float Camera::anchorZ() const {
  return anchor.z;
}

float Camera::atX() const {
  return lookAt.x;
}

float Camera::atY() const {
  return lookAt.y;
}

float Camera::atZ() const {
  return lookAt.z;
}

float Camera::totalXAngle() const {
  return totXAngle;
}

float Camera::totalYAngle() const {
  return totYAngle;
}
