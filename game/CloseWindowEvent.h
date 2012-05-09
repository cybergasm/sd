/*
 * CloseWindowEvent.h
 *
 *  Created on: May 8, 2012
 *      Author: emint
 */

#ifndef CLOSEWINDOWEVENT_H_
#define CLOSEWINDOWEVENT_H_

#include "engine/InputEvent.h"
#include "engine/RenderingWindow.h"

class CloseWindowEvent: public InputEvent {
	public:
		CloseWindowEvent(RenderingWindow* window);
		virtual ~CloseWindowEvent();

		//Closes window
		bool action(Inputs input);

	private:
		RenderingWindow* window;
};

#endif /* CLOSEWINDOWEVENT_H_ */
