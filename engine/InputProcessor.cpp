/*
 * InputProcessor.cpp
 *
 *  Created on: May 5, 2012
 *      Author: emint
 */

#include "InputProcessor.h"

InputProcessor::InputProcessor() {
	// TODO Auto-generated constructor stub

}

InputProcessor::~InputProcessor() {
	// TODO Auto-generated destructor stub
}

void InputProcessor::bind(const InputEvent& evnt, const KeySequence& sequence) {
	set<KeySequence>& currentBindings = sequenceBinding[sequence.inputAt(0)];
	currentBindings.insert(sequence);
	eventBinding.insert(pair<KeySequence, InputEvent>(sequence, evnt));
}

void InputProcessor::bind(const InputEvent& evnt, const InputEvent::Inputs& input) {
	KeySequence inputVec(input);
	bind(evnt, inputVec);
}
