/*
 * TerrainRenderer.h
 *
 *  Created on: 26 sept. 2021
 *      Author: Mathieu
 */

#ifndef INCLUDE_TERRAINRENDERER_H_
#define INCLUDE_TERRAINRENDERER_H_


#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Texture.h"

#include "ComputeShader.h"



class TerrainRenderer {



public:
	Texture* heightmap;
	Texture* colormap;

private:
	static GLsizei workGroupWidth;

	GLsizei m_width;
	GLsizei m_height;

	ComputeShader shader;
	GLuint colorTexture;
	GLuint depthTexture;

	GLuint terrainFB;


	GLsizei m_sampleCount;
	GLfloat* sampleDists;


public:
	TerrainRenderer(GLsizei width, GLsizei height, GLsizei sampleCount = 100);


	virtual ~TerrainRenderer();


	void renderTerrain();

	void updateSize( GLsizei width, GLsizei height );

	void genSampleDists();
	void genSampleDists( GLsizei sampleCount );

private:
	void deleteTextures();

	void genTextures();


};

#endif /* INCLUDE_TERRAINRENDERER_H_ */
