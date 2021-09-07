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
#include "Shader.h"


float viewportVertices[] =
{
	0, 0, 0,
	1, 0, 0,
	0, 1, 0,
	0.8f, 0.4f, 0
};


unsigned int viewportTriangles[] =
{
	0, 1, 2,
	1, 2, 3
};


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

	Shader viewportShader("shaders/viewport.vert", "shaders/viewport.frag");


	//VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(viewportVertices), viewportVertices, GL_STATIC_DRAW );

	//EBO
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(viewportTriangles), viewportTriangles, GL_STATIC_DRAW );

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0); //unbinding the VAO

//	try {
//		ComputeShader testComputeShader(std::string("shaders/tiles.compute"));
//	} catch ( const std::exception& e ) {
//		std::cout << e.what() << std::endl;
//	}

	//main loop
	while( !glfwWindowShouldClose(window) ) {

		glBindVertexArray(VAO);
//		viewportShader.useProgram();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



//		glBindBuffer(ebo);
//		glDrawElements(mode, count, type, indices)

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

