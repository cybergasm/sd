/*
 * InputProcessor.cpp
 *
 *  Created on: May 5, 2012
 *      Author: emint
 */

#include "InputProcessor.h"

InputProcessor::InputProcessor(RenderingWindow* window_) :
	window(window_) {
	// TODO Auto-generated constructor stub

}

InputProcessor::~InputProcessor() {
	// TODO Auto-generated destructor stub
}

void InputProcessor::bind(const KeySequence& sequence, InputEvent* evnt) {
	const vector<InputEvent::Inputs>& inputs = sequence.getSequence();
	for (vector<InputEvent::Inputs>::const_iterator iter = inputs.begin(); iter
	    != inputs.end(); ++iter) {
		vector<InputEvent*>& associatedEvents = inputToEventBinding[*iter];
		associatedEvents.push_back(evnt);
	}
}

void InputProcessor::bindAll(InputEvent* evnt) {
	nondiscriminatoryEvents.push_back(evnt);
}

set<InputEvent*> InputProcessor::getEvents() {
	return processNewInput();
}


void InputProcessor::notifyRegistered(InputEvent::Inputs input,
    set<InputEvent*>& inputEvents) {
	vector<InputEvent*>& associatedEvents = inputToEventBinding[input];
	for (vector<InputEvent*>::iterator iter = associatedEvents.begin(); iter
	    != associatedEvents.end(); ++iter) {
		if ((*iter)->action(input)) {
			inputEvents.insert(*iter);
		}
	}
}

void InputProcessor::notifyNondiscriminatory(InputEvent::Inputs input,
    set<InputEvent*>& inputEvents) {
	for (vector<InputEvent*>::iterator iter = nondiscriminatoryEvents.begin(); iter
	    != nondiscriminatoryEvents.end(); ++iter) {
		if ((*iter)->action(input)) {
			inputEvents.insert(*iter);
		}
	}
}

void InputProcessor::newInput(InputEvent::Inputs input,
    set<InputEvent*>& inputEvents) {
	notifyRegistered(input, inputEvents);
	notifyNondiscriminatory(input, inputEvents);
}

set<InputEvent*> InputProcessor::processNewInput() {
	set<InputEvent*> events;
	vector<InputEvent::Inputs> inputs = window->getEvents();
	for (vector<InputEvent::Inputs>::iterator iter = inputs.begin(); iter
	    != inputs.end(); ++iter) {
		newInput(*iter, events);
	}
	return events;
}

