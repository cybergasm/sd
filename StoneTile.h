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

#include "Mesh3DS.h"
#include "Shader.h"
#include "Camera.h"

class StoneTile {
  public:
    StoneTile(Camera* camera_);
    virtual ~StoneTile();

    /**
     * Displays the tile
     */
    void render();
  private:
    /**
     * We need a camera position for the parallax mapping
     */
    Camera* camera;

    /**
     * Shader that does parallax
     */
    Shader* shader;

    /**
     * Tile Mesh
     */
    Mesh3DS tileMesh;

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
