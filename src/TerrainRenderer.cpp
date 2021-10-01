/*
 * TerrainRenderer.cpp
 *
 *  Created on: 26 sept. 2021
 *      Author: Mathieu
 */

#include <TerrainRenderer.h>

#include <iostream>

GLsizei TerrainRenderer::workGroupWidth = 128;



TerrainRenderer::TerrainRenderer(
		GLsizei width,
		GLsizei height,
		const Texture* heightmap,
		const Texture* colormap,
		GLsizei sampleCount,
		float terrainScale
) :
	m_heightmap(heightmap),
	m_colormap(colormap),
	m_width(width),
	m_height(height),
	shader("shaders/terrain.compute"),
	colorTexture(),
	depthTexture(),
	terrainFB(),
	m_terrainScale(terrainScale),
	m_sampleCount( sampleCount ),
	sampleDistsSBBO()
{
	glGenFramebuffers(1, &terrainFB);
	glGenBuffers(1, &sampleDistsSBBO);

	setTerrainScale(m_terrainScale);
	genSampleDists();
	genTextures();
}



TerrainRenderer::~TerrainRenderer() {
	glDeleteFramebuffers(1, &terrainFB);
	glDeleteBuffers(1, &sampleDistsSBBO);
	deleteTextures();
}


void TerrainRenderer::renderTerrain() {


	glActiveTexture(GL_TEXTURE0);
	m_heightmap->bind();

	glActiveTexture(GL_TEXTURE1);
	m_colormap->bind();

	glBindImageTexture(0, colorTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
	glBindImageTexture(1, depthTexture, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_R32F);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 3, sampleDistsSBBO );

	shader.useProgram();
	glDispatchCompute(m_width / workGroupWidth + 1, 1, 1);
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




void TerrainRenderer::genSampleDists() {
	genSampleDists(m_sampleCount);
}


void TerrainRenderer::genSampleDists( GLsizei sampleCount ) {

	m_sampleCount = sampleCount;

	GLfloat sampleDists[m_sampleCount];


	const GLfloat near = 1.0f;
	const GLfloat far = 100.0f;

	if( m_sampleCount != 0 ) {
		sampleDists[m_sampleCount-1] = near;
		sampleDists[0] = far;
	}

	const float heightDelta = (1.0f - near / far) / m_sampleCount;
	const float heightDeltaOverNear = heightDelta / near;

	for( GLuint i=sampleCount-2; i>0; i-- ) {
		sampleDists[i] = 1.0f / ( 1.0f/sampleDists[i+1] - heightDeltaOverNear );
	}


	shader.useProgram();


	glUniform1ui( shader.getUniformLocation("sampleCount"), m_sampleCount );
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, sampleDistsSBBO);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(float) * m_sampleCount, sampleDists, GL_STATIC_READ);

}


void TerrainRenderer::setTerrainScale( float terrainScale ) {
	m_terrainScale = terrainScale;

	shader.useProgram();
	glUniform1f( shader.getUniformLocation("terrainScale"), m_terrainScale );
}

float TerrainRenderer::getTerrainScale() const {
	return m_terrainScale;
}

