#ifndef SHADER_H
#define SHADER_H

/**
 * Stealing the assignment three shader class for fun and profit.
 */

#include <GL/glew.h>
#include <string>
#include <vector>

class Shader {
  public:
    /**
     * Enumeration of the known inputs the shader could expect
     */
    enum KnownVars {
      Tangent,
      Bitangent,
      Normal,
      Position,
      TextureCoord,
      Time,
      Ka,
      Ks,
      Kd,
      Shininess,
      NormalMap,
      HeightMap,
      DiffuseMap,
      SpecularMap,
    };

    /**
     * Loads a vertex shader and fragment shader, compiles them, and links
     * them into a single GPU program.  The vertex shader file should be
     * at <path>.frag.glsl, and the fragment shader file should be at
     * <path>.vert.glsl.  If the program fails to compile, then the loaded()
     * function will return false.
     * @param path the path to the vertex/fragment shader files
     */
    Shader(const std::string& path);

    /**
     * This function deallocates the shader.
     */
    ~Shader();

    /**
     * Returns the path used to load this shader (without the file extensions)
     * @return the shader path
     */
    const std::string& path() const;

    /**
     * Returns the OpenGL handle for the GPU program.  You can use the handle
     * with OpenGL like this: glUseProgram(shader->programID());
     * Calling glUseProgram() will replace OpenGL's fixed pipeline with your
     * vertex/fragment shader.  You can also use the program handle to
     * get/set uniform values and attributes using glUniformLocation(),
     * glUniform(), glAttributeLocation(), and glAttribute().
     * @return OpenGL handle to the GPU program
     */
    GLuint programID() const;

    /**
     * If the shader loaded successfully, then this function will return true.
     * If the shader didn't load successfully, the error messages can be
     * retrieved from the errors() function.
     */
    bool loaded() const;

    /**
     * Returns a string containing all the shader compile errors.
     * @return shader compilation errors
     */
    const std::string& errors() const;

    /**
     * Sets attibute information on shader using vertex attribute array.
     * Gets id as specified by param 'idName.' Rest of the parameters are
     * as specified to glVertexAttribPointer
     *
     * Does appropriate sanity checks on id and writes out error if problem
     * retrieving value.
     */
    void setVertexAttribArray(std::string idName, GLint size, GLint type,
        bool normalized, GLsizei stride, GLvoid* data) const;

    /**
     * Sets 1-float worth uniform information to id specified by param 'idName'
     *
     * Does appropriate sanity checks on id and writes out error if problem
     * retrieving value.
     */
    void setUniform1f(std::string idName, float value) const;

    /**
     * Sets 2-float worth uniform information to id specified by param 'idName'
     *
     * Does appropriate sanity checks on id and writes out error if problem
     * retrieving value.
     */
    void setUniform2f(std::string idName, float value, float value2) const;

    /**
     * Sets 3-float worth uniform information to id specified by param 'idName'
     *
     * Does appropriate sanity checks on id and writes out error if problem
     * retrieving value.
     */
    void setUniform3f(std::string idName, float value1, float value2,
        float value3) const;

    /**
     * Sets 4-float worth uniform information to id specified by param 'idName'
     *
     * Does appropriate sanity checks on id and writes out error if problem
     * retrieving value.
     */
    void setUniform4f(std::string idName, float value1, float value2,
        float value3, float value4) const;

    /**
     * Sets 1-int worth uniform information to id specified by param 'idName'
     *
     * Does appropriate sanity checks on id and writes out error if problem
     * retrieving value.
     */
    void setUniform1i(std::string idName, int value) const;


    /**
     * The following presents setters for a variety of semantically significant variables
     * that are likely to be used by many shaders. By default these methods do nothing
     * and have to be extended by a specific shader type identifying where they store
     * specified data
     */
    virtual void setTangent(bool normalized, GLsizei stride, GLvoid* data) const;
    virtual void setBitangent(bool normalized, GLsizei stride, GLvoid* data) const;
    virtual void setNormal(bool normalized, GLsizei stride, GLvoid* data) const;
    virtual void setPosition(bool normalized, GLsizei stride, GLvoid* data) const;
    virtual void setTextureCoords(bool normalized, GLsizei stride, GLvoid* data) const;
    virtual void setTime(float in1) const;
    virtual void setKa(float in1, float in2, float in3) const;
    virtual void setKs(float in1, float in2, float in3) const;
    virtual void setKd(float in1, float in2, float in3) const;
    virtual void setShininess(float in1) const;
    virtual void setNormalMap(int in1) const;
    virtual void setHeightMap(int in1) const;
    virtual void setDiffuseMap(int in1) const;
    virtual void setSpecularMap(int in1) const;

    /**
     * Returns the list of variables this shader expects. Returns NULL unless
     * overridden
     */
    virtual const KnownVars* getExpectedVars() const;
  private:
    std::vector<char> readSource(const std::string& path);

    std::string path_;
    std::string errors_;
    GLuint vertexShaderID_;
    GLuint fragmentShaderID_;
    GLuint programID_;
    bool loaded_;
};

#endif

