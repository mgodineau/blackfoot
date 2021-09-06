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


class ComputeShader {

private:
	const GLuint program;



public:
	ComputeShader( const std::string& filename );
	ComputeShader( const ComputeShader& other );

	virtual ~ComputeShader();


	void useProgram() const;





};

#endif /* COMPUTESHADER_H_ */
