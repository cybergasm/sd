/*
 * InputResponder.cpp
 *
 *  Created on: Apr 13, 2012
 *      Author: emint
 */

#include "InputResponder.h"

InputResponder::InputResponder() :
  mouseReady(false) {
  // TODO Auto-generated constructor stub

}

InputResponder::~InputResponder() {
  // TODO Auto-generated destructor stub
}

void InputResponder::characterIs(Character* character_) {
  character = character_;
}

void InputResponder::cameraIs(Camera* camera_) {
  camera = camera_;
}

void InputResponder::windowIs(sf::Window* window_) {
  window = window_;
}

void InputResponder::mouseMoved(int mouseX, int mouseY) {
  float deltaX = mouseX - 0.5f * window->GetWidth();
  float deltaY = mouseY - 0.5f * window->GetHeight();
  camera->rotateIncrementally(-1 * deltaX, -1 * deltaY);
  window->SetCursorPosition(0.5f * window->GetWidth(),
      0.5f * window->GetHeight());
}

void InputResponder::inputIs(sf::Event event) {
  switch (event.Type) {
    case sf::Event::Closed:
      // Close the window we are rendering to.
      window->Close();
      break;
    case sf::Event::KeyPressed:
      /**
       * Key movement, moves character forward and then sets the camera
       * to be anchored to new position
       */
      if (event.Key.Code == sf::Key::W) {
        character->move(aiVector3D(camera->atX() * -1, 0, camera->atZ() * -1));
      } else if (event.Key.Code == sf::Key::S) {
        character->move(aiVector3D(camera->atX(), 0, camera->atZ()));
      } else if (event.Key.Code == sf::Key::A) {
        character->move(
            aiVector3D(camera->sideDirection().x * -1, 0,
                camera->sideDirection().z));
      } else if (event.Key.Code == sf::Key::D) {
        character->move(
            aiVector3D(camera->sideDirection().x, 0, camera->sideDirection().z));
      } else if (event.Key.Code == sf::Key::Space) {
        character->move(
                    aiVector3D(0, -.3, 0));
      } else if (event.Key.Code == sf::Key::V) {
        character->move(
                    aiVector3D(0, .3, 0));
      }
      camera->setAnchor(character->getPos());
      break;
    case sf::Event::MouseMoved:
      /**
       * Mouse movement rotates the camera around the camera and then
       * tells the character of the new x-rotation so we can rotate it
       * so its back is to the camera
       */
      if (window->GetInput().IsMouseButtonDown(sf::Mouse::Left)) {
        if (!mouseReady) {
          window->SetCursorPosition(0.5f * window->GetWidth(),
              0.5f * window->GetHeight());
          mouseReady = true;
        } else {
          mouseMoved(event.MouseMove.X, event.MouseMove.Y);
        }
      } else {
        mouseReady = false;
      }
      character->setCameraRotation(camera->totalXAngle() * (180.0f / M_PI));
      break;
  }
}
