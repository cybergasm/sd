/*
 * InputResponder.cpp
 *
 *  Created on: Apr 13, 2012
 *      Author: emint
 */

#include "InputResponder.h"

InputResponder::InputResponder() {
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

void InputResponder::inputIs(sf::Event event) {
  switch (event.Type) {
    case sf::Event::Closed:
      // Close the window we are rendering to.
      window->Close();
      break;
    case sf::Event::KeyPressed:
      /**
       * Movement
       */
      float degreesToRadians = M_PI / 180;
      if (event.Key.Code == sf::Key::W) {
        character->move(aiVector3D(camera->atX()*-.1, 0, camera->atZ()*-.1));
      } else if (event.Key.Code == sf::Key::S) {
        character->move(aiVector3D(camera->atX()*.1, 0, camera->atZ()*.1));
      } else if (event.Key.Code == sf::Key::A) {
        character->move(aiVector3D(camera->sideDirection().x*-.1, 0, camera->sideDirection().z*.1));
      } else if (event.Key.Code == sf::Key::D) {
        character->move(aiVector3D(camera->sideDirection().x*.1, 0, camera->sideDirection().z*.1));
      } else if (event.Key.Code == sf::Key::U) {
        camera->rotateAroundAngle(0, -degreesToRadians);
      } else if (event.Key.Code == sf::Key::J) {
        camera->rotateAroundAngle(0, degreesToRadians);
      } else if (event.Key.Code == sf::Key::H) {
        camera->rotateAroundAngle(degreesToRadians, 0);
      } else if (event.Key.Code == sf::Key::K) {
        camera->rotateAroundAngle(-degreesToRadians, 0);
      }
      break;
  }
}
