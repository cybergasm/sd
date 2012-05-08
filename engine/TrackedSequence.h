/*
 * TrackedSequence.h
 *
 * This keeps track of the initial sequence and our position
 * in it. This allows us to progress through the sequence but preserve
 * the original to find the corresponding event

 *
 *  Created on: May 8, 2012
 *      Author: emint
 */

#ifndef TRACKEDSEQUENCE_H_
#define TRACKEDSEQUENCE_H_

#include "KeySequence.h"

class TrackedSequence {
	public:
		TrackedSequence();
		TrackedSequence(KeySequence seq, int pos);
		virtual ~TrackedSequence();

		bool operator<(const TrackedSequence& b) const;
		bool operator==(const TrackedSequence& b) const;

		/**
		 * Setters and getters
		 */
		KeySequence getSequence() const;
		int getPosition() const;

		void setSequence(KeySequence sequence);
		void setPosition(int position);
	private:
		KeySequence sequence;
		int position;
};

#endif /* TRACKEDSEQUENCE_H_ */
