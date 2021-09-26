/*
 * TerrainRenderer.h
 *
 *  Created on: 26 sept. 2021
 *      Author: Mathieu
 */

#ifndef INCLUDE_TERRAINRENDERER_H_
#define INCLUDE_TERRAINRENDERER_H_


#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "ComputeShader.h"



class TerrainRenderer {

private:
	static GLsizei workGroupWidth;

	GLsizei m_width;
	GLsizei m_height;

	ComputeShader shader;
	GLuint colorTexture;
	GLuint depthTexture;

	GLuint terrainFB;

public:
	TerrainRenderer(GLsizei width, GLsizei height);


	virtual ~TerrainRenderer();


	void renderTerrain();

	void updateSize( GLsizei width, GLsizei height );


private:
	void deleteTextures();

	void genTextures();

};

#endif /* INCLUDE_TERRAINRENDERER_H_ */
