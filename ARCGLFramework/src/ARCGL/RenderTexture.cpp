#include "ARCGL\RenderTexture.h"

#include "GL\glew.h"
#include "SDL\sdl_opengl.h"

#include <iostream>

RenderTexture::RenderTexture(unsigned int width, unsigned int height) : Texture(width, height)
{

	// generate the frame buffer
	//-------------------------
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	// bind the texture
	glBindTexture(GL_TEXTURE_2D, m_glTextureHandle);

	// make sure the texture paramaters are set
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Generate a buffer to store the depth buffer
	glGenRenderbuffers(1, &m_rbo_depth );
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo_depth);

   //Attach 2D texture to this FBO
   glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_glTextureHandle, 0);
   //-------------------------
   //glGenRenderbuffers(1, &m_rbo);
   //glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
   //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

   //-------------------------
   //Attach depth buffer to FBO
   //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

   //-------------------------
   //Does the GPU support current FBO configuration?
   GLenum status;
   status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

   if( status == GL_FRAMEBUFFER_COMPLETE )
   {
		// AWESOME...
   }
   else
   {
	   // it didnt work!   
   }

   //-------------------------
}

RenderTexture::~RenderTexture()
{
	glDeleteRenderbuffers(1, &m_rbo_depth);
	glDeleteFramebuffers(1, &m_fbo);
}

unsigned int RenderTexture::GetFrameBufferHandle()
{
	return m_fbo;
}