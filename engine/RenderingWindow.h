/*
 * RenderingWindow.h
 *
 * Wrapper class for the underlying windowing system.
 *  Created on: May 8, 2012
 *      Author: emint
 */

#ifndef RENDERINGWINDOW_H_
#define RENDERINGWINDOW_H_

#include <string>
#include <vector>

// SFML automatically includes SDL headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "InputEvent.h"

using namespace std;

class RenderingWindow {
	public:
		RenderingWindow(string winName, unsigned int width, unsigned int height);
		virtual ~RenderingWindow();

		/**
		 * Close the window
		 */
		void close();

		/**
		 * Returns a vector of all inputs that have occured. Sets the passed
		 * in values to be the mouse coordinates at the time of the query if a
		 * mouse event is detected.
		 */
		vector<InputEvent::Inputs> getEvents(int& mouseX, int& mouseY);

		/**
		 * Toggles mouse
		 */
		void showMouseCursor(bool show);

		/**
		 * Display window
		 */
		void display();

		/**
		 * Sets cursor
		 */
		void setCursorPosition(unsigned int x, unsigned int y);

		/**
		 * Returns whether or not specified mouse button is down
		 */
		bool isMouseDown(InputEvent::Inputs input);

		/**
		 * Getters and setters
		 */
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		bool isOpened() const;
		float getFramerate() const;

	private:
		sf::Window* window;

		unsigned int width;
		unsigned int height;
};

#endif /* RENDERINGWINDOW_H_ */
