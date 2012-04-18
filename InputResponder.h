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
#include "Camera.h"

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
     * response to actions
     */
    void characterIs(Character* character);

    /**
     * Register a camera for camera movement
     */
    void cameraIs(Camera* camera);

    /**
     * Register a window respond to window
     * events
     */
    void windowIs(sf::Window* window);
  private:
    /**
     * User character
     */
    Character* character;

    /**
     * Camera to control movement
     */
    Camera* camera;

    /**
     * Window to respond to windowing events like
     * close
     */
    sf::Window* window;
};

#endif /* INPUTRESPONDER_H_ */
