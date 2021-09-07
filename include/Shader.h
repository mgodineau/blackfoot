/*
 * Shader.h
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#ifndef INCLUDE_SHADER_H_
#define INCLUDE_SHADER_H_


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


#include "AbstractShader.h"


class Shader : public AbstractShader {


public:
	Shader( const std::string& filenameVert, const std::string& filenameFrag );
	virtual ~Shader();
};

#endif /* INCLUDE_SHADER_H_ */
