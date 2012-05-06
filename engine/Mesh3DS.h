/*
 * Mesh3DS.h
 *
 *	Class loads a .3ds file and exposes relevant attributes to
 *	classes that do the rendering.
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */

#ifndef MESH3DS_H_
#define MESH3DS_H_

#include <string.h>
#include <iostream>
#include <vector>

// Open Asset Import Library
#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

using namespace std;

class Mesh3DS {
  public:
    Mesh3DS(string path_);
    virtual ~Mesh3DS();

    /**
     * Prints to console information about the
     * loaded model
     */
    void printInfo();


    /**
     * Returns the scene
     */
    const aiScene* getScene() const;

    /**
     * Returns the indices for each mesh
     */
    vector<vector<unsigned>* > getMeshIndices() const;

  private:
    //path to object
    string modelPath;

    //importer to use
    Assimp::Importer importer;

    //a pointer to the loaded scene
    const aiScene* scene;

    //index buffers per each mesh
    vector<vector<unsigned>*> meshIndices;

    //function which loads the index buffers for
    //meshes
    void loadMeshes();
};

#endif /* MESH3DS_H_ */
