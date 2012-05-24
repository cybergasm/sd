/*
 * KeyMovement.h
 *
 *  Created on: May 9, 2012
 *      Author: emint
 */

#ifndef KEYMOVEMENT_H_
#define KEYMOVEMENT_H_

#include "engine/InputEvent.h"
#include "engine/Camera.h"


class KeyMovement: public InputEvent {
	public:
		KeyMovement(Camera* camera);
		virtual ~KeyMovement();

		bool action(InputEvent::Inputs input, int mouseX, int mouseY);
	private:
		Camera* camera;
};

#endif /* KEYMOVEMENT_H_ */
