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
	: AbstractShader()
{

	GLuint shader = createShaderFromFile(filename, GL_COMPUTE_SHADER);

	glLinkProgram(program);
	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "erreur lors du link du program" << std::endl;
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
	}

	glDeleteShader(shader);
}


ComputeShader::~ComputeShader() {}
