/*
 * StoneTile.h
 *
 *  Created on: Apr 20, 2012
 *      Author: emint
 */

#ifndef STONETILE_H_
#define STONETILE_H_

// Open Asset Import Library
#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

#include "Framework.h"

#include "engine/Mesh3DS.h"
#include "engine/ParallaxShader.h"
#include "engine/Camera.h"

class Tile {
  public:
    Tile(string tileTexture);
    virtual ~Tile();

    /**
     * Displays the tile
     */
    void render();
  private:
    /**
     * Shader that does parallax
     */
    ParallaxShader* shader;

    /**
     * Tile Mesh
     */
    Mesh3DS* tileMesh;

    /**
     * Diffuse texture
     */
    sf::Image diffuse;

    /**
     * Height map
     */
    sf::Image height;

    /**
     * Normal map
     */
    sf::Image normal;

    /**
     * Renders one node of the mesh
     */
    void nodeRender(aiNode* node);

    /**
     * Sets mesh vertex data like position
     */
    void setMeshData(u_int meshIdx);

    /**
     * Sets the textures for the renderer
     */
    void setTextures();
};

#endif /* STONETILE_H_ */
