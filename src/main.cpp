/*
 * main.cpp
 *
 *  Created on: 5 sept. 2021
 *      Author: mathieu
 */

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "ComputeShader.h"



GLuint terrainRenderTexture;


void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void renderImage();

int main ( int argc, char* argv[] ) {

	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE); //TODO changer pour CORE_PROFILE

	GLFWwindow* window = glfwCreateWindow(600, 400, "ComancheLike", nullptr, nullptr);
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


	glViewport(0, 0, 600, 400);


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glGenTextures(1, &terrainRenderTexture);
	glTexImage1D(GL_TEXTURE_2D, 0, GL_RGBA, 600, 400, GL_RGB, GL_BYTE, nullptr);



	try {
		ComputeShader testComputeShader(std::string("shaders/tiles.compute"));
	} catch ( const std::exception& e ) {
		std::cout << e.what() << std::endl;
	}

	//main loop
	while( !glfwWindowShouldClose(window) ) {

		renderImage();


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
	glViewport(0, 0, width, height);
}


void renderImage() {

}

