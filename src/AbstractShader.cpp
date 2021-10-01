/*
 * AbstractShader.cpp
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#include "AbstractShader.h"

#include <fstream>
#include <sstream>

#include <iostream> //DEBUG


AbstractShader::AbstractShader()
	: program( glCreateProgram() )
{

}


AbstractShader::~AbstractShader() {
	glDeleteProgram(program);
}


void AbstractShader::useProgram() const {
	glUseProgram(program);
}


GLuint AbstractShader::getUniformLocation(const GLchar* name) const {
	return glGetUniformLocation(program, name);
}

GLuint AbstractShader::getProgram() {
	return program;
}

GLuint AbstractShader::createShader( const char* source, GLenum shaderType ) {


	GLuint shader = glCreateShader(shaderType);

//	const std::string* fileContent = readFile(filename);
//	std::cout << *fileContent << std::endl;

	const char* fileContent_str = source;
	glShaderSource(shader, 1, &fileContent_str, NULL);
	glCompileShader(shader);

	GLint success;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &success);
	char infoLog[512];
	glGetShaderInfoLog( shader, 512, NULL, infoLog );
	std::cout << infoLog << std::endl;
	if( !success ) {
		throw std::runtime_error("Error while compiling the shader");
	}

	glAttachShader(program, shader);

	return shader;
}

GLuint AbstractShader::createShaderFromFile( const std::string& filename, GLenum shaderType ) {
	std::string content;

	std::ifstream fileStream (filename);
	std::stringstream strStream;
	strStream << fileStream.rdbuf();
	content = strStream.str();


	return createShader(content.c_str(), shaderType);

}




