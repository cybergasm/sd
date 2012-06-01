/*
 * ResourceManager.cpp
 *
 *  Created on: May 1, 2012
 *      Author: emint
 */

#include "ResourceManager.h"
#include "CfgFile.h"

ResourceManager* ResourceManager::resourceManager = NULL;

ResourceManager::ResourceManager() {
  CfgFile rootResourceFile("rsrc.config");
  rootResourceFile.printFile();
  populateMeshMap(rootResourceFile.get("meshes"));
  populateShaderMap(rootResourceFile.get("shaders"));
  populateTextureMap(rootResourceFile.get("textures"));

  //initializing known shaders
  //TODO FIX THIS HACK WHERE WE ASSUME WE KNOW WHERE THE ENGINE SHADERS
  //ARE
  plaxShader = new ParallaxShader("../engine/shaders/parallax");
  if (!plaxShader->loaded()) {
    cerr << "Parallax shader not loaded." << endl;
    cerr << plaxShader->errors() << endl;
    exit(-1);
  }

  characterShader = new CharacterShader("../engine/shaders/character");
  if (!characterShader->loaded()) {
    cerr << "Character shader not loaded." << endl;
    cerr << characterShader->errors() << endl;
    exit(-1);
  }
}

ResourceManager::~ResourceManager() {
  // TODO Auto-generated destructor stub
}

void ResourceManager::populateTextureMap(set<string> textureFolders) {
  set<string>::iterator iter;
  for (iter = textureFolders.begin(); iter != textureFolders.end(); ++iter) {
    string folder = *iter;
    CfgFile textureResourceFile(folder + "/textures.rsrc");
    map<string, set<string> > values = textureResourceFile.getAllPairs();
    map<string, set<string> >::iterator valuesIter;
    for (valuesIter = values.begin(); valuesIter != values.end(); ++valuesIter) {
      //get first element in set as we expect only one key value pair of this type
      string textureName = *(valuesIter->second.begin());
      if (textures.find(valuesIter->first) == textures.end()) {
        Texture* img = new Texture(folder+"/"+textureName);
        if (!img->isLoaded()) {
          cerr << "Could not find texture: " << textureName << " in " << folder
              << endl;
        } else {
          cout << "Binding texture name " << valuesIter->first
              << " to texture at " << (folder + "/" + textureName) << endl;
          textures[valuesIter->first] = img;
        }
      }
    }
  }
}

void ResourceManager::populateMeshMap(set<string> meshFolders) {
  set<string>::iterator iter;
  for (iter = meshFolders.begin(); iter != meshFolders.end(); ++iter) {
    string folder = *iter;
    CfgFile meshResource(folder + "/mesh.rsrc");
    map<string, set<string> > values = meshResource.getAllPairs();
    map<string, set<string> >::iterator valuesIter;
    for (valuesIter = values.begin(); valuesIter != values.end(); ++valuesIter) {
      //get first element in set as we expect only one key value pair of this type
      string meshName = *(valuesIter->second.begin());
      if (meshes.find(valuesIter->first) == meshes.end()) {
        cout << "Binding mesh name " << valuesIter->first << " to mesh at "
            << (folder + "/" + meshName) << endl;
        Mesh3DS* mesh = new Mesh3DS(folder + "/" + meshName);
        meshes[valuesIter->first] = mesh;
      }
    }
  }
}

void ResourceManager::populateShaderMap(set<string> shaderFolders) {
  set<string>::iterator iter;
  for (iter = shaderFolders.begin(); iter != shaderFolders.end(); ++iter) {
    string folder = *iter;
    CfgFile shaderResource(folder + "/shaders.rsrc");
    map<string, set<string> > values = shaderResource.getAllPairs();
    map<string, set<string> >::iterator valuesIter;
    for (valuesIter = values.begin(); valuesIter != values.end(); ++valuesIter) {
      //get first element in set as we expect only one key value pair of this type
      string shaderName = *(valuesIter->second.begin());
      if (shaders.find(valuesIter->first) == shaders.end()) {
        cout << "Binding shader name " << valuesIter->first << " to shader at "
            << (folder + "/" + shaderName) << endl;
        Shader* shader = new Shader(folder + "/" + shaderName);

        if (!shader->loaded()) {
          cerr << shader->errors() << endl;
          exit(-1);
        }

        shaders[valuesIter->first] = shader;
      }
    }
  }
}

Mesh3DS* ResourceManager::getMesh(string key) const {
  if (meshes.find(key) == meshes.end()) {
    return NULL;
  }
  return meshes.find(key)->second;
}

Shader* ResourceManager::getShader(string key) const {
  if (shaders.find(key) == shaders.end()) {
    return NULL;
  }
  return shaders.find(key)->second;
}

Texture* ResourceManager::getTexture(string key) const {
  if (textures.find(key) == textures.end()) {
    return NULL;
  }
  return textures.find(key)->second;
}

void ResourceManager::init() {
  if (resourceManager == NULL) {
    resourceManager = new ResourceManager();
  }
}

ResourceManager* ResourceManager::get() {
  return resourceManager;
}

ParallaxShader* ResourceManager::getParallaxShader() const {
  return plaxShader;
}

CharacterShader* ResourceManager::getCharacterShader() const {
  return characterShader;
}
