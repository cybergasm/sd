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
};

#endif /* INPUTRESPONDER_H_ */
