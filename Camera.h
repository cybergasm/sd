/*
 * Camera.h
 *
 * This implements FPS-like camera controls. Note that
 * I used the particle-demo as a guide as it is much cleaner
 * with matrices versus how I was doing it (component-wise,
 * disgusting).
 *
 *  Created on: Mar 5, 2012
 *      Author: emint
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209
#endif

#include "Character.h"

#include "assimp/aiVector3D.h"
class Camera {
  public:
    Camera(float nClip, float fClip, float fov, int wH, int wW);
    virtual ~Camera();

    /**
     * Returns the cross product of up and look-at to get the
     * orthogonal vector to the side.
     */
    aiVector3D sideDirection();

    /**
     * Allows us to control the drawing area in case of resize
     */
    void wHeightIs(int height);
    void wWidthIs(int width);

    /**
     * Given mouse direction re-calculates the new camera orientation
     */
    void rotateIncrementally(int dX, int dY);

    /**
     * Given absolute angle in radians, rotates camera. This is used to
     * position the third person camera at the angle desired around the
     * anchor point.
     */
    void rotateAroundAngle(float angleX, float angleY);

    /**
     * Moves the camera. This camera is constrained in that it forward and
     * backwards corresponds to movement along the z axis only.
     */
    void moveForward();
    void moveBackwards();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    /**
     * Positions the camera in space by setting modelview and projection
     * matrices
     */
    void posCameraSetupView();

    /**
     * Anchors the camera around a point
     */
    void setAnchor(aiVector3D anchor);

    /**
     * Getters for different parameters
     */
    float anchorX();
    float anchorY();
    float anchorZ();

    float atX();
    float atY();
    float atZ();

    float totalXAngle();
    float totalYAngle();
  private:
    //Camera positioning
    aiVector3D anchor, lookAt, upVec;

    //Camera positioning with respect to character
    float zOffset, yOffset;

    //Viewing set-up parameters
    float nearClip;
    float farClip;
    float fov;

    //Need window params for calculations
    int winHeight;
    int winWidth;

    //Constrains how far 'up' we can look
    const float yAxisMax;

    //the rate of movement
    float rateOfMovement;

    //How much we have rotated total (for keeping objects
    //oriented with the camera)
    float totYAngle;
    float totXAngle;

    //how sensistive it is to changes in angle
    float sensitivity;
};

#endif /* CAMERA_H_ */
