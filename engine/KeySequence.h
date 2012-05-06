/*
 * KeySequence.h
 *
 *  Created on: May 6, 2012
 *      Author: emint
 */

#ifndef KEYSEQUENCE_H_
#define KEYSEQUENCE_H_

#include <vector>

#include "InputEvent.h"

using namespace std;

class KeySequence {
	public:
		KeySequence();
		KeySequence(InputEvent::Inputs input);
		virtual ~KeySequence();

		bool operator<(const KeySequence& b) const;
	  bool operator==(const KeySequence& b) const;

		/**
		 * Adds a key to the sequence
		 */
		void add(InputEvent::Inputs input);

		/**
		 * Returns the sequence
		 */
		vector<InputEvent::Inputs> getSequence() const;

		/**
		 * Returns the input at specified sequence
		 */
		InputEvent::Inputs inputAt(int index) const;
	private:
		vector<InputEvent::Inputs> sequence;
};

#endif /* KEYSEQUENCE_H_ */
