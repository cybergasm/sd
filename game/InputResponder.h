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
#include "engine/Camera.h"

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

    /**
     * State variable to tell us if we are ready to move mouse,
     * namely ensures we center it between moves so we get
     * a constant measure of how much it has moved
     */
    bool mouseReady;

    /**
     * Handles mouse movement by changing current angle
     * and updating where we are looking at.
     */
    void mouseMoved(int mouseX, int mouseY);
};

#endif /* INPUTRESPONDER_H_ */
