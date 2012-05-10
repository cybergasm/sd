/*
 * InputResponder.cpp
 *
 *  Created on: Apr 13, 2012
 *      Author: emint
 */

#include "InputResponder.h"
#include "CloseWindowEvent.h"
#include "KeyMovement.h"

InputResponder::InputResponder(RenderingWindow* window_, Character* character_,
    Camera* camera_) :
	character(character_), camera(camera_), window(window_), inputProc(window) {
	CloseWindowEvent* cWindow = new CloseWindowEvent(window);
	inputProc.bind(KeySequence(InputEvent::WinClosed), cWindow);
	KeyMovement* movement = new KeyMovement(character, camera);
	KeySequence movementKeys;
	movementKeys.add(InputEvent::KeyW);
	movementKeys.add(InputEvent::KeyA);
	movementKeys.add(InputEvent::KeyS);
	movementKeys.add(InputEvent::KeyD);
	inputProc.bind(movementKeys, movement);
}

InputResponder::~InputResponder() {
	// TODO Auto-generated destructor stub
}

void InputResponder::processEvents() {
	set<InputEvent*> events = inputProc.getEvents();
	for (set<InputEvent*>::iterator iter = events.begin(); iter != events.end(); ++iter) {
		cout << (*iter)->getEventName() << endl;
	}
}

void InputResponder::mouseMoved(int mouseX, int mouseY) {
	float deltaX = mouseX - 0.5f * window->getWidth();
	float deltaY = mouseY - 0.5f * window->getHeight();
	camera->rotateIncrementally(deltaX, deltaY);
	window->setCursorPosition(0.5f * window->getWidth(),
	    0.5f * window->getHeight());
}

void InputResponder::inputIs(sf::Event event) {

	switch (event.Type) {
		case sf::Event::Closed:
			// Close the window we are rendering to.
			window->close();
			break;
		case sf::Event::KeyPressed:
			/**
			 * Key movement, moves character forward and then sets the camera
			 * to be anchored to new position
			 */
			if (event.Key.Code == sf::Key::W) {
				character->move(aiVector3D(camera->atX(), 0, camera->atZ()));
			} else if (event.Key.Code == sf::Key::S) {
				character->move(aiVector3D(camera->atX() * -1, 0, camera->atZ() * -1));
			} else if (event.Key.Code == sf::Key::A) {
				character->move(
				    aiVector3D(camera->sideDirection().x * -1, 0,
				        camera->sideDirection().z * -1));
			} else if (event.Key.Code == sf::Key::D) {
				character->move(
				    aiVector3D(camera->sideDirection().x, 0, camera->sideDirection().z));
			} else if (event.Key.Code == sf::Key::Space) {
				character->move(aiVector3D(0, -.3, 0));
			} else if (event.Key.Code == sf::Key::V) {
				character->move(aiVector3D(0, .3, 0));
			} else if (event.Key.Code == sf::Key::J) {

			}
			camera->setAnchor(character->getPos());
			break;
		case sf::Event::MouseMoved:
			/**
			 * Mouse movement rotates the camera around the camera and then
			 * tells the character of the new x-rotation so we can rotate it
			 * so its back is to the camera
			 */
			if (window->isMouseDown(InputEvent::LMouse)) {
				if (!mouseReady) {
					window->setCursorPosition(0.5f * window->getWidth(),
					    0.5f * window->getHeight());
					mouseReady = true;
				} else {
					mouseMoved(event.MouseMove.X, event.MouseMove.Y);
				}
			} else {
				mouseReady = false;
			}
			character->setCameraRotation(camera->totalXAngle() * (180.0f / M_PI));
			break;
	}
}
