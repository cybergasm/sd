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

Character::Character() :
  aniTime(0), aniTimeDir(1), xPos(0), yPos(0), zPos(0),
      characterMesh("models/main_character.3ds") {
  shader = new Shader("shaders/character");

  if (!shader->loaded()) {
    cerr << shader->errors() << endl;
    exit(-1);
  }

  if (!texture.LoadFromFile("textures/main_char_tex.jpg")) {
    cerr << "Error loading character textures." << endl;
  }

}

Character::~Character() {
}

void Character::move(aiVector3D translation) {
  xPos += translation.x;
  yPos += translation.y;
  zPos += translation.z;
}

void Character::render() {
  aniTime +=  aniTimeDir*.02;
  if (aniTime > 10) {
    aniTimeDir = -1;
  } else if (aniTime < 0) {
    aniTimeDir = 1;
  }

  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader->programID()));
  glPushMatrix();
  glTranslatef(xPos, yPos, zPos);
  nodeRender(characterMesh.getScene()->mRootNode);
  GL_CHECK(glUseProgram(oldId));
  glPopMatrix();
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
  const aiScene* scene = characterMesh.getScene();

  for (unsigned int mesh = 0; mesh < node->mNumMeshes; mesh++) {
    //Only render Triangles
    if (scene->mMeshes[node->mMeshes[mesh]]->mPrimitiveTypes
        == aiPrimitiveType_TRIANGLE) {
      aiMesh* meshObj = scene->mMeshes[node->mMeshes[mesh]];
      glPushMatrix();
      if (meshObj->mName == aiString("0") || meshObj->mName == aiString("1")) {
        glRotatef(aniTime, 1, 1, 0);
      } else if (meshObj->mName == aiString("2")) {
        glScalef(1, 1 - aniTime*.06, 1);
      }
      //Load the character texture
      setTexture();
      //Set the material properties
      //setMeshMaterials(node->mMeshes[mesh]);
      //Set vertices, normals, and tex coords
      setMeshData(node->mMeshes[mesh]);

      //Get the vector of indices for this mesh
      vector<unsigned> curIndices = *characterMesh.getMeshIndices().at(
          node->mMeshes[mesh]);
      GL_CHECK(glDrawElements(
              GL_TRIANGLES,
              3 * characterMesh.getScene()->mMeshes[node->mMeshes[mesh]]->mNumFaces,
              GL_UNSIGNED_INT, &curIndices[0]));
      glPopMatrix();
    }
  }
  glPopMatrix();
}

//This is a slight modification of my 248 assignment 3 code which sets all the vertex data for this mesh
void Character::setMeshData(u_int meshIdx) {
  const aiScene* scene = characterMesh.getScene();
  aiMesh* mesh = scene->mMeshes[meshIdx];
  // Get a handle to the variables for the vertex data inside the shader.
  GLint position = glGetAttribLocation(shader->programID(), "positionIn");
  GLint texcoord = glGetAttribLocation(shader->programID(), "texCoordIn");
  GLint normal = glGetAttribLocation(shader->programID(), "normalIn");

  if (position == -1) {
    cerr << "Position ID not found." << endl;
  }

  if (texcoord == -1) {
    cerr << "Texcoord ID not found." << endl;
  }

  if (normal == -1) {
    cerr << "Normal ID not found." << endl;
  }

  GL_CHECK(glEnableVertexAttribArray(position));
  GL_CHECK(glVertexAttribPointer(position, 3, GL_FLOAT, 0, sizeof(aiVector3D),
          mesh->mVertices));

  // Texture coords.  Note the [0] at the end, very important
  GL_CHECK(glEnableVertexAttribArray(texcoord));
  GL_CHECK(glVertexAttribPointer(texcoord, 2, GL_FLOAT, 0, sizeof(aiVector3D),
          mesh->mTextureCoords[0]));

  // Normals
  GL_CHECK(glEnableVertexAttribArray(normal));
  GL_CHECK(glVertexAttribPointer(normal, 3, GL_FLOAT, 0, sizeof(aiVector3D),
          mesh->mNormals));
}

//This is a slight modification of my 248 assignment 3 code which sets the material information
void Character::setMeshMaterials(u_int meshIdx) {
  const aiScene* scene = characterMesh.getScene();
  aiMaterial* material =
      scene->mMaterials[scene->mMeshes[meshIdx]->mMaterialIndex];
  aiColor3D color;

  // Get a handle to the diffuse, specular, and ambient variables
  // inside the shader.  Then set them with the diffuse, specular, and
  // ambient color.
  GLint diffuse = glGetUniformLocation(shader->programID(), "Kd");
  GLint specular = glGetUniformLocation(shader->programID(), "Ks");
  GLint ambient = glGetUniformLocation(shader->programID(), "Ka");
  GLint shininess = glGetUniformLocation(shader->programID(), "alpha");

  if (diffuse == -1) {
    cerr << "Diffuse ID not found." << endl;
  }

  if (specular == -1) {
    cerr << "Specular ID not found." << endl;
  }

  if (ambient == -1) {
    cerr << "Ambient ID not found." << endl;
  }

  if (shininess == -1) {
    cerr << "Shininess ID not found." << endl;
  }
  material->Get(AI_MATKEY_COLOR_DIFFUSE,color) ;
  GL_CHECK(glUniform3f(diffuse, color.r, color.g, color.b));

  // Specular material
  material->Get(AI_MATKEY_COLOR_DIFFUSE,color) ;
  GL_CHECK(glUniform3f(specular, color.r, color.g, color.b));

  // Ambient material
  material->Get(AI_MATKEY_COLOR_DIFFUSE,color) ;
  GL_CHECK(glUniform3f(ambient, color.r, color.g, color.b));

  // Specular power
  float value;
  if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS,value) ) {
    GL_CHECK(glUniform1f(shininess, value));
  } else {
    GL_CHECK(glUniform1f(shininess, 1));
  }
}

void Character::setTexture() {
  GLint textureHandle = glGetUniformLocation(shader->programID(), "textureImg");
  glUniform1i(textureHandle, 0); // Making the texture be GL_TEXTURE0
  glActiveTexture(GL_TEXTURE0);
  texture.Bind();
}
