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


#include "InputEvent.h"

using namespace std;

class InputProcessor {
	public:

		/**
		 * Exported keys the user could input
		 */
		enum Inputs {
			KeyA,
			KeyB,
			KeyC,
			KeyD,
			KeyE,
			KeyF,
			KeyG,
			KeyH,
			KeyI,
			KeyJ,
			KeyK,
			KeyL,
			KeyM,
			KeyN,
			KeyO,
			KeyP,
			KeyQ,
			KeyR,
			KeyS,
			KeyT,
			KeyU,
			KeyV,
			KeyW,
			KeyX,
			KeyY,
			KeyZ,
			Key1,
			Key2,
			Key3,
			Key4,
			Key5,
			Key6,
			Key7,
			Key8,
			Key9,
			KeyEnter
		};

		InputProcessor();
		virtual ~InputProcessor();

		/**
		 * Binds the InputEvent evnt to the sequence of inputs
		 * specified by inputs.
		 *
		 * Overwrites any previous bindings.
		 */
		void bind(const InputEvent& evnt, const vector<Inputs>& sequence);


		/**
		 * Overload for single key
		 */
		void bind(const InputEvent& evnt, const Inputs& input);
	private:
		map<InputEvent, vector<Inputs> > keyBindings;

};

#endif /* INPUTPROCESSOR_H_ */
