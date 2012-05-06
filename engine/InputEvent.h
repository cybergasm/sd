/*
 * InputEvent.h
 *
 *  Created on: May 5, 2012
 *      Author: emint
 */

#ifndef INPUTEVENT_H_
#define INPUTEVENT_H_

#include <string>

using namespace std;


class InputEvent {
	public:
		InputEvent(string eventName_);
		virtual ~InputEvent();

		bool operator<(const InputEvent& b) const;
		bool operator==(const InputEvent& b) const;
		/**
		 * Returns the string name
		 */
		string getEventName() const;
	private:
		string eventName;
};

#endif /* INPUTEVENT_H_ */
