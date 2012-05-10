/*
 * KeyMovement.cpp
 *
 *  Created on: May 9, 2012
 *      Author: emint
 */

#include "KeyMovement.h"

KeyMovement::KeyMovement(Character* character_, Camera* camera_) :
	InputEvent("KeyMove"), character(character_), camera(camera_) {
	// TODO Auto-generated constructor stub

}

KeyMovement::~KeyMovement() {
	// TODO Auto-generated destructor stub
}

bool KeyMovement::action(InputEvent::Inputs input) {
	bool moved = false;
	if (input == InputEvent::KeyW) {
		character->move(aiVector3D(camera->atX(), 0, camera->atZ()));
		moved = true;
	} else if (input == InputEvent::KeyA) {
		character->move(
		    aiVector3D(camera->sideDirection().x * -1, 0,
		        camera->sideDirection().z * -1));
		moved = true;
	} else if (input == InputEvent::KeyS) {
		character->move(aiVector3D(camera->atX() * -1, 0, camera->atZ() * -1));
		moved = true;
	} else if (input == InputEvent::KeyD) {
		character->move(
		    aiVector3D(camera->sideDirection().x, 0, camera->sideDirection().z));
		moved = true;
	}
	camera->setAnchor(character->getPos());
	return moved;
}
