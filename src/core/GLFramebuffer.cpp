#include <core/GLFramebuffer.hpp>

GLFramebuffer::GLFramebuffer() {
  glGenFramebuffers(1, &m_id);
}

GLFramebuffer::~GLFramebuffer() {
  glDeleteFramebuffers(1, &m_id);
}

void GLFramebuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}

void GLFramebuffer::Unbind() {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GLFramebuffer::AttachTexture(unsigned int width, unsigned int height, unsigned int internal_format, unsigned int format, unsigned int type, unsigned int attachment) {
  this->Bind();

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, type, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture, 0);

  this->Unbind();
}

void GLFramebuffer::AttachRenderbuffer(unsigned int width, unsigned int height, unsigned int internal_format, unsigned int attachment) {
  this->Bind();

  unsigned int renderbuffer;
  glGenRenderbuffers(1, &renderbuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);

  glRenderbufferStorage(GL_RENDERBUFFER, internal_format, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderbuffer);

  this->Unbind();
}

void GLFramebuffer::ResizeFramebuffer(unsigned int width, unsigned int height) {
  this->Bind();

  this->AttachTexture(width, height, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_COLOR_ATTACHMENT0);
  this->AttachRenderbuffer(width, height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);

  this->Unbind();
}

void GLFramebuffer::CheckStatus() {
  this->Bind();

  if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cout << "ERROR::FRAMEBUFFER::FRAMEBUFFER_NOT_COMPLETE\n";
  }

  this->Unbind();
}