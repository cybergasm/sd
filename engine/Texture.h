/*
 * Texture.h
 *
 *  Wrapper around sf::Image representing an OpenGL Texture
 *
 *  Created on: Jun 1, 2012
 *      Author: emint
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

// SFML automatically includes SDL headers
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Color.h"

using namespace std;

class Texture {
  public:
    Texture(string path);
    Texture(unsigned int width, unsigned int height);
    virtual ~Texture();

    //Whether or not the image was initialized correctly
    bool isLoaded() const;

    //Binds image using appropriate OpenGL calls
    void bind() const;

    //Allows you to set an underlying pixel
    void setPixel (int x, int y, engine::Color color);

    //Gets dimensions
    unsigned int getHeight() const;
    unsigned int getWidth() const;

  private:
    //Path to image on disk
    string path;

    //Pointer to underlying image
    sf::Image* img;

    //Whether or not the image load was succesful
    bool loadSuccesful;

    //Dimensions
    unsigned int width;
    unsigned int height;
};

#endif /* TEXTURE_H_ */
