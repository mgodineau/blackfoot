/*
 * ComputeShader.h
 *
 *  Created on: 6 sept. 2021
 *      Author: mathieu
 */

#ifndef COMPUTESHADER_H_
#define COMPUTESHADER_H_


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "AbstractShader.h"


class ComputeShader : public AbstractShader {




public:
	ComputeShader( const std::string& filename );

	virtual ~ComputeShader();





};

#endif /* COMPUTESHADER_H_ */
