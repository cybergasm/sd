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
#include "engine/BloomFilterEffect.h"
#include "engine/LuminanceFilterEffect.h"

class InputResponder {
  public:
    InputResponder(RenderingWindow* window, Character* character, Camera* camera, BloomFilterEffect* bloom, LuminanceFilterEffect* luminance);
    virtual ~InputResponder();

    /**
     * Processes current events
     */
    void processEvents();
  private:
    /**
     * The input processor
     */
    InputProcessor inputProc;
};

#endif /* INPUTRESPONDER_H_ */
