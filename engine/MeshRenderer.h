/*
 * MeshRenderer.h
 *
 *  Created on: May 21, 2012
 *      Author: emint
 */

#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

#include "Shader.h"
#include "Mesh3DS.h"
#include "ResourceManager.h"
#include "Texture.h"

// Open Asset Import Library
#include <assimp/assimp.hpp>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

#include <string>

using namespace std;

class MeshRenderer {
  public:
    MeshRenderer();
    virtual ~MeshRenderer();

    //Sets the appropriate textures. The value is a
    //key into the resource manager. These calls mipmap on
    //call, so should be called infrequently
    void setDiffuseTex(string texName);
    void setNormTex(string texName);
    void setSpecTex(string texName);
    void setHeightTex(string texName);

    //Sets the appropriate texture to the passed in image. Performs no
    //mimap
    void setDiffuseTex(Texture* tex);
    void setNormTex(Texture* tex);
    void setSpecTex(Texture* tex);
    void setHeightTex(Texture* tex);

    //Render call that goes through rendering passed in mesh with the
    //given shader
    void renderMesh(Mesh3DS* mesh, Shader* shader) const;

    /**
     * Custom methods to be overridden for custom functionality
     */
    virtual void setCustomAttributes(string meshName, Shader* shader) const;
    virtual void setCustomTextures(string meshName, Shader* shader,
        int texCount) const;
    virtual void setWholeMeshTransform() const;
    virtual void setCustomTransformation(string meshName) const;
    virtual void setCustomUniforms(string meshName, Shader* shader) const;
    virtual float getTime() const;

  private:
    //Pointers to different textures which we might need
    Texture* diffuseTex;
    Texture* normalTex;
    Texture* heightTex;
    Texture* specTex;

    //Helper function to Mipmap
    void mipmapTexture() const;

    //Renders one node in the aiMesh; called recusively
    void nodeRender(aiNode* node, Mesh3DS* mesh, Shader* shader) const;

    //Sets attributes to pass
    void setAttributes(Mesh3DS* mesh, Shader* shader, u_int meshIdx) const;

    //Sets known textures
    void setTextures(Mesh3DS* mesh, Shader* shader, u_int meshIdx) const;

    //Sets known uniforms
    void setUniform(Mesh3DS* mesh, Shader* shader, u_int meshIdx) const;
};

#endif /* MESHRENDERER_H_ */
