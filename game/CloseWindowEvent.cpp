/*
 * CloseWindowEvent.cpp
 *
 *  Created on: May 8, 2012
 *      Author: emint
 */

#include "CloseWindowEvent.h"

CloseWindowEvent::CloseWindowEvent(RenderingWindow* window_) :
	InputEvent("CloseWindow"), window(window_) {
	// TODO Auto-generated constructor stub

}

CloseWindowEvent::~CloseWindowEvent() {
	// TODO Auto-generated destructor stub
}

bool CloseWindowEvent::action(Inputs input) {
	window->close();
	return true;
}
