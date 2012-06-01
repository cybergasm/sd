/*
 * Texture.cpp
 *
 *  Created on: Jun 1, 2012
 *      Author: emint
 */

#include "Texture.h"

Texture::Texture(string path_) : path(path_) {
  img = new sf::Image();
  loadSuccesful = img->LoadFromFile(path);
}

Texture::~Texture() {
}

bool Texture::isLoaded() const {
  return loadSuccesful;
}
