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
      if (event.Key.Code == sf::Key::W) {
        character->move(aiVector3D(0, 0, -.05));
      } else if (event.Key.Code == sf::Key::S) {
        character->move(aiVector3D(0, 0, .05));
      } else if (event.Key.Code == sf::Key::A) {
        character->move(aiVector3D(-.05, 0, 0));
      } else if (event.Key.Code == sf::Key::D) {
        character->move(aiVector3D(.05, 0, 0));
      }
      break;
  }
}
