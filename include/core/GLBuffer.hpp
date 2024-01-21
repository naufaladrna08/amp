#ifndef GL_BUFFER_HPP
#define GL_BUFFER_HPP
#include <glad/glad.h>

class GLBuffer {
  public: 
    GLBuffer();
    ~GLBuffer();

    void Bind();
    void BindVAO();
    void Unbind();

    void BufferData(unsigned int vertex_size, const void* vertex_data, unsigned int element_size, const void* element_data, unsigned int usage);

  private:
    unsigned int m_vao, m_ibo, m_vbo;
};

#endif 