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

  //initializing known shaders
  plaxShader = new ParallaxShader("shaders/parallax");
}

ResourceManager::~ResourceManager() {
  // TODO Auto-generated destructor stub
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
          cerr << shader->errors() <<endl;
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
