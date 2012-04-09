/*
 * Mesh3DS.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */

#include "Mesh3DS.h"

Mesh3DS::Mesh3DS(string modelPath_) :
  modelPath(modelPath_) {
  scene = importer.ReadFile(
      modelPath,
      aiProcess_CalcTangentSpace | aiProcess_Triangulate
          | aiProcess_JoinIdenticalVertices
          | aiProcessPreset_TargetRealtime_Quality);

  if (!scene || scene->mNumMeshes <= 0) {
    cerr << importer.GetErrorString() << endl;
    exit(-1);
  }

  loadMeshes();
}

Mesh3DS::~Mesh3DS() {
  // TODO Auto-generated destructor stub
}

void Mesh3DS::printInfo() {
  cout << "=== MODEL: " << modelPath << " ===" << endl;
  cout << "=== Number of meshes: " << scene->mNumMeshes << " ===" << endl;
  for (u_int meshIndex = 0; meshIndex < scene->mNumMeshes; meshIndex++) {
    aiMesh* mesh = scene->mMeshes[meshIndex];
    cout << "===== Mesh " << meshIndex << " =====" << endl;
    cout << "===== Mesh is triangle? " << (mesh->mPrimitiveTypes
        == aiPrimitiveType_TRIANGLE) << " =====" << endl;
    cout << "===== Number of faces: " << mesh->mNumFaces << " =====" << endl;
    cout << "===== Mesh has texture coords? " << (mesh->HasTextureCoords(0))
        << " =====" << endl;
    cout << "===== Mesh has normals? " << (mesh->HasNormals()) << " ====="
        << endl;
    cout << "===== Mesh has tangents? " << (mesh->HasTangentsAndBitangents())
        << " =====" << endl;
    cout << "===== Mesh name " << mesh->mName.data << " =====" << endl;
  }
}

const aiScene* Mesh3DS::getScene() {
  return scene;
}

vector<vector<unsigned>* > Mesh3DS::getMeshIndices() {
  return meshIndices;
}

void Mesh3DS::loadMeshes() {
  for (unsigned int mesh = 0; mesh < scene->mNumMeshes; mesh++) {
    aiMesh* curMesh = scene->mMeshes[mesh];
      vector<unsigned>* indexBuf = new vector<unsigned> ();
      for (unsigned int faceIdx = 0; faceIdx < curMesh->mNumFaces; faceIdx++) {
        for (unsigned int faceVertexIdx = 0; faceVertexIdx
            < curMesh->mFaces[faceIdx].mNumIndices; faceVertexIdx++) {
          indexBuf->push_back(curMesh->mFaces[faceIdx].mIndices[faceVertexIdx]);
        }
      }
      meshIndices.push_back(indexBuf);
  }
}
