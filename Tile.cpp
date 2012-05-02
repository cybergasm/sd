/*
 * StoneTile.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: emint
 */

#include "Tile.h"

#include <iostream>
#include <stdio.h>

#include "ResourceManager.h"

using namespace std;

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

Tile::Tile(string tileTexture) {
  tileMesh = (ResourceManager::get())->getMesh("tile");

  if (tileMesh == NULL) {
    cerr << "Could not load resource tile." <<endl;
    exit(-1);
  }

  //load the parallax shader
  shader = (ResourceManager::get())->getShader("parallax");

  if (!diffuse.LoadFromFile("textures/"+tileTexture+"_tile_diffuse.jpg")) {
    cerr << "Could not load tile diffuse texture." << endl;
    exit(-1);
  }

  if (!height.LoadFromFile("textures/"+tileTexture+"_tile_displacement.jpg")) {
    cerr << "Could not load tile displacement texture." << endl;
    exit(-1);
  }

  if (!normal.LoadFromFile("textures/"+tileTexture+"_tile_normal.jpg")) {
    cerr << "Could not load tile normal texture." << endl;
    exit(-1);
  }

  glActiveTexture(GL_TEXTURE0);
  //mipmap the texture
  height.Bind();
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  glActiveTexture(GL_TEXTURE0);
  //mipmap the texture
  diffuse.Bind();
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  glActiveTexture(GL_TEXTURE0);
  //mipmap the texture
  normal.Bind();
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));
}

Tile::~Tile() {
}

void Tile::render() {
  //Remember the program at time of call so we can
  //reset
  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader->programID()));

  nodeRender(tileMesh->getScene()->mRootNode);

  GL_CHECK(glUseProgram(oldId));
}

void Tile::nodeRender(aiNode* node) {
  //save matrix
  glPushMatrix();

  //multiply the transform transform
  GLfloat matrix[16] = { node->mTransformation.a1, node->mTransformation.b1,
      node->mTransformation.c1, node->mTransformation.d1,
      node->mTransformation.a2, node->mTransformation.b2,
      node->mTransformation.c2, node->mTransformation.d2,
      node->mTransformation.a3, node->mTransformation.b3,
      node->mTransformation.c3, node->mTransformation.d3,
      node->mTransformation.a4, node->mTransformation.b4,
      node->mTransformation.c4, node->mTransformation.d4 };
  glMultMatrixf(matrix);

  for (u_int child = 0; child < node->mNumChildren; child++) {
    nodeRender(node->mChildren[child]);
  }
  const aiScene* scene = tileMesh->getScene();

  for (unsigned int mesh = 0; mesh < node->mNumMeshes; mesh++) {
    //Only render Triangles
    if (scene->mMeshes[node->mMeshes[mesh]]->mPrimitiveTypes
        == aiPrimitiveType_TRIANGLE) {

      //Set vertices, normals, and tex coords
      setMeshData(node->mMeshes[mesh]);

      //set the texture
      setTextures();

      //Get the vector of indices for this mesh
      vector<unsigned> curIndices = *tileMesh->getMeshIndices().at(
          node->mMeshes[mesh]);
      GL_CHECK(glDrawElements(
              GL_TRIANGLES,
              3 * tileMesh->getScene()->mMeshes[node->mMeshes[mesh]]->mNumFaces,
              GL_UNSIGNED_INT, &curIndices[0]));

    }
  }

  glPopMatrix();
}

void Tile::setMeshData(u_int meshIdx) {
  const aiScene* scene = tileMesh->getScene();
  aiMesh* mesh = scene->mMeshes[meshIdx];

  shader->setVertexAttribArray("normalIn", 3, GL_FLOAT, 0, sizeof(aiVector3D),
      mesh->mNormals);
  shader->setVertexAttribArray("texCoordIn", 2, GL_FLOAT, 0,
      sizeof(aiVector3D), mesh->mTextureCoords[0]);
  shader->setVertexAttribArray("positionIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), mesh->mVertices);
  shader->setVertexAttribArray("tangentIn", 3, GL_FLOAT, 0, sizeof(aiVector3D),
      mesh->mTangents);
  shader->setVertexAttribArray("bitangentIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), mesh->mBitangents);
}

void Tile::setTextures() {
  GLint diffuseHandle = glGetUniformLocation(shader->programID(), "diffuseTex");
  GLint heightHandle = glGetUniformLocation(shader->programID(), "heightMap");
  GLint normHandle = glGetUniformLocation(shader->programID(), "normalMap");

  if (diffuseHandle == -1) {
    cerr << "Error getting id for tile diffuse texture." << endl;
  }

  if (heightHandle == -1) {
    cerr << "Error getting id for tile height map." << endl;
  }

  if (normHandle == -1) {
    cerr << "Error getting id for normal map." << endl;
  }

  glUniform1i(diffuseHandle, 0);
  glActiveTexture(GL_TEXTURE0);
  diffuse.Bind();

  glUniform1i(heightHandle, 1);
  glActiveTexture(GL_TEXTURE1);
  height.Bind();

  glUniform1i(heightHandle, 2);
  glActiveTexture(GL_TEXTURE2);
  normal.Bind();
}
