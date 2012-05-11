/*
 * MouseLookEvent.h
 *
 *  Created on: May 10, 2012
 *      Author: emint
 */

#ifndef MOUSELOOKEVENT_H_
#define MOUSELOOKEVENT_H_

#include "engine/InputEvent.h"
#include "Character.h"
#include "engine/RenderingWindow.h"
#include "engine/Camera.h"
#include "engine/InputEvent.h"

class MouseLookEvent: public InputEvent {
	public:
		MouseLookEvent(Character* character, RenderingWindow* window,
		    Camera* camera);
		virtual ~MouseLookEvent();

		bool action(InputEvent::Inputs, int mouseX, int mouseY);
	private:
		/**
		 * We need all three to update the character, get mouse state, and update
		 * camera rotation.
		 */
		Character* character;
		RenderingWindow* window;
		Camera* camera;

		/**
		 * State variable to tell us if we are ready to move mouse,
		 * namely ensures we center it between moves so we get
		 * a constant measure of how much it has moved
		 */
		bool mouseReady;
};

#endif /* MOUSELOOKEVENT_H_ */
