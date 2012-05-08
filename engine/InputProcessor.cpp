/*
 * InputProcessor.cpp
 *
 *  Created on: May 5, 2012
 *      Author: emint
 */

#include "InputProcessor.h"

InputProcessor::InputProcessor(sf::Window* window_) :
	window(window_) {
	// TODO Auto-generated constructor stub

}

InputProcessor::~InputProcessor() {
	// TODO Auto-generated destructor stub
}

void InputProcessor::bind(const KeySequence& sequence, const InputEvent& evnt) {
	set<KeySequence>& currentBindings = sequenceBinding[sequence.inputAt(0)];
	currentBindings.insert(sequence);
	eventBinding.insert(pair<KeySequence, InputEvent> (sequence, evnt));
}

set<InputEvent> InputProcessor::getEvents() {
	return processNewInput();
}

void InputProcessor::handleNewSequences(InputEvent::Inputs input,
    set<InputEvent>& inputEvents) {
	map<InputEvent::Inputs, set<KeySequence> >::iterator newSeqIter =
	    sequenceBinding.find(input);
	//Get the sequences this input starts
	set<KeySequence> newSequences = newSeqIter->second;
	//Go through all the sequences this iput starts
	for (set<KeySequence>::iterator iter = newSequences.begin(); iter
	    != newSequences.end(); ++iter) {
		//if this sequence is just this input, do the event
		if (iter->length() == 1) {
			map<KeySequence, InputEvent>::iterator inEvent = eventBinding.find(*iter);
			if (inEvent != eventBinding.end()) {
				inputEvents.insert(inEvent->second);
			}
		} else {
			//if there is more. make a tracked event and store it
			TrackedSequence newSequence(*iter, 1);
			//insert the event at the key following the first
			set<TrackedSequence>& trackedSequences =
			    currentlyTrackedSequences[iter->inputAt(1)];
			trackedSequences.insert(newSequence);
		}
	}
}

void InputProcessor::addToExistingSequences(InputEvent::Inputs input,
    set<InputEvent>& inputEvents) {
	map<InputEvent::Inputs, set<TrackedSequence> >::iterator
	    dependentSequencesItr = currentlyTrackedSequences.find(input);

	//check if there are any depending on this input
	if (dependentSequencesItr == currentlyTrackedSequences.end()) {
		return;
	}

	//get all that depend
	set<TrackedSequence> dependentSequences = dependentSequencesItr->second;

	//we might have the same input twice in a row. If this is the case we
	//need to explicitly re-insert the events, as we have to avoid changing
	//the set while we iterate
	set<TrackedSequence> doubleInput;

	//iterate through all those that depend
	for (set<TrackedSequence>::iterator iter = dependentSequences.begin(); iter
	    != dependentSequences.end(); ++iter) {
		//if we are at the last position, get the corresponding event since this will consume it
		if (iter->getPosition() == (iter->getSequence().length() - 1)) {
			map<KeySequence, InputEvent>::iterator inEvent = eventBinding.find(iter->getSequence());
			if (inEvent != eventBinding.end()) {
				inputEvents.insert(inEvent->second);
			}
		}
		//get sequence
		TrackedSequence newSeq = *iter;
		int newPosition = iter->getPosition() + 1;
		newSeq.setPosition(newPosition);
		InputEvent::Inputs newInput = newSeq.getSequence().inputAt(newPosition);
		//see if next input is this same input
		if (newInput != input) {
			set<TrackedSequence>& newTracked = currentlyTrackedSequences[newSeq.getSequence().inputAt(newPosition)];
			newTracked.insert(newSeq);
		} else {
			//if it is, save it to re-insert at end.
			doubleInput.insert(newSeq);
		}
	}
	//remove the dependent events
	currentlyTrackedSequences.erase(input);
	//add any dependent on same input
	if (doubleInput.size() != 0) {
		currentlyTrackedSequences[input] = doubleInput;
	}
}

void InputProcessor::newInput(InputEvent::Inputs input,
    set<InputEvent>& inputEvents) {
	map<InputEvent::Inputs, set<KeySequence> >::iterator newSeqIter =
	    sequenceBinding.find(input);

	//If we do not have any bindings for this sequence
	if (newSeqIter == sequenceBinding.end()) {
		return;
	}

	//order of calls here is actually important. We want to handle
	//any pre-existing sequences first so that we don't double count the
	//input for the sequences we start. Say you have an event 'W W' and the
	//key W is pressed. Then in the opposite order you add 'W W' to the
	//sequences to extend and then extend it. Order dependence could be
	//avoided but it would require more state tracking.
	addToExistingSequences(input, inputEvents);
	handleNewSequences(input, inputEvents);
}

set<InputEvent> InputProcessor::processNewInput() {
	sf::Event evt;
	set<InputEvent> events;
	while (window->GetEvent(evt)) {
		switch (evt.Type) {
			case sf::Event::Closed:
				// return that the window needs to be closed
				events.insert(InputEvent("WindowClose"));
				break;
			case sf::Event::KeyPressed:
				if (evt.Key.Code == sf::Key::A) {
					newInput(InputEvent::KeyA, events);
				} else if (evt.Key.Code == sf::Key::B) {
					newInput(InputEvent::KeyB, events);
				} else if (evt.Key.Code == sf::Key::C) {
					newInput(InputEvent::KeyC, events);
				} else if (evt.Key.Code == sf::Key::D) {
					newInput(InputEvent::KeyD, events);
				} else if (evt.Key.Code == sf::Key::E) {
					newInput(InputEvent::KeyE, events);
				} else if (evt.Key.Code == sf::Key::F) {
					newInput(InputEvent::KeyF, events);
				} else if (evt.Key.Code == sf::Key::G) {
					newInput(InputEvent::KeyG, events);
				} else if (evt.Key.Code == sf::Key::H) {
					newInput(InputEvent::KeyH, events);
				} else if (evt.Key.Code == sf::Key::I) {
					newInput(InputEvent::KeyI, events);
				} else if (evt.Key.Code == sf::Key::J) {
					newInput(InputEvent::KeyJ, events);
				} else if (evt.Key.Code == sf::Key::K) {
					newInput(InputEvent::KeyK, events);
				} else if (evt.Key.Code == sf::Key::L) {
					newInput(InputEvent::KeyL, events);
				} else if (evt.Key.Code == sf::Key::M) {
					newInput(InputEvent::KeyM, events);
				} else if (evt.Key.Code == sf::Key::M) {
					newInput(InputEvent::KeyM, events);
				} else if (evt.Key.Code == sf::Key::N) {
					newInput(InputEvent::KeyN, events);
				} else if (evt.Key.Code == sf::Key::O) {
					newInput(InputEvent::KeyO, events);
				} else if (evt.Key.Code == sf::Key::P) {
					newInput(InputEvent::KeyP, events);
				} else if (evt.Key.Code == sf::Key::Q) {
					newInput(InputEvent::KeyQ, events);
				} else if (evt.Key.Code == sf::Key::R) {
					newInput(InputEvent::KeyR, events);
				} else if (evt.Key.Code == sf::Key::S) {
					newInput(InputEvent::KeyS, events);
				} else if (evt.Key.Code == sf::Key::T) {
					newInput(InputEvent::KeyT, events);
				} else if (evt.Key.Code == sf::Key::U) {
					newInput(InputEvent::KeyU, events);
				} else if (evt.Key.Code == sf::Key::V) {
					newInput(InputEvent::KeyV, events);
				} else if (evt.Key.Code == sf::Key::W) {
					newInput(InputEvent::KeyW, events);
				} else if (evt.Key.Code == sf::Key::X) {
					newInput(InputEvent::KeyX, events);
				} else if (evt.Key.Code == sf::Key::Y) {
					newInput(InputEvent::KeyY, events);
				} else if (evt.Key.Code == sf::Key::Z) {
					newInput(InputEvent::KeyZ, events);
				} else if (evt.Key.Code == sf::Key::Num1) {
					newInput(InputEvent::Key1, events);
				} else if (evt.Key.Code == sf::Key::Num2) {
					newInput(InputEvent::Key2, events);
				} else if (evt.Key.Code == sf::Key::Num3) {
					newInput(InputEvent::Key3, events);
				} else if (evt.Key.Code == sf::Key::Num4) {
					newInput(InputEvent::Key4, events);
				} else if (evt.Key.Code == sf::Key::Num5) {
					newInput(InputEvent::Key5, events);
				} else if (evt.Key.Code == sf::Key::Num6) {
					newInput(InputEvent::Key6, events);
				} else if (evt.Key.Code == sf::Key::Num7) {
					newInput(InputEvent::Key7, events);
				} else if (evt.Key.Code == sf::Key::Num8) {
					newInput(InputEvent::Key8, events);
				} else if (evt.Key.Code == sf::Key::Num9) {
					newInput(InputEvent::Key9, events);
				} else if (evt.Key.Code == sf::Key::Return) {
					newInput(InputEvent::KeyEnter, events);
				}
				break;
		}
	}
	return events;
}

