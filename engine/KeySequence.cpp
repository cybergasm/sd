/*
 * KeySequence.cpp
 *
 *  Created on: May 6, 2012
 *      Author: emint
 */

#include "KeySequence.h"

KeySequence::KeySequence() {
	// TODO Auto-generated constructor stub

}

KeySequence::KeySequence(InputEvent::Inputs input) {
	sequence.push_back(input);
}

KeySequence::~KeySequence() {
	// TODO Auto-generated destructor stub
}

void KeySequence::add(InputEvent::Inputs input) {
	sequence.push_back(input);
}

bool KeySequence::operator <(const KeySequence& b) const{
	return sequence < b.getSequence();
}

bool KeySequence::operator ==(const KeySequence& b) const{
	return sequence == b.getSequence();
}

InputEvent::Inputs KeySequence::inputAt(int index) const {
	return sequence.at(index);
}

vector<InputEvent::Inputs> KeySequence::getSequence() const{
	return sequence;
}
