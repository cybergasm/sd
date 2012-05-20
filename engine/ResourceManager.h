/*
 * ResourceManager.h
 *
 *  Class which uses the config files to instantiate objects
 *  for each required resource type exposing them through a
 *  <key, value> interface. Statically accessed.
 *
 *  Created on: May 1, 2012
 *      Author: emint
 */

#ifndef RESOURCEMANAGER_H_
#define RESOURCEMANAGER_H_

#include <map>
#include <set>
#include <string.h>


#include "Mesh3DS.h"
#include "Shader.h"
#include "ParallaxShader.h"
#include "CharacterShader.h"

using namespace std;

class ResourceManager {
  public:
    ResourceManager();
    virtual ~ResourceManager();

    /**
     * Static method returns a static handle to the resource manager.
     * This assumes init is called so that the resource manager is initialized.
     */
    static ResourceManager* get();

    /**
     * Static method that initializes the resource manager by reading in the
     * 'rscr.config'
     */
    static void init();

    /**
     * The public handle
     */
    static ResourceManager* resourceManager;

    /**
     * Access methods for the different resources
     */
    Mesh3DS* getMesh(string key) const;
    Shader* getShader(string key) const;

    /**
     * Accessor method for different shaders exposed by the
     * engine
     */
    ParallaxShader* getParallaxShader() const;
    CharacterShader* getCharacterShader() const;
  private:

    //map holding handles to their respective objects
    map <string, Mesh3DS*> meshes;
    map <string, Shader*> shaders;

    void populateMeshMap(set<string> meshFolders);
    void populateShaderMap(set<string> shaderFolders);

    //Specific shaders exposed by the game engine
    ParallaxShader* plaxShader;
    CharacterShader* characterShader;
};

#endif /* RESOURCEMANAGER_H_ */
