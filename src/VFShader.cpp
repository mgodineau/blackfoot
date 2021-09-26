/*
 * Shader.cpp
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#include <VFShader.h>
#include <iostream>

VFShader::VFShader(const std::string &filenameVert,
		const std::string &filenameFrag) :
		AbstractShader() {



	GLuint vertex = createShaderFromFile(filenameVert, GL_VERTEX_SHADER);
	GLuint fragment = createShaderFromFile(filenameFrag, GL_FRAGMENT_SHADER);

	glLinkProgram(program);


	int success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		std::cout << "erreur lors du link du program" << std::endl;
		char infoLog[512];
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;

	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

VFShader::~VFShader() {
}

