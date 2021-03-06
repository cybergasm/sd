/*
 * InputResponder.cpp
 *
 *  Created on: Apr 13, 2012
 *      Author: emint
 */

#include "InputResponder.h"
#include "CloseWindowEvent.h"
#include "KeyMovement.h"
#include "MouseLookEvent.h"
#include "PostprocessParameterInputEvent.h"


InputResponder::InputResponder(RenderingWindow* window, Character* character,
    Camera* camera, BloomFilterEffect* bloom, LuminanceFilterEffect* luminance) : inputProc(window){

	//Wire up the event to close window
	CloseWindowEvent* cWindow = new CloseWindowEvent(window);
	inputProc.bind(KeySequence(InputEvent::WinClosed), cWindow);

	//Wire up the event to move the character along the axis
	KeyMovement* movement = new KeyMovement(character, camera);
	KeySequence movementKeys;
	movementKeys.add(InputEvent::KeyW);
	movementKeys.add(InputEvent::KeyA);
	movementKeys.add(InputEvent::KeyS);
	movementKeys.add(InputEvent::KeyD);
	inputProc.bind(movementKeys, movement);

	//Wire up the mouse to rotate view
	MouseLookEvent* mouseLook = new MouseLookEvent(character, window, camera);
	inputProc.bind(KeySequence(InputEvent::MouseMove), mouseLook);

	//Wire up the postprocesseffects controller
	PostprocessParameterInputEvent* pprocessInputs = new PostprocessParameterInputEvent(bloom, luminance);
	KeySequence paramKeys;
	paramKeys.add(InputEvent::Key1);
	paramKeys.add(InputEvent::Key2);
	paramKeys.add(InputEvent::Key3);
	paramKeys.add(InputEvent::Key4);
	inputProc.bind(paramKeys, pprocessInputs);
}

InputResponder::~InputResponder() {
	// TODO Auto-generated destructor stub
}

void InputResponder::processEvents() {
	set<InputEvent*> events = inputProc.getEvents();
}
