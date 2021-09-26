/*
 * Shader.h
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#ifndef INCLUDE_VFSHADER_H_
#define INCLUDE_VFSHADER_H_


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>


#include "AbstractShader.h"


class VFShader : public AbstractShader {


public:
	VFShader( const std::string& filenameVert, const std::string& filenameFrag );
	virtual ~VFShader();
};

#endif /* INCLUDE_VFSHADER_H_ */
