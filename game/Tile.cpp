/*
 * StoneTile.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: emint
 */

#include "Tile.h"

#include <iostream>
#include <stdio.h>

#include "engine/ResourceManager.h"

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
  shader = (ResourceManager::get())->getParallaxShader();

  diffuse = (ResourceManager::get())->getTexture(tileTexture+"_diffuse");
  height = (ResourceManager::get())->getTexture(tileTexture+"_height");
  normal = (ResourceManager::get())->getTexture(tileTexture+"_normal");

  glActiveTexture(GL_TEXTURE0);
  //mipmap the texture
  height->Bind();
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  glActiveTexture(GL_TEXTURE0);
  //mipmap the texture
  diffuse->Bind();
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));

  glActiveTexture(GL_TEXTURE0);
  //mipmap the texture
  normal->Bind();
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

  int stride = sizeof(aiVector3D);
  shader->setAttributeNormalIn(false, stride, mesh->mNormals);
  shader->setAttributeTexCoordIn(false, stride, mesh->mTextureCoords[0]);
  shader->setAttributePositionIn(false, stride, mesh->mVertices);
  shader->setAttributeTangentIn(false, stride, mesh->mTangents);
  shader->setAttributeBitangentIn(false, stride, mesh->mBitangents);
}

void Tile::setTextures() {
  shader->setUniformDiffuseTex(0);
  glActiveTexture(GL_TEXTURE0);
  diffuse->Bind();

  shader->setUniformHeightMap(1);
  glActiveTexture(GL_TEXTURE1);
  height->Bind();

  shader->setUniformNormalMap(2);
  glActiveTexture(GL_TEXTURE2);
  normal->Bind();
}
