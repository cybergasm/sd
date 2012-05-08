/*
 * TrackedSequence.cpp
 *
 *  Created on: May 8, 2012
 *      Author: emint
 */

#include "TrackedSequence.h"

TrackedSequence::TrackedSequence() {
	// TODO Auto-generated constructor stub

}

TrackedSequence::TrackedSequence(KeySequence seq, int pos) : sequence(seq), position(pos) {
	// TODO Auto-generated constructor stub

}

TrackedSequence::~TrackedSequence() {
	// TODO Auto-generated destructor stub
}


void TrackedSequence::setSequence(KeySequence sequence_) {
	sequence = sequence_;
}

void TrackedSequence::setPosition(int position_) {
	position = position_;
}

KeySequence TrackedSequence::getSequence() const{
	return sequence;
}

int TrackedSequence::getPosition() const{
	return position;
}

bool TrackedSequence::operator <(const TrackedSequence& b) const{
	return sequence < b.getSequence() || (sequence == b.getSequence() && position < b.getPosition());
}

bool TrackedSequence::operator ==(const TrackedSequence& b) const {
	return sequence == b.getSequence() && position == b.getPosition();
}
