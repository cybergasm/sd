/*
 * LightMovementEvent.cpp
 *
 *  Created on: May 29, 2012
 *      Author: emint
 */

#include "LightMovementEvent.h"

LightMovementEvent::LightMovementEvent(GLfloat* lightPos_) :
  InputEvent("lightMovement"), lightPos(lightPos_) {
}

LightMovementEvent::~LightMovementEvent() {
}

bool LightMovementEvent::action(InputEvent::Inputs input, int mouseX,
    int mouseY) {
  bool moved = false;
  if (input == InputEvent::KeyI) {
    lightPos[2] += .1;
    moved = true;
  } else if (input == InputEvent::KeyJ) {
    lightPos[0] -= .1;
    moved = true;
  } else if (input == InputEvent::KeyK) {
    lightPos[2] -= .1;
    moved = true;
  } else if (input == InputEvent::KeyL) {
    lightPos[0] += .1;
    moved = true;
  }
  return moved;
}
