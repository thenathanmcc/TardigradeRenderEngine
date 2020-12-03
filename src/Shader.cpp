/**
 * Shader.cpp Shader implementation code
 * @author: Nathan McCulloch
 */

#include <string>
#include <Shader.hpp>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>


void Shader::loadShaders(std::string vertexShaderFilePath, std::string fragmentShaderFilePath) {
	unsigned int vertexID, fragmentID;

	std::string vertexFileCode;
	std::string fragmentFileCode;

	//Read Vertex Shader file
	std::ifstream vertexShaderFile;
	vertexShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try {
		vertexShaderFile.open(vertexShaderFilePath);
		std::stringstream vertexShaderStream;

		vertexShaderStream << vertexShaderFile.rdbuf();
		vertexShaderFile.close();

		vertexFileCode = vertexShaderStream.str();
	} catch (std::ifstream::failure& err) {
		printf("VERTEX_SHADER_ERROR::FAILED_TO_READ_VERTEX_SHADER_FILE\n");
		return;
	}


	//Read Fragment Shader file
	std::ifstream fragmentShaderFile;
	fragmentShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit);
	try {
		fragmentShaderFile.open(fragmentShaderFilePath);
		std::stringstream fragmentShaderStream;

		fragmentShaderStream << fragmentShaderFile.rdbuf();
		fragmentShaderFile.close();

		fragmentFileCode = fragmentShaderStream.str();
	} catch (std::ifstream::failure& err) {
		printf("FRAGMENT_SHADER_ERROR::FAILED_TO_READ_FRAGMENT_SHADER_FILE\n");
		return;
	}

	const char* vertexShaderCode = vertexFileCode.c_str();
	const char* fragmentShaderCode = fragmentFileCode.c_str();

	//Compile Vertex Shader
	vertexID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexID, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexID);
	checkCompilationErrors(vertexID, "VERTEX_SHADER");

	//Compile Fragment Shader
	fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentID, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentID);
	checkCompilationErrors(fragmentID, "FRAGMENT_SHADER");

	//Create Shader Program and link shaders
	shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexID);
	glAttachShader(shaderProgramID, fragmentID);
	glLinkProgram(shaderProgramID);
	checkLinkingErrors(shaderProgramID);

	//Delete vertex and fragment shaders as they are no longer needed
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}


void Shader::checkCompilationErrors(unsigned int shaderID, std::string shaderType){
	int success;
	char infoLog[1024];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		std::cout <<  shaderType << "_ERROR::FAILED_TO_COMPILE_SHADER" << "\nINFO LOG:\n" << infoLog << std::endl;
	}
}

void Shader::checkLinkingErrors(unsigned int shaderID) {
	int success;
	char infoLog[1024];
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
		std::cout << "SHADER_PROGRAM_ERROR::FAILED_TO_LINK_SHADER_PROGRAM" << "\nINFO LOG:\n" << infoLog << std::endl;
	}
}

//Uniform setter functions
void Shader::setBool(const std::string &UniformName, bool value) const {
	glUniform1i(glGetUniformLocation(shaderProgramID, UniformName.c_str()), (int) value);
}

void Shader::setInt(const std::string &UniformName, int value) const {
	glUniform1i(glGetUniformLocation(shaderProgramID, UniformName.c_str()), value);
}

void Shader::setFloat(const std::string &UniformName, float value) const {
	glUniform1f(glGetUniformLocation(shaderProgramID, UniformName.c_str()), value);
}

void Shader::setMat4(const std::string &UniformName, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(shaderProgramID, UniformName.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::updateViewMatrix(const glm::mat4 &mat) const {
	glUniformMatrix4fv(m_VMID, 1, GL_FALSE, &mat[0][0]);
}

void Shader::updateModelMatrix(const glm::mat4 &mat) const {
	glUniformMatrix4fv(m_MMID, 1, GL_FALSE, &mat[0][0]);
}

void Shader::updateMVPMatrix(const glm::mat4 &mat) const {
	glUniformMatrix4fv(m_MVPID, 1, GL_FALSE, &mat[0][0]);
}

Shader::~Shader(){
	glDeleteProgram(shaderProgramID);
}