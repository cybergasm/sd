/*
 * Character.h
 *  Represents a character on the screen.
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

// Open Asset Import Library
#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

#include "Framework.h"

#include "Mesh3DS.h"
#include "Shader.h"

class Character {
  public:
    Character();
    virtual ~Character();

    /**
     * Displays character on screen
     */
    void render();
  private:
    /**
     * Mesh of character and related attributes
     */
    Mesh3DS characterMesh;

    /**
     * Renders a node in the given mesh
     */
    void nodeRender(aiNode* node);

    /**
     * Character shader.
     */
    Shader* shader;

    /**
     * Texture to shade with
     */
    sf::Image texture;

    /**
     * Sets up the texture data
     */
    void setTexture();

    /**
     * Sets the material values
     */
    void setMeshMaterials(u_int mesh);

    /**
     * Sets relevant mesh data such as position, texcoords, and normals
     */
    void setMeshData(u_int mesh);
};

#endif /* CHARACTER_H_ */
