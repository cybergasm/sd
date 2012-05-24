/*
 * RenderingWindow.cpp
 *
 *  Created on: May 8, 2012
 *      Author: emint
 */

#include "RenderingWindow.h"

RenderingWindow::RenderingWindow(string winName, unsigned int width_,
    unsigned int height_) :
	width(width_), height(height_) {
	sf::WindowSettings settings(24, 8, 2);
	window = new sf::Window(sf::VideoMode(width, height), winName.c_str(),
	    sf::Style::Close, settings);
}

RenderingWindow::~RenderingWindow() {
	// TODO Auto-generated destructor stub
}

void RenderingWindow::close() {
	window->Close();
}

vector<InputEvent::Inputs> RenderingWindow::getEvents(int& mouseX, int& mouseY) {
	sf::Event evt;
	vector<InputEvent::Inputs> toReturn;
	while (window->GetEvent(evt)) {
		switch (evt.Type) {
			case sf::Event::Closed:
				// return that the window needs to be closed
				toReturn.push_back(InputEvent::WinClosed);
				break;
			case sf::Event::KeyPressed:
				if (evt.Key.Code == sf::Key::A) {
					toReturn.push_back(InputEvent::KeyA);
				} else if (evt.Key.Code == sf::Key::B) {
					toReturn.push_back(InputEvent::KeyB);
				} else if (evt.Key.Code == sf::Key::C) {
					toReturn.push_back(InputEvent::KeyC);
				} else if (evt.Key.Code == sf::Key::D) {
					toReturn.push_back(InputEvent::KeyD);
				} else if (evt.Key.Code == sf::Key::E) {
					toReturn.push_back(InputEvent::KeyE);
				} else if (evt.Key.Code == sf::Key::F) {
					toReturn.push_back(InputEvent::KeyF);
				} else if (evt.Key.Code == sf::Key::G) {
					toReturn.push_back(InputEvent::KeyG);
				} else if (evt.Key.Code == sf::Key::H) {
					toReturn.push_back(InputEvent::KeyH);
				} else if (evt.Key.Code == sf::Key::I) {
					toReturn.push_back(InputEvent::KeyI);
				} else if (evt.Key.Code == sf::Key::J) {
					toReturn.push_back(InputEvent::KeyJ);
				} else if (evt.Key.Code == sf::Key::K) {
					toReturn.push_back(InputEvent::KeyK);
				} else if (evt.Key.Code == sf::Key::L) {
					toReturn.push_back(InputEvent::KeyL);
				} else if (evt.Key.Code == sf::Key::M) {
					toReturn.push_back(InputEvent::KeyM);
				} else if (evt.Key.Code == sf::Key::M) {
					toReturn.push_back(InputEvent::KeyM);
				} else if (evt.Key.Code == sf::Key::N) {
					toReturn.push_back(InputEvent::KeyN);
				} else if (evt.Key.Code == sf::Key::O) {
					toReturn.push_back(InputEvent::KeyO);
				} else if (evt.Key.Code == sf::Key::P) {
					toReturn.push_back(InputEvent::KeyP);
				} else if (evt.Key.Code == sf::Key::Q) {
					toReturn.push_back(InputEvent::KeyQ);
				} else if (evt.Key.Code == sf::Key::R) {
					toReturn.push_back(InputEvent::KeyR);
				} else if (evt.Key.Code == sf::Key::S) {
					toReturn.push_back(InputEvent::KeyS);
				} else if (evt.Key.Code == sf::Key::T) {
					toReturn.push_back(InputEvent::KeyT);
				} else if (evt.Key.Code == sf::Key::U) {
					toReturn.push_back(InputEvent::KeyU);
				} else if (evt.Key.Code == sf::Key::V) {
					toReturn.push_back(InputEvent::KeyV);
				} else if (evt.Key.Code == sf::Key::W) {
					toReturn.push_back(InputEvent::KeyW);
				} else if (evt.Key.Code == sf::Key::X) {
					toReturn.push_back(InputEvent::KeyX);
				} else if (evt.Key.Code == sf::Key::Y) {
					toReturn.push_back(InputEvent::KeyY);
				} else if (evt.Key.Code == sf::Key::Z) {
					toReturn.push_back(InputEvent::KeyZ);
				} else if (evt.Key.Code == sf::Key::Num1) {
					toReturn.push_back(InputEvent::Key1);
				} else if (evt.Key.Code == sf::Key::Num2) {
					toReturn.push_back(InputEvent::Key2);
				} else if (evt.Key.Code == sf::Key::Num3) {
					toReturn.push_back(InputEvent::Key3);
				} else if (evt.Key.Code == sf::Key::Num4) {
					toReturn.push_back(InputEvent::Key4);
				} else if (evt.Key.Code == sf::Key::Num5) {
					toReturn.push_back(InputEvent::Key5);
				} else if (evt.Key.Code == sf::Key::Num6) {
					toReturn.push_back(InputEvent::Key6);
				} else if (evt.Key.Code == sf::Key::Num7) {
					toReturn.push_back(InputEvent::Key7);
				} else if (evt.Key.Code == sf::Key::Num8) {
					toReturn.push_back(InputEvent::Key8);
				} else if (evt.Key.Code == sf::Key::Num9) {
					toReturn.push_back(InputEvent::Key9);
				} else if (evt.Key.Code == sf::Key::Space) {
				  toReturn.push_back(InputEvent::Space);
				} else if (evt.Key.Code == sf::Key::Return) {
					toReturn.push_back(InputEvent::KeyEnter);
				}
				break;
			case sf::Event::MouseMoved:
				toReturn.push_back(InputEvent::MouseMove);
				mouseX = evt.MouseMove.X;
				mouseY = evt.MouseMove.Y;
				break;
			case sf::Event::MouseButtonPressed:
				toReturn.push_back(InputEvent::MouseDown);
				mouseX = evt.MouseButton.X;
				mouseY = evt.MouseButton.Y;
				break;
			case sf::Event::MouseButtonReleased:
				toReturn.push_back(InputEvent::MouseUp);
				mouseX = evt.MouseButton.X;
				mouseY = evt.MouseButton.Y;
				break;
		}
	}

	return toReturn;
}

unsigned int RenderingWindow::getHeight() const {
	return height;
}

unsigned int RenderingWindow::getWidth() const {
	return width;
}

bool RenderingWindow::isOpened() const {
	return window->IsOpened();
}

void RenderingWindow::display() {
	window->Display();
}

void RenderingWindow::setCursorPosition(unsigned int x, unsigned int y) {
	window->SetCursorPosition(x, y);
}

float RenderingWindow::getFramerate() const {
	return window->GetFrameTime();
}

void RenderingWindow::showMouseCursor(bool show) {
	window->ShowMouseCursor(show);
}

bool RenderingWindow::isMouseDown(InputEvent::Inputs input) {
	if (input == InputEvent::LMouse) {
		return window->GetInput().IsMouseButtonDown(sf::Mouse::Left);
	} else if (input == InputEvent::RMouse) {
		return window->GetInput().IsMouseButtonDown(sf::Mouse::Right);
	}
	return false;
}
