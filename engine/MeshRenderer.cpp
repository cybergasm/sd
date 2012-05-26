/*
 * MeshRenderer.cpp
 *
 *  Created on: May 21, 2012
 *      Author: emint
 */

#include "MeshRenderer.h"
#include <stdio.h>

MeshRenderer::MeshRenderer() :
  diffuseTex(NULL), normalTex(NULL), heightTex(NULL), specTex(NULL) {

}

#define GL_CHECK(x) {\
  (x);\
  GLenum error = glGetError();\
  if (GL_NO_ERROR != error) {\
    printf("%s\n", gluErrorString(error));\
  }\
}

MeshRenderer::~MeshRenderer() {
  // TODO Auto-generated destructor stub
}

void MeshRenderer::setDiffuseTex(string texName) {
  diffuseTex = (ResourceManager::get())->getTexture(texName);
  diffuseTex->Bind();
  glActiveTexture(GL_TEXTURE0);
  mipmapTexture();
}

void MeshRenderer::setHeightTex(string texName) {
  heightTex = (ResourceManager::get())->getTexture(texName);
  heightTex->Bind();
  glActiveTexture(GL_TEXTURE0);
  mipmapTexture();
}

void MeshRenderer::setNormTex(string texName) {
  normalTex = (ResourceManager::get())->getTexture(texName);
  normalTex->Bind();
  glActiveTexture(GL_TEXTURE0);
  mipmapTexture();
}

void MeshRenderer::setSpecTex(string texName) {
  specTex = (ResourceManager::get())->getTexture(texName);
  specTex->Bind();
  glActiveTexture(GL_TEXTURE0);
  mipmapTexture();
}

void MeshRenderer::setDiffuseTex(sf::Image* tex) {
  diffuseTex = tex;
}

void MeshRenderer::setHeightTex(sf::Image* tex) {
  heightTex = tex;
}

void MeshRenderer::setNormTex(sf::Image* tex) {
  normalTex = tex;
}

void MeshRenderer::setSpecTex(sf::Image* tex) {
  specTex = tex;
}

void MeshRenderer::renderMesh(Mesh3DS* mesh, Shader* shader) const {
  //Remember the program at time of call so we can
  //reset
  GLint oldId;
  glGetIntegerv(GL_CURRENT_PROGRAM, &oldId);
  GL_CHECK(glUseProgram(shader->programID()));
  //Save old state and transform model
  glPushMatrix();

  setWholeMeshTransform();

  nodeRender(mesh->getScene()->mRootNode, mesh, shader);

  glPopMatrix();

  GL_CHECK(glUseProgram(oldId));
}

void MeshRenderer::setWholeMeshTransform() const {

}

void MeshRenderer::setCustomTransformation(string meshName) const {

}

void MeshRenderer::nodeRender(aiNode* node, Mesh3DS* mesh, Shader* shader) const {
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
    nodeRender(node->mChildren[child], mesh, shader);
  }
  const aiScene* scene = mesh->getScene();

  for (unsigned int meshIdx = 0; meshIdx < node->mNumMeshes; meshIdx++) {
    //Only render Triangles
    if (scene->mMeshes[node->mMeshes[meshIdx]]->mPrimitiveTypes
        == aiPrimitiveType_TRIANGLE) {

      //save the pre-mesh transformation matrix
      glPushMatrix();
      aiMesh* meshFromScene = scene->mMeshes[meshIdx];
      setCustomTransformation(string(meshFromScene->mName.data));

      //Set vertices, normals, and tex coords
      setAttributes(mesh, shader, node->mMeshes[meshIdx]);

      //Sets uniforms, like materials
      setUniform(mesh, shader, node->mMeshes[meshIdx]);

      //set the texture
      setTextures(mesh, shader, node->mMeshes[meshIdx]);

      //Get the vector of indices for this mesh
      vector<unsigned> curIndices = *mesh->getMeshIndices().at(
          node->mMeshes[meshIdx]);
      GL_CHECK(
          glDrawElements(
              GL_TRIANGLES,
              3 * mesh->getScene()->mMeshes[node->mMeshes[meshIdx]]->mNumFaces,
              GL_UNSIGNED_INT, &curIndices[0]));
      //reset matrix after mesh is done
      glPopMatrix();
    }
  }

  glPopMatrix();
}

void MeshRenderer::setUniform(Mesh3DS* mesh, Shader* shader, u_int meshIdx) const {
  const Shader::KnownVars* vars = shader->getExpectedVars();
  const aiScene* scene = mesh->getScene();
  aiMesh* meshFromScene = scene->mMeshes[meshIdx];
  aiMaterial* material =
      scene->mMaterials[scene->mMeshes[meshIdx]->mMaterialIndex];
  aiColor3D color;
  material->Get(AI_MATKEY_COLOR_DIFFUSE,color) ;

  int numVars = shader->getExpectedVarsCount();
  for (int i = 0; i < numVars; i++) {
    if (vars[i] == Shader::Time) {
      shader->setTime(getTime());
    } else if (vars[i] == Shader::Ka) {
      shader->setKa(color.r, color.g, color.b);
    } else if (vars[i] == Shader::Kd) {
      shader->setKd(color.r, color.g, color.b);
    } else if (vars[i] == Shader::Ks) {
      shader->setKs(color.r, color.g, color.b);
    } else if (vars[i] == Shader::Shininess) {
      float value;
      if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS,value) ) {
        shader->setShininess(value);
      } else {
        shader->setShininess(1);
      }
    }
  }
  setCustomUniforms(string(meshFromScene->mName.data), shader);
}

void MeshRenderer::setCustomUniforms(string meshName, Shader* shader) const {

}

float MeshRenderer::getTime() const {
  return 0.0f;
}

void MeshRenderer::setTextures(Mesh3DS* mesh, Shader* shader, u_int meshIdx) const {
  const Shader::KnownVars* vars = shader->getExpectedVars();
  int numVars = shader->getExpectedVarsCount();

  int textureCount = 0;
  for (int i = 0; i < numVars; i++) {
    if (vars[i] == Shader::NormalMap) {
      shader->setNormalMap(textureCount);
      glActiveTexture(GL_TEXTURE0 + textureCount);
      normalTex->Bind();
      textureCount++;
    } else if (vars[i] == Shader::HeightMap) {
      shader->setHeightMap(textureCount);
      glActiveTexture(GL_TEXTURE0 + textureCount);
      heightTex->Bind();
      textureCount++;
    } else if (vars[i] == Shader::DiffuseMap) {
      shader->setDiffuseMap(textureCount);
      glActiveTexture(GL_TEXTURE0 + textureCount);
      diffuseTex->Bind();
      textureCount++;
    } else if (vars[i] == Shader::SpecularMap) {
      shader->setSpecularMap(textureCount);
      glActiveTexture(GL_TEXTURE0 + textureCount);
      specTex->Bind();
      textureCount++;
    }
  }

  const aiScene* scene = mesh->getScene();
  aiMesh* meshFromScene = scene->mMeshes[meshIdx];

  setCustomTextures(string(meshFromScene->mName.data), shader, textureCount);
}

void MeshRenderer::setCustomTextures(string meshName, Shader* shader,
    int texCount) const {

}
void MeshRenderer::setAttributes(Mesh3DS* mesh, Shader* shader, u_int meshIdx) const {
  const aiScene* scene = mesh->getScene();
  aiMesh* meshFromScene = scene->mMeshes[meshIdx];

  const Shader::KnownVars* vars = shader->getExpectedVars();
  int numVars = shader->getExpectedVarsCount();
  int stride = sizeof(aiVector3D);

  for (int i = 0; i < numVars; i++) {
    if (vars[i] == Shader::Normal) {
      shader->setNormal(false, stride, meshFromScene->mNormals);
    } else if (vars[i] == Shader::Bitangent) {
      shader->setBitangent(false, stride, meshFromScene->mBitangents);
    } else if (vars[i] == Shader::Tangent) {
      shader->setTangent(false, stride, meshFromScene->mTangents);
    } else if (vars[i] == Shader::TextureCoord) {
      shader->setTextureCoords(false, stride, meshFromScene->mTextureCoords[0]);
    } else if (vars[i] == Shader::Position) {
      shader->setPosition(false, stride, meshFromScene->mVertices);
    }
  }
  setCustomAttributes(string(meshFromScene->mName.data), shader);
}

void MeshRenderer::setCustomAttributes(string meshName, Shader* shader) const {

}

void MeshRenderer::mipmapTexture() const {
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE));
  GL_CHECK(
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
          GL_LINEAR_MIPMAP_NEAREST));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
  GL_CHECK(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
  GL_CHECK(glGenerateMipmapEXT(GL_TEXTURE_2D));
}
