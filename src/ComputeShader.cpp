/*
 * ComputeShader.cpp
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#include "ComputeShader.h"

#include <iostream> //tmp
#include <fstream>

ComputeShader::ComputeShader( const std::string& filename )
	: program( glCreateProgram() )
{

	GLuint shader = glCreateShader( GL_COMPUTE_SHADER );

	std::string source;
	std::ifstream fileStream (filename);
	while( fileStream.good() ) {
		std::string line;
		std::getline(fileStream, line);
		source += line + "\n";
	}
	fileStream.close();


	std::cout << "content of : \"" << filename << "\" : " << std::endl
			<< source << std::endl;

	const char* source_cStr = source.c_str();
	glShaderSource(shader, 1, &source_cStr, NULL);
	glCompileShader(shader);


	glAttachShader( program, shader );
	glLinkProgram(program);

	glDeleteShader(shader);
}


ComputeShader::ComputeShader( const ComputeShader& other )
	: program(other.program)
{

}



ComputeShader::~ComputeShader() {
	glDeleteProgram(program);
}

void ComputeShader::useProgram() const {
	glUseProgram( program );
}
