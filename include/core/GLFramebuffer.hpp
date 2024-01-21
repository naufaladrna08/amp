#ifndef GLFRAMEBUFFER_HPP
#define GLFRAMEBUFFER_HPP

#include <glad/glad.h>
#include <iostream>

class GLFramebuffer {
  public:
    GLFramebuffer();
    ~GLFramebuffer();

    void Bind();
    void Unbind();

    void AttachTexture(unsigned int width, unsigned int height, unsigned int internal_format, unsigned int format, unsigned int type, unsigned int attachment);
    void AttachRenderbuffer(unsigned int width, unsigned int height, unsigned int internal_format, unsigned int attachment);

    void ResizeFramebuffer(unsigned int width, unsigned int height);

    void CheckStatus();

    unsigned int GetID() { return m_id; }

  private:
    unsigned int m_id;
    unsigned int m_width, m_height;
};

#endif