/*
 * KeyMovement.cpp
 *
 *  Created on: May 9, 2012
 *      Author: emint
 */

#include "KeyMovement.h"

KeyMovement::KeyMovement(Camera* camera_) :
	InputEvent("KeyMove"), camera(camera_) {
	// TODO Auto-generated constructor stub

}

KeyMovement::~KeyMovement() {
	// TODO Auto-generated destructor stub
}

bool KeyMovement::action(InputEvent::Inputs input, int mouseX, int mouseY) {
	bool moved = false;
	if (input == InputEvent::KeyW) {
	  camera->moveForward();
	  moved = true;
	} else if (input == InputEvent::KeyA) {
	  camera->moveLeft();
	  moved = true;
	} else if (input == InputEvent::KeyS) {
	  camera->moveBackwards();
	  moved = true;
	} else if (input == InputEvent::KeyD) {
	  camera->moveRight();
	  moved = true;
	} else if (input == InputEvent::Space) {
	  camera->moveUp();
	  moved = true;
	} else if (input == InputEvent::KeyV) {
	  camera->moveDown();
	  moved = true;
	}
	return moved;
}
