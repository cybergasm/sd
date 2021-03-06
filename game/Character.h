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

#include "engine/Mesh3DS.h"
#include "engine/CharacterShader.h"
#include "engine/MeshRenderer.h"

class Character : public MeshRenderer{
  public:
    Character();
    virtual ~Character();

    /**
     * Displays character on screen
     */
    void render(float framerate);

    /**
     * Functions moving character along
     * specified axis
     */
    void move(aiVector3D translation);

    /**
     * Specifies how much the camera has rotated around
     * the player
     */
    void setCameraRotation(float cameraRot);

    /**
     * Returns position
     */
    aiVector3D getPos();

    /**
     * Overrides custom render methods
     */
    void setWholeMeshTransform() const;
    void setCustomTransformation(string meshName) const;
    float getTime() const;
  private:
    /**
     * Movement rate of the character
     */
    float movementRate;

    /**
     * The angle that the camera has rotated around to make the
     * character's orientation line up
     */
    float cameraRotation;

    /**
     * Animation time tracker that goes between 0, 10
     */
    float cyclicAniTime;

    /**
     * Timer that simply increments
     */
    float straightAniTime;

    /**
     * Whether time is increasing or decreasing and
     * the rate of change
     */
    float aniTimeRate;

    /**
     * Position of character
     */
    float xPos, yPos, zPos;

    /**
     * Moves time proportional to rate
     */
    void updateTime(float framerate);
};

#endif /* CHARACTER_H_ */
