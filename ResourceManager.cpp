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
      if (meshFolders.find(meshName) == meshFolders.end()) {
        cout << "Binding mesh name " << valuesIter->first << " to mesh at "
            << (folder + "/" + meshName) << endl;
        Mesh3DS* mesh = new Mesh3DS(folder + "/" + meshName);
        meshes[valuesIter->first] = mesh;
      }
    }
  }
}

Mesh3DS* ResourceManager::getMesh(string key) {
  if (meshes.find(key) == meshes.end()) {
    return NULL;
  }
  return meshes[key];
}

void ResourceManager::init() {
  if (resourceManager == NULL) {
    resourceManager = new ResourceManager();
  }
}

ResourceManager* ResourceManager::get() {
  return resourceManager;
}
