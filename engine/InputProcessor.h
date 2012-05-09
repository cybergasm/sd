/*
 * InputProcessor.h
 *
 *  Created on: May 5, 2012
 *      Author: emint
 */

#ifndef INPUTPROCESSOR_H_
#define INPUTPROCESSOR_H_

#include <map>
#include <string.h>
#include <vector>

#include "KeySequence.h"
#include "InputEvent.h"
#include "TrackedSequence.h"
#include "RenderingWindow.h"

using namespace std;

class InputProcessor {
	public:

		InputProcessor(RenderingWindow* window);
		virtual ~InputProcessor();

		/**
		 * Binds the InputEvent evnt to the sequence of inputs
		 * specified by inputs.
		 *
		 * Overwrites any previous bindings.
		 */
		void bind(const KeySequence& sequence, InputEvent* evnt);

		/**
		 * Binds a key to all inputs
		 */
		void bindAll(InputEvent* evnt);

		/**
		 * Checks for new input and returns any input events it finds.
		 */
		set<InputEvent*> getEvents();

	private:
		//The window since we use the sf library
		RenderingWindow* window;

		//The binding of input to events in whose key-sequence it belongs
		map<InputEvent::Inputs, vector<InputEvent*> > inputToEventBinding;

		//The events that want to know about every input
		vector<InputEvent*> nondiscriminatoryEvents;

		//This method processes input and returns the events that are
		//to be fired
		set<InputEvent*> processNewInput();

		//Performs changes necessary for detecting a new input. Takes the set into which to
		//place the input. This saves us time later reiterating a returned set to add it
		//to the master list.
		void newInput(InputEvent::Inputs input, set<InputEvent*>& inputEvents);

		//Notifies events which have input as part of their sequence, and adds them to the set
		//if they say they have fired.
		void notifyRegistered(InputEvent::Inputs input, set<InputEvent*>& inputEvents);

		//Notifies all the nondiscriminatory events and adds them to the set if they note that
		//they have fired.
		void notifyNondiscriminatory(InputEvent::Inputs input, set<InputEvent*>& inputEvents);
};

#endif /* INPUTPROCESSOR_H_ */
