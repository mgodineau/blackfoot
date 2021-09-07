/*
 * Shader.cpp
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#include <Shader.h>

Shader::Shader( const std::string& filenameVert, const std::string& filenameFrag ) {

	GLuint vert = createShader(filenameVert, GL_VERTEX_SHADER);
	GLuint frag = createShader(filenameFrag, GL_FRAGMENT_SHADER);


	glLinkProgram(program);

	glDeleteShader(frag);
	glDeleteShader(vert);

}

Shader::~Shader() {
}

