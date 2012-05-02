/*
 * Character.cpp
 *
 *  Created on: Apr 8, 2012
 *      Author: emint
 */

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

#include "Character.h"

#include <stdio.h>

#include "ResourceManager.h"

Character::Character() :
  movementRate(.05), cameraRotation(0), cyclicAniTime(0), straightAniTime(0),
      aniTimeRate(1), xPos(0), yPos(.25), zPos(0) {
  characterMesh = (ResourceManager::get())->getMesh("spirit");
  if (characterMesh == NULL) {
    cerr << "Cannot find resource main_character."<<endl;
    exit(-1);
  }
  //load the character shader that animates the mesh
  shader = new Shader("shaders/character");

  if (!shader->loaded()) {
    cerr << shader->errors() << endl;
    exit(-1);
  }

  //grab our texture
  if (!texture.LoadFromFile("textures/main_char_tex.jpg")) {
    cerr << "Error loading character textures." << endl;
  }

  glActiveTexture(GL_TEXTURE0);
  //mipmap the texture
  texture.Bind();
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));
}

Character::~Character() {
}

void Character::move(aiVector3D translation) {
  xPos += movementRate * translation.x;
  yPos += movementRate * translation.y;
  zPos += movementRate * translation.z;
}

aiVector3D Character::getPos() {
  return aiVector3D(xPos, yPos, zPos);
}

void Character::updateTime(float framerate) {
  cyclicAniTime += aniTimeRate * framerate * 6.0f;
  straightAniTime += framerate * 6.0f;

  if (cyclicAniTime > 10) {
    aniTimeRate = -1;
  } else if (cyclicAniTime < 0) {
    aniTimeRate = 1;
  }
}

void Character::setCameraRotation(float cameraRot) {
  cameraRotation = cameraRot;
}

void Character::render(float framerate) {
  //move internal animation timer forward
  updateTime(framerate);

  //Remember the program at time of call so we can
  //reset
  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader->programID()));

  //Save old state and translate model
  glPushMatrix();
  //Move it to position
  glTranslatef(xPos, yPos, zPos);
  //Make it smaller so it fits better
  glScalef(.25, .25, .25);
  //Rotate it so its back is to the camera
  glRotatef(cameraRotation, 0, 1, 0);

  nodeRender(characterMesh->getScene()->mRootNode);

  glPopMatrix();

  GL_CHECK(glUseProgram(oldId));
}

void Character::meshAnimate(aiString meshName) {
  if (meshName == aiString("0") || meshName == aiString("1")) {
    glRotatef(cyclicAniTime, 1, 1, 0);
  } else if (meshName == aiString("2")) {
    glScalef(1, 1 - cyclicAniTime * .09, 1);
  }
}

void Character::nodeRender(aiNode* node) {
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

  //render all children
  for (u_int child = 0; child < node->mNumChildren; child++) {
    nodeRender(node->mChildren[child]);
  }
  const aiScene* scene = characterMesh->getScene();

  for (unsigned int mesh = 0; mesh < node->mNumMeshes; mesh++) {
    //Only render Triangles
    if (scene->mMeshes[node->mMeshes[mesh]]->mPrimitiveTypes
        == aiPrimitiveType_TRIANGLE) {
      //Need the name of this mesh
      aiMesh* meshObj = scene->mMeshes[node->mMeshes[mesh]];

      //save pre-animation matrix
      glPushMatrix();

      //animate this mesh
      meshAnimate(meshObj->mName);

      //Load the character texture
      setTexture();

      //Set the material properties
      setMeshMaterials(node->mMeshes[mesh]);

      //Set vertices, normals, and tex coords
      setMeshData(node->mMeshes[mesh]);

      //Get the vector of indices for this mesh
      vector<unsigned> curIndices = *characterMesh->getMeshIndices().at(
          node->mMeshes[mesh]);
      GL_CHECK(glDrawElements(
              GL_TRIANGLES,
              3 * characterMesh->getScene()->mMeshes[node->mMeshes[mesh]]->mNumFaces,
              GL_UNSIGNED_INT, &curIndices[0]));

      //reset the animation transformation
      glPopMatrix();
    }
  }
  glPopMatrix();
}

//This is a slight modification of my 248 assignment 3 code which sets all the vertex data for this mesh
void Character::setMeshData(u_int meshIdx) {
  const aiScene* scene = characterMesh->getScene();
  aiMesh* mesh = scene->mMeshes[meshIdx];

  shader->setVertexAttribArray("normalIn", 3, GL_FLOAT, 0, sizeof(aiVector3D),
      mesh->mNormals);
  shader->setVertexAttribArray("texCoordIn", 2, GL_FLOAT, 0,
      sizeof(aiVector3D), mesh->mTextureCoords[0]);
  shader->setVertexAttribArray("positionIn", 3, GL_FLOAT, 0,
      sizeof(aiVector3D), mesh->mVertices);
  shader->setUniform1f("t", straightAniTime);
}

//This is a slight modification of my 248 assignment 3 code which sets the material information
void Character::setMeshMaterials(u_int meshIdx) {
  const aiScene* scene = characterMesh->getScene();
  aiMaterial* material =
      scene->mMaterials[scene->mMeshes[meshIdx]->mMaterialIndex];
  aiColor3D color;
  material->Get(AI_MATKEY_COLOR_DIFFUSE,color) ;
  shader->setUniform3f("Kd", color.r, color.g, color.b);

  shader->setUniform3f("Ks", color.r, color.g, color.b);

  shader->setUniform3f("Ka", color.r, color.g, color.b);

  // Specular power
  float value;
  if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS,value) ) {
    shader->setUniform1f("alpha", value);
  } else {
    shader->setUniform1f("alpha", 1);
  }
}

void Character::setTexture() {
  GLint textureHandle = glGetUniformLocation(shader->programID(), "textureImg");

  if (textureHandle == -1) {
    cerr << "Error retrieving id for character texture."<<endl;
  }

  glUniform1i(textureHandle, 0);
  glActiveTexture(GL_TEXTURE0);
  texture.Bind();
}
