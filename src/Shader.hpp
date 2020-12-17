/**
 * Shader.hpp class definition
 * @author: Nathan McCulloch
 */


#ifndef SHADER_HPP
#define SHADER_HPP


#include <string>
#include "Texture.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>



class Shader {
public:

    /* Default Constructor */
    Shader() {}

    /* Constructor using file paths */
    Shader(std::string vertexShaderFilePath, std::string fragmentShaderFilePath){
    	loadShaders(vertexShaderFilePath, fragmentShaderFilePath);
        m_MVPID = glGetUniformLocation(shaderProgramID, "MVP");
        m_MMID = glGetUniformLocation(shaderProgramID, "M");
        m_VMID = glGetUniformLocation(shaderProgramID, "V");
    }

    GLuint getShaderID();

    void use();

    void loadShaders(std::string vertexShaderFilePath, std::string fragmentShaderFilePath);

    void checkCompilationErrors(unsigned int shaderID, std::string shaderType);

    void checkLinkingErrors(unsigned int shaderID);

    ~Shader();

    void setBool(const std::string &UniformName, bool value) const;

    void setInt(const std::string &UniformName, int value) const;

    void setFloat(const std::string &UniformName, float value) const;

    void setMat4(const std::string &UniformName, const glm::mat4 &mat) const;

    void updateViewMatrix(const glm::mat4 &mat) const;

    void updateModelMatrix(const glm::mat4 &mat) const;

    void updateMVPMatrix(const glm::mat4 &mat) const;

    void setRenderMode(float renderMode);

    void setTexture(Texture* texture);

    void setupShaderParameters();

    void setDiffuseColour(glm::vec3 colour);

    void setAmbientColour(glm::vec3 colour);

    void setSpecularColour(glm::vec3 colour);

    void setOpacity(float opacity);

    void setLightPosition(glm::vec3 lightPos);

private:
    std::string m_shaderName;
    float m_renderMode;

    glm::vec4 m_diffuseColour;
    glm::vec4 m_ambientColour;
    glm::vec4 m_specularColour;
    float m_opacity;

    Texture* m_texture;
    GLuint m_textureID;
    GLuint m_lightPosID;
    glm::vec3 m_lightPos;

    GLuint shaderProgramID;  // Shader Program ID
    GLuint m_MVPID;          // MVP Matrix ID
    GLuint m_VMID;           // View Matrix ID
    GLuint m_MMID;           // Model Matrix ID

 };
 #endif