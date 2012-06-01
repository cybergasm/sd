/*
 * Color.cpp
 *
 *  Created on: Jun 1, 2012
 *      Author: emint
 */

#include "Color.h"

namespace engine {

Color::Color(float r, float g, float b) : r_(r), g_(g), b_(b) {

}

Color::~Color() {
}

float Color::r() const {
  return r_;
}

float Color::b() const {
  return b_;
}

float Color::g() const {
  return g_;
}

}
