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
		/**
		 * Exported keys the user could input
		 */
		enum Inputs {
			KeyA,
			KeyB,
			KeyC,
			KeyD,
			KeyE,
			KeyF,
			KeyG,
			KeyH,
			KeyI,
			KeyJ,
			KeyK,
			KeyL,
			KeyM,
			KeyN,
			KeyO,
			KeyP,
			KeyQ,
			KeyR,
			KeyS,
			KeyT,
			KeyU,
			KeyV,
			KeyW,
			KeyX,
			KeyY,
			KeyZ,
			Key1,
			Key2,
			Key3,
			Key4,
			Key5,
			Key6,
			Key7,
			Key8,
			Key9,
			KeyEnter,
			WinClosed,
			LMouse,
			RMouse,
			MouseMove,
			MouseDown,
			MouseUp
		};

		InputEvent(string eventName_);
		virtual ~InputEvent();

		bool operator<(const InputEvent& b) const;
		bool operator==(const InputEvent& b) const;

		/**
		 * Returns the string name
		 */
		string getEventName() const;

		/**
		 * Action method allowing the user to specify what the event does in
		 * response to its keys being found. This is meant to be overriden, otherwise
		 * it is an empty method.
		 *
		 * The method is given the input that triggered it.
		 *
		 * The return value is whether or not the event has occurred.
		 */
		virtual bool action(Inputs trigger, int mouseX, int mouseY);



	private:
		string eventName;
};

#endif /* INPUTEVENT_H_ */
