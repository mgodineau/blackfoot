/*
 * Texture.h
 *
 *  Created on: 27 sept. 2021
 *      Author: Mathieu
 */

#ifndef INCLUDE_TEXTURE_H_
#define INCLUDE_TEXTURE_H_

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Texture {



private:
	GLuint texture;


public:
	Texture( const std::string& filename );

	virtual ~Texture();


	void bind( GLenum target = GL_TEXTURE_2D ) const;

	const GLuint getHandler() const;

};

#endif /* INCLUDE_TEXTURE_H_ */
