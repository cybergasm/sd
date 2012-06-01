/*
 * Texture.cpp
 *
 *  Created on: Jun 1, 2012
 *      Author: emint
 */

#include "Texture.h"

Texture::Texture(string path_) :
  path(path_) {
  img = new sf::Image();
  loadSuccesful = img->LoadFromFile(path);
}

Texture::Texture(unsigned int width_, unsigned int height_) :
  path(""), loadSuccesful(true), width(width_), height(height_) {
  img = new sf::Image(width, height);
}

Texture::~Texture() {
}

bool Texture::isLoaded() const {
  return loadSuccesful;
}

void Texture::bind() const {
  img->Bind();
}

void Texture::setPixel(int x, int y, engine::Color color) {
  img->SetPixel(x, y, sf::Color(color.r(), color.g(), color.b()));
}

unsigned int Texture::getHeight() const {
  return height;
}

unsigned int Texture::getWidth() const {
  return width;
}
