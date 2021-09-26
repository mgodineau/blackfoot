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

#include "ComputeShader.h"

#include "stb_image.h"


float viewportVertices[] =
{
	-1, -1, 0,
	1, -1, 0,
	-1, 1, 0,
	1, 1, 0
};


unsigned int viewportTriangles[] =
{
	0, 1, 2,
	1, 2, 3
};


GLuint terrainRenderTexture;


void framebuffer_size_callback( GLFWwindow* window, int width, int height );
void renderImage();
GLuint genRenderTexture( GLuint width, GLuint height );
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


	GLuint width = 600;
	GLuint height = 400;

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);




	terrainRenderTexture = genRenderTexture(width, height);
	GLuint brickTex = readTexture("images/brick.jpg");




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


	VFShader viewportShader("shaders/viewport.vert", "shaders/viewport.frag");
	ComputeShader testComputeShader(std::string("shaders/tiles.compute"));

	//main loop
	while( !glfwWindowShouldClose(window) ) {

		//compute shader
		//glBindTexture(GL_TEXTURE_2D, terrainRenderTexture);
		glBindImageTexture(0, terrainRenderTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
		viewportShader.useProgram();
		glDispatchCompute(1, 1, 1);

		glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );



		// affichage sur l'écran
		glBindVertexArray(VAO);
//		glBindTexture(GL_TEXTURE_2D, terrainRenderTexture);
		glBindTexture(GL_TEXTURE_2D, brickTex);

		viewportShader.useProgram();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);




		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


void framebuffer_size_callback( GLFWwindow* window, int width, int height ) {
	glViewport(0, 0, width, height);
	terrainRenderTexture = genRenderTexture(width, height);
}


void renderImage() {

}


GLuint genRenderTexture( GLuint width, GLuint height ) {

	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture( GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);


	return texture;
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


