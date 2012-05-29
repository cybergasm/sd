/*
 * LightMovementEvent.h
 *
 *  Created on: May 29, 2012
 *      Author: emint
 */

#ifndef LIGHTMOVEMENTEVENT_H_
#define LIGHTMOVEMENTEVENT_H_

#include <engine/InputEvent.h>
#include <GL/glew.h>

class LightMovementEvent : public InputEvent{
  public:
    LightMovementEvent(GLfloat* lightPos);
    virtual ~LightMovementEvent();

    bool action(InputEvent::Inputs input, int mouseX, int mouseY);

  private:
    //array of floats storing light
    GLfloat* lightPos;
};

#endif /* LIGHTMOVEMENTEVENT_H_ */
