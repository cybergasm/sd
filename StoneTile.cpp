/*
 * StoneTile.cpp
 *
 *  Created on: Apr 20, 2012
 *      Author: emint
 */

#include "StoneTile.h"

#include <iostream>
#include <stdio.h>

using namespace std;

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

StoneTile::StoneTile() :
  tileMesh("models/tile.3ds") {
  //load the parallax shader
  shader = new Shader("shaders/parallax");

  if (!shader->loaded()) {
    cerr << shader->errors() << endl;
    exit(-1);
  }

  if (!diffuse.LoadFromFile("textures/cobble_tile_diffuse.jpg")) {
    cerr << "Could not load tile diffuse texture." << endl;
    exit(-1);
  }
}

StoneTile::~StoneTile() {
}

void StoneTile::render() {
  //Remember the program at time of call so we can
  //reset
  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader->programID()));

  nodeRender(tileMesh.getScene()->mRootNode);

  GL_CHECK(glUseProgram(oldId));
}

void StoneTile::nodeRender(aiNode* node) {
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
  const aiScene* scene = tileMesh.getScene();

  for (unsigned int mesh = 0; mesh < node->mNumMeshes; mesh++) {
    //Only render Triangles
    if (scene->mMeshes[node->mMeshes[mesh]]->mPrimitiveTypes
        == aiPrimitiveType_TRIANGLE) {

      //Set vertices, normals, and tex coords
      setMeshData(node->mMeshes[mesh]);

      //set the texture
      setTextures();

      //Get the vector of indices for this mesh
      vector<unsigned> curIndices = *tileMesh.getMeshIndices().at(
          node->mMeshes[mesh]);
      GL_CHECK(glDrawElements(
              GL_TRIANGLES,
              3 * tileMesh.getScene()->mMeshes[node->mMeshes[mesh]]->mNumFaces,
              GL_UNSIGNED_INT, &curIndices[0]));

    }
  }

  glPopMatrix();
}

void StoneTile::setMeshData(u_int meshIdx) {
  const aiScene* scene = tileMesh.getScene();
  aiMesh* mesh = scene->mMeshes[meshIdx];

  /*shader->setVertexAttribArray("normalIn", 3, GL_FLOAT, 0, sizeof(aiVector3D),
   mesh->mNormals);*/
  shader->setVertexAttribArray("texCoordIn", 2, GL_FLOAT, 0,
      sizeof(aiVector3D), mesh->mTextureCoords[0]);
  shader->setVertexAttribArray("positionIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), mesh->mVertices);
}

void StoneTile::setTextures() {
  GLint diffuseHandle = glGetUniformLocation(shader->programID(), "diffuseTex");

  if (diffuseHandle == -1) {
    cerr << "Error getting id for tile diffuse texture."<<endl;
  }

  glUniform1i(diffuseHandle, 0); // Making the texture be GL_TEXTURE0
  glActiveTexture(GL_TEXTURE0);
  diffuse.Bind();
}
