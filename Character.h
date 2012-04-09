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

#include <GL/glew.h>

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
};

#endif /* CHARACTER_H_ */
