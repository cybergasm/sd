/*
 * Character.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */

#include "Character.h"

Character::Character() :
  characterMesh("models/main_character.3ds") {

  shader = new Shader("shaders/character");

  if (!shader->loaded()) {
    cerr << shader->errors() << endl;
    exit(-1);
  }
}

Character::~Character() {
  // TODO Auto-generated destructor stub
}

void Character::render() {
  nodeRender(characterMesh.getScene()->mRootNode);
}

void Character::nodeRender(aiNode* node) {
  //save matrix
  glPushMatrix();
  //multiply our transform
  GLfloat matrix[16] = { node->mTransformation.a1, node->mTransformation.b1,
      node->mTransformation.c1, node->mTransformation.d1,
      node->mTransformation.a2, node->mTransformation.b2,
      node->mTransformation.c2, node->mTransformation.d2,
      node->mTransformation.a3, node->mTransformation.b3,
      node->mTransformation.c3, node->mTransformation.d3,
      node->mTransformation.a4, node->mTransformation.b4,
      node->mTransformation.c4, node->mTransformation.d4 };
  glMultMatrixf(matrix);

  //render all children
  for (u_int child = 0; child < node->mNumChildren; child++) {
    nodeRender(node->mChildren[child]);
  }

  for (unsigned int mesh = 0; mesh < node->mNumMeshes; mesh++) {
    if (characterMesh.getScene()->mMeshes[node->mMeshes[mesh]]->mPrimitiveTypes
        == aiPrimitiveType_TRIANGLE) {
      vector<unsigned> curIndices = *characterMesh.getMeshIndices().at(
          node->mMeshes[mesh]);
      glBegin(GL_TRIANGLES);
      aiMesh* curMesh = characterMesh.getScene()->mMeshes[node->mMeshes[mesh]];

      glColor3f(1, 0, 0);
      for (unsigned int vertexIdx = 0; vertexIdx < curIndices.size(); vertexIdx++) {
        aiVector3D vertex = curMesh->mVertices[curIndices.at(vertexIdx)];
        glVertex3f(vertex.x, vertex.y, vertex.z);
      }
      glEnd();
    }
  }
  glPopMatrix();
}
