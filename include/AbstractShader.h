/*
 * AbstractShader.h
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#ifndef ABSTRACTSHADER_H_
#define ABSTRACTSHADER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

class AbstractShader {

protected:
	GLuint program;

protected:
	AbstractShader();

public:
	virtual ~AbstractShader();

	void useProgram() const;

	GLuint getUniformLocation( const GLchar* name ) const;

	GLuint getProgram();


	void setUniform1i( const GLchar* name, GLint value );


protected:
	GLuint createShader(const char *source, GLenum shaderType);

	GLuint createShaderFromFile(const std::string &filename,
			GLenum shaderType);



};

#endif /* ABSTRACTSHADER_H_ */
