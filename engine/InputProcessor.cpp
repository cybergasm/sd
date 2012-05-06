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

void InputProcessor::bind(const InputEvent& evnt, const vector<Inputs>& sequence) {
	keyBindings[evnt] = sequence;
}

void InputProcessor::bind(const InputEvent& evnt, const Inputs& input) {
	vector<Inputs> inputVec;
	inputVec.push_back(input);
	bind(evnt, inputVec);
}
