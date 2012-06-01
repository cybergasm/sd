/*
 * Color.h
 *
 *  Created on: Jun 1, 2012
 *      Author: emint
 */

#ifndef COLOR_H_
#define COLOR_H_

namespace engine {

class Color {
  public:
    Color(float r, float g, float b);
    virtual ~Color();

    float r() const;
    float g() const;
    float b() const;

  private:
    //Color values. I am switching the naming convention
    //here as I think it looks better and is more commonplace
    //to have methods that look like color.r() versus color.getColor()
    float r_;
    float g_;
    float b_;
};

}

#endif /* COLOR_H_ */
