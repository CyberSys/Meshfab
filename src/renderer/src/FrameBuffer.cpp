#include "FrameBuffer.h"

#include <iostream>
#include <glew.h>

Frambuffer::Frambuffer() :
	m_width(0),
	m_height(0),
	prev_frame(0)
{
}

Frambuffer::~Frambuffer()
{
}

void Frambuffer::Create(int width, int height)
{
	m_width = width;
	m_height = height;

	//we need to kkeep track of current frmebuffer 
	//bounded to rebind the previous one
	int prev_framebuffer = 0;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev_framebuffer);

	glGenFramebuffers(1, &m_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	// create a color attachment texture
	glGenTextures(1, &colortexture);
	glBindTexture(GL_TEXTURE_2D, colortexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colortexture, 0);

	// create a renderbuffer object for depth and stencil attachment
	glGenRenderbuffers(1, &depthtexture);
	glBindRenderbuffer(GL_RENDERBUFFER, depthtexture);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthtexture); // now actually attach it

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	//rebind to previous one
	glBindFramebuffer(GL_FRAMEBUFFER, prev_framebuffer);
}

void Frambuffer::resize(int newwidth, int newheight)
{
	m_width = newwidth;
	m_height = newheight;

	//delete old textures 
	glDeleteFramebuffers(1, &m_id);
	glDeleteTextures(1,&colortexture);
	glDeleteRenderbuffers(1,&depthtexture);

	//recreate textures with new size
	Create(newwidth,newheight);
}

unsigned int Frambuffer::ColorTexture_Get()
{
	return colortexture;
}

unsigned int Frambuffer::DepthTexture_Get()
{
	return depthtexture;
}

float Frambuffer::AspectRatio()
{
	return (float)(m_width) / (float)(m_height);
}

void Frambuffer::begin()
{
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &prev_frame);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void Frambuffer::end()
{
	glBindFramebuffer(GL_FRAMEBUFFER, prev_frame);
	prev_frame = 0;
}
