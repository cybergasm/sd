/*
 * InputResponder.h
 *
 *  Created on: Apr 13, 2012
 *      Author: emint
 */

#ifndef INPUTRESPONDER_H_
#define INPUTRESPONDER_H_

#include "Framework.h"
#include "Character.h"

class InputResponder {
  public:
    InputResponder();
    virtual ~InputResponder();

    /**
     * Takes action given event
     */
    void inputIs(sf::Event event);

    /**
     * Register a character to modify as
     * response to movement events
     */
    void characterIs(Character* character);

    /**
     * Register a window respond to window
     * events
     */
    void windowIs(sf::Window* window);
  private:
    /**
     * User character to respond to moves
     */
    Character* character;

    /**
     * Window to respond to windowing events like
     * close
     */
    sf::Window* window;
};

#endif /* INPUTRESPONDER_H_ */
