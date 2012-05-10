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
#include "engine/RenderingWindow.h"
#include "engine/InputProcessor.h"
#include "engine/InputEvent.h"

class InputResponder {
  public:
    InputResponder(RenderingWindow* window, Character* character, Camera* camera);
    virtual ~InputResponder();

    /**
     * Takes action given event
     */
    void inputIs(sf::Event event);

    /**
     * Processes current events
     */
    void processEvents();
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
    RenderingWindow* window;

    /**
     * The input processor
     */
    InputProcessor inputProc;

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
