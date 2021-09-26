/*
 * TerrainRenderer.cpp
 *
 *  Created on: 26 sept. 2021
 *      Author: Mathieu
 */

#include <TerrainRenderer.h>


GLsizei TerrainRenderer::workGroupWidth = 128;



TerrainRenderer::TerrainRenderer( GLsizei width, GLsizei height ) :
	m_width(width),
	m_height(height),
	shader("shaders/terrain.compute"),
//	shader("shaders/tiles.compute"),
	colorTexture(),
	depthTexture(),
	terrainFB()
{
	glGenFramebuffers(1, &terrainFB);


	genTextures();
}



TerrainRenderer::~TerrainRenderer() {
	glDeleteFramebuffers(1, &terrainFB);
	deleteTextures();
}


void TerrainRenderer::renderTerrain() {

	glBindImageTexture(0, colorTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	glBindImageTexture(1, depthTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	shader.useProgram();
	glDispatchCompute(m_width / workGroupWidth, 1, 1);
//	glDispatchCompute(m_width / 10, m_height / 10, 1);
	glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );



	glBindFramebuffer(GL_READ_FRAMEBUFFER, terrainFB);
	glBlitFramebuffer(
		0, 0, m_width, m_height,
		0, 0, m_width, m_height,
		GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
		GL_NEAREST
	);

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}



void TerrainRenderer::updateSize( GLsizei width, GLsizei height ) {
	m_width = width;
	m_height = height;

	deleteTextures();
	genTextures();
}


void TerrainRenderer::deleteTextures() {
	glDeleteTextures(1, &colorTexture);
	glDeleteTextures(1, &depthTexture);
}



void TerrainRenderer::genTextures() {
	glBindFramebuffer(GL_FRAMEBUFFER, terrainFB);


	glGenTextures(1, &colorTexture);
	glBindTexture(GL_TEXTURE_2D, colorTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_width, m_height, 0, GL_RGBA, GL_FLOAT, NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);


	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_width, m_height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
