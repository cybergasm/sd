/*
 * MouseLookEvent.cpp
 *
 *  Created on: May 10, 2012
 *      Author: emint
 */

#include "MouseLookEvent.h"
#include <iostream>
MouseLookEvent::MouseLookEvent(RenderingWindow* window_, Camera* camera_) :
  InputEvent("MouseLook"), window(window_), camera(camera_), mouseReady(true) {
}

MouseLookEvent::~MouseLookEvent() {
  // TODO Auto-generated destructor stub
}

bool MouseLookEvent::action(InputEvent::Inputs input, int mouseX, int mouseY) {
  //We move if the mouse button is also pressed
  if (window->isMouseDown(InputEvent::LMouse)) {
    //check if we have to reset mouse to middle so
    //measurement is always from center
    if (!mouseReady) {
      //if so, reset it
      window->setCursorPosition(0.5f * window->getWidth(),
          0.5f * window->getHeight());
      mouseReady = true;
    } else {
      //if not, figure out what the offset is
      float deltaX = mouseX - 0.5f * window->getWidth();
      float deltaY = mouseY - 0.5f * window->getHeight();
      camera->rotateIncrementally(deltaX, deltaY);
      window->setCursorPosition(0.5f * window->getWidth(),
          0.5f * window->getHeight());
    }
  } else {
    mouseReady = false;
  }
  return mouseReady;
}
