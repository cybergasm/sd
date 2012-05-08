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
#include <set>

// SFML automatically includes SDL headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "KeySequence.h"
#include "InputEvent.h"
#include "TrackedSequence.h"

using namespace std;

class InputProcessor {
	public:

		InputProcessor(sf::Window* window);
		virtual ~InputProcessor();

		/**
		 * Binds the InputEvent evnt to the sequence of inputs
		 * specified by inputs.
		 *
		 * Overwrites any previous bindings.
		 */
		void bind(const KeySequence& sequence, const InputEvent& evnt);

		/**
		 * Checks for new input and returns any input events it finds.
		 */
		set<InputEvent> getEvents();

	private:
		//The window since we use the sf library
		sf::Window* window;

		//the binding of sequence to event to fire when sequence complete
		map<KeySequence, InputEvent> eventBinding;
		//the binding of input to sequences it starts
		map<InputEvent::Inputs, set<KeySequence> > sequenceBinding;
		//the binding of input to sequences that are currently waiting on it
		map<InputEvent::Inputs, set<TrackedSequence> > currentlyTrackedSequences;

		//this method processes input and returns the events that are
		//to be fired
		set<InputEvent> processNewInput();

		//Performs changes necessary for detecting a new input. Takes the set into which to
		//place the input. This saves us time later reiterating a returned set to add it
		//to the master list.
		void newInput(InputEvent::Inputs input, set<InputEvent>& inputEvents);

		//Handles sequence that start with this input
		void handleNewSequences(InputEvent::Inputs input,
		    set<InputEvent>& inputEvents);

		//Tries to extend events waiting on this input
		void addToExistingSequences(InputEvent::Inputs input,
		    set<InputEvent>& inputEvents);
};

#endif /* INPUTPROCESSOR_H_ */
