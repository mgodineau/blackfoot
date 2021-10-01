/*
 * main.cpp
 *
 *  Created on: 5 sept. 2021
 *      Author: mathieu
 */

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <VFShader.h>

#include "stb_image.h"


#include "ComputeShader.h"
#include "TerrainRenderer.h"






//GLuint terrainRenderTexture;
GLsizei m_width, m_height;

//GLuint FBO;
TerrainRenderer* terrain;


void framebuffer_size_callback( GLFWwindow* window, int width, int height );
GLuint readTexture( const std::string& filename );

int main ( int argc, char* argv[] ) {

	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); //TODO changer pour CORE_PROFILE

	GLFWwindow* window = glfwCreateWindow(600, 400, "ComancheLike", NULL, NULL);
	if( window == nullptr ) {
		std::cerr << "failed to create glfw window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if( !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress) ) {
		std::cerr << "failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}


	m_width = 600;
	m_height = 400;

	glViewport(0, 0, m_width, m_height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	Texture heightmap("images/heightmap.jpg");
	terrain = new TerrainRenderer(m_width, m_height, &heightmap, &heightmap, 200, 10);


	//main loop
	while( !glfwWindowShouldClose(window) ) {


		terrain->renderTerrain();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	delete terrain;

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
	m_width = width;
	m_height = height;

	terrain->updateSize(m_width, m_height);

	glViewport(0, 0, m_width, m_height);
}





GLuint readTexture( const std::string& filename ) {

	int width, height, ch;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &ch, 0);


	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);

	return texture;
}


