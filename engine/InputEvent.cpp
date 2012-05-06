/*
 * InputEvent.cpp
 *
 *  Created on: May 5, 2012
 *      Author: emint
 */

#include "InputEvent.h"

InputEvent::InputEvent(string eventName_) : eventName(eventName_){
	// TODO Auto-generated constructor stub

}

InputEvent::~InputEvent() {
	// TODO Auto-generated destructor stub
}

bool InputEvent::operator <(const InputEvent& b) const {
	return this->eventName < b.getEventName();
}

bool InputEvent::operator ==(const InputEvent& b) const {
	return this->eventName == b.getEventName();
}

string InputEvent::getEventName() const{
	return eventName;
}
