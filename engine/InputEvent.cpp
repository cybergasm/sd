/*
 * InputEvent.cpp
 *
 *  Created on: May 5, 2012
 *      Author: emint
 */

#include "InputEvent.h"
#include <iostream>

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

bool InputEvent::action(Inputs trigger, int mouseX, int mouseY) {
	std::cout<<"Default nop action."<<std::endl;
	return true;
}
