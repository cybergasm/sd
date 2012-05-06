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

#include "KeySequence.h"
#include "InputEvent.h"

using namespace std;

class InputProcessor {
	public:

		InputProcessor();
		virtual ~InputProcessor();

		/**
		 * Binds the InputEvent evnt to the sequence of inputs
		 * specified by inputs.
		 *
		 * Overwrites any previous bindings.
		 */
		void bind(const InputEvent& evnt, const KeySequence& sequence);


		/**
		 * Overload for single key
		 */
		void bind(const InputEvent& evnt, const InputEvent::Inputs & input);
	private:
		map<KeySequence, InputEvent > eventBinding;
		map<InputEvent::Inputs, set<KeySequence> > sequenceBinding;
};

#endif /* INPUTPROCESSOR_H_ */
