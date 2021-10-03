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
	const Texture* m_heightmap;
	const Texture* m_colormap;

private:
	static GLsizei workGroupWidth;

	GLsizei m_width;
	GLsizei m_height;

	ComputeShader shader;
	GLuint colorTexture;
	GLuint depthTexture;

	GLuint terrainFB;


	float m_terrainScale;
	GLuint m_sampleCount;
	GLuint sampleDistsSBBO;


public:
	TerrainRenderer(
			GLsizei width,
			GLsizei height,
			const Texture* heightmap,
			const Texture* colormap,
			float terrainScale = 100);


	virtual ~TerrainRenderer();


	void renderTerrain();

	void updateSize( GLsizei width, GLsizei height );

	void genSampleDists();
	void genSampleDists( GLsizei sampleCount );


	void setTerrainScale( float terrainScale );

	float getTerrainScale() const;

private:
	void deleteTextures();

	void genTextures();



};

#endif /* INCLUDE_TERRAINRENDERER_H_ */
