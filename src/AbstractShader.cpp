/*
 * AbstractShader.cpp
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#include "AbstractShader.h"

#include <fstream>


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


GLuint AbstractShader::createShader( const std::string& filename, GLenum shaderType ) {


	GLuint shader = glCreateShader(shaderType);

	const std::string* fileContent = readFile(filename);
	const char* fileContent_str = fileContent->c_str();
	glShaderSource(shader, 1, &fileContent_str, NULL);
	delete fileContent;

	glCompileShader(shader);

	glAttachShader(shader, program);
	return shader;
}

std::string* AbstractShader::readFile( const std::string& filename ) const {
	std::string* content = new std::string();

	std::ifstream fileStream (filename);
	while( fileStream.good() ) {
		std::string line;
		std::getline(fileStream, line);
		*content += line + "\n";
	}
		fileStream.close();


	return content;
}

