/*
 * MouseLookEvent.h
 *
 *  Created on: May 10, 2012
 *      Author: emint
 */

#ifndef MOUSELOOKEVENT_H_
#define MOUSELOOKEVENT_H_

#include "engine/InputEvent.h"
#include "engine/RenderingWindow.h"
#include "engine/Camera.h"
#include "engine/InputEvent.h"

class MouseLookEvent: public InputEvent {
	public:
		MouseLookEvent(RenderingWindow* window,
		    Camera* camera);
		virtual ~MouseLookEvent();

		bool action(InputEvent::Inputs, int mouseX, int mouseY);
	private:
		/**
		 * We need the window to get mouse state, and camera to update
		 * camera rotation.
		 */
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
