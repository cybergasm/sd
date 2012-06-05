/*
 * PostprocessParameterInputEvent.h
 *
 *  Created on: Jun 5, 2012
 *      Author: emint
 */

#ifndef POSTPROCESSPARAMETERINPUTEVENT_H_
#define POSTPROCESSPARAMETERINPUTEVENT_H_

#include "engine/InputEvent.h"
#include "engine/BloomFilterEffect.h"
#include "engine/LuminanceFilterEffect.h"

class PostprocessParameterInputEvent: public InputEvent {
  public:
    PostprocessParameterInputEvent(BloomFilterEffect* bloom, LuminanceFilterEffect* luminance);
    virtual ~PostprocessParameterInputEvent();

    bool action(InputEvent::Inputs input, int mouseX, int mouseY);

  private:

    BloomFilterEffect* bloom;
    LuminanceFilterEffect* luminance;
};

#endif /* POSTPROCESSPARAMETERINPUTEVENT_H_ */
