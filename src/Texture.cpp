/*
 * Texture.cpp
 *
 *  Created on: 27 sept. 2021
 *      Author: Mathieu
 */

#include <Texture.h>

#include <stb_image.h>

Texture::Texture( const std::string& filename ) :
	texture()
{

	glGenTextures(1, &texture);
	bind();


	GLsizei width, height, ch;
	unsigned char* data;



	stbi_load(filename.c_str(), &width, &height, &ch, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}

Texture::~Texture() {
	glDeleteTextures(1, &texture);
}


void Texture::bind( GLenum target ) const {
	glBindTexture( target, texture );
}


const GLuint Texture::getHandler() const {
	return texture;
}
