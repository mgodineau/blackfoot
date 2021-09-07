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


//protected:
	GLuint createShader( const std::string& filename, GLenum shaderType );

	std::string* readFile(const std::string& filename) const;


};






#endif /* ABSTRACTSHADER_H_ */
