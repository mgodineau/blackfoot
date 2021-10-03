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

	terrain = nullptr;
	Texture* heightmap = nullptr;
	Texture* colormap = nullptr;
	
	try {
//		heightmap = new Texture("images/heightmap.jpg");
		heightmap = new Texture("images/terrain/height/D16rgb.png");
		colormap = new Texture("images/terrain/color/C16W.png");
	
		terrain = new TerrainRenderer(m_width, m_height, heightmap, colormap, 50);
	} catch( const std::exception& e ) {
		std::cout << e.what() << std::endl;
	}
	
	//main loop
	while( !glfwWindowShouldClose(window) ) {
		
//		double start = glfwGetTime();
		
		terrain->renderTerrain();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
		
//		double time = glfwGetTime() - start;
//		std::cout << "time = " << time << "s; fps = " << 1.0/time << std::endl;
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

