/*
 * PostprocessParameterInputEvent.cpp
 *
 *  Created on: Jun 5, 2012
 *      Author: emint
 */

#include "PostprocessParameterInputEvent.h"

PostprocessParameterInputEvent::PostprocessParameterInputEvent(
    BloomFilterEffect* bloom_, LuminanceFilterEffect* luminance_) :
  InputEvent("PostprocessParam"), bloom(bloom_), luminance(luminance_) {

}

PostprocessParameterInputEvent::~PostprocessParameterInputEvent() {
  // TODO Auto-generated destructor stub
}

bool PostprocessParameterInputEvent::action(InputEvent::Inputs input,
    int mouseX, int mouseY) {
  //increase luminance threshold
  if (input == InputEvent::Key1) {
    luminance->setLumThresh(luminance->getLumThresh() + .03);
  } else if (input == InputEvent::Key2) {
    //Decrease luminance threshold
    luminance->setLumThresh(luminance->getLumThresh() - .03);
  } else if (input == InputEvent::Key3) {
    //Increase bloom factor
    bloom->setBloomFactor(bloom->getBloomFactor() + .03);
  } else if (input == InputEvent::Key4){
    //Decrease bloom factor
    bloom->setBloomFactor(bloom->getBloomFactor() - .03);
  }

  return true;
}
