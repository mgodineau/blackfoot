/*
 * Texture.cpp
 *
 *  Created on: 27 sept. 2021
 *      Author: Mathieu
 */

#include <system_error>


#include <Texture.h>

#include <stb_image.h>

Texture::Texture( const std::string& filename ) :
	texture()
{

	glGenTextures(1, &texture);
	bind();


	GLsizei width, height, ch;
	unsigned char* data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	data = stbi_load(filename.c_str(), &width, &height, &ch, 0);
	if( !data ) {
		std::string msg = "unable to open the file \"" + filename + "\"";
		throw std::system_error( std::error_code(), msg );
	}

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
